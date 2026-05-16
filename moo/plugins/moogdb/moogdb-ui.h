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

G_END_DECLS

#endif /* MOO_GDB_UI_H */
