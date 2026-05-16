/*
 *   moogdb-session.h
 *
 *   Public API for the MooGdbSession GObject — a thin wrapper around
 *   a `gdb --interpreter=mi3` subprocess.  Phase 1 (commit 1) only
 *   exposes the spawn-and-quit lifecycle plus a `-gdb-version`
 *   round-trip; execution control, breakpoints, and frame inspection
 *   land in subsequent commits.
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#ifndef MOO_GDB_SESSION_H
#define MOO_GDB_SESSION_H

#include <glib-object.h>

G_BEGIN_DECLS

/* High-level session state.  Driven by the MI exec/notify stream
 * dispatcher; UI code subscribes to "state-changed" to know when to
 * enable/disable the toolbar buttons. */
typedef enum {
    MOO_GDB_STATE_IDLE,       /* created but gdb not yet spawned     */
    MOO_GDB_STATE_LOADING,    /* gdb spawned, waiting for prompt     */
    MOO_GDB_STATE_READY,      /* prompt seen, ready to accept cmds   */
    MOO_GDB_STATE_RUNNING,    /* target executing (Phase 2)          */
    MOO_GDB_STATE_STOPPED,    /* target stopped (Phase 2)            */
    MOO_GDB_STATE_EXITED,     /* gdb has quit                        */
    MOO_GDB_STATE_ERROR
} MooGdbState;

#define MOO_TYPE_GDB_SESSION (moo_gdb_session_get_type ())
G_DECLARE_FINAL_TYPE (MooGdbSession, moo_gdb_session,
                      MOO, GDB_SESSION, GObject)

/* Lifecycle ----------------------------------------------------------- */

/* Create a session.  Does NOT spawn gdb yet — call moo_gdb_session_start. */
MooGdbSession *moo_gdb_session_new       (void);

/* Spawn `gdb --interpreter=mi3 -nx --quiet [target]`.  `target` may
 * be NULL for a session that loads its target later.  Returns FALSE
 * and sets `error` if the spawn failed (e.g. gdb not on PATH). */
gboolean       moo_gdb_session_start     (MooGdbSession *session,
                                          const char    *target,
                                          GError       **error);

/* Send "-gdb-exit" and wait for the subprocess to die.  Safe to call
 * even if the session was never started. */
void           moo_gdb_session_quit      (MooGdbSession *session);

/* State accessors ---------------------------------------------------- */

MooGdbState    moo_gdb_session_get_state (MooGdbSession *session);

/* Most-recent `-gdb-version` reply, or NULL until populated. */
const char    *moo_gdb_session_get_version (MooGdbSession *session);

/* Signals (on the session GObject) ------------------------------------
 *
 *   "state-changed"  :: ()
 *       fired whenever moo_gdb_session_get_state() would return
 *       a different value than the last firing.
 *
 *   "console-output" :: (const char *line)
 *       a single CLI-style line from gdb (~"..." MI record).
 *       Already de-escaped.
 *
 *   "log-output"     :: (const char *line)
 *       gdb's own internal log lines (&"..." MI record).
 *
 *   "exited"         :: ()
 *       gdb has terminated.  The session is no longer usable.
 *
 * Phase-2 signals — "stopped", "breakpoint-added", "breakpoint-removed",
 * "running" — will be added when execution control lands.
 */

G_END_DECLS

#endif /* MOO_GDB_SESSION_H */
