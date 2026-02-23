#ifndef MOOPYTHON_PYGOBJECTMOD_H
#define MOOPYTHON_PYGOBJECTMOD_H
#include <Python.h>
#include <pygobject.h>
#include "mooutils/mooutils-misc.h"
G_GNUC_UNUSED static gboolean
init_pygobject_mod (void)
{
    pygobject_init (-1, -1, -1);
    if (PyErr_Occurred ()) {
        g_warning ("pygobject_init() failed");
        PyErr_Print ();
        return FALSE;
    }
    return TRUE;
}
G_GNUC_UNUSED static void
reset_log_func (void)
{
#ifdef pyg_disable_warning_redirections
    pyg_disable_warning_redirections ();
#else
    moo_reset_log_func ();
#endif
}
#endif
