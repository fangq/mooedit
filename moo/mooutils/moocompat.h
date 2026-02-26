#ifndef MOO_GTK_H
#define MOO_GTK_H

#include <mooglib/moo-glib.h>
#include <gtk/gtk.h>

#ifndef GTK_WIDGET_REALIZED
#endif

#ifndef GTK_WIDGET_MAPPED
#endif

#ifndef GTK_WIDGET_VISIBLE
#endif

#ifndef gtk_widget_is_drawable
#endif

#ifndef GTK_WIDGET_SENSITIVE
#endif

#ifndef GTK_WIDGET_HAS_FOCUS
#endif

#ifndef GTK_WIDGET_CAN_FOCUS
#endif

#ifndef GTK_WIDGET_IS_SENSITIVE
#endif

#ifndef GTK_WIDGET_TOPLEVEL
#endif

#ifndef GTK_WIDGET_STATE
#define GTK_WIDGET_STATE(w) (gtk_widget_get_state (GTK_WIDGET (w)))
#endif


#if defined(GTK_DISABLE_DEPRECATED)

inline static void
_moo_noop_gtk_toolbar_set_tooltips (G_GNUC_UNUSED GtkToolbar *toolbar,
                                    G_GNUC_UNUSED gboolean    enable)
{
}

#define gtk_toolbar_set_tooltips _moo_noop_gtk_toolbar_set_tooltips

#endif /* GTK_DISABLE_DEPRECATED */


#if defined(GTK_DISABLE_DEPRECATED)

inline static void
_moo_gtk_activatable_set_related_action (GtkAction *action,
                               GtkWidget *proxy)
{
    gtk_activatable_set_related_action (GTK_ACTIVATABLE (proxy), action);
}

#define gtk_activatable_set_related_action _moo_gtk_activatable_set_related_action

#endif /* GTK_DISABLE_DEPRECATED */

#if GTK_CHECK_VERSION(2,24,0)
#undef GTK_WIDGET_REALIZED
#endif // GTK_CHECK_VERSION(2,24,0)

#if GTK_CHECK_VERSION(2,22,0) && defined(GTK_DISABLE_DEPRECATED)

inline static void
_moo_noop_gtk_dialog_set_has_separator (G_GNUC_UNUSED GtkDialog *dialog,
                                        G_GNUC_UNUSED gboolean setting)
{
}

#define gtk_dialog_set_has_separator _moo_noop_gtk_dialog_set_has_separator

#define GTK_WIDGET_SET_CAN_FOCUS(w) gtk_widget_set_can_focus (GTK_WIDGET (w), TRUE)

#define GTK_WIDGET_UNSET_CAN_FOCUS(w) gtk_widget_set_can_focus (GTK_WIDGET (w), FALSE)

#else /* gtk-2.22.0 && DISABLE_DEPRECATED */

#define GTK_WIDGET_SET_CAN_FOCUS(w) gtk_widget_set_can_focus ((w), TRUE)

#define GTK_WIDGET_UNSET_CAN_FOCUS(w) gtk_widget_set_can_focus ((w), FALSE)

#endif /* gtk-2.22.0 && DISABLE_DEPRECATED */


#if GTK_CHECK_VERSION(2,24,0) && defined(GTK_DISABLE_DEPRECATED)

inline static void
_moo_gdk_drawable_get_size (GdkDrawable *drawable,
                            gint        *width,
                            gint        *height)
{
    if (width)
        *width = gdk_window_get_width (GDK_KEY_WINDOW (drawable));
    if (height)
        *height = gdk_window_get_height (GDK_KEY_WINDOW (drawable));
}


#else /* gtk-2.242.0 && DISABLE_DEPRECATED */

#endif /* gtk-2.24.0 && DISABLE_DEPRECATED */


#endif /* MOO_GTK_H */
