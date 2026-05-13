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
#endif

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
