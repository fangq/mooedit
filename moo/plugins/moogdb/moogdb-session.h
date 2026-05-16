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

/* Forward a raw command line to gdb's stdin.  Useful for the
 * console pane: any CLI command (e.g. "info threads", "print x",
 * or any -MI- command) is sent verbatim, prefixed only with the
 * usual numeric token so the reply can be matched.  Empty / NULL
 * lines are no-ops. */
void           moo_gdb_session_send_raw  (MooGdbSession *s,
                                          const char    *cmd);

/* Set the target executable to debug.  May be called before or
 * after start(); the path is forwarded to gdb via `-file-exec-and-
 * symbols`.  Safe to set NULL (clears the current target). */
void           moo_gdb_session_set_target (MooGdbSession *s,
                                           const char    *target);

/* Set the program arguments (NULL-terminated argv-style; the
 * binary itself is NOT in the list).  Sent to gdb via
 * `-exec-arguments` so a later `-exec-run` picks them up. */
void           moo_gdb_session_set_args   (MooGdbSession     *s,
                                           const char *const *argv);

/* Set the working directory for the target program.  Forwarded
 * via `-environment-cd`. */
void           moo_gdb_session_set_cwd    (MooGdbSession *s,
                                           const char    *cwd);

/* Execution control.  All async; subscribe to "state-changed"
 * (and Phase-4's "stopped" / "running") to observe transitions. */
void           moo_gdb_session_run        (MooGdbSession *s);
void           moo_gdb_session_continue   (MooGdbSession *s);
void           moo_gdb_session_step_over  (MooGdbSession *s);   /* -exec-next   */
void           moo_gdb_session_step_into  (MooGdbSession *s);   /* -exec-step   */
void           moo_gdb_session_step_out   (MooGdbSession *s);   /* -exec-finish */
/* Send SIGINT to the inferior so the user can break into a hung
 * program.  After this fires the user gets the usual *stopped
 * notification with reason="signal-received". */
void           moo_gdb_session_pause      (MooGdbSession *s);   /* -exec-interrupt */

/* Breakpoints.  Returns the gdb-assigned number async via the
 * "breakpoint-added" signal — there's no synchronous return value
 * because the -break-insert reply may not arrive immediately. */
void           moo_gdb_session_break_add  (MooGdbSession *s,
                                           const char    *file,
                                           int            line);
void           moo_gdb_session_break_remove(MooGdbSession *s, int number);

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
 *   "running"             :: ()
 *       fired on the *running async record.
 *
 *   "stopped"             :: (reason, file, line, function)
 *       carries the file/line/function gdb reported in the
 *       *stopped record's frame={...} field.  All strings borrowed.
 *
 *   "breakpoint-added"    :: (int number, const char *file, int line)
 *       -break-insert succeeded.
 *
 *   "breakpoint-removed"  :: (int number)
 *       breakpoint identified by `number` was removed.
 *
 *   "exited"              :: ()
 *       gdb has terminated.  The session is no longer usable.
 */

G_END_DECLS

#endif /* MOO_GDB_SESSION_H */
