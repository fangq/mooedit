/*
 *   moospellcheck.cpp
 *
 *   gspell-based spell-checker integration for MooEditView.
 *
 *   Architecture:
 *
 *   * GspellChecker is owned per GtkTextBuffer (one per document — medit
 *     supports multiple views sharing a single buffer, so the checker is
 *     installed on the buffer and the highlighting is enabled per view).
 *   * The view-level setup (squiggle highlight + right-click suggestion
 *     popover + language menu) is enabled by gspell_text_view_basic_setup().
 *     gspell attaches its signal handlers via weak refs, so view disposal
 *     cleans up automatically.
 *
 *   For commit #2 the checker is hard-coded to en_US and always enabled
 *   on attach.  Commit #3 wires this to MOO_EDIT_PREFS_SPELL_*.
 *
 *   Copyright (C) 2026 — part of medit.
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#include "config.h"
#include "mooedit/moospellcheck.h"

#ifdef MOO_BUILD_SPELL
#  include <gspell/gspell.h>

/* gspell's misspelled-word tag is anonymous (created with name=NULL) and
 * uses PANGO_UNDERLINE_SINGLE + a theme-derived underline-rgba.  On dark
 * themes the default colour is dim red, low contrast.  Override to a
 * brighter red for visibility.
 *
 * gtk_text_buffer_create_tag adds the tag to the table FIRST, then sets
 * its properties — so at tag-added time underline-rgba isn't set yet.
 * Defer the override to notify::underline-rgba; by then both `underline`
 * and `underline-rgba` are populated by gspell and we can identify the
 * tag and overwrite it.
 *
 * Also tried PANGO_UNDERLINE_ERROR for a wavy line: works in a vanilla
 * GtkTextView but renders straight in medit's MooTextView.  Root cause
 * not yet identified (Pango ≥ 1.50 + same theme/font); for now we keep
 * the straight line but make it bright red instead of dim.  Drawing a
 * cairo wave by hand in MooTextView's draw chain is a future option.
 */
static void
on_tag_underline_rgba_notify (GObject       *object,
                              G_GNUC_UNUSED GParamSpec *pspec,
                              gpointer       data)
{
    GtkTextTag      *tag   = GTK_TEXT_TAG (object);
    GtkTextTagTable *table = GTK_IS_TEXT_TAG_TABLE (data) ? GTK_TEXT_TAG_TABLE (data) : NULL;
    char            *name  = NULL;
    GdkRGBA          bright_red = { 1.0, 0.25, 0.25, 1.0 };

    g_object_get (tag, "name", &name, NULL);

    /* Anonymous tag with rgba set → gspell's misspelled-word tag.
     * Disconnect so our own override doesn't recurse. */
    if (name == NULL)
    {
        g_signal_handlers_disconnect_by_func (
            tag, (gpointer) on_tag_underline_rgba_notify, table);
        g_object_set (tag,
                      "underline-rgba", &bright_red,
                      NULL);

        /* Force max priority so any other underline-set tag in the same
         * range can't override us. */
        if (table != NULL)
        {
            int size = gtk_text_tag_table_get_size (table);
            if (size > 0)
                gtk_text_tag_set_priority (tag, size - 1);
        }
    }
    g_free (name);
}

static void
on_spell_tag_added (GtkTextTagTable *table,
                    GtkTextTag      *tag,
                    G_GNUC_UNUSED gpointer user_data)
{
    char *name = NULL;

    g_object_get (tag, "name", &name, NULL);

    /* Anonymous tag — most likely gspell's about-to-be-styled misspelled
     * tag.  Watch for underline-rgba to flip from unset to set.  Pass
     * the tag table so the notify handler can bump priority. */
    if (name == NULL)
    {
        g_signal_connect (tag, "notify::underline-rgba",
                          G_CALLBACK (on_tag_underline_rgba_notify), table);
    }
    g_free (name);
}

static void
install_spell_tag_hook (GtkTextBuffer *buffer)
{
    GtkTextTagTable *table = gtk_text_buffer_get_tag_table (buffer);
    if (g_object_get_data (G_OBJECT (table), "moo-spell-tag-hook"))
        return;
    g_signal_connect (table, "tag-added",
                      G_CALLBACK (on_spell_tag_added), NULL);
    g_object_set_data (G_OBJECT (table), "moo-spell-tag-hook",
                       GINT_TO_POINTER (1));
}
#endif /* MOO_BUILD_SPELL */

void
_moo_spell_check_attach (G_GNUC_UNUSED MooEditView *view)
{
#ifdef MOO_BUILD_SPELL
    GtkTextBuffer       *buffer;
    GspellTextBuffer    *gbuffer;
    GspellTextView      *gview;

    g_return_if_fail (MOO_IS_EDIT_VIEW (view));

    buffer  = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    gbuffer = gspell_text_buffer_get_from_gtk_text_buffer (buffer);

    /* Hook the buffer's tag table so when gspell adds its anonymous
     * misspelled-word tag we can override the underline-rgba (default
     * picks the theme's dim error colour which is hard to read on dark
     * themes).  Idempotent across attach() calls. */
    install_spell_tag_hook (buffer);

    /* Install the en_US checker on the buffer if no other view of the
     * same buffer has already done so.  Buffer owns the ref. */
    if (gspell_text_buffer_get_spell_checker (gbuffer) == NULL)
    {
        const GspellLanguage *lang;
        GspellChecker        *checker;

        lang = gspell_language_lookup ("en_US");
        /* lookup may return NULL if no en_US dict is installed; gspell
         * accepts NULL and defaults to the user's locale (we fall back
         * gracefully rather than refusing to attach). */
        checker = gspell_checker_new (lang);
        gspell_text_buffer_set_spell_checker (gbuffer, checker);
        g_object_unref (checker);
    }

    gview = gspell_text_view_get_from_gtk_text_view (GTK_TEXT_VIEW (view));
    /* basic_setup enables inline checking, the language menu, and the
     * "Add to dictionary"/"Ignore"/suggestion items in the popup. */
    gspell_text_view_basic_setup (gview);
#endif
}

void
_moo_spell_check_detach (G_GNUC_UNUSED MooEditView *view)
{
#ifdef MOO_BUILD_SPELL
    GspellTextView *gview;

    if (!MOO_IS_EDIT_VIEW (view))
        return;

    /* Disable just the inline highlight on this view; leave the
     * buffer-level checker in place so re-attach (e.g. after toggling
     * the pref) is cheap.  When the view is being disposed gspell's
     * own weak ref drops its per-view state automatically. */
    gview = gspell_text_view_get_from_gtk_text_view (GTK_TEXT_VIEW (view));
    if (gview != NULL)
        gspell_text_view_set_inline_spell_checking (gview, FALSE);
#endif
}

void
_moo_spell_check_apply_prefs (G_GNUC_UNUSED MooEditView *view)
{
#ifdef MOO_BUILD_SPELL
    /* TODO (commit #3): read MOO_EDIT_PREFS_SPELL_* and reconfigure
     * (toggle inline checking, switch language, etc.). */
#endif
}

/* ── Popup-menu integration ────────────────────────────────────────────────
 *
 * medit overrides right-click to show a custom popup built from its
 * UI XML ("Editor/Popup"), bypassing GtkTextView's default popup-creation
 * — so the "populate-popup" signal is never emitted and gspell's normal
 * hook can't add suggestion items.  Instead we build the spell-check
 * submenu directly using the public gspell checker API and append it.
 */

#ifdef MOO_BUILD_SPELL

typedef struct {
    /* GspellChecker — owned by buffer, weak-ref'd here for safety */
    GspellChecker *checker;
    /* word and its range — copied so handlers survive the popup tear-down */
    GtkTextBuffer *buffer;
    GtkTextMark   *word_start;
    GtkTextMark   *word_end;
    char          *word;
} SpellPopupCtx;

static void
spell_popup_ctx_free (gpointer data, G_GNUC_UNUSED GClosure *closure)
{
    SpellPopupCtx *ctx = (SpellPopupCtx *) data;
    if (ctx->word_start)
        gtk_text_buffer_delete_mark (ctx->buffer, ctx->word_start);
    if (ctx->word_end)
        gtk_text_buffer_delete_mark (ctx->buffer, ctx->word_end);
    g_free (ctx->word);
    g_slice_free (SpellPopupCtx, ctx);
}

static void
on_replace_with_suggestion (GtkMenuItem *item, gpointer data)
{
    SpellPopupCtx *ctx = (SpellPopupCtx *) data;
    const char    *replacement;
    GtkTextIter    start, end;

    replacement = (const char *) g_object_get_data (G_OBJECT (item),
                                                    "moo-spell-replacement");
    if (!replacement || !ctx->word_start || !ctx->word_end)
        return;

    gtk_text_buffer_get_iter_at_mark (ctx->buffer, &start, ctx->word_start);
    gtk_text_buffer_get_iter_at_mark (ctx->buffer, &end,   ctx->word_end);

    gtk_text_buffer_begin_user_action (ctx->buffer);
    gtk_text_buffer_delete (ctx->buffer, &start, &end);
    gtk_text_buffer_insert (ctx->buffer, &start, replacement, -1);
    gtk_text_buffer_end_user_action (ctx->buffer);

    /* Tell gspell we corrected it so its session stats stay sane. */
    if (ctx->checker && ctx->word)
        gspell_checker_set_correction (ctx->checker,
                                       ctx->word, -1,
                                       replacement, -1);
}

static void
on_add_to_dictionary (G_GNUC_UNUSED GtkMenuItem *item, gpointer data)
{
    SpellPopupCtx *ctx = (SpellPopupCtx *) data;
    if (ctx->checker && ctx->word)
        gspell_checker_add_word_to_personal (ctx->checker, ctx->word, -1);
}

static void
on_ignore_word (G_GNUC_UNUSED GtkMenuItem *item, gpointer data)
{
    SpellPopupCtx *ctx = (SpellPopupCtx *) data;
    if (ctx->checker && ctx->word)
        gspell_checker_add_word_to_session (ctx->checker, ctx->word, -1);
}

/* Standard word-boundary scan: alphanumeric + apostrophes + connecting
 * punctuation grow the word; everything else terminates it.  Returns
 * TRUE if a non-empty word was found around `iter`. */
static gboolean
extract_word_at_iter (GtkTextBuffer *buffer,
                      const GtkTextIter *iter,
                      GtkTextIter *out_start,
                      GtkTextIter *out_end,
                      char **out_word)
{
    GtkTextIter start = *iter;
    GtkTextIter end   = *iter;
    GtkTextIter probe;

    /* Walk backwards while preceding char is part of a word */
    probe = start;
    while (gtk_text_iter_backward_char (&probe))
    {
        gunichar c = gtk_text_iter_get_char (&probe);
        if (!g_unichar_isalpha (c) && c != '\'' && c != 0x2019 /* ’ */)
            break;
        start = probe;
    }

    /* Walk forwards while current char is part of a word */
    while (!gtk_text_iter_is_end (&end))
    {
        gunichar c = gtk_text_iter_get_char (&end);
        if (!g_unichar_isalpha (c) && c != '\'' && c != 0x2019)
            break;
        gtk_text_iter_forward_char (&end);
    }

    if (gtk_text_iter_equal (&start, &end))
        return FALSE;

    *out_start = start;
    *out_end   = end;
    *out_word  = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
    return TRUE;
}

#endif /* MOO_BUILD_SPELL */

void
_moo_spell_check_populate_popup (G_GNUC_UNUSED MooEditView *view,
                                 G_GNUC_UNUSED GtkMenu     *menu,
                                 G_GNUC_UNUSED int          widget_x,
                                 G_GNUC_UNUSED int          widget_y)
{
#ifdef MOO_BUILD_SPELL
    GtkTextView      *tv;
    GtkTextBuffer    *buffer;
    GspellTextBuffer *gbuffer;
    GspellChecker    *checker;
    GtkTextIter       click_iter, word_start, word_end;
    char             *word = NULL;
    GSList           *suggestions, *l;
    int               bx, by;
    GtkWidget        *spell_sep, *sub, *sub_item;
    SpellPopupCtx    *ctx;
    int               i;

    g_return_if_fail (MOO_IS_EDIT_VIEW (view));
    g_return_if_fail (GTK_IS_MENU (menu));

    tv      = GTK_TEXT_VIEW (view);
    buffer  = gtk_text_view_get_buffer (tv);
    gbuffer = gspell_text_buffer_get_from_gtk_text_buffer (buffer);
    checker = gspell_text_buffer_get_spell_checker (gbuffer);
    if (checker == NULL)
        return;

    /* Resolve click position → buffer iter.  Negative coords means
     * "use the cursor" (keyboard-triggered popup). */
    if (widget_x < 0 || widget_y < 0)
    {
        gtk_text_buffer_get_iter_at_mark (buffer, &click_iter,
                                          gtk_text_buffer_get_insert (buffer));
    }
    else
    {
        gtk_text_view_window_to_buffer_coords (tv, GTK_TEXT_WINDOW_WIDGET,
                                               widget_x, widget_y, &bx, &by);
        gtk_text_view_get_iter_at_location (tv, &click_iter, bx, by);
    }

    if (!extract_word_at_iter (buffer, &click_iter, &word_start, &word_end, &word))
        return;

    /* Word found.  Spell-check it; if it's already correct, nothing to add. */
    if (gspell_checker_check_word (checker, word, -1, NULL))
    {
        g_free (word);
        return;
    }

    /* Build the shared context (one copy of the marks / word string is
     * shared across all menu-item handlers via closure-notify cleanup). */
    ctx = g_slice_new0 (SpellPopupCtx);
    ctx->checker    = checker;
    ctx->buffer     = buffer;
    ctx->word_start = gtk_text_buffer_create_mark (buffer, NULL, &word_start, TRUE);
    ctx->word_end   = gtk_text_buffer_create_mark (buffer, NULL, &word_end,   FALSE);
    ctx->word       = word;   /* takes ownership */

    /* Prepend (so the spell entries appear at the TOP of medit's
     * already-long custom popup, where the user can actually see them).
     * Order ends up: [Spelling ▸] [separator] [...medit's items...]. */
    spell_sep = gtk_separator_menu_item_new ();
    gtk_widget_show (spell_sep);
    gtk_menu_shell_prepend (GTK_MENU_SHELL (menu), spell_sep);

    sub_item = gtk_menu_item_new_with_label ("Spelling");
    gtk_widget_show (sub_item);
    gtk_menu_shell_prepend (GTK_MENU_SHELL (menu), sub_item);
    sub = gtk_menu_new ();
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (sub_item), sub);

    suggestions = gspell_checker_get_suggestions (checker, word, -1);
    if (suggestions == NULL)
    {
        GtkWidget *none = gtk_menu_item_new_with_label ("(no suggestions)");
        gtk_widget_set_sensitive (none, FALSE);
        gtk_widget_show (none);
        gtk_menu_shell_append (GTK_MENU_SHELL (sub), none);
    }
    else
    {
        /* Cap to 10 entries so the popup stays usable. */
        for (l = suggestions, i = 0; l != NULL && i < 10; l = l->next, i++)
        {
            char      *suggestion = (char *) l->data;
            GtkWidget *mi         = gtk_menu_item_new_with_label (suggestion);

            g_object_set_data_full (G_OBJECT (mi), "moo-spell-replacement",
                                    g_strdup (suggestion), g_free);
            g_signal_connect_data (mi, "activate",
                                   G_CALLBACK (on_replace_with_suggestion),
                                   ctx, NULL, (GConnectFlags) 0);
            gtk_widget_show (mi);
            gtk_menu_shell_append (GTK_MENU_SHELL (sub), mi);
        }
    }
    g_slist_free_full (suggestions, g_free);

    /* Separator + actions. */
    {
        GtkWidget *sep  = gtk_separator_menu_item_new ();
        GtkWidget *add  = gtk_menu_item_new_with_label ("Add to Dictionary");
        GtkWidget *ign  = gtk_menu_item_new_with_label ("Ignore All");

        gtk_widget_show (sep);
        gtk_widget_show (add);
        gtk_widget_show (ign);
        gtk_menu_shell_append (GTK_MENU_SHELL (sub), sep);
        gtk_menu_shell_append (GTK_MENU_SHELL (sub), add);
        gtk_menu_shell_append (GTK_MENU_SHELL (sub), ign);

        g_signal_connect_data (add, "activate",
                               G_CALLBACK (on_add_to_dictionary),
                               ctx, NULL, (GConnectFlags) 0);
        /* Free the ctx exactly once via the last menu-item's closure. */
        g_signal_connect_data (ign, "activate",
                               G_CALLBACK (on_ignore_word),
                               ctx, spell_popup_ctx_free, (GConnectFlags) 0);
    }
#endif /* MOO_BUILD_SPELL */
}
