/*
 *   mooterminal.c
 *
 *   Native VTE terminal plugin for medit — replaces terminal.py
 *   No Python dependency required.
 *
 *   Copyright (C) 2004-2010 by Yevgen Muntyan <emuntyan@users.sourceforge.net>
 *   Copyright (C) 2024-2025 — C port
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gtk/gtk.h>
#include <vte/vte.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

#include "mooedit/mooplugin.h"
#include "mooedit/mooplugin-macro.h"
#include "mooedit/mooeditwindow.h"
#include "mooedit/mooedit.h"
#include "mooutils/moopane.h"
#include "mooutils/moostock.h"
#include "mooutils/mooprefs.h"
#include "mooutils/mooi18n.h"

/* ================================================================ */
/* Preferences keys                                                 */
/* ================================================================ */

#define TERMINAL_PLUGIN_ID      "Terminal"
#define COLOR_SCHEME_KEY        "Plugins/Terminal/color_scheme"
#define SHELL_KEY               "Plugins/Terminal/shell"
#define FONT_KEY                "Plugins/Terminal/font"
#define SCROLLBACK_KEY          "Plugins/Terminal/scrollback_lines"

/* ================================================================ */
/* Color schemes — ported from terminal.py (stolen from Konsole)    */
/* ================================================================ */

typedef struct {
    const char *name;
    const char *fg;
    const char *bg;
    const char *palette[16];  /* 16 ANSI colors */
    gboolean    has_colors;
} TermColorScheme;

static const TermColorScheme color_schemes[] = {
    { "Default", NULL, NULL, {NULL}, FALSE },
    { "Black on White",
      "#000000", "#ffffff",
      { "#000000", "#b21818", "#18b218", "#b26818",
        "#1818b2", "#b218b2", "#18b2b2", "#b2b2b2",
        "#686868", "#ff5454", "#54ff54", "#ffff54",
        "#5454ff", "#ff54ff", "#54ffff", "#ffffff" },
      TRUE },
    { "Black on Light Yellow",
      "#000000", "#ffffdd",
      { "#000000", "#b21818", "#18b218", "#b26818",
        "#1818b2", "#b218b2", "#18b2b2", "#b2b2b2",
        "#686868", "#ff5454", "#54ff54", "#ffff54",
        "#5454ff", "#ff54ff", "#54ffff", "#ffffff" },
      TRUE },
    { "Marble",
      "#ffffff", "#000000",
      { "#000000", "#b21818", "#18b218", "#b26818",
        "#1818b2", "#b218b2", "#18b2b2", "#b2b2b2",
        "#686868", "#ff5454", "#54ff54", "#ffff54",
        "#5454ff", "#ff54ff", "#54ffff", "#ffffff" },
      TRUE },
    { "Green on Black",
      "#18f018", "#000000",
      { "#000000", "#b21818", "#18b218", "#b26818",
        "#1818b2", "#b218b2", "#18b2b2", "#b2b2b2",
        "#686868", "#ff5454", "#54ff54", "#ffff54",
        "#5454ff", "#ff54ff", "#54ffff", "#ffffff" },
      TRUE },
    { "Paper, Light",
      "#000000", "#ffffff",
      { "#000000", "#b21818", "#18b218", "#b26818",
        "#1818b2", "#b218b2", "#18b2b2", "#b2b2b2",
        "#686868", "#ff5454", "#54ff54", "#ffff54",
        "#5454ff", "#ff54ff", "#54ffff", "#ffffff" },
      TRUE },
    { "Paper",
      "#000000", "#ffffff",
      { "#000000", "#b21818", "#18b218", "#b26818",
        "#1818b2", "#b218b2", "#18b2b2", "#b2b2b2",
        "#686868", "#ff5454", "#54ff54", "#ffff54",
        "#5454ff", "#ff54ff", "#54ffff", "#ffffff" },
      TRUE },
    { "Linux Colors",
      "#b2b2b2", "#000000",
      { "#000000", "#b21818", "#18b218", "#b26818",
        "#1818b2", "#b218b2", "#18b2b2", "#b2b2b2",
        "#686868", "#ff5454", "#54ff54", "#ffff54",
        "#5454ff", "#ff54ff", "#54ffff", "#ffffff" },
      TRUE },
    { "VIM Colors",
      "#000000", "#ffffff",
      { "#000000", "#c00000", "#008000", "#808000",
        "#0000c0", "#c000c0", "#008080", "#c0c0c0",
        "#808080", "#ff6060", "#00ff00", "#ffff00",
        "#8080ff", "#ff40ff", "#00ffff", "#ffffff" },
      TRUE },
    { "White on Black",
      "#ffffff", "#000000",
      { "#000000", "#b21818", "#18b218", "#b26818",
        "#1818b2", "#b218b2", "#18b2b2", "#b2b2b2",
        "#686868", "#ff5454", "#54ff54", "#ffff54",
        "#5454ff", "#ff54ff", "#54ffff", "#ffffff" },
      TRUE },
};

#define N_COLOR_SCHEMES (sizeof(color_schemes) / sizeof(color_schemes[0]))

static const TermColorScheme *
find_color_scheme (const char *name)
{
    guint i;
    if (!name || !name[0])
        return &color_schemes[0];
    for (i = 0; i < N_COLOR_SCHEMES; i++) {
        if (g_strcmp0 (color_schemes[i].name, name) == 0)
            return &color_schemes[i];
    }
    return &color_schemes[0];
}

static void
apply_color_scheme (VteTerminal *term, const TermColorScheme *cs)
{
    if (!cs || !cs->has_colors)
        return;

    GdkRGBA fg, bg;
    GdkRGBA palette[16];
    int i;

    gdk_rgba_parse (&fg, cs->fg);
    gdk_rgba_parse (&bg, cs->bg);

    for (i = 0; i < 16; i++)
        gdk_rgba_parse (&palette[i], cs->palette[i]);

    vte_terminal_set_color_foreground (term, &fg);
    vte_terminal_set_color_background (term, &bg);
    vte_terminal_set_colors (term, &fg, &bg, palette, 16);
}

/* ================================================================ */
/* Shell detection                                                  */
/* ================================================================ */

static char *
get_user_shell (void)
{
    const char *shell;

    /* Check prefs first */
    shell = moo_prefs_get_string (SHELL_KEY);
    if (shell && shell[0])
        return g_strdup (shell);

    /* Try environment */
    shell = g_getenv ("SHELL");
    if (shell && shell[0])
        return g_strdup (shell);

    /* Try passwd */
#ifndef __WIN32__
    {
        struct passwd *pw = getpwuid (getuid ());
        if (pw && pw->pw_shell && pw->pw_shell[0])
            return g_strdup (pw->pw_shell);
    }
#endif

    return g_strdup ("/bin/sh");
}

static gboolean
shell_supports_pushd (const char *shell)
{
    const char *name = strrchr (shell, '/');
    name = name ? name + 1 : shell;
    return g_strcmp0 (name, "bash") == 0;
}

/* ================================================================ */
/* Terminal widget                                                  */
/* ================================================================ */

static void
terminal_spawn (VteTerminal *term)
{
    char *shell = get_user_shell ();
    char *argv[] = { shell, NULL };

    /* Try spawn_async first (VTE >= 0.63), fall back to spawn_sync */
#if VTE_CHECK_VERSION(0, 63, 0)
    vte_terminal_spawn_async (term,
        VTE_PTY_DEFAULT, NULL, argv, NULL,
        G_SPAWN_DEFAULT, NULL, NULL, NULL,
        -1, NULL, NULL, NULL);
#elif VTE_CHECK_VERSION(0, 48, 0)
    vte_terminal_spawn_sync (term,
        VTE_PTY_DEFAULT, NULL, argv, NULL,
        G_SPAWN_DEFAULT, NULL, NULL, NULL, NULL, NULL);
#else
    vte_terminal_fork_command_full (term,
        VTE_PTY_DEFAULT, NULL, argv, NULL,
        G_SPAWN_DEFAULT, NULL, NULL, NULL, NULL);
#endif

    g_free (shell);
}

static void
on_child_exited (VteTerminal *term, gint status, gpointer user_data)
{
    (void)status;
    (void)user_data;
    vte_terminal_reset (term, TRUE, TRUE);
    terminal_spawn (term);
}

static VteTerminal *
create_terminal (void)
{
    VteTerminal *term;
    const char *cs_name;
    const TermColorScheme *cs;
    const char *font_name;
    int scrollback;

    term = VTE_TERMINAL (vte_terminal_new ());

    /* Color scheme */
    cs_name = moo_prefs_get_string (COLOR_SCHEME_KEY);
    cs = find_color_scheme (cs_name);
    apply_color_scheme (term, cs);

    /* Font */
    font_name = moo_prefs_get_string (FONT_KEY);
    if (font_name && font_name[0]) {
        PangoFontDescription *fd = pango_font_description_from_string (font_name);
        if (fd) {
            vte_terminal_set_font (term, fd);
            pango_font_description_free (fd);
        }
    }

    /* Scrollback */
    scrollback = moo_prefs_get_int (SCROLLBACK_KEY);
    if (scrollback <= 0)
        scrollback = 1000000;
    vte_terminal_set_scrollback_lines (term, scrollback);

    /* Size */
    vte_terminal_set_size (term, vte_terminal_get_column_count (term), 10);
    gtk_widget_set_size_request (GTK_WIDGET (term), 10, 10);

    return term;
}

/* ================================================================ */
/* Context menu                                                     */
/* ================================================================ */

static void
on_copy_activate (GtkMenuItem *item, VteTerminal *term)
{
    (void)item;
#if VTE_CHECK_VERSION(0, 50, 0)
    vte_terminal_copy_clipboard_format (term, VTE_FORMAT_TEXT);
#else
    vte_terminal_copy_clipboard (term);
#endif
}

static void
on_paste_activate (GtkMenuItem *item, VteTerminal *term)
{
    (void)item;
    vte_terminal_paste_clipboard (term);
}

static void
on_font_activate (GtkMenuItem *item, VteTerminal *term)
{
    GtkWidget *dlg;
    (void)item;

    dlg = gtk_font_chooser_dialog_new ("Pick a Font",
            GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (term))));

    {
        const PangoFontDescription *old_font = vte_terminal_get_font (term);
        if (old_font)
            gtk_font_chooser_set_font_desc (GTK_FONT_CHOOSER (dlg), old_font);
    }

    if (gtk_dialog_run (GTK_DIALOG (dlg)) == GTK_RESPONSE_OK) {
        PangoFontDescription *fd = gtk_font_chooser_get_font_desc (GTK_FONT_CHOOSER (dlg));
        if (fd) {
            vte_terminal_set_font (term, fd);
            char *name = pango_font_description_to_string (fd);
            moo_prefs_set_string (FONT_KEY, name);
            g_free (name);
            pango_font_description_free (fd);
        }
    }

    gtk_widget_destroy (dlg);
}

static void
on_scheme_activate (GtkMenuItem *item, VteTerminal *term)
{
    const char *name = g_object_get_data (G_OBJECT (item), "scheme-name");
    const TermColorScheme *cs = find_color_scheme (name);
    apply_color_scheme (term, cs);
    moo_prefs_set_string (COLOR_SCHEME_KEY, name);
}

static gboolean
on_button_press (VteTerminal *term, GdkEventButton *event, gpointer data)
{
    GtkWidget *menu, *item, *submenu;
    guint i;
    (void)data;

    if (event->button != 3 || event->type != GDK_BUTTON_PRESS)
        return FALSE;

    menu = gtk_menu_new ();

    /* Copy */
    item = gtk_menu_item_new_with_label ("Copy");
    g_signal_connect (item, "activate", G_CALLBACK (on_copy_activate), term);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

    /* Paste */
    item = gtk_menu_item_new_with_label ("Paste");
    g_signal_connect (item, "activate", G_CALLBACK (on_paste_activate), term);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

    gtk_menu_shell_append (GTK_MENU_SHELL (menu),
                           gtk_separator_menu_item_new ());

    /* Font */
    item = gtk_menu_item_new_with_label ("Select Font...");
    g_signal_connect (item, "activate", G_CALLBACK (on_font_activate), term);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

    /* Color Scheme submenu */
    item = gtk_menu_item_new_with_label ("Color Scheme");
    submenu = gtk_menu_new ();
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (item), submenu);

    for (i = 0; i < N_COLOR_SCHEMES; i++) {
        GtkWidget *cs_item = gtk_menu_item_new_with_label (color_schemes[i].name);
        g_object_set_data (G_OBJECT (cs_item), "scheme-name",
                           (gpointer)color_schemes[i].name);
        g_signal_connect (cs_item, "activate",
                          G_CALLBACK (on_scheme_activate), term);
        gtk_menu_shell_append (GTK_MENU_SHELL (submenu), cs_item);
    }

    gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

    gtk_widget_show_all (menu);
    gtk_menu_popup_at_pointer (GTK_MENU (menu), (GdkEvent *)event);

    return TRUE;
}

/* ================================================================ */
/* "cd to document directory" support                               */
/* ================================================================ */

static void
terminal_chdir (VteTerminal *term, const char *path, gboolean use_pushd)
{
    char *command;
    const char *cmd = use_pushd ? "pushd" : "cd";

    if (!path || !path[0])
        return;

    command = g_strdup_printf ("%s '%s'\n", cmd, path);
    vte_terminal_feed_child (term, command, -1);
    g_free (command);
}

/* ================================================================ */
/* Plugin structure                                                 */
/* ================================================================ */

typedef struct {
    MooWinPlugin parent;
    VteTerminal *terminal;
    MooPane     *pane;
    gulong       child_exited_id;
    gulong       icon_title_id;
    gboolean     support_pushd;
} TerminalWindowPlugin;

static void
on_icon_title_changed (VteTerminal *term, gpointer data)
{
    TerminalWindowPlugin *plugin = data;
    const char *title;

    title = vte_terminal_get_icon_title (term);
    if (title && plugin->pane)
        moo_pane_set_frame_text (plugin->pane, title);
}

static gboolean
terminal_window_plugin_create (TerminalWindowPlugin *plugin)
{
    MooEditWindow *window;
    MooPaneLabel *label;
    GtkWidget *frame, *hbox, *scrollbar;

    window = MOO_WIN_PLUGIN (plugin)->window;

    label = moo_pane_label_new (MOO_STOCK_TERMINAL, NULL,
                                _("Terminal"),
                                _("Terminal"));

    plugin->terminal = create_terminal ();

    plugin->child_exited_id = g_signal_connect (plugin->terminal,
        "child-exited", G_CALLBACK (on_child_exited), plugin);

    g_signal_connect (plugin->terminal, "button-press-event",
                      G_CALLBACK (on_button_press), plugin);

    terminal_spawn (plugin->terminal);

    /* Build the container */
    frame = gtk_frame_new (NULL);
    hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add (GTK_CONTAINER (frame), hbox);
    gtk_box_pack_start (GTK_BOX (hbox), GTK_WIDGET (plugin->terminal),
                        TRUE, TRUE, 0);

    scrollbar = gtk_scrollbar_new (GTK_ORIENTATION_VERTICAL,
                    gtk_scrollable_get_vadjustment (GTK_SCROLLABLE (plugin->terminal)));
    gtk_box_pack_start (GTK_BOX (hbox), scrollbar, FALSE, FALSE, 0);
    gtk_widget_show_all (frame);

    plugin->pane = moo_edit_window_add_pane (window,
        TERMINAL_PLUGIN_ID, frame, label, MOO_PANE_POS_BOTTOM);

    plugin->icon_title_id = g_signal_connect (plugin->terminal,
        "icon-title-changed", G_CALLBACK (on_icon_title_changed), plugin);

    on_icon_title_changed (plugin->terminal, plugin);

    moo_pane_label_free (label);

    return TRUE;
}

static void
terminal_window_plugin_destroy (TerminalWindowPlugin *plugin)
{
    MooEditWindow *window = MOO_WIN_PLUGIN (plugin)->window;

    if (plugin->terminal) {
        g_signal_handler_disconnect (plugin->terminal, plugin->child_exited_id);
        g_signal_handler_disconnect (plugin->terminal, plugin->icon_title_id);
    }

    moo_edit_window_remove_pane (window, TERMINAL_PLUGIN_ID);
    plugin->terminal = NULL;
    plugin->pane = NULL;
}

/* ================================================================ */
/* Plugin registration — follows ctags plugin pattern               */
/* ================================================================ */

typedef struct {
    MooPlugin parent;
} TerminalPlugin;

static gboolean
terminal_plugin_init (G_GNUC_UNUSED TerminalPlugin *plugin)
{
    /* Register preference keys */
    moo_prefs_new_key_string (COLOR_SCHEME_KEY, "Default");
    moo_prefs_new_key_string (SHELL_KEY, NULL);
    moo_prefs_new_key_string (FONT_KEY, NULL);
    moo_prefs_new_key_int (SCROLLBACK_KEY, 1000000);
    return TRUE;
}

static void
terminal_plugin_deinit (G_GNUC_UNUSED TerminalPlugin *plugin)
{
}

MOO_PLUGIN_DEFINE_INFO (terminal,
                        "Terminal",
                        "Embedded terminal emulator",
                        "Yevgen Muntyan <emuntyan@users.sourceforge.net>",
                        MOO_VERSION)

MOO_WIN_PLUGIN_DEFINE (Terminal, terminal)

MOO_PLUGIN_DEFINE (Terminal, terminal,
                   NULL, NULL, NULL, NULL, NULL,
                   terminal_window_plugin_get_type (),
                   0)

gboolean
_moo_terminal_plugin_init (void)
{
    MooPluginParams params = { TRUE, TRUE };
    return moo_plugin_register (TERMINAL_PLUGIN_ID,
                                terminal_plugin_get_type (),
                                &terminal_plugin_info,
                                &params);
}