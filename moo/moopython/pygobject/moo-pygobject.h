/*
 *   moo-pygobject.h
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

#ifndef MOO_PYGOBJECT_H
#define MOO_PYGOBJECT_H

#include <Python.h>
#include <mooglib/moo-glib.h>

G_BEGIN_DECLS

/* Python 3 module initialization function - required for Python 3 extensions */
PyMODINIT_FUNC PyInit__moo(void);

/* Internal initialization function */
gboolean    _moo_module_init            (void);

/* External function table - defined elsewhere */
extern const PyMethodDef _moo_functions[];

/* Class and constant registration functions */
void        _moo_register_classes       (PyObject       *dict);
void        _moo_add_constants          (PyObject       *module,
                                         const char     *strip_prefix);

G_END_DECLS

#ifndef pyg_register_boxed_custom
#define pyg_register_boxed_custom(type, from_func, to_func) \
    pyg_register_boxed(type, from_func, to_func)
#endif

#endif /* MOO_PYGOBJECT_H */
