/*
 * moo-gtk3-compat.h
 *
 * GTK2 → GTK3 compatibility definitions for medit.
 *
 * This header provides backward-compatible macros for APIs that were
 * fully removed in GTK3 (not just deprecated). For deprecated-but-still-
 * present functions (gtk_widget_render_icon, gtk_rc_parse_string,
 * gtk_widget_modify_cursor), GTK3 still provides them so we do NOT
 * redefine them here — just suppress deprecation warnings at call sites.
 *
 * Include AFTER <gtk/gtk.h>.
 */

#ifndef MOO_GTK3_COMPAT_H
#define MOO_GTK3_COMPAT_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

/* ═══════════════════════════════════════════════════════════════════════
 * GTK_STOCK_* → freedesktop icon name compatibility
 *
 * GTK 3.10+ deprecates stock items. GTK 3.x still defines them but
 * future GTK4 removes them. Provide fallback definitions in case
 * the GTK headers no longer define them (GTK4 or stripped builds).
 * ═══════════════════════════════════════════════════════════════════════ */

#ifndef GTK_STOCK_NEW
#define GTK_STOCK_NEW            "document-new"
#define GTK_STOCK_OPEN           "document-open"
#define GTK_STOCK_SAVE           "document-save"
#define GTK_STOCK_SAVE_AS        "document-save-as"
#define GTK_STOCK_CLOSE          "window-close"
#define GTK_STOCK_QUIT           "application-exit"
#define GTK_STOCK_UNDO           "edit-undo"
#define GTK_STOCK_REDO           "edit-redo"
#define GTK_STOCK_CUT            "edit-cut"
#define GTK_STOCK_COPY           "edit-copy"
#define GTK_STOCK_PASTE          "edit-paste"
#define GTK_STOCK_DELETE         "edit-delete"
#define GTK_STOCK_FIND           "edit-find"
#define GTK_STOCK_FIND_AND_REPLACE "edit-find-replace"
#define GTK_STOCK_PRINT          "document-print"
#define GTK_STOCK_PRINT_PREVIEW  "document-print-preview"
#define GTK_STOCK_PROPERTIES     "document-properties"
#define GTK_STOCK_PREFERENCES    "preferences-system"
#define GTK_STOCK_HELP           "help-browser"
#define GTK_STOCK_ABOUT          "help-about"
#define GTK_STOCK_REFRESH        "view-refresh"
#define GTK_STOCK_EXECUTE        "system-run"
#define GTK_STOCK_STOP           "process-stop"
#define GTK_STOCK_OK             "gtk-ok"
#define GTK_STOCK_CANCEL         "gtk-cancel"
#define GTK_STOCK_APPLY          "gtk-apply"
#define GTK_STOCK_YES            "gtk-yes"
#define GTK_STOCK_NO             "gtk-no"
#define GTK_STOCK_GO_BACK        "go-previous"
#define GTK_STOCK_GO_FORWARD     "go-next"
#define GTK_STOCK_GO_UP          "go-up"
#define GTK_STOCK_GO_DOWN        "go-down"
#define GTK_STOCK_ADD            "list-add"
#define GTK_STOCK_REMOVE         "list-remove"
#define GTK_STOCK_CLEAR          "edit-clear"
#define GTK_STOCK_BOLD           "format-text-bold"
#define GTK_STOCK_ITALIC         "format-text-italic"
#define GTK_STOCK_UNDERLINE      "format-text-underline"
#define GTK_STOCK_STRIKETHROUGH  "format-text-strikethrough"
#define GTK_STOCK_INDENT         "format-indent-more"
#define GTK_STOCK_UNINDENT       "format-indent-less"
#define GTK_STOCK_ZOOM_IN        "zoom-in"
#define GTK_STOCK_ZOOM_OUT       "zoom-out"
#define GTK_STOCK_ZOOM_100       "zoom-original"
#define GTK_STOCK_ZOOM_FIT       "zoom-fit-best"
#define GTK_STOCK_SPELL_CHECK    "tools-check-spelling"
#define GTK_STOCK_SELECT_ALL     "edit-select-all"
#define GTK_STOCK_SELECT_COLOR   "color-picker"
#define GTK_STOCK_SELECT_FONT    "font-select"
#define GTK_STOCK_SORT_ASCENDING  "view-sort-ascending"
#define GTK_STOCK_SORT_DESCENDING "view-sort-descending"
#define GTK_STOCK_EDIT           "document-edit"
#define GTK_STOCK_DIALOG_ERROR   "dialog-error"
#define GTK_STOCK_DIALOG_WARNING "dialog-warning"
#define GTK_STOCK_DIALOG_INFO    "dialog-information"
#define GTK_STOCK_DIALOG_QUESTION "dialog-question"
#define GTK_STOCK_DIALOG_AUTHENTICATION "dialog-password"
#define GTK_STOCK_FILE           "text-x-generic"
#define GTK_STOCK_DIRECTORY      "folder"
#define GTK_STOCK_JUMP_TO        "go-jump"
#define GTK_STOCK_GOTO_TOP       "go-top"
#define GTK_STOCK_GOTO_BOTTOM    "go-bottom"
#define GTK_STOCK_GOTO_FIRST     "go-first"
#define GTK_STOCK_GOTO_LAST      "go-last"
#define GTK_STOCK_HOME           "go-home"
#define GTK_STOCK_INFO           "dialog-information"
#define GTK_STOCK_MEDIA_PLAY     "media-playback-start"
#define GTK_STOCK_MEDIA_PAUSE    "media-playback-pause"
#define GTK_STOCK_MEDIA_STOP     "media-playback-stop"
#define GTK_STOCK_FULLSCREEN     "view-fullscreen"
#define GTK_STOCK_LEAVE_FULLSCREEN "view-restore"
#define GTK_STOCK_HARDDISK       "drive-harddisk"
#define GTK_STOCK_NETWORK        "network-workgroup"
#define GTK_STOCK_MISSING_IMAGE  "image-missing"
#define GTK_STOCK_PAGE_SETUP     "document-page-setup"
#define GTK_STOCK_REVERT_TO_SAVED "document-revert"
#define GTK_STOCK_DISCARD        "edit-delete"
#define GTK_STOCK_COLOR_PICKER   "color-picker"
#define GTK_STOCK_CONNECT        "network-connect"
#define GTK_STOCK_DISCONNECT     "network-disconnect"
#define GTK_STOCK_DND            "text-x-generic"
#define GTK_STOCK_DND_MULTIPLE   "text-x-generic"
#define GTK_STOCK_CONVERT        "gtk-convert"
#define GTK_STOCK_INDEX          "view-list"
#define GTK_STOCK_JUSTIFY_CENTER "format-justify-center"
#define GTK_STOCK_JUSTIFY_FILL   "format-justify-fill"
#define GTK_STOCK_JUSTIFY_LEFT   "format-justify-left"
#define GTK_STOCK_JUSTIFY_RIGHT  "format-justify-right"
#define GTK_STOCK_ORIENTATION_PORTRAIT  "orientation-portrait"
#define GTK_STOCK_ORIENTATION_LANDSCAPE "orientation-landscape"
#endif /* GTK_STOCK_NEW */


/* ═══════════════════════════════════════════════════════════════════════
 * Deprecated-but-present functions
 *
 * GTK 3.x still provides these in gtk/deprecated/ headers:
 *   - gtk_widget_render_icon()
 *   - gtk_widget_render_icon_pixbuf()
 *   - gtk_rc_parse_string()
 *   - gtk_widget_modify_cursor()
 *   - gtk_widget_modify_style()
 *   - gtk_widget_get_modifier_style()
 *
 * We do NOT redefine them. They produce deprecation warnings but
 * compile and link fine. Suppress warnings at call sites if needed:
 *
 *   G_GNUC_BEGIN_IGNORE_DEPRECATIONS
 *   gtk_widget_render_icon (...);
 *   G_GNUC_END_IGNORE_DEPRECATIONS
 * ═══════════════════════════════════════════════════════════════════════ */


/* ═══════════════════════════════════════════════════════════════════════
 * Fully removed APIs — provide compat macros/wrappers
 * ═══════════════════════════════════════════════════════════════════════ */

/* gdk_cursor_new() — removed in favor of gdk_cursor_new_for_display().
   GTK 3.16+ removed the bare gdk_cursor_new. */
#ifndef gdk_cursor_new
#define gdk_cursor_new(cursor_type) \
    gdk_cursor_new_for_display (gdk_display_get_default (), (cursor_type))
#endif

/* gdk_cursor_unref() — removed, mapped to g_object_unref */
#ifndef gdk_cursor_unref
#define gdk_cursor_unref(cursor) g_object_unref (cursor)
#endif


/* ═══════════════════════════════════════════════════════════════════════
 * Widget allocation helper
 *
 * Convenience to get a widget's GdkRectangle allocation inline.
 * Used in moobigpaned.c etc.
 * ═══════════════════════════════════════════════════════════════════════ */

static inline GdkRectangle
moo_widget_get_alloc (GtkWidget *widget)
{
    GdkRectangle alloc;
    gtk_widget_get_allocation (widget, (GtkAllocation*) &alloc);
    return alloc;
}


/* ═══════════════════════════════════════════════════════════════════════
 * GdkRegion → cairo_region_t compatibility
 *
 * GdkRegion was removed in GTK3 and replaced by cairo_region_t.
 * ═══════════════════════════════════════════════════════════════════════ */

/* Type alias */
typedef cairo_region_t GdkRegion;

/* GdkRegion functions → cairo_region equivalents */
#define gdk_region_new()                cairo_region_create ()
#define gdk_region_destroy(r)           cairo_region_destroy (r)
#define gdk_region_copy(r)              cairo_region_copy (r)
#define gdk_region_empty(r)             cairo_region_is_empty (r)
#define gdk_region_equal(r1,r2)         cairo_region_equal (r1, r2)
#define gdk_region_union_with_rect(r,rect) \
    cairo_region_union_rectangle (r, rect)
#define gdk_region_union(r1,r2)         cairo_region_union (r1, r2)
#define gdk_region_intersect(r1,r2)     cairo_region_intersect (r1, r2)
#define gdk_region_subtract(r1,r2)      cairo_region_subtract (r1, r2)

static inline gboolean
gdk_region_point_in (const cairo_region_t *region, int x, int y)
{
    return cairo_region_contains_point (region, x, y);
}

#define gdk_region_rect_in(r,rect)      cairo_region_contains_rectangle (r, rect)
#define gdk_region_offset(r,dx,dy)      cairo_region_translate (r, dx, dy)
#define gdk_region_get_rectangles(r, rects, n) \
    do { \
        int _n = cairo_region_num_rectangles (r); \
        *(n) = _n; \
        *(rects) = g_new (GdkRectangle, _n); \
        for (int _i = 0; _i < _n; _i++) \
            cairo_region_get_rectangle ((r), _i, &(*(rects))[_i]); \
    } while (0)


/* ═══════════════════════════════════════════════════════════════════════
 * Convenience: suppress deprecation warnings for blocks of legacy code
 * ═══════════════════════════════════════════════════════════════════════ */

#ifndef MOO_BEGIN_IGNORE_DEPRECATIONS
#define MOO_BEGIN_IGNORE_DEPRECATIONS  G_GNUC_BEGIN_IGNORE_DEPRECATIONS
#define MOO_END_IGNORE_DEPRECATIONS    G_GNUC_END_IGNORE_DEPRECATIONS
#endif


G_END_DECLS

#endif /* MOO_GTK3_COMPAT_H */