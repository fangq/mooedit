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

typedef struct {
    MooPlugin parent;
} MarkdownPlugin;

typedef struct {
    MooWinPlugin parent;
    MooPane     *pane;          /* registered side-pane (NULL until #2) */
    GtkWidget   *html_view;     /* MooHtml widget (set in #3) */
} MarkdownWindowPlugin;

static gboolean
markdown_window_plugin_create (G_GNUC_UNUSED MarkdownWindowPlugin *plugin)
{
    /* TODO commit #2: build a MooHtml inside a scrolled window, register
     * the pane via moo_edit_window_add_pane(..., MOO_PANE_POS_RIGHT). */
    return TRUE;
}

static void
markdown_window_plugin_destroy (G_GNUC_UNUSED MarkdownWindowPlugin *plugin)
{
    /* TODO commit #2: tear down the pane via moo_edit_window_remove_pane. */
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
