/*
 *   moogdb-ui.cpp
 *
 *   Phase 1: just enough UI to verify the gdb subprocess + MI parser
 *   round-trip.  "Debug → Test GDB connection" pops up a dialog,
 *   spawns gdb, runs `-gdb-version`, accumulates the console-output
 *   lines into the dialog's body, and tears the session down when
 *   the user closes the dialog.  Subsequent commits replace this
 *   with breakpoint margins / toolbar / current-line marker.
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#include "plugins/moogdb/moogdb-ui.h"
#include "plugins/moogdb/moogdb-session.h"

#include "mooedit/mooeditor.h"
#include "mooedit/mooeditview.h"
#include "mooedit/mootextview.h"
#include "mooedit/mootextbuffer.h"
#include "mooedit/moolinemark.h"
#include "mooutils/mooi18n.h"
#include "mooutils/moodialogs.h"
#include <string.h>

typedef struct {
    GtkWidget     *dialog;
    GtkTextBuffer *buffer;
    MooGdbSession *session;
} TestCtx;

static void
on_console_output (G_GNUC_UNUSED MooGdbSession *s,
                   const char *line, gpointer user_data)
{
    TestCtx *ctx = (TestCtx *) user_data;
    if (!line) return;
    GtkTextIter end;
    gtk_text_buffer_get_end_iter (ctx->buffer, &end);
    gtk_text_buffer_insert (ctx->buffer, &end, line, -1);
}

static void
on_state_changed (MooGdbSession *s, gpointer user_data)
{
    TestCtx *ctx = (TestCtx *) user_data;
    MooGdbState st = moo_gdb_session_get_state (s);
    if (st == MOO_GDB_STATE_ERROR || st == MOO_GDB_STATE_EXITED) {
        GtkTextIter end;
        gtk_text_buffer_get_end_iter (ctx->buffer, &end);
        const char *msg = (st == MOO_GDB_STATE_ERROR)
            ? "\n[gdb session error]\n"
            : "\n[gdb session ended]\n";
        gtk_text_buffer_insert (ctx->buffer, &end, msg, -1);
    }
}

static void
on_dialog_response (G_GNUC_UNUSED GtkDialog *dlg,
                    G_GNUC_UNUSED int response, gpointer user_data)
{
    TestCtx *ctx = (TestCtx *) user_data;
    if (ctx->session) {
        moo_gdb_session_quit (ctx->session);
        g_object_unref (ctx->session);
        ctx->session = NULL;
    }
    gtk_widget_destroy (ctx->dialog);
    g_free (ctx);
}

void
moo_gdb_ui_test_connection (MooEditWindow *window)
{
    GtkWidget *dialog = gtk_dialog_new_with_buttons (
        _("GDB Connection Test"),
        GTK_WINDOW (window),
        (GtkDialogFlags) (GTK_DIALOG_DESTROY_WITH_PARENT),
        _("_Close"), GTK_RESPONSE_CLOSE,
        (const char *) NULL);
    gtk_window_set_default_size (GTK_WINDOW (dialog), 600, 380);

    GtkWidget *content =
        gtk_dialog_get_content_area (GTK_DIALOG (dialog));

    GtkWidget *scroll = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroll),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand (scroll, TRUE);
    gtk_widget_set_vexpand (scroll, TRUE);
    gtk_box_pack_start (GTK_BOX (content), scroll, TRUE, TRUE, 0);

    GtkWidget *view = gtk_text_view_new ();
    gtk_text_view_set_editable      (GTK_TEXT_VIEW (view), FALSE);
    gtk_text_view_set_monospace     (GTK_TEXT_VIEW (view), TRUE);
    gtk_text_view_set_left_margin   (GTK_TEXT_VIEW (view), 8);
    gtk_text_view_set_right_margin  (GTK_TEXT_VIEW (view), 8);
    gtk_container_add (GTK_CONTAINER (scroll), view);

    TestCtx *ctx = g_new0 (TestCtx, 1);
    ctx->dialog  = dialog;
    ctx->buffer  = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    ctx->session = moo_gdb_session_new ();

    /* Header line so the user can see something happened even if gdb
     * doesn't print any console lines. */
    gtk_text_buffer_set_text (ctx->buffer,
        "Spawning gdb (mi3) and running -gdb-version...\n\n", -1);

    g_signal_connect (ctx->session, "console-output",
                      G_CALLBACK (on_console_output), ctx);
    g_signal_connect (ctx->session, "state-changed",
                      G_CALLBACK (on_state_changed), ctx);
    g_signal_connect (dialog, "response",
                      G_CALLBACK (on_dialog_response), ctx);

    gtk_widget_show_all (dialog);

    GError *err = NULL;
    if (!moo_gdb_session_start (ctx->session, NULL, &err)) {
        GtkTextIter end;
        gtk_text_buffer_get_end_iter (ctx->buffer, &end);
        char *msg = g_strdup_printf (
            "Failed to spawn gdb: %s\n\n"
            "Make sure `gdb` is installed and on your PATH.\n",
            err ? err->message : "(unknown error)");
        gtk_text_buffer_insert (ctx->buffer, &end, msg, -1);
        g_free (msg);
        if (err) g_error_free (err);
    }
}

/* ═════════════ Per-window state + breakpoint margin ═════════════════
 *
 * MooGdbWin holds one MooGdbSession (lazily created on first use)
 * plus a `breakpoints` table keyed by canonical file path.  Each
 * value is a GHashTable<int line -> Breakpoint*>, where Breakpoint
 * carries the gdb-assigned number plus the MooLineMark that shows
 * the red dot in the gutter.
 */

typedef struct {
    int          number;       /* -1 until -break-insert reply arrives */
    char        *file;
    int          line;
    MooLineMark *mark;         /* visual mark in the gutter (or NULL) */
} GdbBreakpoint;

struct _MooGdbWin {
    MooEditWindow *window;
    MooGdbSession *session;        /* lazily created */
    GHashTable    *bp_by_file;     /* char* -> GHashTable<int, GdbBreakpoint*> */
    GHashTable    *bp_by_number;   /* int   -> GdbBreakpoint* (borrowed) */
    gulong         line_mark_handler_id;
    gulong         doc_loaded_handler_id;
    gulong         bp_added_handler_id;
    gulong         bp_removed_handler_id;
    gulong         stopped_handler_id;

    /* Current-line marker.  At most one across the whole window:
     * when the debugger stops, we open the relevant file and place
     * an arrow icon at the line; when it resumes (or quits), we
     * remove the mark.  exec_file/exec_line cache the location so
     * doc-loaded can re-attach the mark if the user closed and
     * reopened the file mid-session. */
    MooLineMark   *exec_mark;
    char          *exec_file;
    int            exec_line;
};

static void
free_bp (gpointer p)
{
    GdbBreakpoint *bp = (GdbBreakpoint *) p;
    if (!bp) return;
    g_free (bp->file);
    if (bp->mark)
        g_object_unref (bp->mark);
    g_free (bp);
}

static void
free_file_table (gpointer p)
{
    g_hash_table_destroy ((GHashTable *) p);
}

/* Look up an existing breakpoint at file:line, or NULL. */
static GdbBreakpoint *
lookup_bp (MooGdbWin *win, const char *file, int line)
{
    if (!win->bp_by_file || !file) return NULL;
    GHashTable *line_tbl = (GHashTable *)
        g_hash_table_lookup (win->bp_by_file, file);
    if (!line_tbl) return NULL;
    return (GdbBreakpoint *)
        g_hash_table_lookup (line_tbl, GINT_TO_POINTER (line));
}

static void
register_bp (MooGdbWin *win, GdbBreakpoint *bp)
{
    GHashTable *line_tbl = (GHashTable *)
        g_hash_table_lookup (win->bp_by_file, bp->file);
    if (!line_tbl) {
        line_tbl = g_hash_table_new_full (g_direct_hash, g_direct_equal,
                                          NULL, free_bp);
        g_hash_table_insert (win->bp_by_file, g_strdup (bp->file), line_tbl);
    }
    g_hash_table_insert (line_tbl, GINT_TO_POINTER (bp->line), bp);
    if (bp->number >= 0)
        g_hash_table_insert (win->bp_by_number,
                              GINT_TO_POINTER (bp->number), bp);
}

/* Find the open MooEditView showing `file` (if any) and place a red
 * dot in its gutter at `line`.  Safe to call before/after the
 * actual file is loaded — we'll re-place on doc-loaded events too. */
static void
attach_visual_mark (G_GNUC_UNUSED MooGdbWin *win, GdbBreakpoint *bp)
{
    if (bp->mark) return;
    MooEditor *editor = moo_editor_instance ();
    MooEditArray *docs = moo_editor_get_docs (editor);
    if (!docs) return;
    for (guint i = 0; i < docs->n_elms; i++) {
        MooEdit *doc = docs->elms[i];
        char *fn = moo_edit_get_filename (doc);
        gboolean match = fn && !strcmp (fn, bp->file);
        g_free (fn);
        if (!match) continue;
        MooEditView *view = moo_edit_get_view (doc);
        if (!view) continue;
        GtkTextBuffer *buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
        if (!MOO_IS_TEXT_BUFFER (buf)) continue;

        bp->mark = (MooLineMark *) g_object_new (MOO_TYPE_LINE_MARK,
            "visible", TRUE, (const char *) NULL);
        moo_line_mark_set_stock_id (bp->mark, "gtk-stop");
        /* line is 1-based in our model; MooTextBuffer expects 0-based */
        moo_text_buffer_add_line_mark (MOO_TEXT_BUFFER (buf),
                                       bp->mark, bp->line - 1);
        break;
    }
}

static void
detach_visual_mark (GdbBreakpoint *bp)
{
    if (!bp->mark) return;
    MooTextBuffer *buf = moo_line_mark_get_buffer (bp->mark);
    if (buf)
        moo_text_buffer_delete_line_mark (buf, bp->mark);
    g_object_unref (bp->mark);
    bp->mark = NULL;
}

/* Remove the current-line marker (if any).  Called when execution
 * resumes, when gdb quits, and before each new "stopped" event so we
 * always have at most one. */
static void
clear_exec_mark (MooGdbWin *win)
{
    if (win->exec_mark) {
        MooTextBuffer *buf = moo_line_mark_get_buffer (win->exec_mark);
        if (buf)
            moo_text_buffer_delete_line_mark (buf, win->exec_mark);
        g_object_unref (win->exec_mark);
        win->exec_mark = NULL;
    }
    g_free (win->exec_file);
    win->exec_file = NULL;
    win->exec_line = 0;
}

/* Place / replace the current-line marker at file:line.  Opens the
 * file in the editor if it isn't already, focuses the view, and
 * scrolls the line into view.  Caches the location so on_doc_loaded
 * can re-attach if the file gets closed and reopened later. */
static void
set_exec_mark (MooGdbWin *win, const char *file, int line)
{
    clear_exec_mark (win);
    if (!file || line <= 0) return;

    win->exec_file = g_strdup (file);
    win->exec_line = line;

    /* Open / focus the doc holding `file`.  moo_editor_get_doc takes
     * a path-like string (UTF-8 filename), not a GFile, so we don't
     * need to wrap it. */
    MooEditor *editor = moo_editor_instance ();
    MooEdit   *doc    = moo_editor_get_doc (editor, file);
    if (!doc) {
        moo_editor_open_path (editor, file, NULL, 0, win->window);
        doc = moo_editor_get_doc (editor, file);
    }
    if (!doc) return;

    MooEditView *view = moo_edit_get_view (doc);
    if (!view) return;
    GtkTextBuffer *buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    if (!MOO_IS_TEXT_BUFFER (buf)) return;

    win->exec_mark = (MooLineMark *) g_object_new (MOO_TYPE_LINE_MARK,
        "visible", TRUE, (const char *) NULL);
    moo_line_mark_set_stock_id (win->exec_mark, "gtk-go-forward");
    moo_text_buffer_add_line_mark (MOO_TEXT_BUFFER (buf),
                                   win->exec_mark, line - 1);

    /* Scroll the view so the user can actually see where we
     * stopped.  moo_edit_window_set_active_doc focuses the right
     * tab; gtk_text_view_scroll_to_iter positions the cursor line
     * roughly mid-viewport. */
    moo_edit_window_set_active_doc (win->window, doc);
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_line (buf, &iter, line - 1);
    gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW (view),
                                  &iter, 0.0, TRUE, 0.0, 0.3);
}

/* Session "stopped" / "running" / "exited" handlers. */

static void
on_session_stopped (G_GNUC_UNUSED MooGdbSession *s,
                    G_GNUC_UNUSED const char *reason,
                    const char *file, int line,
                    G_GNUC_UNUSED const char *function,
                    gpointer user_data)
{
    MooGdbWin *win = (MooGdbWin *) user_data;
    set_exec_mark (win, file, line);
}

static void
on_session_running (G_GNUC_UNUSED MooGdbSession *s, gpointer user_data)
{
    MooGdbWin *win = (MooGdbWin *) user_data;
    clear_exec_mark (win);
}

static void
on_session_exited (G_GNUC_UNUSED MooGdbSession *s, gpointer user_data)
{
    MooGdbWin *win = (MooGdbWin *) user_data;
    clear_exec_mark (win);
}

static void
on_session_error (G_GNUC_UNUSED MooGdbSession *s, const char *msg,
                  gpointer user_data)
{
    MooGdbWin *win = (MooGdbWin *) user_data;
    if (!msg) return;
    /* Lightweight surfacing — full console panel arrives in
     * commit 7.  Until then, show a dialog so the user sees that
     * the most recent command failed (otherwise gdb errors
     * vanish silently into the parsed-but-ignored result stream). */
    moo_error_dialog (_("GDB Error"), msg, GTK_WIDGET (win->window));
}

/* Session "breakpoint-added" handler — gdb gave us a number; if we
 * have a pending placeholder at file:line, fill in its number and
 * register it in the by-number table for fast removal. */
static void
on_session_bp_added (G_GNUC_UNUSED MooGdbSession *s,
                     int number, const char *file, int line,
                     gpointer user_data)
{
    MooGdbWin *win = (MooGdbWin *) user_data;
    GdbBreakpoint *bp = lookup_bp (win, file, line);
    if (!bp) {
        /* Created via gdb console / =breakpoint-created with no prior
         * UI request — synthesize a record so the gutter mark shows. */
        bp = g_new0 (GdbBreakpoint, 1);
        bp->number = number;
        bp->file   = g_strdup (file);
        bp->line   = line;
        register_bp (win, bp);
        attach_visual_mark (win, bp);
        return;
    }
    bp->number = number;
    g_hash_table_insert (win->bp_by_number, GINT_TO_POINTER (number), bp);
    attach_visual_mark (win, bp);
}

static void
on_session_bp_removed (G_GNUC_UNUSED MooGdbSession *s,
                       int number, gpointer user_data)
{
    MooGdbWin *win = (MooGdbWin *) user_data;
    GdbBreakpoint *bp = (GdbBreakpoint *)
        g_hash_table_lookup (win->bp_by_number, GINT_TO_POINTER (number));
    if (!bp) return;
    detach_visual_mark (bp);
    GHashTable *line_tbl = (GHashTable *)
        g_hash_table_lookup (win->bp_by_file, bp->file);
    g_hash_table_remove (win->bp_by_number, GINT_TO_POINTER (number));
    /* line_tbl's free_bp destructor frees the entry. */
    if (line_tbl)
        g_hash_table_remove (line_tbl, GINT_TO_POINTER (bp->line));
}

/* Lazy session create — used when the user toggles a breakpoint
 * before they've launched the debugger.  Just enough state to track
 * breakpoints; -exec-run + execution control comes from Phase 5. */
static MooGdbSession *
ensure_session (MooGdbWin *win)
{
    if (win->session) return win->session;
    win->session = moo_gdb_session_new ();
    win->bp_added_handler_id = g_signal_connect (
        win->session, "breakpoint-added",
        G_CALLBACK (on_session_bp_added), win);
    win->bp_removed_handler_id = g_signal_connect (
        win->session, "breakpoint-removed",
        G_CALLBACK (on_session_bp_removed), win);
    win->stopped_handler_id = g_signal_connect (
        win->session, "stopped",
        G_CALLBACK (on_session_stopped), win);
    g_signal_connect (win->session, "running",
                      G_CALLBACK (on_session_running), win);
    g_signal_connect (win->session, "exited",
                      G_CALLBACK (on_session_exited), win);
    g_signal_connect (win->session, "error",
                      G_CALLBACK (on_session_error), win);
    GError *err = NULL;
    if (!moo_gdb_session_start (win->session, NULL, &err)) {
        g_warning ("[gdb] failed to spawn gdb: %s",
                   err ? err->message : "(unknown)");
        if (err) g_error_free (err);
        g_object_unref (win->session);
        win->session = NULL;
    }
    return win->session;
}

void
moo_gdb_win_toggle_bp (MooGdbWin *win, const char *file, int line)
{
    g_return_if_fail (win != NULL && file != NULL && line > 0);
    GdbBreakpoint *existing = lookup_bp (win, file, line);
    if (existing) {
        if (existing->number >= 0 && win->session)
            moo_gdb_session_break_remove (win->session, existing->number);
        else {
            /* Not yet registered with gdb (race between toggle and
             * insert reply).  Just drop the local visual + record. */
            detach_visual_mark (existing);
            GHashTable *line_tbl = (GHashTable *)
                g_hash_table_lookup (win->bp_by_file, file);
            if (line_tbl)
                g_hash_table_remove (line_tbl, GINT_TO_POINTER (line));
        }
        return;
    }

    /* New breakpoint — placeholder entry so future on_session_bp_added
     * can find it by (file,line). */
    GdbBreakpoint *bp = g_new0 (GdbBreakpoint, 1);
    bp->number = -1;
    bp->file   = g_strdup (file);
    bp->line   = line;
    register_bp (win, bp);
    attach_visual_mark (win, bp);

    MooGdbSession *s = ensure_session (win);
    if (s)
        moo_gdb_session_break_add (s, file, line);
}

/* ── Execution control forwards ──────────────────────────────────── */

void
moo_gdb_win_start (MooGdbWin *win)
{
    g_return_if_fail (win != NULL);
    MooGdbSession *s = ensure_session (win);
    if (!s) return;
    /* If the user hasn't told us about a target binary yet, try the
     * doc that's currently active — useful when a built binary lives
     * next to its source file.  Project-config dialog (commit 8)
     * replaces this guesswork. */
    MooEditor *editor = moo_editor_instance ();
    MooEdit   *doc    = moo_edit_window_get_active_doc (win->window);
    (void) editor;
    if (doc) {
        char *file = moo_edit_get_filename (doc);
        if (file) {
            /* Strip an extension to get a plausible executable name —
             * for foo.c, look for ./foo.  Not bulletproof, but a
             * sensible default for "Start Debugging" while we wait
             * for the per-project config UI. */
            char *dot = strrchr (file, '.');
            char *guess;
            if (dot && dot > strrchr (file, '/'))
                guess = g_strndup (file, dot - file);
            else
                guess = g_strdup (file);
            moo_gdb_session_set_target (s, guess);
            g_free (guess);
            g_free (file);
        }
    }
    moo_gdb_session_run (s);
}

void moo_gdb_win_continue (MooGdbWin *win)
    { if (win && win->session) moo_gdb_session_continue   (win->session); }
void moo_gdb_win_step_over (MooGdbWin *win)
    { if (win && win->session) moo_gdb_session_step_over  (win->session); }
void moo_gdb_win_step_into (MooGdbWin *win)
    { if (win && win->session) moo_gdb_session_step_into  (win->session); }
void moo_gdb_win_step_out  (MooGdbWin *win)
    { if (win && win->session) moo_gdb_session_step_out   (win->session); }
void moo_gdb_win_pause     (MooGdbWin *win)
    { if (win && win->session) moo_gdb_session_pause      (win->session); }
void moo_gdb_win_stop      (MooGdbWin *win)
    { if (win && win->session) { moo_gdb_session_quit (win->session); } }

/* MooTextView "line-mark-clicked" signal handler.  Convert the
 * clicked (view, line) into (file, line) and forward to toggle_bp. */
static gboolean
on_line_mark_clicked (MooTextView *tview, int line, MooGdbWin *win)
{
    /* The MooTextView in medit is wrapped by a MooEditView; the
     * doc gives us the filename.  Walk up: view is the MooEditView. */
    if (!MOO_IS_EDIT_VIEW (tview))
        return FALSE;
    MooEdit *doc = moo_edit_view_get_doc (MOO_EDIT_VIEW (tview));
    if (!doc) return FALSE;
    char *file = moo_edit_get_filename (doc);
    if (!file) return FALSE;
    /* line argument is 0-based; our model uses 1-based. */
    moo_gdb_win_toggle_bp (win, file, line + 1);
    g_free (file);
    return TRUE;
}

/* On editor "doc-loaded" we may need to re-attach previously
 * registered breakpoint marks AND the current-line marker — both
 * were created before the file's buffer was visible (or removed
 * when the file was closed). */
static void
on_doc_loaded (G_GNUC_UNUSED MooEditor *editor, MooEdit *doc,
               MooGdbWin *win)
{
    char *file = moo_edit_get_filename (doc);
    if (!file) return;

    /* Breakpoints */
    GHashTable *line_tbl = (GHashTable *)
        g_hash_table_lookup (win->bp_by_file, file);
    if (line_tbl) {
        GHashTableIter it;
        gpointer key, val;
        g_hash_table_iter_init (&it, line_tbl);
        while (g_hash_table_iter_next (&it, &key, &val))
            attach_visual_mark (win, (GdbBreakpoint *) val);
    }

    /* Current-line marker — only one across the window. */
    if (win->exec_file && !strcmp (win->exec_file, file) && !win->exec_mark) {
        char *saved_file = g_strdup (win->exec_file);
        int   saved_line = win->exec_line;
        set_exec_mark (win, saved_file, saved_line);
        g_free (saved_file);
    }

    g_free (file);
}

MooGdbWin *
moo_gdb_win_new (MooEditWindow *window)
{
    MooGdbWin *win = g_new0 (MooGdbWin, 1);
    win->window      = window;
    win->bp_by_file  = g_hash_table_new_full (g_str_hash, g_str_equal,
                                               g_free, free_file_table);
    win->bp_by_number = g_hash_table_new (g_direct_hash, g_direct_equal);

    /* Catch line-mark-clicked on every editor view that lives in
     * this window.  Connecting once at the class level keeps the
     * code small at the cost of routing every click through one
     * handler — fine for Phase 3. */
    GObjectClass *vklass = (GObjectClass *) g_type_class_peek (
        MOO_TYPE_EDIT_VIEW);
    (void) vklass;
    /* Per-instance signal connection on existing views + new views
     * via the editor's doc-list-changed signal would be the proper
     * approach.  For now we connect at the class-default level,
     * meaning every MooTextView instance fires our handler.  The
     * handler short-circuits on non-MOO_EDIT_VIEW objects. */
    win->line_mark_handler_id = g_signal_add_emission_hook (
        g_signal_lookup ("line-mark-clicked", MOO_TYPE_TEXT_VIEW),
        0,
        [](GSignalInvocationHint *, guint, const GValue *params,
           gpointer user_data) -> gboolean {
            MooGdbWin *w = (MooGdbWin *) user_data;
            MooTextView *tview = MOO_TEXT_VIEW (g_value_get_object (&params[0]));
            int          line  = g_value_get_int    (&params[1]);
            on_line_mark_clicked (tview, line, w);
            /* TRUE → stay subscribed */
            return TRUE;
        },
        win, NULL);

    MooEditor *editor = moo_editor_instance ();
    win->doc_loaded_handler_id = g_signal_connect (
        editor, "after-doc-loaded",
        G_CALLBACK (on_doc_loaded), win);

    return win;
}

void
moo_gdb_win_free (MooGdbWin *win)
{
    if (!win) return;

    if (win->line_mark_handler_id)
        g_signal_remove_emission_hook (
            g_signal_lookup ("line-mark-clicked", MOO_TYPE_TEXT_VIEW),
            win->line_mark_handler_id);

    MooEditor *editor = moo_editor_instance ();
    if (win->doc_loaded_handler_id)
        g_signal_handler_disconnect (editor, win->doc_loaded_handler_id);

    clear_exec_mark (win);

    if (win->session) {
        moo_gdb_session_quit (win->session);
        g_object_unref (win->session);
    }
    g_hash_table_destroy (win->bp_by_file);
    g_hash_table_destroy (win->bp_by_number);
    g_free (win);
}
