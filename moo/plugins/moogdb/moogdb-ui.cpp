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

#include "mooutils/mooi18n.h"
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
