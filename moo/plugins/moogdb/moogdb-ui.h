/*
 *   moogdb-ui.h
 *
 *   UI plumbing for the GDB plugin: menu actions, toolbar (Phase 2),
 *   breakpoint margin (Phase 2), current-line marker (Phase 2).
 *
 *   Phase 1 only exposes the "Test GDB connection" menu action.
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#ifndef MOO_GDB_UI_H
#define MOO_GDB_UI_H

#include <gtk/gtk.h>
#include "mooedit/mooeditwindow.h"

G_BEGIN_DECLS

/* Phase 1 entry point.  Spawn a transient MooGdbSession, run
 * `-gdb-version`, collect the console output into a dialog, then
 * tear the session down.  Confirms the plugin → gdb wiring works
 * end-to-end before commit 2 builds out execution control. */
void  moo_gdb_ui_test_connection (MooEditWindow *window);

/* Per-window state opaque type — owned by the plugin's
 * MooGdbWindowPlugin instance. */
typedef struct _MooGdbWin MooGdbWin;

/* Lifecycle — called from moo_gdb_window_plugin_create/destroy. */
MooGdbWin *moo_gdb_win_new      (MooEditWindow *window);
void       moo_gdb_win_free     (MooGdbWin     *win);

/* Toggle a breakpoint at the user's line.  If a breakpoint is
 * already set there, removes it; otherwise asks the running session
 * (or a fresh one if there's none) to insert a new one.  Phase-3
 * scope: visual mark + send -break-insert / -break-delete; doesn't
 * try to launch the inferior. */
void       moo_gdb_win_toggle_bp(MooGdbWin     *win,
                                 const char    *file,
                                 int            line);

/* Execution control — forwarded to the (lazy) session.  start kicks
 * off "-exec-run"; subsequent commands target the running inferior.
 * No-op if there's no session yet (start) or no live inferior
 * (continue / step). */
void       moo_gdb_win_start    (MooGdbWin     *win);
void       moo_gdb_win_continue (MooGdbWin     *win);
void       moo_gdb_win_step_over(MooGdbWin     *win);
void       moo_gdb_win_step_into(MooGdbWin     *win);
void       moo_gdb_win_step_out (MooGdbWin     *win);
void       moo_gdb_win_pause    (MooGdbWin     *win);
void       moo_gdb_win_stop     (MooGdbWin     *win);

/* Pop a "Configure Target" dialog letting the user set the
 * binary path, command-line arguments, and working directory for
 * the next Start Debugging.  Values are stored on the
 * MooGdbWin and applied each time moo_gdb_win_start runs. */
void       moo_gdb_win_configure(MooGdbWin     *win);

G_END_DECLS

#endif /* MOO_GDB_UI_H */
