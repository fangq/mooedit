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

/* Fetch the per-window MooGdbWin from the window-plugin instance
 * attached to `window`.  Returns NULL if the plugin isn't loaded
 * for this window (shouldn't happen for actions that come from the
 * editor's menu chain, but keep the guard for safety). */
static MooGdbWin *
get_win_state (MooEditWindow *window)
{
    MooWinPlugin *wp = (MooWinPlugin *)
        moo_win_plugin_lookup (MOO_GDB_PLUGIN_ID, window);
    if (!wp) return NULL;
    return ((MooGdbWindowPlugin *) wp)->win;
}

#define DEFINE_FORWARD(action, fn) \
    static void action (MooEditWindow *w) { \
        MooGdbWin *gw = get_win_state (w); \
        if (gw) fn (gw); \
    }

DEFINE_FORWARD (debug_start_cb,     moo_gdb_win_start)
DEFINE_FORWARD (debug_continue_cb,  moo_gdb_win_continue)
DEFINE_FORWARD (debug_step_over_cb, moo_gdb_win_step_over)
DEFINE_FORWARD (debug_step_into_cb, moo_gdb_win_step_into)
DEFINE_FORWARD (debug_step_out_cb,  moo_gdb_win_step_out)
DEFINE_FORWARD (debug_pause_cb,     moo_gdb_win_pause)
DEFINE_FORWARD (debug_stop_cb,      moo_gdb_win_stop)

static void
debug_toggle_bp_cb (MooEditWindow *window)
{
    MooGdbWin *gw = get_win_state (window);
    if (!gw) return;
    MooEdit *doc = moo_edit_window_get_active_doc (window);
    if (!doc) return;
    char *file = moo_edit_get_filename (doc);
    if (!file) return;
    MooEditView *view = moo_edit_get_view (doc);
    GtkTextBuffer *buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark (buf, &iter,
        gtk_text_buffer_get_insert (buf));
    int line = gtk_text_iter_get_line (&iter) + 1;
    moo_gdb_win_toggle_bp (gw, file, line);
    g_free (file);
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

    moo_window_class_new_action (klass, "DebugToggleBreakpoint", NULL,
        "display-name",     _("Toggle Breakpoint"),
        "label",            _("Toggle _Breakpoint"),
        "tooltip",          _("Toggle a breakpoint at the current line"),
        "default-accel",    "F9",
        "closure-callback", debug_toggle_bp_cb,
        nullptr);

    moo_window_class_new_action (klass, "DebugStart", NULL,
        "display-name",     _("Start Debugging"),
        "label",            _("_Start Debugging"),
        "tooltip",          _("Run the current target under gdb"),
        "default-accel",    "F5",
        "closure-callback", debug_start_cb,
        nullptr);

    moo_window_class_new_action (klass, "DebugContinue", NULL,
        "display-name",     _("Continue"),
        "label",            _("_Continue"),
        "tooltip",          _("Continue execution until the next stop"),
        "default-accel",    "<shift>F5",
        "closure-callback", debug_continue_cb,
        nullptr);

    moo_window_class_new_action (klass, "DebugStepOver", NULL,
        "display-name",     _("Step Over"),
        "label",            _("Step _Over"),
        "tooltip",          _("Step over the next source line"),
        "default-accel",    "F10",
        "closure-callback", debug_step_over_cb,
        nullptr);

    moo_window_class_new_action (klass, "DebugStepInto", NULL,
        "display-name",     _("Step Into"),
        "label",            _("Step _Into"),
        "tooltip",          _("Step into the next source line"),
        "default-accel",    "F11",
        "closure-callback", debug_step_into_cb,
        nullptr);

    moo_window_class_new_action (klass, "DebugStepOut", NULL,
        "display-name",     _("Step Out"),
        "label",            _("Step Ou_t"),
        "tooltip",          _("Run until the current function returns"),
        "default-accel",    "<shift>F11",
        "closure-callback", debug_step_out_cb,
        nullptr);

    moo_window_class_new_action (klass, "DebugPause", NULL,
        "display-name",     _("Pause"),
        "label",            _("_Pause Execution"),
        "tooltip",          _("Send SIGINT to the running inferior "
                              "so it stops at its current line"),
        "default-accel",    "F6",
        "closure-callback", debug_pause_cb,
        nullptr);

    moo_window_class_new_action (klass, "DebugStop", NULL,
        "display-name",     _("Stop Debugging"),
        "label",            _("Sto_p Debugging"),
        "tooltip",          _("End the debugging session"),
        "closure-callback", debug_stop_cb,
        nullptr);

    if (xml)
    {
        plugin->ui_merge_id = moo_ui_xml_new_merge_id (xml);
        /* Slot everything under the existing "Edit" menu for now —
         * a dedicated "Debug" submenu in medit.xml lands in commit 8
         * alongside the project-config dialog. */
        const char *const items[] = {
            "DebugTestConnection",
            "DebugStart",
            "DebugContinue",
            "DebugStepOver",
            "DebugStepInto",
            "DebugStepOut",
            "DebugPause",
            "DebugStop",
            "DebugToggleBreakpoint",
        };
        for (int i = 0; i < (int) G_N_ELEMENTS (items); i++)
            moo_ui_xml_add_item (xml, plugin->ui_merge_id,
                                 "Editor/Menubar/Edit",
                                 items[i], items[i], -1);
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
