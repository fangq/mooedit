/*
 *   moostock.h
 *
 *   Copyright (C) 2004-2010 by Yevgen Muntyan <emuntyan@users.sourceforge.net>
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with medit.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MOOUTILS_STOCK_H
#define MOOUTILS_STOCK_H

#include <gtk/gtk.h>
#include "mooutils/moo-gtk3-compat.h"

G_BEGIN_DECLS


/* GTK3 migration: every name below is a freedesktop icon-naming-spec name
 * present in Adwaita / hicolor. The legacy "moo-*" names worked under GTK2
 * because moostock.c registered them with a GtkIconFactory, but GTK3's
 * "icon-name" property and gtk_image_new_from_icon_name() bypass the
 * factory and query GtkIconTheme directly, which never knew the moo-* names. */
#define MOO_STOCK_TERMINAL              "utilities-terminal"
#define MOO_STOCK_KEYBOARD              "preferences-desktop-keyboard"
#define MOO_STOCK_MENU                  "view-list"
#define MOO_STOCK_RESTART               "view-refresh"

#define MOO_STOCK_DOC_DELETED           "dialog-error"
#define MOO_STOCK_DOC_MODIFIED_ON_DISK  "dialog-warning"
#define MOO_STOCK_DOC_MODIFIED          "document-save"

#define MOO_STOCK_NEW_WINDOW            "window-new"

#define MOO_STOCK_FILE_SELECTOR         "system-file-manager"
#define MOO_STOCK_FILE_BOOKMARK         "user-bookmarks"
#define MOO_STOCK_FOLDER                "folder"
#define MOO_STOCK_FILE                  "text-x-generic"
#define MOO_STOCK_NEW_FOLDER            "folder-new"

#define MOO_STOCK_SAVE_NONE             "edit-clear-all"
#define MOO_STOCK_SAVE_SELECTED         "document-save"

#define MOO_STOCK_NEW_PROJECT           "document-new"
#define MOO_STOCK_OPEN_PROJECT          "document-open"
#define MOO_STOCK_CLOSE_PROJECT         "window-close"
#define MOO_STOCK_PROJECT_OPTIONS       "preferences-system"
#define MOO_STOCK_BUILD                 "applications-development"
#define MOO_STOCK_COMPILE               "applications-development"
#define MOO_STOCK_EXECUTE               "system-run"

#define MOO_STOCK_FIND_IN_FILES         "edit-find"
#define MOO_STOCK_FIND_FILE             "edit-find"

#define MOO_STOCK_FILE_COPY             "edit-copy"
#define MOO_STOCK_FILE_MOVE             "go-jump"
#define MOO_STOCK_FILE_LINK             "insert-link"
#define MOO_STOCK_FILE_SAVE_AS          "document-save-as"
#define MOO_STOCK_FILE_SAVE_COPY        "document-save-as"

#define MOO_STOCK_EDIT_BOOKMARK         "user-bookmarks"

#define MOO_STOCK_PLUGINS               "preferences-system"


void        _moo_stock_init                 (void);


G_END_DECLS

#endif /* MOOUTILS_STOCK_H */
