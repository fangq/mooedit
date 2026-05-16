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
#include "mooutils/moopane.h"
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

    /* Current-line marker.  At most one across the whole window:
     * when the debugger stops, we open the relevant file and place
     * an arrow icon at the line; when it resumes (or quits), we
     * remove the mark.  exec_file/exec_line cache the location for
     * possible later use (doc-load re-attach) when we add that. */
    MooLineMark   *exec_mark;
    char          *exec_file;
    int            exec_line;

    /* Console pane: monospaced log of gdb's ~/&/@ stream records
     * plus error replies, with an entry below for the user to send
     * raw commands.  Lives in the editor window's bottom pane area
     * (MOO_PANE_POS_BOTTOM). */
    GtkWidget     *console_pane;
    GtkTextBuffer *console_buffer;
    GtkTextView   *console_view;
    GtkEntry      *console_entry;

    /* Per-session user-configurable settings, set via the
     * "Configure Target" dialog.  All optional — when unset, the
     * old extension-strip heuristic kicks in for the target and
     * gdb inherits the editor's cwd / empty args. */
    char          *cfg_target;
    char          *cfg_args;
    char          *cfg_cwd;
};

/* ── Console pane ─────────────────────────────────────────────────── */

#define MOO_GDB_CONSOLE_PANE_ID "MooGdbConsole"

/* Append `text` to the console buffer with optional `tag_name`
 * for colour coding.  Auto-scrolls so the latest line is visible. */
static void
console_append (MooGdbWin *win, const char *text, const char *tag_name)
{
    if (!win->console_buffer || !text || !*text) return;
    GtkTextIter end;
    gtk_text_buffer_get_end_iter (win->console_buffer, &end);
    if (tag_name)
        gtk_text_buffer_insert_with_tags_by_name (
            win->console_buffer, &end, text, -1, tag_name, NULL);
    else
        gtk_text_buffer_insert (win->console_buffer, &end, text, -1);

    /* Scroll the view so the bottom stays in sight even when the
     * user hasn't focused the pane recently. */
    if (win->console_view) {
        GtkTextMark *insert =
            gtk_text_buffer_get_insert (win->console_buffer);
        gtk_text_view_scroll_mark_onscreen (win->console_view, insert);
    }
}

static void
on_console_signal (G_GNUC_UNUSED MooGdbSession *s,
                   const char *line, gpointer user_data)
{
    console_append ((MooGdbWin *) user_data, line, NULL);
}

static void
on_log_signal (G_GNUC_UNUSED MooGdbSession *s,
               const char *line, gpointer user_data)
{
    console_append ((MooGdbWin *) user_data, line, "log");
}

static void
on_console_error (G_GNUC_UNUSED MooGdbSession *s,
                  const char *msg, gpointer user_data)
{
    MooGdbWin *win = (MooGdbWin *) user_data;
    char *line = g_strdup_printf ("error: %s\n", msg ? msg : "(unknown)");
    console_append (win, line, "error");
    g_free (line);
}

/* User pressed Enter in the entry — forward the line to gdb, then
 * echo it locally so the transcript reads coherently. */
static void
on_console_entry_activate (GtkEntry *entry, gpointer user_data)
{
    MooGdbWin *win = (MooGdbWin *) user_data;
    const char *text = gtk_entry_get_text (entry);
    if (!text || !*text) return;
    /* Echo with a leading "(gdb) " so the user can tell their
     * commands apart from gdb's responses. */
    char *echo = g_strdup_printf ("(gdb) %s\n", text);
    console_append (win, echo, "input");
    g_free (echo);
    if (win->session)
        moo_gdb_session_send_raw (win->session, text);
    gtk_entry_set_text (entry, "");
}

/* Build the console pane widget tree.  Layout:
 *
 *   ┌──────────────────────────────────────┐
 *   │ scrolled-window                       │
 *   │  └ GtkTextView (read-only, mono)      │
 *   ├──────────────────────────────────────┤
 *   │ GtkEntry  ← user types here           │
 *   └──────────────────────────────────────┘
 *
 * Wrapped in a vbox so the entry stays a single line at the bottom
 * regardless of content size in the text view. */
static void
build_console_pane (MooGdbWin *win)
{
    GtkWidget *vbox   = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *scroll = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroll),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand (scroll, TRUE);
    gtk_widget_set_vexpand (scroll, TRUE);

    GtkWidget *view = gtk_text_view_new ();
    gtk_text_view_set_editable      (GTK_TEXT_VIEW (view), FALSE);
    gtk_text_view_set_monospace     (GTK_TEXT_VIEW (view), TRUE);
    gtk_text_view_set_left_margin   (GTK_TEXT_VIEW (view), 6);
    gtk_text_view_set_right_margin  (GTK_TEXT_VIEW (view), 6);
    gtk_text_view_set_top_margin    (GTK_TEXT_VIEW (view), 4);
    gtk_text_view_set_bottom_margin (GTK_TEXT_VIEW (view), 4);
    gtk_text_view_set_wrap_mode     (GTK_TEXT_VIEW (view),
                                     GTK_WRAP_WORD_CHAR);
    gtk_container_add (GTK_CONTAINER (scroll), view);
    gtk_box_pack_start (GTK_BOX (vbox), scroll, TRUE, TRUE, 0);

    /* Three tags for the three stream kinds: dimmed for log lines,
     * red-ish for errors, italic-grey for echoed user input. */
    GtkTextBuffer *buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    gtk_text_buffer_create_tag (buf, "log",
        "foreground", "#7f7f7f", NULL);
    gtk_text_buffer_create_tag (buf, "error",
        "foreground", "#c0392b",
        "weight",     PANGO_WEIGHT_BOLD,
        NULL);
    gtk_text_buffer_create_tag (buf, "input",
        "foreground", "#1a73e8",
        "style",      PANGO_STYLE_ITALIC,
        NULL);

    GtkWidget *entry = gtk_entry_new ();
    gtk_entry_set_placeholder_text (GTK_ENTRY (entry),
        "Type a gdb command (e.g. `print x`, `info threads`) and press Enter");
    gtk_box_pack_start (GTK_BOX (vbox), entry, FALSE, FALSE, 0);
    g_signal_connect (entry, "activate",
        G_CALLBACK (on_console_entry_activate), win);

    gtk_widget_show_all (vbox);

    MooPaneLabel *label = moo_pane_label_new ("utilities-terminal", NULL,
                                              _("GDB Console"),
                                              _("GDB Console"));
    moo_edit_window_add_pane (win->window, MOO_GDB_CONSOLE_PANE_ID,
                              vbox, label, MOO_PANE_POS_BOTTOM);
    moo_pane_label_free (label);

    win->console_pane   = vbox;
    win->console_buffer = buf;
    win->console_view   = GTK_TEXT_VIEW (view);
    win->console_entry  = GTK_ENTRY (entry);
}

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
    /* bp->file must be non-NULL — g_str_hash requires a real C
     * string.  Caller is expected to filter NULL paths before
     * calling us; this is a belt-and-braces guard. */
    if (!bp->file) {
        free_bp (bp);
        return;
    }
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
    /* moo_editor_get_docs returns transfer-full — caller frees with
     * moo_edit_array_free. */
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
        /* MooTextView's left gutter doesn't display marks unless
         * the show-line-marks property is on (the default is off).
         * Turn it on for the view we just dropped a mark in so the
         * gutter actually renders the red dot. */
        g_object_set (view, "show-line-marks", TRUE, NULL);
        break;
    }
    moo_edit_array_free (docs);
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
    g_object_set (view, "show-line-marks", TRUE, NULL);

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
    /* Session signals are released automatically when the session
     * is unref'd in moo_gdb_win_free, so we don't need to track
     * handler ids individually. */
    g_signal_connect (win->session, "breakpoint-added",
                      G_CALLBACK (on_session_bp_added), win);
    g_signal_connect (win->session, "breakpoint-removed",
                      G_CALLBACK (on_session_bp_removed), win);
    g_signal_connect (win->session, "stopped",
                      G_CALLBACK (on_session_stopped), win);
    g_signal_connect (win->session, "running",
                      G_CALLBACK (on_session_running), win);
    g_signal_connect (win->session, "exited",
                      G_CALLBACK (on_session_exited), win);
    /* Funnel console / log / error stream records into the
     * bottom-pane transcript.  Errors used to pop a dialog; now
     * they're appended to the pane in a bold red tag, which is
     * less interrupting and survives across multiple errors in a
     * single command burst. */
    g_signal_connect (win->session, "console-output",
                      G_CALLBACK (on_console_signal), win);
    g_signal_connect (win->session, "log-output",
                      G_CALLBACK (on_log_signal), win);
    g_signal_connect (win->session, "error",
                      G_CALLBACK (on_console_error), win);
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

    /* Pick the target binary.  Priority order:
     *   1. Whatever the user set via "Configure Target".
     *   2. Heuristic: strip the extension from the active doc's
     *      filename (foo.c → ./foo) — works for trivial single-
     *      file builds. */
    char *target = NULL;
    if (win->cfg_target && *win->cfg_target) {
        target = g_strdup (win->cfg_target);
    } else {
        MooEdit *doc = moo_edit_window_get_active_doc (win->window);
        if (doc) {
            char *file = moo_edit_get_filename (doc);
            if (file) {
                char *dot = strrchr (file, '.');
                if (dot && dot > strrchr (file, '/'))
                    target = g_strndup (file, dot - file);
                else
                    target = g_strdup (file);
                g_free (file);
            }
        }
    }
    if (target) {
        moo_gdb_session_set_target (s, target);
        g_free (target);
    }

    /* Apply optional cwd and argv. */
    if (win->cfg_cwd && *win->cfg_cwd)
        moo_gdb_session_set_cwd (s, win->cfg_cwd);

    if (win->cfg_args && *win->cfg_args) {
        GError *err = NULL;
        char **argv = NULL;
        int    argc = 0;
        if (g_shell_parse_argv (win->cfg_args, &argc, &argv, &err)) {
            moo_gdb_session_set_args (s, (const char *const *) argv);
            g_strfreev (argv);
        } else {
            console_append (win,
                "warning: couldn't parse program arguments: ", "log");
            console_append (win, err->message, "error");
            console_append (win, "\n", "error");
            g_error_free (err);
        }
    } else {
        /* Clear any previously-set args so a stale list doesn't
         * carry between runs. */
        moo_gdb_session_set_args (s, NULL);
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

/* ── Configure-target dialog ─────────────────────────────────────── */

/* Helper: build a labelled-entry row "label: [entry] [browse?]" and
 * pack it into `grid` at `row`.  Returns the entry so the caller
 * can stash a pointer for later read-back. */
static GtkEntry *
add_labelled_entry (GtkGrid *grid, int row,
                    const char *label_text, const char *initial,
                    gboolean with_browse)
{
    GtkWidget *label = gtk_label_new (label_text);
    gtk_label_set_xalign (GTK_LABEL (label), 1.0);
    gtk_widget_set_hexpand (label, FALSE);
    gtk_grid_attach (grid, label, 0, row, 1, 1);

    GtkWidget *entry = gtk_entry_new ();
    if (initial) gtk_entry_set_text (GTK_ENTRY (entry), initial);
    gtk_widget_set_hexpand (entry, TRUE);
    gtk_entry_set_width_chars (GTK_ENTRY (entry), 40);
    gtk_grid_attach (grid, entry, 1, row, 1, 1);
    (void) with_browse;   /* file-chooser button reserved for later */
    return GTK_ENTRY (entry);
}

void
moo_gdb_win_configure (MooGdbWin *win)
{
    g_return_if_fail (win != NULL);

    GtkWidget *dlg = gtk_dialog_new_with_buttons (
        _("Configure Debug Target"),
        GTK_WINDOW (win->window),
        (GtkDialogFlags) (GTK_DIALOG_DESTROY_WITH_PARENT
                          | GTK_DIALOG_MODAL),
        _("_Cancel"), GTK_RESPONSE_CANCEL,
        _("_OK"),     GTK_RESPONSE_OK,
        (const char *) NULL);
    gtk_dialog_set_default_response (GTK_DIALOG (dlg), GTK_RESPONSE_OK);

    GtkWidget *content = gtk_dialog_get_content_area (GTK_DIALOG (dlg));
    GtkWidget *grid    = gtk_grid_new ();
    gtk_grid_set_row_spacing    (GTK_GRID (grid), 6);
    gtk_grid_set_column_spacing (GTK_GRID (grid), 8);
    g_object_set (grid, "margin", 12, NULL);
    gtk_box_pack_start (GTK_BOX (content), grid, TRUE, TRUE, 0);

    GtkEntry *target_entry = add_labelled_entry (GTK_GRID (grid), 0,
        _("Target binary:"), win->cfg_target, TRUE);
    gtk_entry_set_placeholder_text (target_entry,
        _("e.g. ./a.out — leave empty to auto-derive from current source"));

    GtkEntry *args_entry = add_labelled_entry (GTK_GRID (grid), 1,
        _("Program arguments:"), win->cfg_args, FALSE);
    gtk_entry_set_placeholder_text (args_entry,
        _("Shell-style: my_arg \"quoted with space\" --verbose"));

    GtkEntry *cwd_entry = add_labelled_entry (GTK_GRID (grid), 2,
        _("Working directory:"), win->cfg_cwd, TRUE);
    gtk_entry_set_placeholder_text (cwd_entry,
        _("Empty: inherit medit's cwd"));

    gtk_widget_show_all (dlg);

    if (gtk_dialog_run (GTK_DIALOG (dlg)) == GTK_RESPONSE_OK)
    {
        g_free (win->cfg_target);
        g_free (win->cfg_args);
        g_free (win->cfg_cwd);
        win->cfg_target = g_strdup (gtk_entry_get_text (target_entry));
        win->cfg_args   = g_strdup (gtk_entry_get_text (args_entry));
        win->cfg_cwd    = g_strdup (gtk_entry_get_text (cwd_entry));
        console_append (win, "Debug target updated.\n", "log");
    }
    gtk_widget_destroy (dlg);
}

MooGdbWin *
moo_gdb_win_new (MooEditWindow *window)
{
    MooGdbWin *win = g_new0 (MooGdbWin, 1);
    win->window      = window;
    win->bp_by_file  = g_hash_table_new_full (g_str_hash, g_str_equal,
                                               g_free, free_file_table);
    win->bp_by_number = g_hash_table_new (g_direct_hash, g_direct_equal);

    /* Build the console transcript pane up-front so the user sees
     * a greeting line even before they start a debug session. */
    build_console_pane (win);
    console_append (win,
        "GDB Console — type a command and press Enter, "
        "or use Ctrl+F5 to start debugging.\n", "log");

    /* Note: gutter-click breakpoint toggling and doc-loaded
     * re-attach were tried via an emission hook on
     * line-mark-clicked + a connect on a doc-loaded editor signal,
     * but the signal lookup races plugin init (the class isn't
     * always initialized yet) and there's no doc-loaded signal on
     * MooEditor.  The F9 menu action covers the common case for
     * now; per-view connection on a doc-show signal can be added
     * later when those concerns are sorted out. */
    return win;
}

void
moo_gdb_win_free (MooGdbWin *win)
{
    if (!win) return;

    if (win->console_pane)
        moo_edit_window_remove_pane (win->window, MOO_GDB_CONSOLE_PANE_ID);

    clear_exec_mark (win);

    if (win->session) {
        moo_gdb_session_quit (win->session);
        g_object_unref (win->session);
    }
    g_hash_table_destroy (win->bp_by_file);
    g_hash_table_destroy (win->bp_by_number);
    g_free (win->cfg_target);
    g_free (win->cfg_args);
    g_free (win->cfg_cwd);
    g_free (win);
}
