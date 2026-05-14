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

#define MARKDOWN_PLUGIN_ID "MarkdownPreview"

#ifdef MOO_BUILD_MARKDOWN

#include <gtk/gtk.h>
#include "mooapp/moohtml.h"

typedef struct {
    MooPlugin parent;
} MarkdownPlugin;

typedef struct {
    MooWinPlugin parent;
    MooPane     *pane;          /* registered side-pane (NULL until #2) */
    GtkWidget   *html_view;     /* MooHtml widget (set in #3) */
} MarkdownWindowPlugin;

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
    return TRUE;
}

static void
markdown_window_plugin_destroy (MarkdownWindowPlugin *plugin)
{
    MooEditWindow *window = MOO_WIN_PLUGIN (plugin)->window;

    /* The pane owns the scrolled window which owns the MooHtml; removing
     * it from the paned tears the whole subtree down via GTK ref drops. */
    moo_edit_window_remove_pane (window, MARKDOWN_PLUGIN_ID);
    plugin->pane      = NULL;
    plugin->html_view = NULL;
}

static gboolean
markdown_plugin_init (G_GNUC_UNUSED MarkdownPlugin *plugin)
{
    /* TODO commit #5: register MOO_EDIT_PREFS_MARKDOWN_PREVIEW bool key. */
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
