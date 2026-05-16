/*
 *   moogdb.cpp
 *
 *   Plugin entry point for the in-editor GDB-based debugger.
 *
 *   Phase 1 (this commit) only registers a "Debug → Test GDB
 *   connection" menu item that spawns a transient gdb subprocess
 *   and runs `-gdb-version`.  The next commits layer on:
 *
 *     #2  target launch + run / continue
 *     #3  breakpoint margin (-break-insert / -break-delete)
 *     #4  *stopped event + current-line marker
 *     #5  step over / into / out + toolbar
 *     #6  pause / interrupt + error states
 *     #7  console output panel
 *     #8  per-project config dialog
 *
 *   When MOO_BUILD_GDB is not defined the whole file compiles to a
 *   no-op _moo_gdb_plugin_init() so plugin-builtin.cpp can call it
 *   unconditionally.
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
#include "mooedit/mooeditor.h"
#include "mooutils/moostock.h"
#include "mooutils/mooi18n.h"
#include "mooutils/moouixml.h"

#define MOO_GDB_PLUGIN_ID "MooGdb"

#ifdef MOO_BUILD_GDB

#include <gtk/gtk.h>
#include "plugins/moogdb/moogdb-ui.h"

typedef struct {
    MooPlugin parent;
    guint     ui_merge_id;
} MooGdbPlugin;

typedef struct {
    MooWinPlugin parent;
    MooGdbWin   *win;     /* per-window breakpoint state + session */
} MooGdbWindowPlugin;

/* Menu callback wired to "DebugTestConnection".  Forwarded straight
 * to the UI helper which owns the lifecycle of the transient
 * MooGdbSession. */
static void
debug_test_connection_cb (MooEditWindow *window)
{
    moo_gdb_ui_test_connection (window);
}

static gboolean
moo_gdb_window_plugin_create (MooGdbWindowPlugin *plugin)
{
    MooEditWindow *window = MOO_WIN_PLUGIN (plugin)->window;
    plugin->win = moo_gdb_win_new (window);
    return TRUE;
}

static void
moo_gdb_window_plugin_destroy (MooGdbWindowPlugin *plugin)
{
    moo_gdb_win_free (plugin->win);
    plugin->win = NULL;
}

static gboolean
moo_gdb_plugin_init (MooGdbPlugin *plugin)
{
    MooWindowClass *klass  = (MooWindowClass *) g_type_class_ref (
        MOO_TYPE_EDIT_WINDOW);
    MooEditor      *editor = moo_editor_instance ();
    MooUiXml       *xml    = moo_editor_get_ui_xml (editor);

    g_return_val_if_fail (klass != NULL, FALSE);

    moo_window_class_new_action (klass, "DebugTestConnection", NULL,
        "display-name",     _("Test GDB Connection"),
        "label",            _("_Test GDB Connection"),
        "tooltip",          _("Spawn gdb and run -gdb-version to "
                              "verify the debugger wiring is working"),
        "closure-callback", debug_test_connection_cb,
        nullptr);

    if (xml)
    {
        plugin->ui_merge_id = moo_ui_xml_new_merge_id (xml);
        /* Slot the menu item under the existing "Edit" menu for now;
         * a dedicated "Debug" submenu will be added once Phase 2
         * brings the breakpoint / step actions that justify it. */
        moo_ui_xml_add_item (xml, plugin->ui_merge_id,
                             "Editor/Menubar/Edit",
                             "DebugTestConnection",
                             "DebugTestConnection", -1);
    }

    g_type_class_unref (klass);
    return TRUE;
}

static void
moo_gdb_plugin_deinit (MooGdbPlugin *plugin)
{
    MooEditor *editor = moo_editor_instance ();
    MooUiXml  *xml    = moo_editor_get_ui_xml (editor);
    if (xml && plugin->ui_merge_id)
        moo_ui_xml_remove_ui (xml, plugin->ui_merge_id);
}

MOO_PLUGIN_DEFINE_INFO (moo_gdb,
                        "GDB Debugger",
                        "C/C++ source-level debugger via GDB/MI",
                        "medit project",
                        MOO_VERSION)

MOO_WIN_PLUGIN_DEFINE (MooGdb, moo_gdb)

MOO_PLUGIN_DEFINE (MooGdb, moo_gdb,
                   NULL, NULL, NULL, NULL, NULL,
                   moo_gdb_window_plugin_get_type (),
                   0)

#endif /* MOO_BUILD_GDB */

extern "C" gboolean
_moo_gdb_plugin_init (void)
{
#ifdef MOO_BUILD_GDB
    MooPluginParams params = { TRUE, TRUE };
    return moo_plugin_register (MOO_GDB_PLUGIN_ID,
                                moo_gdb_plugin_get_type (),
                                &moo_gdb_plugin_info,
                                &params);
#else
    return FALSE;
#endif
}
