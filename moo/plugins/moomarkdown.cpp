/*
 *   moomarkdown.cpp
 *
 *   In-editor Markdown preview pane.  Skeleton commit (#1 of the
 *   markdown-preview series).  Subsequent commits fill in:
 *     #2  pane attach/detach in the window-plugin create/destroy hooks
 *     #3  MD → HTML conversion via md4c + load into a MooHtml widget
 *     #4  debounced live preview on buffer changes
 *     #5  View-menu toggle + persistent pref
 *     #6  CI workflow updates + GFM extensions enabled
 *
 *   When MOO_BUILD_MARKDOWN is not defined the whole file compiles to a
 *   no-op _moo_markdown_plugin_init() so plugin-builtin.cpp can call it
 *   unconditionally.
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
#include "mooedit/mooplugin.h"
#include "mooedit/mooplugin-macro.h"
#include "mooedit/mooeditwindow.h"
#include "mooedit/mooedit.h"
#include "mooutils/moostock.h"
#include "mooutils/mooi18n.h"
#include "mooutils/mooprefs.h"

#define MARKDOWN_PLUGIN_ID "MarkdownPreview"

/* Persistent pref controlling whether the preview pane should be shown
 * the moment a window opens.  TRUE by default (the pane is small and
 * the renderer no-ops cheaply for non-Markdown buffers); set to FALSE
 * for users who'd rather have it stay hidden until they trigger it via
 * View → Panes → Markdown Preview.  The pane is still registered in
 * the PanesMenu regardless, so per-window show/hide is always one menu
 * click away. */
#define MARKDOWN_SHOW_PREF "Plugins/MarkdownPreview/show"

#ifdef MOO_BUILD_MARKDOWN

#include <gtk/gtk.h>
#include <md4c-html.h>
#include "mooapp/moohtml.h"
#include "mooedit/mooeditview.h"

typedef struct {
    MooPlugin parent;
} MarkdownPlugin;

typedef struct {
    MooWinPlugin parent;
    MooPane     *pane;          /* registered side-pane */
    GtkWidget   *html_view;     /* MooHtml widget */

    /* Live-preview state — tracked so we can disconnect on doc switch
     * and on plugin teardown without dangling-handler crashes. */
    gulong       notify_active_doc_id;  /* on the MooEditWindow */
    GtkTextBuffer *current_buffer;      /* whichever buffer "changed" is connected to */
    gulong       buffer_changed_id;     /* handler id on current_buffer */
    guint        render_timeout_id;     /* g_timeout source for debounce */
} MarkdownWindowPlugin;

/* How long the user has to be idle (no edits) before we re-render the
 * preview.  200 ms feels live without slamming md4c on every keystroke.
 * Cheap to tune later if users want lower-latency feedback. */
#define MARKDOWN_DEBOUNCE_MS 200

/* md4c invokes this for every chunk of generated HTML.  Append into
 * the GString the caller passed via userdata.  Inlined for clarity —
 * the callback is hot but the work is tiny. */
static void
md4c_output_cb (const MD_CHAR *text, MD_SIZE size, void *userdata)
{
    g_string_append_len ((GString *) userdata, text, size);
}

/* Markdown-specific tag styling — applied after every MooHtml load so
 * the Markdown preview pane has its own visual identity (theme-aware
 * link colour, subtle code/pre backgrounds, slightly coloured headings)
 * without touching how the About dialog renders.
 *
 * MooHtml's tags are mostly anonymous; we identify each kind by the
 * narrow predicates added to moohtml.h.  Theme awareness reuses the
 * same luma-based picker we already use for spell-check underlines. */
typedef struct {
    GdkRGBA link;
    GdkRGBA code_bg;       /* background for inline <code> and <pre>   */
    GdkRGBA code_fg;       /* foreground for code (a touch dimmer)     */
    GdkRGBA heading_fg;    /* shared colour for H1/H2 (others: theme)  */
    GdkRGBA hr_fg;
    GdkRGBA quote_bg;      /* soft background for <blockquote>         */
    GdkRGBA quote_fg;      /* dimmer text inside <blockquote>          */
    GdkRGBA table_bg;      /* soft background for tables               */
} MarkdownPalette;

static void
markdown_pick_palette (GtkWidget *html_view, MarkdownPalette *p)
{
    GtkStyleContext *ctx = gtk_widget_get_style_context (html_view);
    GdkRGBA bg = { 1.0, 1.0, 1.0, 1.0 };
    double  luma;

    gtk_style_context_save (ctx);
    gtk_style_context_add_class (ctx, GTK_STYLE_CLASS_VIEW);
    G_GNUC_BEGIN_IGNORE_DEPRECATIONS
    gtk_style_context_get_background_color (ctx,
        gtk_style_context_get_state (ctx), &bg);
    G_GNUC_END_IGNORE_DEPRECATIONS
    gtk_style_context_restore (ctx);

    luma = 0.299 * bg.red + 0.587 * bg.green + 0.114 * bg.blue;
    if (luma <= 0.5)
    {
        /* Dark theme: punchy accents on a near-black background. */
        gdk_rgba_parse (&p->link,       "#7eb6ff");   /* light blue */
        gdk_rgba_parse (&p->code_bg,    "#2b2b2b");   /* slightly lighter than bg */
        gdk_rgba_parse (&p->code_fg,    "#e6e6e6");
        gdk_rgba_parse (&p->heading_fg, "#9cdcfe");   /* cyan-blue (VS-Code-ish) */
        gdk_rgba_parse (&p->hr_fg,      "#444444");
        gdk_rgba_parse (&p->quote_bg,   "#1e2227");   /* faint panel tint */
        gdk_rgba_parse (&p->quote_fg,   "#a8b1bd");   /* muted grey-blue */
        gdk_rgba_parse (&p->table_bg,   "#1e2227");   /* same as quote */
    }
    else
    {
        /* Light theme: deeper colours so they read on white. */
        gdk_rgba_parse (&p->link,       "#1a73e8");   /* Google-style blue */
        gdk_rgba_parse (&p->code_bg,    "#f5f5f5");   /* very light grey */
        gdk_rgba_parse (&p->code_fg,    "#222222");
        gdk_rgba_parse (&p->heading_fg, "#1a1a1a");   /* near-black, lets size carry */
        gdk_rgba_parse (&p->hr_fg,      "#cccccc");
        gdk_rgba_parse (&p->quote_bg,   "#f6f8fa");   /* GitHub-ish faint panel */
        gdk_rgba_parse (&p->quote_fg,   "#586069");   /* GitHub-ish muted text */
        gdk_rgba_parse (&p->table_bg,   "#fafbfc");   /* even softer than quote */
    }
}

/* Iterate every tag in the preview buffer's table and override its
 * properties based on its element kind.  Idempotent — every render
 * call rebuilds the buffer, so this just paints over MooHtml's
 * fresh tags.  Called from markdown_render() right after the load. */
static void
markdown_restyle_tags (GtkWidget *html_view)
{
    GtkTextBuffer   *buf   = gtk_text_view_get_buffer (GTK_TEXT_VIEW (html_view));
    GtkTextTagTable *table = gtk_text_buffer_get_tag_table (buf);
    MarkdownPalette  pal;

    markdown_pick_palette (html_view, &pal);

    gtk_text_tag_table_foreach (
        table,
        [](GtkTextTag *tag, gpointer data) {
            const MarkdownPalette *p = (const MarkdownPalette *) data;
            int h;

            if (_moo_html_tag_is_link (tag))
            {
                /* High-contrast underlined link — matches the GitHub
                 * preview, where every link gets a single line below. */
                g_object_set (tag,
                              "foreground-rgba", &p->link,
                              "underline",       PANGO_UNDERLINE_SINGLE,
                              NULL);
            }

            if ((h = _moo_html_tag_get_heading (tag)) > 0)
            {
                /* Lift H1/H2 with a coloured tint; H3+ rely on size +
                 * weight alone to avoid a rainbow effect. */
                if (h <= 2)
                    g_object_set (tag, "foreground-rgba", &p->heading_fg, NULL);
            }

            if (_moo_html_tag_is_pre (tag))
            {
                /* <pre> block — tight line-to-line spacing inside the
                 * code block (pixels-above/below-lines apply to *every*
                 * line, so anything > a couple of px adds a visible gap
                 * between consecutive code lines).  The block-edge
                 * padding above and below the whole block comes from
                 * the blank lines around <pre> in the parsed HTML. */
                g_object_set (tag,
                              "paragraph-background-rgba", &p->code_bg,
                              "foreground-rgba",           &p->code_fg,
                              "left-margin",                6,
                              "right-margin",               6,
                              "pixels-above-lines",         1,
                              "pixels-below-lines",         1,
                              "pixels-inside-wrap",         0,
                              "scale",                      0.92,
                              NULL);
            }
            else if (_moo_html_tag_is_table (tag))
            {
                /* Tables render as column-aligned monospace text with a
                 * thin under-header rule; the faint background plus a
                 * left indent make the block read as a tabular unit. */
                g_object_set (tag,
                              "paragraph-background-rgba", &p->table_bg,
                              "left-margin",               16,
                              "right-margin",              16,
                              "scale",                     0.92,
                              "pixels-above-lines",        2,
                              "pixels-below-lines",        2,
                              NULL);
            }
            else if (_moo_html_tag_is_monospace (tag))
            {
                /* Inline <code> — span-background only (not whole para). */
                g_object_set (tag,
                              "background-rgba", &p->code_bg,
                              "foreground-rgba", &p->code_fg,
                              "scale",           0.92,
                              NULL);
            }

            if (_moo_html_tag_is_blockquote (tag))
            {
                /* GitHub-style: indented, italic, muted text on a faint
                 * paragraph background.  left-margin already came from
                 * the MOO_HTML_LEFT_MARGIN flag in the tag's attr. */
                g_object_set (tag,
                              "paragraph-background-rgba", &p->quote_bg,
                              "foreground-rgba",           &p->quote_fg,
                              "style",                     PANGO_STYLE_ITALIC,
                              "pixels-above-lines",        4,
                              "pixels-below-lines",        4,
                              NULL);
            }
        },
        &pal);
}

/* Convert the active document's buffer text to HTML via md4c and load
 * it into the MooHtml widget.  No-op when there's no active doc or
 * the pane was never built.  Caller can pass the active view via
 * `view_hint` to avoid re-querying it.  Cheap enough to call on every
 * buffer change once we add debouncing in commit #4. */
static void
markdown_render (MarkdownWindowPlugin *plugin, MooEditView *view_hint)
{
    MooEditWindow *window;
    MooEditView   *view;
    GtkTextBuffer *buffer;
    GtkTextIter    start, end;
    char          *md;
    GString       *html;
    int            rc;

    if (plugin == NULL || plugin->html_view == NULL)
        return;

    window = MOO_WIN_PLUGIN (plugin)->window;
    view   = view_hint ? view_hint : moo_edit_window_get_active_view (window);
    if (view == NULL)
        return;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    gtk_text_buffer_get_bounds (buffer, &start, &end);
    md = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
    if (md == NULL)
        return;

    /* md4c writes only the <body> contents; wrap with an HTML envelope
     * so MooHtml's libxml2-based parser starts in the right state.
     * MD_DIALECT_GITHUB enables tables, strikethrough, task-lists, and
     * autolinks — the de-facto GFM feature set users expect today. */
    html = g_string_sized_new (strlen (md) * 2 + 64);
    g_string_append (html, "<html><body>");
    rc = md_html (md, (MD_SIZE) strlen (md),
                  md4c_output_cb, html,
                  MD_DIALECT_GITHUB, 0);
    g_string_append (html, "</body></html>");

    if (rc == 0)
    {
        _moo_html_load_memory (GTK_TEXT_VIEW (plugin->html_view),
                               html->str, html->len, NULL, "UTF-8");
        /* Override MooHtml's defaults with the Markdown-preview palette
         * (theme-aware links, code backgrounds, heading tints).  Cheap
         * — fewer than a couple dozen tags per render. */
        markdown_restyle_tags (plugin->html_view);
    }

    g_string_free (html, TRUE);
    g_free (md);
}

/* Debounce-timer callback.  Render once and clear the slot so the next
 * "buffer changed" can arm a fresh timer. */
static gboolean
markdown_render_timeout (gpointer data)
{
    MarkdownWindowPlugin *plugin = (MarkdownWindowPlugin *) data;
    plugin->render_timeout_id = 0;
    markdown_render (plugin, NULL);
    return G_SOURCE_REMOVE;
}

/* GtkTextBuffer "changed" signal handler.  Reset the debounce timer
 * so multiple rapid edits coalesce into a single render once the user
 * pauses. */
static void
markdown_on_buffer_changed (G_GNUC_UNUSED GtkTextBuffer *buffer,
                            gpointer                     data)
{
    MarkdownWindowPlugin *plugin = (MarkdownWindowPlugin *) data;
    if (plugin->render_timeout_id != 0)
        g_source_remove (plugin->render_timeout_id);
    plugin->render_timeout_id =
        g_timeout_add (MARKDOWN_DEBOUNCE_MS, markdown_render_timeout, plugin);
}

/* (Re-)wire the "changed" handler onto whichever buffer is current for
 * the window's active doc.  Tolerates NULL doc (just disconnects). */
static void
markdown_rewire_buffer_signal (MarkdownWindowPlugin *plugin)
{
    MooEditWindow *window = MOO_WIN_PLUGIN (plugin)->window;
    MooEditView   *view;
    GtkTextBuffer *buffer = NULL;

    view = moo_edit_window_get_active_view (window);
    if (view != NULL)
        buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    if (buffer == plugin->current_buffer)
        return;     /* nothing to do — already wired to this buffer */

    if (plugin->current_buffer != NULL && plugin->buffer_changed_id != 0)
    {
        g_signal_handler_disconnect (plugin->current_buffer,
                                     plugin->buffer_changed_id);
        plugin->buffer_changed_id = 0;
    }
    plugin->current_buffer = buffer;
    if (buffer != NULL)
        plugin->buffer_changed_id = g_signal_connect (
            buffer, "changed",
            G_CALLBACK (markdown_on_buffer_changed), plugin);
}

/* MooEditWindow "notify::active-doc" handler.  Re-wire to the new doc's
 * buffer and trigger an immediate render (no debounce — switching docs
 * isn't typing). */
static void
markdown_on_active_doc_notify (G_GNUC_UNUSED GObject *window,
                                G_GNUC_UNUSED GParamSpec *pspec,
                                gpointer data)
{
    MarkdownWindowPlugin *plugin = (MarkdownWindowPlugin *) data;
    markdown_rewire_buffer_signal (plugin);
    markdown_render (plugin, NULL);
}

static gboolean
markdown_window_plugin_create (MarkdownWindowPlugin *plugin)
{
    MooEditWindow *window = MOO_WIN_PLUGIN (plugin)->window;
    GtkWidget     *scroll;
    GtkWidget     *html;
    MooPaneLabel  *label;

    /* MooHtml is a GtkTextView subclass that renders simplified HTML
     * into a GtkTextBuffer using tags — perfect for a no-WebKit preview.
     * Wrap in a GtkScrolledWindow so long documents are scrollable. */
    html   = (GtkWidget *) g_object_new (MOO_TYPE_HTML, NULL);
    gtk_text_view_set_editable      (GTK_TEXT_VIEW (html), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (html), FALSE);
    gtk_text_view_set_wrap_mode      (GTK_TEXT_VIEW (html), GTK_WRAP_WORD_CHAR);
    gtk_widget_set_size_request (html, 360, -1);   /* sensible default width */

    /* Bump the base font 1.2× so the preview reads at a comfortable
     * size next to the source editor.  Applied via CSS on this widget
     * only so other GtkTextViews in the window stay unaffected.  Per-
     * tag scale overrides (headings, code) compound on top of this. */
    {
        static GtkCssProvider *fp = NULL;
        if (fp == NULL)
        {
            fp = gtk_css_provider_new ();
            gtk_css_provider_load_from_data (
                fp, "textview { font-size: 120%; }", -1, NULL);
        }
        gtk_style_context_add_provider (
            gtk_widget_get_style_context (html),
            GTK_STYLE_PROVIDER (fp),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

    /* Open up line spacing — MooHtml's default is tight because the tags
     * it creates per-element don't set any paragraph margins.  Adding view-
     * level defaults gives every paragraph a few pixels of breathing room
     * (overridable per-tag, which is what headings and <pre> already do). */
    gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (html), 3);
    gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW (html), 3);
    gtk_text_view_set_pixels_inside_wrap (GTK_TEXT_VIEW (html), 2);
    gtk_text_view_set_left_margin   (GTK_TEXT_VIEW (html), 10);
    gtk_text_view_set_right_margin  (GTK_TEXT_VIEW (html), 10);
    gtk_text_view_set_top_margin    (GTK_TEXT_VIEW (html), 8);
    gtk_text_view_set_bottom_margin (GTK_TEXT_VIEW (html), 8);

    scroll = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroll),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scroll),
                                         GTK_SHADOW_IN);
    gtk_container_add (GTK_CONTAINER (scroll), html);
    gtk_widget_show_all (scroll);

    /* The icon-name field is the GTK stock icon shown next to the pane
     * label; "text-x-generic" is the freedesktop icon for plain text
     * which renders fine on every theme (Adwaita / Default / etc.). */
    label = moo_pane_label_new ("text-x-generic", NULL,
                                _("Markdown Preview"),
                                _("Markdown Preview"));
    plugin->pane = moo_edit_window_add_pane (window,
                                             MARKDOWN_PLUGIN_ID,
                                             scroll, label,
                                             MOO_PANE_POS_RIGHT);
    moo_pane_label_free (label);

    plugin->html_view = html;

    /* Honour the user's "show on open" preference.  When FALSE the
     * pane is still registered (so it appears in View → Panes →
     * Markdown Preview), it just doesn't auto-open. */
    if (moo_prefs_get_bool (MARKDOWN_SHOW_PREF))
        moo_edit_window_show_pane (window, MARKDOWN_PLUGIN_ID);

    /* Wire live-preview signals:
     *   * notify::active-doc on the window → re-target our buffer
     *     "changed" handler when the user switches tabs.
     *   * "changed" on the active doc's buffer → schedule a debounced
     *     re-render.
     * Both are torn down in markdown_window_plugin_destroy. */
    plugin->notify_active_doc_id = g_signal_connect (
        window, "notify::active-doc",
        G_CALLBACK (markdown_on_active_doc_notify), plugin);
    markdown_rewire_buffer_signal (plugin);

    /* Initial render of whatever's currently the active document. */
    markdown_render (plugin, NULL);
    return TRUE;
}

static void
markdown_window_plugin_destroy (MarkdownWindowPlugin *plugin)
{
    MooEditWindow *window = MOO_WIN_PLUGIN (plugin)->window;

    /* Live-preview teardown: cancel pending render, drop signal handlers. */
    if (plugin->render_timeout_id != 0)
    {
        g_source_remove (plugin->render_timeout_id);
        plugin->render_timeout_id = 0;
    }
    if (plugin->current_buffer != NULL && plugin->buffer_changed_id != 0)
    {
        g_signal_handler_disconnect (plugin->current_buffer,
                                     plugin->buffer_changed_id);
        plugin->buffer_changed_id = 0;
    }
    plugin->current_buffer = NULL;
    if (plugin->notify_active_doc_id != 0)
    {
        g_signal_handler_disconnect (window, plugin->notify_active_doc_id);
        plugin->notify_active_doc_id = 0;
    }

    /* The pane owns the scrolled window which owns the MooHtml; removing
     * it from the paned tears the whole subtree down via GTK ref drops. */
    moo_edit_window_remove_pane (window, MARKDOWN_PLUGIN_ID);
    plugin->pane      = NULL;
    plugin->html_view = NULL;
}

static gboolean
markdown_plugin_init (G_GNUC_UNUSED MarkdownPlugin *plugin)
{
    moo_prefs_new_key_bool (MARKDOWN_SHOW_PREF, TRUE);
    return TRUE;
}

static void
markdown_plugin_deinit (G_GNUC_UNUSED MarkdownPlugin *plugin)
{
}

MOO_PLUGIN_DEFINE_INFO (markdown,
                        "Markdown Preview",
                        "Live Markdown preview side pane",
                        "medit project",
                        MOO_VERSION)

MOO_WIN_PLUGIN_DEFINE (Markdown, markdown)

MOO_PLUGIN_DEFINE (Markdown, markdown,
                   NULL, NULL, NULL, NULL, NULL,
                   markdown_window_plugin_get_type (),
                   0)

#endif /* MOO_BUILD_MARKDOWN */

extern "C" gboolean
_moo_markdown_plugin_init (void)
{
#ifdef MOO_BUILD_MARKDOWN
    MooPluginParams params = { TRUE, TRUE };
    return moo_plugin_register (MARKDOWN_PLUGIN_ID,
                                markdown_plugin_get_type (),
                                &markdown_plugin_info,
                                &params);
#else
    return FALSE;
#endif
}
