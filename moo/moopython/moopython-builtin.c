/*
 *   moopython-builtin.c
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <Python.h>
#define NO_IMPORT_PYGOBJECT
/* Remove PyGTK includes for PyGObject conversion */
#include <pygobject.h>
#include "mooedit/mooplugin-loader.h"
#include "moopython/moopython-builtin.h"
#include "moopython/moopython-api.h"
#include "moopython/moopython-loader.h"
#include "moopython/pygobject/moo-pygobject.h"  /* Updated path */
#include "moopython/moopython-pygobjectmod.h"   /* Updated filename */
#include "mooutils/mooutils-misc.h"
#include "moopython/pygobject/moo-mod.h"        /* Updated path */

static gboolean create_moo_module (void)
{
    PyObject *moo_module;
    PyObject *code;

    /* Python 3: Py_file_input is still valid */
    code = Py_CompileString (MOO_PY, "moo.py", Py_file_input);

    if (!code)
        return FALSE;

    /* Python 3: PyImport_ExecCodeModule is deprecated, use PyImport_ExecCodeModuleEx */
#if PY_VERSION_HEX >= 0x03000000
    moo_module = PyImport_ExecCodeModuleEx ((char*) "moo", code, "moo.py");
#else
    moo_module = PyImport_ExecCodeModule ((char*) "moo", code);
#endif

    if (!moo_module)
        PyErr_Print ();

    Py_DECREF (code);

    return !PyErr_Occurred ();
}

gboolean
_moo_python_builtin_init (void)
{
    if (!Py_IsInitialized ())
    {
        if (!moo_python_api_init ())
        {
            g_warning ("could not initialize Python API");
            return FALSE;
        }

        /* Initialize PyGObject instead of the old PyGTK module system */
        if (!init_pygobject_mod ())
        {
            g_warning ("could not initialize PyGObject");
            PyErr_Print ();
            moo_python_api_deinit ();
            return FALSE;
        }

        if (!_moo_module_init ())
        {
            g_warning ("could not initialize _moo module");
            PyErr_Print ();
            moo_python_api_deinit ();
            return FALSE;
        }

        reset_log_func ();

        if (!create_moo_module ())
        {
            g_warning ("could not initialize moo module");
            PyErr_Print ();
            moo_python_api_deinit ();
            return FALSE;
        }
    }

    if (!moo_plugin_loader_lookup (MOO_PYTHON_PLUGIN_LOADER_ID))
    {
        MooPluginLoader *loader = _moo_python_get_plugin_loader ();
        moo_plugin_loader_register (loader, MOO_PYTHON_PLUGIN_LOADER_ID);
        _moo_python_plugin_loader_free (loader);
    }

    return TRUE;
}