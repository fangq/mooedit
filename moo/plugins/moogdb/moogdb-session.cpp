/*
 *   moogdb-session.cpp
 *
 *   Phase 1 implementation of MooGdbSession.  Spawns a gdb
 *   subprocess in MI mode, reads lines asynchronously, dispatches
 *   MI records, and supports a single round-trip command
 *   (`-gdb-version`).  Execution control and breakpoints land in
 *   later commits.
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#include "plugins/moogdb/moogdb-session.h"
#include "plugins/moogdb/moogdb-mi-parser.h"

#include <gio/gio.h>
#include <string.h>

/* ── Object layout ────────────────────────────────────────────────── */

struct _MooGdbSession {
    GObject parent;

    GSubprocess      *gdb;
    GOutputStream    *gdb_in;
    GDataInputStream *gdb_out;
    GCancellable     *cancellable;

    MooGdbState       state;
    char             *version;

    /* Monotonic command counter.  Each outgoing -command is prefixed
     * with `<token>` so the matching `<token>^done,...` response can
     * be routed back to the issuer. */
    guint             next_token;
    GHashTable       *pending;   /* token (GINT) → ResponseCB struct */
};

G_DEFINE_TYPE (MooGdbSession, moo_gdb_session, G_TYPE_OBJECT)

typedef void (*ResponseCB) (MooGdbSession *s,
                            MooGdbMiRecord *record,
                            gpointer        user_data);

typedef struct {
    ResponseCB cb;
    gpointer   user_data;
} PendingEntry;

/* ── Signals ──────────────────────────────────────────────────────── */

enum {
    SIG_STATE_CHANGED,
    SIG_CONSOLE_OUTPUT,
    SIG_LOG_OUTPUT,
    SIG_RUNNING,
    SIG_STOPPED,
    SIG_BP_ADDED,
    SIG_BP_REMOVED,
    SIG_ERROR,
    SIG_EXITED,
    N_SIGNALS
};
static guint signals[N_SIGNALS];

/* ── Forwards ─────────────────────────────────────────────────────── */

static void  start_read_loop  (MooGdbSession *s);
static void  on_line_async    (GObject *source, GAsyncResult *res, gpointer user_data);
static void  dispatch_record  (MooGdbSession *s, MooGdbMiRecord *r);
static void  send_command     (MooGdbSession *s,
                               const char    *cmd,
                               ResponseCB     cb,
                               gpointer       user_data);
static void  set_state        (MooGdbSession *s, MooGdbState st);
static void  on_version_reply (MooGdbSession *s,
                               MooGdbMiRecord *r,
                               gpointer        user_data);
static void  emit_bp_added_from_bkpt (MooGdbSession *s,
                                       MooGdbMiValue *bkpt_val);

/* ── Life-cycle ───────────────────────────────────────────────────── */

static void
moo_gdb_session_init (MooGdbSession *s)
{
    s->state       = MOO_GDB_STATE_IDLE;
    s->next_token  = 1;
    s->pending     = g_hash_table_new_full (g_direct_hash, g_direct_equal,
                                             NULL, g_free);
    s->cancellable = g_cancellable_new ();
}

static void
moo_gdb_session_finalize (GObject *object)
{
    MooGdbSession *s = MOO_GDB_SESSION (object);
    /* If gdb is still alive, force it down — quit() does a polite
     * "-gdb-exit" but at finalize we may not have time to wait. */
    if (s->gdb) {
        g_cancellable_cancel (s->cancellable);
        g_subprocess_force_exit (s->gdb);
        g_object_unref (s->gdb);
    }
    g_clear_object (&s->gdb_out);
    g_clear_object (&s->cancellable);
    /* gdb_in is owned by gdb; don't unref. */
    g_hash_table_destroy (s->pending);
    g_free (s->version);
    G_OBJECT_CLASS (moo_gdb_session_parent_class)->finalize (object);
}

static void
moo_gdb_session_class_init (MooGdbSessionClass *klass)
{
    GObjectClass *go = G_OBJECT_CLASS (klass);
    go->finalize = moo_gdb_session_finalize;

    signals[SIG_STATE_CHANGED] = g_signal_new (
        "state-changed", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
        0, NULL, NULL, g_cclosure_marshal_VOID__VOID,
        G_TYPE_NONE, 0);

    signals[SIG_CONSOLE_OUTPUT] = g_signal_new (
        "console-output", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
        0, NULL, NULL, g_cclosure_marshal_VOID__STRING,
        G_TYPE_NONE, 1, G_TYPE_STRING);

    signals[SIG_LOG_OUTPUT] = g_signal_new (
        "log-output", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
        0, NULL, NULL, g_cclosure_marshal_VOID__STRING,
        G_TYPE_NONE, 1, G_TYPE_STRING);

    signals[SIG_RUNNING] = g_signal_new (
        "running", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
        0, NULL, NULL, g_cclosure_marshal_VOID__VOID,
        G_TYPE_NONE, 0);

    /* "stopped" carries the file/line/function gdb reported via the
     * *stopped record's `frame` field, plus the textual stop reason
     * (breakpoint-hit, end-stepping-range, exited-normally, ...).
     * Strings are borrowed; copy them in the handler if needed. */
    signals[SIG_STOPPED] = g_signal_new (
        "stopped", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
        0, NULL, NULL, NULL,
        G_TYPE_NONE, 4,
        G_TYPE_STRING,    /* reason  */
        G_TYPE_STRING,    /* file    (canonical path, may be NULL) */
        G_TYPE_INT,       /* line    (1-based, 0 if unknown) */
        G_TYPE_STRING);   /* function (may be NULL) */

    /* "breakpoint-added" :: (int number, const char *file, int line)
     * Fires for both the synchronous reply to -break-insert and the
     * async =breakpoint-created notification (gdb sends both for
     * the same insert; consumers should dedupe by number). */
    signals[SIG_BP_ADDED] = g_signal_new (
        "breakpoint-added", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
        0, NULL, NULL, NULL,
        G_TYPE_NONE, 3, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT);

    signals[SIG_BP_REMOVED] = g_signal_new (
        "breakpoint-removed", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
        0, NULL, NULL, g_cclosure_marshal_VOID__INT,
        G_TYPE_NONE, 1, G_TYPE_INT);

    /* "error" :: (const char *msg)
     * Fired when gdb responds with `^error,msg="..."`.  Useful for
     * surfacing problems like "No such file or directory" from a
     * -file-exec-and-symbols, or "function not defined" from a
     * -break-insert.  Stay tolerant — error is per-command, not a
     * session-fatal state. */
    signals[SIG_ERROR] = g_signal_new (
        "error", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
        0, NULL, NULL, g_cclosure_marshal_VOID__STRING,
        G_TYPE_NONE, 1, G_TYPE_STRING);

    signals[SIG_EXITED] = g_signal_new (
        "exited", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
        0, NULL, NULL, g_cclosure_marshal_VOID__VOID,
        G_TYPE_NONE, 0);
}

MooGdbSession *
moo_gdb_session_new (void)
{
    return MOO_GDB_SESSION (g_object_new (MOO_TYPE_GDB_SESSION, NULL));
}

/* ── State ────────────────────────────────────────────────────────── */

static void
set_state (MooGdbSession *s, MooGdbState st)
{
    if (s->state == st) return;
    s->state = st;
    g_signal_emit (s, signals[SIG_STATE_CHANGED], 0);
}

MooGdbState moo_gdb_session_get_state   (MooGdbSession *s) { return s->state; }
const char *moo_gdb_session_get_version (MooGdbSession *s) { return s->version; }

/* ── Spawn ────────────────────────────────────────────────────────── */

gboolean
moo_gdb_session_start (MooGdbSession *s, const char *target, GError **error)
{
    g_return_val_if_fail (MOO_IS_GDB_SESSION (s), FALSE);
    if (s->gdb) {
        g_set_error (error, G_IO_ERROR, G_IO_ERROR_PENDING,
                     "session already started");
        return FALSE;
    }

    GSubprocessLauncher *launcher =
        g_subprocess_launcher_new ((GSubprocessFlags)
            (G_SUBPROCESS_FLAGS_STDIN_PIPE
             | G_SUBPROCESS_FLAGS_STDOUT_PIPE
             | G_SUBPROCESS_FLAGS_STDERR_MERGE));

    /* Build argv: gdb --interpreter=mi3 -nx --quiet [target]
     *   -nx     skip ~/.gdbinit (avoids surprising user-config
     *           interactions; we control the environment).
     *   --quiet suppress the version banner; we'll fetch it with
     *           -gdb-version explicitly. */
    GPtrArray *argv = g_ptr_array_new ();
    g_ptr_array_add (argv, (gpointer) "gdb");
    g_ptr_array_add (argv, (gpointer) "--interpreter=mi3");
    g_ptr_array_add (argv, (gpointer) "-nx");
    g_ptr_array_add (argv, (gpointer) "--quiet");
    if (target && *target)
        g_ptr_array_add (argv, (gpointer) target);
    g_ptr_array_add (argv, NULL);

    s->gdb = g_subprocess_launcher_spawnv (launcher,
                                            (const char *const *) argv->pdata,
                                            error);
    g_ptr_array_free (argv, TRUE);
    g_object_unref (launcher);

    if (!s->gdb) {
        set_state (s, MOO_GDB_STATE_ERROR);
        return FALSE;
    }

    s->gdb_in  = g_subprocess_get_stdin_pipe (s->gdb);
    s->gdb_out = g_data_input_stream_new (
        g_subprocess_get_stdout_pipe (s->gdb));

    set_state (s, MOO_GDB_STATE_LOADING);
    start_read_loop (s);

    /* Fire off the version probe right away.  The reply arrives via
     * the async read loop; on_version_reply stores the result and
     * transitions us to READY. */
    send_command (s, "-gdb-version", on_version_reply, NULL);
    return TRUE;
}

/* ── Quit ─────────────────────────────────────────────────────────── */

void
moo_gdb_session_quit (MooGdbSession *s)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    if (!s->gdb) return;
    /* Polite exit; the read loop will see EOF and emit "exited". */
    send_command (s, "-gdb-exit", NULL, NULL);
}

/* ── Raw command forwarding ──────────────────────────────────────── */

void
moo_gdb_session_send_raw (MooGdbSession *s, const char *cmd)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    if (!cmd || !*cmd) return;
    /* Strip a single trailing newline so the user's "info threads\n"
     * doesn't double up.  send_command appends its own. */
    char *trimmed = g_strdup (cmd);
    g_strchomp (trimmed);
    send_command (s, trimmed, NULL, NULL);
    g_free (trimmed);
}

/* ── Sending commands ─────────────────────────────────────────────── */

static void
send_command (MooGdbSession *s, const char *cmd,
              ResponseCB cb, gpointer user_data)
{
    if (!s->gdb_in) return;
    int token = (int) s->next_token++;
    char *line = g_strdup_printf ("%d%s\n", token, cmd);
    g_output_stream_write_all (s->gdb_in, line, strlen (line),
                                NULL, NULL, NULL);
    g_output_stream_flush (s->gdb_in, NULL, NULL);
    g_free (line);

    if (cb) {
        PendingEntry *pe = g_new (PendingEntry, 1);
        pe->cb        = cb;
        pe->user_data = user_data;
        g_hash_table_insert (s->pending, GINT_TO_POINTER (token), pe);
    }
}

/* ── Async read loop ──────────────────────────────────────────────── */

static void
start_read_loop (MooGdbSession *s)
{
    g_data_input_stream_read_line_async (
        s->gdb_out, G_PRIORITY_DEFAULT, s->cancellable,
        on_line_async, s);
}

static void
on_line_async (GObject *source, GAsyncResult *res, gpointer user_data)
{
    MooGdbSession *s = MOO_GDB_SESSION (user_data);
    GError *err = NULL;
    gsize len;
    char *line = g_data_input_stream_read_line_finish (
        G_DATA_INPUT_STREAM (source), res, &len, &err);

    if (!line) {
        /* EOF or error → gdb is gone. */
        if (err) g_error_free (err);
        set_state (s, MOO_GDB_STATE_EXITED);
        g_signal_emit (s, signals[SIG_EXITED], 0);
        return;
    }

    MooGdbMiRecord *rec = moo_gdb_mi_parse (line);
    g_free (line);
    if (rec) {
        dispatch_record (s, rec);
        moo_gdb_mi_record_free (rec);
    }

    /* Keep reading. */
    start_read_loop (s);
}

static void
dispatch_record (MooGdbSession *s, MooGdbMiRecord *r)
{
    MooGdbMiKind k = moo_gdb_mi_record_kind (r);
    switch (k) {
    case MOO_GDB_MI_RESULT: {
        const char *klass = moo_gdb_mi_record_class (r);
        /* Surface gdb-reported errors so the UI can flag them.  The
         * msg field of ^error,msg="..." carries a human-readable
         * description; we forward it verbatim. */
        if (klass && !strcmp (klass, "error")) {
            MooGdbMiValue *msg = moo_gdb_mi_record_field (r, "msg");
            const char *mstr = msg ? moo_gdb_mi_value_string (msg) : NULL;
            g_signal_emit (s, signals[SIG_ERROR], 0,
                           mstr ? mstr : "(unknown gdb error)");
        }
        int tok = moo_gdb_mi_record_token (r);
        if (tok >= 0) {
            PendingEntry *pe = (PendingEntry *)
                g_hash_table_lookup (s->pending, GINT_TO_POINTER (tok));
            if (pe) {
                ResponseCB cb = pe->cb;
                gpointer ud   = pe->user_data;
                /* Remove before invoking so the callback can safely
                 * issue another command. */
                g_hash_table_remove (s->pending, GINT_TO_POINTER (tok));
                if (cb) cb (s, r, ud);
            }
        }
        break;
    }
    case MOO_GDB_MI_CONSOLE: {
        const char *t = moo_gdb_mi_record_text (r);
        if (t) g_signal_emit (s, signals[SIG_CONSOLE_OUTPUT], 0, t);
        break;
    }
    case MOO_GDB_MI_LOG: {
        const char *t = moo_gdb_mi_record_text (r);
        if (t) g_signal_emit (s, signals[SIG_LOG_OUTPUT], 0, t);
        break;
    }
    case MOO_GDB_MI_PROMPT:
        if (s->state == MOO_GDB_STATE_LOADING)
            set_state (s, MOO_GDB_STATE_READY);
        break;
    case MOO_GDB_MI_EXEC: {
        const char *klass = moo_gdb_mi_record_class (r);
        if (!klass) break;
        if (!strcmp (klass, "running")) {
            set_state (s, MOO_GDB_STATE_RUNNING);
            g_signal_emit (s, signals[SIG_RUNNING], 0);
        } else if (!strcmp (klass, "stopped")) {
            /* Pull file/line/function from the optional frame={…} */
            const char *file = NULL, *func = NULL;
            int         line = 0;
            MooGdbMiValue *frame = moo_gdb_mi_record_field (r, "frame");
            if (frame) {
                MooGdbMiValue *v;
                /* fullname is gdb's canonical absolute path; fall
                 * back to relative `file` if missing. */
                v = moo_gdb_mi_value_tuple_get (frame, "fullname");
                if (!v) v = moo_gdb_mi_value_tuple_get (frame, "file");
                if (v) file = moo_gdb_mi_value_string (v);
                v = moo_gdb_mi_value_tuple_get (frame, "line");
                if (v) {
                    const char *ls = moo_gdb_mi_value_string (v);
                    if (ls) line = atoi (ls);
                }
                v = moo_gdb_mi_value_tuple_get (frame, "func");
                if (v) func = moo_gdb_mi_value_string (v);
            }
            const char *reason = NULL;
            MooGdbMiValue *rv = moo_gdb_mi_record_field (r, "reason");
            if (rv) reason = moo_gdb_mi_value_string (rv);

            set_state (s, MOO_GDB_STATE_STOPPED);
            g_signal_emit (s, signals[SIG_STOPPED], 0,
                           reason, file, line, func);
        }
        break;
    }
    case MOO_GDB_MI_NOTIFY: {
        const char *klass = moo_gdb_mi_record_class (r);
        if (!klass) break;
        if (!strcmp (klass, "breakpoint-created")
            || !strcmp (klass, "breakpoint-modified"))
        {
            MooGdbMiValue *bkpt = moo_gdb_mi_record_field (r, "bkpt");
            emit_bp_added_from_bkpt (s, bkpt);
        }
        else if (!strcmp (klass, "breakpoint-deleted"))
        {
            MooGdbMiValue *idv = moo_gdb_mi_record_field (r, "id");
            if (idv) {
                const char *idstr = moo_gdb_mi_value_string (idv);
                if (idstr)
                    g_signal_emit (s, signals[SIG_BP_REMOVED],
                                   0, atoi (idstr));
            }
        }
        break;
    }
    default:
        /* STATUS / TARGET — wired in later commits. */
        break;
    }
}

/* ── Target / arguments / cwd ────────────────────────────────────── */

void
moo_gdb_session_set_target (MooGdbSession *s, const char *target)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    if (!s->gdb_in) return;
    char *escaped = target
        ? g_strescape (target, "")
        : g_strdup ("");
    char *cmd = g_strdup_printf ("-file-exec-and-symbols \"%s\"", escaped);
    send_command (s, cmd, NULL, NULL);
    g_free (cmd);
    g_free (escaped);
}

void
moo_gdb_session_set_args (MooGdbSession *s, const char *const *argv)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    if (!s->gdb_in) return;
    /* `-exec-arguments arg1 arg2 ...` — each arg shell-quoted to
     * survive embedded spaces.  Empty argv clears the list. */
    GString *cmd = g_string_new ("-exec-arguments");
    if (argv) {
        for (int i = 0; argv[i]; i++) {
            char *quoted = g_shell_quote (argv[i]);
            g_string_append_c (cmd, ' ');
            g_string_append   (cmd, quoted);
            g_free (quoted);
        }
    }
    send_command (s, cmd->str, NULL, NULL);
    g_string_free (cmd, TRUE);
}

void
moo_gdb_session_set_cwd (MooGdbSession *s, const char *cwd)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    if (!s->gdb_in || !cwd) return;
    char *quoted = g_shell_quote (cwd);
    char *cmd    = g_strdup_printf ("-environment-cd %s", quoted);
    send_command (s, cmd, NULL, NULL);
    g_free (cmd);
    g_free (quoted);
}

/* ── Execution control ────────────────────────────────────────────── */

void
moo_gdb_session_run (MooGdbSession *s)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    /* -exec-run starts the inferior from main(); the *running record
     * arrives first, then *stopped on the first breakpoint / signal. */
    send_command (s, "-exec-run", NULL, NULL);
}

void
moo_gdb_session_continue (MooGdbSession *s)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    send_command (s, "-exec-continue", NULL, NULL);
}

/* -exec-next advances over a single source line; if the line is a
 * function call, the call returns before gdb stops again. */
void
moo_gdb_session_step_over (MooGdbSession *s)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    send_command (s, "-exec-next", NULL, NULL);
}

/* -exec-step advances by one source line, descending into any
 * function call on that line. */
void
moo_gdb_session_step_into (MooGdbSession *s)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    send_command (s, "-exec-step", NULL, NULL);
}

/* -exec-finish runs until the current function returns. */
void
moo_gdb_session_step_out (MooGdbSession *s)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    send_command (s, "-exec-finish", NULL, NULL);
}

/* -exec-interrupt sends SIGINT to the running inferior.  Use this
 * to break into a hung program.  gdb responds with the usual
 * *stopped record (reason="signal-received") which our existing
 * dispatcher already routes to set_exec_mark. */
void
moo_gdb_session_pause (MooGdbSession *s)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    /* --all interrupts every thread in a multi-threaded program. */
    send_command (s, "-exec-interrupt --all", NULL, NULL);
}

/* ── Breakpoints ──────────────────────────────────────────────────── */

/* Decode a `bkpt={number="N",fullname="...",file="...",line="L",...}`
 * value into (number, file, line) and emit "breakpoint-added".
 * `bkpt_val` may be NULL — we just return without firing.
 *
 * Pending breakpoints (set via -break-insert -f before any binary
 * has been loaded) come back without fullname/file/line; gdb stuffs
 * the original location into `original-location="file:line"`
 * instead.  Parse that fallback so the UI's placeholder
 * (registered under the same file:line key it requested) can still
 * find a match. */
static void
emit_bp_added_from_bkpt (MooGdbSession *s, MooGdbMiValue *bkpt_val)
{
    if (!bkpt_val) return;
    MooGdbMiValue *v;
    int   number = -1;
    const char *file = NULL;
    int   line = 0;
    /* Buffer for the parsed-from-original-location filename — must
     * outlive the signal emission below. */
    char  file_buf[1024];
    file_buf[0] = '\0';

    v = moo_gdb_mi_value_tuple_get (bkpt_val, "number");
    if (v) {
        const char *ns = moo_gdb_mi_value_string (v);
        if (ns) number = atoi (ns);
    }
    v = moo_gdb_mi_value_tuple_get (bkpt_val, "fullname");
    if (!v) v = moo_gdb_mi_value_tuple_get (bkpt_val, "file");
    if (v) file = moo_gdb_mi_value_string (v);
    v = moo_gdb_mi_value_tuple_get (bkpt_val, "line");
    if (v) {
        const char *ls = moo_gdb_mi_value_string (v);
        if (ls) line = atoi (ls);
    }

    /* Fallback for pending breakpoints. */
    if (!file) {
        v = moo_gdb_mi_value_tuple_get (bkpt_val, "original-location");
        if (v) {
            const char *orig = moo_gdb_mi_value_string (v);
            if (orig) {
                const char *colon = strrchr (orig, ':');
                if (colon && colon > orig
                    && (gsize)(colon - orig) < sizeof file_buf)
                {
                    memcpy (file_buf, orig, colon - orig);
                    file_buf[colon - orig] = '\0';
                    file = file_buf;
                    if (line <= 0)
                        line = atoi (colon + 1);
                }
            }
        }
    }

    /* Still no file — gdb gave us a function-name breakpoint or
     * similar location we can't easily map to a margin mark.  Drop
     * silently rather than crash downstream consumers that key by
     * (file, line). */
    if (number < 0 || !file) return;

    g_signal_emit (s, signals[SIG_BP_ADDED], 0, number, file, line);
}

static void
on_break_insert_reply (MooGdbSession *s, MooGdbMiRecord *r,
                       G_GNUC_UNUSED gpointer user_data)
{
    const char *klass = moo_gdb_mi_record_class (r);
    if (!klass || strcmp (klass, "done") != 0) return;
    MooGdbMiValue *bkpt = moo_gdb_mi_record_field (r, "bkpt");
    emit_bp_added_from_bkpt (s, bkpt);
}

void
moo_gdb_session_break_add (MooGdbSession *s, const char *file, int line)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    g_return_if_fail (file != NULL && line > 0);
    /* -break-insert -f FILE:LINE — the -f flag makes the breakpoint
     * "pending": gdb accepts it even if no symbol table is loaded
     * yet and resolves it later when the inferior gets loaded.
     *
     * NB: do NOT shell-quote the path here — gdb echoes the
     * original location back via `original-location="..."`, and
     * adding `'` quotes makes the round-trip path mismatch the
     * placeholder we registered under the unquoted path.  Paths
     * with embedded spaces would be a problem; if/when that hits,
     * use MI-quoting (`"..."`) rather than shell-quoting. */
    char *cmd = g_strdup_printf ("-break-insert -f %s:%d", file, line);
    send_command (s, cmd, on_break_insert_reply, NULL);
    g_free (cmd);
}

void
moo_gdb_session_break_remove (MooGdbSession *s, int number)
{
    g_return_if_fail (MOO_IS_GDB_SESSION (s));
    g_return_if_fail (number >= 0);
    char *cmd = g_strdup_printf ("-break-delete %d", number);
    send_command (s, cmd, NULL, NULL);
    g_free (cmd);
    /* gdb sends =breakpoint-deleted async on success; that's the
     * primary signal path — we emit "breakpoint-removed" from the
     * NOTIFY branch of the dispatcher.  Emit it locally too in case
     * the deletion races: harmless if duplicated. */
    g_signal_emit (s, signals[SIG_BP_REMOVED], 0, number);
}

/* ── -gdb-version reply ───────────────────────────────────────────── */

static void
on_version_reply (MooGdbSession *s, MooGdbMiRecord *r,
                  G_GNUC_UNUSED gpointer user_data)
{
    /* `-gdb-version` doesn't return its data structured; instead it
     * streams the version through `~"..."` CONSOLE records, then a
     * single `^done` arrives.  Our console handler already emits the
     * lines; here we just stash the most-recent banner-looking line. */
    const char *klass = moo_gdb_mi_record_class (r);
    if (klass && !strcmp (klass, "done") && !s->version)
        s->version = g_strdup ("(see console output)");
}
