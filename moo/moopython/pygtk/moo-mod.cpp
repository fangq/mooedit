/* -- THIS FILE IS GENERATED - DO NOT EDIT *//* -*- Mode: C; c-basic-offset: 4 -*- */

#include <Python.h>
#include <gtk/gtk.h>


#include <string.h>
#if PY_VERSION_HEX >= 0x03000000
#define PyString_Check PyUnicode_Check
#define PyString_CheckExact PyUnicode_CheckExact
#define PyString_AS_STRING PyUnicode_AsUTF8
#define PyString_AsString PyUnicode_AsUTF8
#define PyString_FromString PyUnicode_FromString
#define PyString_FromStringAndSize PyUnicode_FromStringAndSize
#define PyInt_Check PyLong_Check
#define PyInt_FromLong PyLong_FromLong
#define PyInt_AsLong PyLong_AsLong
#define PyInt_AS_LONG PyLong_AsLong
#endif
#ifndef PyGtkWidget_Type
extern PyTypeObject PyGObject_Type;
#define PyGtkWidget_Type PyGObject_Type
#define PyGtkAction_Type PyGObject_Type
#define PyGtkFrame_Type PyGObject_Type
#define PyGtkTable_Type PyGObject_Type
#define PyGtkVBox_Type PyGObject_Type
#define PyGtkEntry_Type PyGObject_Type
#define PyGtkToggleToolButton_Type PyGObject_Type
#define PyGtkNotebook_Type PyGObject_Type
#define PyGtkObject_Type PyGObject_Type
#define PyGtkBin_Type PyGObject_Type
#define PyGtkDialog_Type PyGObject_Type
#define PyGtkTextBuffer_Type PyGObject_Type
#define PyGtkTextView_Type PyGObject_Type
#define PyGtkWindow_Type PyGObject_Type
#define PyGFile_Type PyGObject_Type
#define PyGtkAccelGroup_Type PyGObject_Type
#define PyGdkPixbuf_Type PyGObject_Type
#endif
static int pygtk_text_iter_from_pyobject(PyObject *obj, GtkTextIter *iter) {
    if (!obj || obj == Py_None) { memset(iter, 0, sizeof(GtkTextIter)); return 1; }
    { typedef struct { PyObject_HEAD GType gtype; void *boxed; } _B;
      _B *b = (_B*)obj;
      if (b->boxed && b->gtype == GTK_TYPE_TEXT_ITER) { *iter = *(GtkTextIter*)(b->boxed); return 1; } }
    PyErr_SetString(PyExc_TypeError, "expected Gtk.TextIter or None"); return 0;
}
static PyObject* pygtk_text_iter_to_pyobject(GtkTextIter *i) { (void)i; Py_RETURN_NONE; }
static int pygdk_rectangle_from_pyobject(PyObject *obj, GdkRectangle *r) {
    if (!obj || obj == Py_None) { r->x=r->y=r->width=r->height=0; return 1; }
    if (PyTuple_Check(obj) && PyTuple_Size(obj)==4) {
        r->x=(int)PyLong_AsLong(PyTuple_GET_ITEM(obj,0));
        r->y=(int)PyLong_AsLong(PyTuple_GET_ITEM(obj,1));
        r->width=(int)PyLong_AsLong(PyTuple_GET_ITEM(obj,2));
        r->height=(int)PyLong_AsLong(PyTuple_GET_ITEM(obj,3));
        return !PyErr_Occurred(); }
    PyErr_SetString(PyExc_TypeError, "expected (x,y,w,h) tuple"); return 0;
}

#line 18 "./moopython/pygtk/moo.override"
#include <Python.h>
#define NO_IMPORT_PYGOBJECT
/* Remove PyGTK includes for PyGObject conversion */
#include <pygobject.h>
#include "moopython/moopython-utils.h"
#include "moopython/pygobject/moo-pygobject.h"

#include "mooutils/mooprefsdialog.h"
#include "mooutils/moocombo.h"
#include "mooutils/mooentry.h"
#include "mooutils/moofiledialog.h"
#include "mooutils/moohistorymgr.h"
#include "mooutils/moohistorylist.h"
#include "mooutils/moohistorycombo.h"
#include "mooutils/moofontsel.h"
#include "mooutils/moofiltermgr.h"
#include "mooutils/mooprefs.h"
#include "mooutils/mooutils-enums.h"
#include "mooutils/mooutils-misc.h"
#include "mooutils/moo-mime.h"
#include "mooutils/mooi18n.h"
#include "mooutils/moohelp.h"
#include "mooutils/moofileicon.h"
#include "mooutils/moodialogs.h"
#include "mooutils/moofilewatch.h"
#include "mooutils/moomenuaction.h"
#include "mooutils/moomenutoolbutton.h"
#include "mooutils/moonotebook.h"
#include "mooutils/mooundo.h"
#include "mooutils/mooutils-script.h"
#include "mooutils/moo-test-utils.h"

#include "moofileview/moofileview.h"

#include "mooedit/mooedit.h"
#include "mooedit/mooeditor.h"
#include "mooedit/mooeditwindow.h"
#include "mooedit/mooeditbookmark.h"
#include "mooedit/mooplugin.h"
#include "mooedit/mooedit-enums.h"
#include "mooedit/mooeditprefs.h"
#include "mooedit/mooeditaction.h"
#include "mooedit/mooeditaction-factory.h"
#include "mooedit/mootextbuffer.h"
#include "mooedit/moolangmgr.h"
#include "mooedit/mooeditfileinfo.h"
#include "mooedit/mooedit-script.h"
#include "mooedit/mooedittab.h"

#include "plugins/support/moocmdview.h"
#include "plugins/support/mooeditwindowoutput.h"

#include "plugins/usertools/moocommand.h"

#include "mooapp/mooapp.h"

#include "moolua/medit-lua.h"

#line 119 "/home/fangq/space/git/Temp/newsrc/mooedit/moo/moopython/pygtk/moo.c"


#ifdef __cplusplus
extern "C" {
#endif

/* ---------- types from other modules ---------- */


/* ---------- forward type declarations ---------- */
extern PyTypeObject G_GNUC_INTERNAL PyMooPaneLabel_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooPaneParams_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooPluginInfo_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooPluginParams_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooAction_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooActionCollection_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooApp_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooBigPaned_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooCmdView_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooCombo_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooDocPlugin_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooEdit_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooEditAction_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooEditBookmark_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooEditTab_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooEditView_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooEditWindow_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooEditor_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooEntry_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooFileDialog_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooGladeXml_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooHistoryCombo_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooHistoryList_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooHistoryMgr_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooLineMark_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooLineView_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooLuaState_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooMenuAction_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooMenuMgr_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooMenuToolButton_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooNotebook_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooOpenInfo_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooPane_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooPaned_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooPlugin_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooPrefsDialog_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooPrefsPage_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooReloadInfo_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooSaveInfo_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooTextBuffer_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooTextView_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooUiXml_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooWinPlugin_Type;
extern PyTypeObject G_GNUC_INTERNAL PyMooWindow_Type;

#line 175 "/home/fangq/space/git/Temp/newsrc/mooedit/moo/moopython/pygtk/moo.c"



/* ----------- MooPaneLabel ----------- */

static int
_wrap_moo_pane_label_new(PyGBoxed *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "icon_name", (char*) "icon_pixbuf", (char*) "label_text", (char*) "window_title", NULL };
    char *icon_name = NULL, *label_text = NULL, *window_title = NULL;
    GdkPixbuf *icon_pixbuf = NULL;
    PyGObject *py_icon_pixbuf = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|zOzz:MooPaneLabel.__init__", kwlist, &icon_name, &py_icon_pixbuf, &label_text, &window_title))
        return -1;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_label_new");
#endif
    if ((PyObject *)py_icon_pixbuf == Py_None)
        icon_pixbuf = NULL;
    else if (py_icon_pixbuf && pygobject_check(py_icon_pixbuf, &PyGdkPixbuf_Type))
        icon_pixbuf = GDK_PIXBUF(py_icon_pixbuf->obj);
    else if (py_icon_pixbuf) {
        PyErr_SetString(PyExc_TypeError, "icon_pixbuf should be a GdkPixbuf or None");
        return -1;
    }
    self->gtype = MOO_TYPE_PANE_LABEL;
    self->free_on_dealloc = FALSE;
    self->boxed = moo_pane_label_new(icon_name, (GdkPixbuf *) icon_pixbuf, label_text, window_title);

    if (!self->boxed) {
        PyErr_SetString(PyExc_RuntimeError, "could not create MooPaneLabel object");
        return -1;
    }
    self->free_on_dealloc = TRUE;
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooPaneLabel_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.PaneLabel",                   /* tp_name */
    sizeof(PyGBoxed),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_moo_pane_label_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooPaneParams ----------- */

static int
_wrap_moo_pane_params_new(PyGBoxed *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "window_position", (char*) "detached", (char*) "maximized", (char*) "keep_on_top", NULL };
    GdkRectangle window_position = { 0, 0, 0, 0 };
    PyObject *py_window_position;
    int detached, maximized, keep_on_top;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"Oiii:MooPaneParams.__init__", kwlist, &py_window_position, &detached, &maximized, &keep_on_top))
        return -1;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_params_new");
#endif
    if (!pygdk_rectangle_from_pyobject(py_window_position, &window_position))
        return -1;
    self->gtype = MOO_TYPE_PANE_PARAMS;
    self->free_on_dealloc = FALSE;
    self->boxed = moo_pane_params_new(&window_position, detached, maximized, keep_on_top);

    if (!self->boxed) {
        PyErr_SetString(PyExc_RuntimeError, "could not create MooPaneParams object");
        return -1;
    }
    self->free_on_dealloc = TRUE;
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooPaneParams_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.PaneParams",                   /* tp_name */
    sizeof(PyGBoxed),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_moo_pane_params_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooPluginInfo ----------- */

static int
_wrap_moo_plugin_info_new(PyGBoxed *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "name", (char*) "description", (char*) "author", (char*) "version", NULL };
    char *name, *description = NULL, *author = NULL, *version = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|zzz:MooPluginInfo.__init__", kwlist, &name, &description, &author, &version))
        return -1;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_plugin_info_new");
#endif
    self->gtype = MOO_TYPE_PLUGIN_INFO;
    self->free_on_dealloc = FALSE;
    self->boxed = moo_plugin_info_new(name, description, author, version);

    if (!self->boxed) {
        PyErr_SetString(PyExc_RuntimeError, "could not create MooPluginInfo object");
        return -1;
    }
    self->free_on_dealloc = TRUE;
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooPluginInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.PluginInfo",                   /* tp_name */
    sizeof(PyGBoxed),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_moo_plugin_info_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooPluginParams ----------- */

static int
_wrap_moo_plugin_params_new(PyGBoxed *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "enabled", (char*) "visible", NULL };
    int enabled = TRUE, visible = TRUE;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|ii:MooPluginParams.__init__", kwlist, &enabled, &visible))
        return -1;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_plugin_params_new");
#endif
    self->gtype = MOO_TYPE_PLUGIN_PARAMS;
    self->free_on_dealloc = FALSE;
    self->boxed = moo_plugin_params_new(enabled, visible);

    if (!self->boxed) {
        PyErr_SetString(PyExc_RuntimeError, "could not create MooPluginParams object");
        return -1;
    }
    self->free_on_dealloc = TRUE;
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooPluginParams_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.PluginParams",                   /* tp_name */
    sizeof(PyGBoxed),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)_wrap_moo_plugin_params_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooUiNode ----------- */

static int
pygobject_no_constructor(G_GNUC_UNUSED PyObject *self, G_GNUC_UNUSED PyObject *args, G_GNUC_UNUSED PyObject *kwargs)
{
    gchar buf[512];

    g_snprintf(buf, sizeof(buf), "%s is an abstract widget", Py_TYPE(self)->tp_name);
    PyErr_SetString(PyExc_NotImplementedError, buf);
    return -1;
}

static PyObject *
_wrap_moo_ui_node_get_path(PyObject *self)
{
    gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_node_get_path");
#endif
    ret = moo_ui_node_get_path(pyg_pointer_get(self, MooUiNode));
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_ui_node_get_child(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "name", NULL };
    char *name;
    MooUiNode *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooUiNode.get_child", kwlist, &name))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_node_get_child");
#endif
    ret = moo_ui_node_get_child(pyg_pointer_get(self, MooUiNode), name);
    /* pyg_pointer_new handles NULL checking */
    return pyg_pointer_new(MOO_TYPE_UI_NODE, ret);
}

static const PyMethodDef _PyMooUiNode_methods[] = {
    { "get_path", (PyCFunction)_wrap_moo_ui_node_get_path, METH_NOARGS,
      NULL },
    { "get_child", (PyCFunction)_wrap_moo_ui_node_get_child, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooUiNode_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.UiNode",                   /* tp_name */
    sizeof(PyGPointer),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    0,             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooUiNode_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    0,                 /* tp_dictoffset */
    (initproc)pygobject_no_constructor,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooAction ----------- */

PyTypeObject G_GNUC_INTERNAL PyMooAction_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.Action",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooActionCollection ----------- */

PyTypeObject G_GNUC_INTERNAL PyMooActionCollection_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.ActionCollection",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooApp ----------- */

static PyObject *
_wrap_moo_app_get_editor(PyGObject *self)
{
    MooEditor *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_app_get_editor");
#endif
    
    ret = moo_app_get_editor(MOO_APP(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_app_quit(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_app_quit");
#endif
    
    ret = moo_app_quit(MOO_APP(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_app_instance(G_GNUC_UNUSED PyGObject *self)
{
    MooApp *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_app_instance");
#endif
    
    ret = moo_app_instance();
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static const PyMethodDef _PyMooApp_methods[] = {
    { "get_editor", (PyCFunction)_wrap_moo_app_get_editor, METH_NOARGS,
      NULL },
    { "quit", (PyCFunction)_wrap_moo_app_quit, METH_NOARGS,
      NULL },
    { "instance", (PyCFunction)_wrap_moo_app_instance, METH_NOARGS|METH_STATIC,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooApp_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.App",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooApp_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooBigPaned ----------- */

static int
_wrap_MooBigPaned__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.BigPaned.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.BigPaned object");
        return -1;
    }
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooBigPaned_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.BigPaned",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooBigPaned__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooTextView ----------- */

static int
_wrap_MooTextView__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.TextView.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.TextView object");
        return -1;
    }
    return 0;
}

static PyObject *
_wrap_moo_text_view_set_font_from_string(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "font", NULL };
    char *font;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooTextView.set_font_from_string", kwlist, &font))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_text_view_set_font_from_string");
#endif
    
    moo_text_view_set_font_from_string(MOO_TEXT_VIEW(self->obj), font);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_text_view_set_lang_by_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "lang_id", NULL };
    char *lang_id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooTextView.set_lang_by_id", kwlist, &lang_id))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_text_view_set_lang_by_id");
#endif
    
    moo_text_view_set_lang_by_id(MOO_TEXT_VIEW(self->obj), lang_id);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooTextView_methods[] = {
    { "set_font_from_string", (PyCFunction)_wrap_moo_text_view_set_font_from_string, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_lang_by_id", (PyCFunction)_wrap_moo_text_view_set_lang_by_id, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooTextView_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.TextView",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooTextView_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooTextView__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooLineView ----------- */

static int
_wrap_MooLineView__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.LineView.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.LineView object");
        return -1;
    }
    return 0;
}

static PyObject *
_wrap_moo_line_view_clear(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_line_view_clear");
#endif
    
    moo_line_view_clear(MOO_LINE_VIEW(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooLineView_methods[] = {
    { "clear", (PyCFunction)_wrap_moo_line_view_clear, METH_NOARGS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooLineView_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.LineView",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooLineView_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooLineView__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooCmdView ----------- */

static int
_wrap_MooCmdView__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.CmdView.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.CmdView object");
        return -1;
    }
    return 0;
}

static PyObject *
_wrap_moo_cmd_view_run_command(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "cmd", (char*) "working_dir", (char*) "job_name", NULL };
    char *cmd, *working_dir = NULL, *job_name = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|zz:MooCmdView.run_command", kwlist, &cmd, &working_dir, &job_name))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_cmd_view_run_command");
#endif
    
    ret = moo_cmd_view_run_command(MOO_CMD_VIEW(self->obj), cmd, working_dir, job_name);
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_cmd_view_set_filter_by_id(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "id", NULL };
    char *id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooCmdView.set_filter_by_id", kwlist, &id))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_cmd_view_set_filter_by_id");
#endif
    
    moo_cmd_view_set_filter_by_id(MOO_CMD_VIEW(self->obj), id);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_cmd_view_write_with_filter(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "text", (char*) "error", NULL };
    char *text;
    int error = FALSE;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|i:MooCmdView.write_with_filter", kwlist, &text, &error))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_cmd_view_write_with_filter");
#endif
    
    moo_cmd_view_write_with_filter(MOO_CMD_VIEW(self->obj), text, error);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooCmdView_methods[] = {
    { "run_command", (PyCFunction)_wrap_moo_cmd_view_run_command, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_filter_by_id", (PyCFunction)_wrap_moo_cmd_view_set_filter_by_id, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "write_with_filter", (PyCFunction)_wrap_moo_cmd_view_write_with_filter, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooCmdView_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.CmdView",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooCmdView_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooCmdView__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooCombo ----------- */

static int
_wrap_MooCombo__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.Combo.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.Combo object");
        return -1;
    }
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooCombo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.Combo",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooCombo__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooDocPlugin ----------- */

static PyObject *
_wrap_moo_doc_plugin_get_doc(PyGObject *self)
{
    MooEdit *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_doc_plugin_get_doc");
#endif
    
    ret = moo_doc_plugin_get_doc(MOO_DOC_PLUGIN(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_doc_plugin_get_plugin(PyGObject *self)
{
    MooPlugin *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_doc_plugin_get_plugin");
#endif
    
    ret = moo_doc_plugin_get_plugin(MOO_DOC_PLUGIN(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_doc_plugin_get_window(PyGObject *self)
{
    MooEditWindow *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_doc_plugin_get_window");
#endif
    
    ret = moo_doc_plugin_get_window(MOO_DOC_PLUGIN(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_MooDocPlugin__do_create(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooDocPlugin.create", kwlist, &PyMooDocPlugin_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_DOC_PLUGIN_CLASS(klass)->create)
        ret = MOO_DOC_PLUGIN_CLASS(klass)->create(MOO_DOC_PLUGIN(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooDocPlugin.create not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_MooDocPlugin__do_destroy(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooDocPlugin.destroy", kwlist, &PyMooDocPlugin_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_DOC_PLUGIN_CLASS(klass)->destroy)
        MOO_DOC_PLUGIN_CLASS(klass)->destroy(MOO_DOC_PLUGIN(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooDocPlugin.destroy not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooDocPlugin_methods[] = {
    { "get_doc", (PyCFunction)_wrap_moo_doc_plugin_get_doc, METH_NOARGS,
      NULL },
    { "get_plugin", (PyCFunction)_wrap_moo_doc_plugin_get_plugin, METH_NOARGS,
      NULL },
    { "get_window", (PyCFunction)_wrap_moo_doc_plugin_get_window, METH_NOARGS,
      NULL },
    { "do_create", (PyCFunction)_wrap_MooDocPlugin__do_create, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_destroy", (PyCFunction)_wrap_MooDocPlugin__do_destroy, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooDocPlugin_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.DocPlugin",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooDocPlugin_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};

static gboolean
_wrap_MooDocPlugin__proxy_do_create(MooDocPlugin *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    gboolean retval;
    PyObject *py_main_retval;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_create");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = Py_BuildValue("(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, "O", &py_main_retval)) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    
    retval = PyObject_IsTrue(py_main_retval)? TRUE : FALSE;
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
    
    return retval;
}
static void
_wrap_MooDocPlugin__proxy_do_destroy(MooDocPlugin *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_destroy");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}

static int
__MooDocPlugin_class_init(G_GNUC_UNUSED gpointer gclass, G_GNUC_UNUSED PyTypeObject *pyclass)
{
    PyObject *o;
    MooDocPluginClass *klass = MOO_DOC_PLUGIN_CLASS(gclass);
    PyObject *gsignals = PyDict_GetItemString(pyclass->tp_dict, "__gsignals__");

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_create");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "create")))
            klass->create = _wrap_MooDocPlugin__proxy_do_create;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_destroy");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "destroy")))
            klass->destroy = _wrap_MooDocPlugin__proxy_do_destroy;
        Py_DECREF(o);
    }
    return 0;
}


/* ----------- MooEdit ----------- */

static PyObject *
_wrap_moo_edit_append_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "text", NULL };
    char *text;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooEdit.append_text", kwlist, &text))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_append_text");
#endif
    
    moo_edit_append_text(MOO_EDIT(self->obj), text);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_begin_non_undoable_action(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_begin_non_undoable_action");
#endif
    
    moo_edit_begin_non_undoable_action(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_begin_user_action(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_begin_user_action");
#endif
    
    moo_edit_begin_user_action(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_can_redo(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_can_redo");
#endif
    
    ret = moo_edit_can_redo(MOO_EDIT(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_can_undo(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_can_undo");
#endif
    
    ret = moo_edit_can_undo(MOO_EDIT(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_clear(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_clear");
#endif
    
    moo_edit_clear(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_close(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_close");
#endif
    
    ret = moo_edit_close(MOO_EDIT(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_comment_selection(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_comment_selection");
#endif
    
    moo_edit_comment_selection(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_copy(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_copy");
#endif
    
    moo_edit_copy(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_cut(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_cut");
#endif
    
    moo_edit_cut(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_delete_selected_lines(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_delete_selected_lines");
#endif
    
    moo_edit_delete_selected_lines(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_delete_selected_text(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_delete_selected_text");
#endif
    
    moo_edit_delete_selected_text(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_delete_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "start", (char*) "end", NULL };
    GtkTextIter *start, *end;
    PyObject *py_start, *py_end;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"OO:MooEdit.delete_text", kwlist, &py_start, &py_end))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_delete_text");
#endif
    if (py_start != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_start, start)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    if (py_end != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_end, end)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    
    moo_edit_delete_text(MOO_EDIT(self->obj), start, end);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_end_non_undoable_action(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_end_non_undoable_action");
#endif
    
    moo_edit_end_non_undoable_action(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_end_user_action(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_end_user_action");
#endif
    
    moo_edit_end_user_action(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_buffer(PyGObject *self)
{
    GtkTextBuffer *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_buffer");
#endif
    
    ret = moo_edit_get_buffer(MOO_EDIT(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_get_char_at_pos(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "pos", NULL };
    GtkTextIter *pos;
    PyObject *py_pos;
    gunichar ret;
    Py_UNICODE py_ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooEdit.get_char_at_pos", kwlist, &py_pos))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_char_at_pos");
#endif
    if (py_pos != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_pos, pos)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    
    ret = moo_edit_get_char_at_pos(MOO_EDIT(self->obj), pos);
    
#if !defined(Py_UNICODE_SIZE) || Py_UNICODE_SIZE == 2
    if (ret > 0xffff) {
        PyErr_SetString(PyExc_RuntimeError, "returned character can not be represented in 16-bit unicode");
        return NULL;
    }
#endif
    py_ret = (Py_UNICODE)ret;
    return PyUnicode_FromUnicode(&py_ret, 1);

}

static PyObject *
_wrap_moo_edit_get_char_count(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_char_count");
#endif
    
    ret = moo_edit_get_char_count(MOO_EDIT(self->obj));
    
    return PyLong_FromLong(ret);
}

static PyObject *
_wrap_moo_edit_get_clean(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_clean");
#endif
    
    ret = moo_edit_get_clean(MOO_EDIT(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_get_cursor_pos(PyGObject *self)
{
    GtkTextIter ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_cursor_pos");
#endif
    
    ret = *moo_edit_get_cursor_pos(MOO_EDIT(self->obj));
    
    return pygtk_text_iter_to_pyobject(&ret);
}

static PyObject *
_wrap_moo_edit_get_display_basename(PyGObject *self)
{
    const gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_display_basename");
#endif
    
    ret = moo_edit_get_display_basename(MOO_EDIT(self->obj));
    
    if (ret)
        return PyUnicode_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_display_name(PyGObject *self)
{
    const gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_display_name");
#endif
    
    ret = moo_edit_get_display_name(MOO_EDIT(self->obj));
    
    if (ret)
        return PyUnicode_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_editor(PyGObject *self)
{
    MooEditor *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_editor");
#endif
    
    ret = moo_edit_get_editor(MOO_EDIT(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_get_encoding(PyGObject *self)
{
    const gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_encoding");
#endif
    
    ret = moo_edit_get_encoding(MOO_EDIT(self->obj));
    
    if (ret)
        return PyUnicode_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_end_pos(PyGObject *self)
{
    GtkTextIter ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_end_pos");
#endif
    
    ret = *moo_edit_get_end_pos(MOO_EDIT(self->obj));
    
    return pygtk_text_iter_to_pyobject(&ret);
}

static PyObject *
_wrap_moo_edit_get_file(PyGObject *self)
{
    GFile *ret;
    PyObject *py_ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_file");
#endif
    
    ret = moo_edit_get_file(MOO_EDIT(self->obj));
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static PyObject *
_wrap_moo_edit_get_filename(PyGObject *self)
{
    gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_filename");
#endif
    
    ret = moo_edit_get_filename(MOO_EDIT(self->obj));
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_lang_id(PyGObject *self)
{
    gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_lang_id");
#endif
    
    ret = moo_edit_get_lang_id(MOO_EDIT(self->obj));
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_line_at_cursor(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_line_at_cursor");
#endif
    
    ret = moo_edit_get_line_at_cursor(MOO_EDIT(self->obj));
    
    return PyLong_FromLong(ret);
}

static PyObject *
_wrap_moo_edit_get_line_at_pos(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "pos", NULL };
    GtkTextIter *pos;
    PyObject *py_pos;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooEdit.get_line_at_pos", kwlist, &py_pos))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_line_at_pos");
#endif
    if (py_pos != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_pos, pos)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    
    ret = moo_edit_get_line_at_pos(MOO_EDIT(self->obj), pos);
    
    return PyLong_FromLong(ret);
}

static PyObject *
_wrap_moo_edit_get_line_count(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_line_count");
#endif
    
    ret = moo_edit_get_line_count(MOO_EDIT(self->obj));
    
    return PyLong_FromLong(ret);
}

static PyObject *
_wrap_moo_edit_get_line_end_type(PyGObject *self)
{
    gint ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_line_end_type");
#endif
    
    ret = moo_edit_get_line_end_type(MOO_EDIT(self->obj));
    
    return pyg_enum_from_gtype(MOO_TYPE_LINE_END_TYPE, ret);
}

static PyObject *
_wrap_moo_edit_get_line_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "line", NULL };
    int line = -1;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|i:MooEdit.get_line_text", kwlist, &line))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_line_text");
#endif
    
    ret = moo_edit_get_line_text(MOO_EDIT(self->obj), line);
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_line_text_at_pos(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "pos", NULL };
    GtkTextIter *pos;
    PyObject *py_pos;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooEdit.get_line_text_at_pos", kwlist, &py_pos))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_line_text_at_pos");
#endif
    if (py_pos != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_pos, pos)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    
    ret = moo_edit_get_line_text_at_pos(MOO_EDIT(self->obj), pos);
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_n_views(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_n_views");
#endif
    
    ret = moo_edit_get_n_views(MOO_EDIT(self->obj));
    
    return PyLong_FromLong(ret);
}

static PyObject *
_wrap_moo_edit_get_pos_at_line(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "line", NULL };
    int line;
    GtkTextIter ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:MooEdit.get_pos_at_line", kwlist, &line))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_pos_at_line");
#endif
    
    ret = *moo_edit_get_pos_at_line(MOO_EDIT(self->obj), line);
    
    return pygtk_text_iter_to_pyobject(&ret);
}

static PyObject *
_wrap_moo_edit_get_pos_at_line_end(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "line", NULL };
    int line;
    GtkTextIter ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:MooEdit.get_pos_at_line_end", kwlist, &line))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_pos_at_line_end");
#endif
    
    ret = *moo_edit_get_pos_at_line_end(MOO_EDIT(self->obj), line);
    
    return pygtk_text_iter_to_pyobject(&ret);
}

static PyObject *
_wrap_moo_edit_get_selected_lines(PyGObject *self)
{
    gchar **ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_selected_lines");
#endif
    
    ret = moo_edit_get_selected_lines(MOO_EDIT(self->obj));
    
    if (ret) {
        PyObject *py_ret = _moo_strv_to_pyobject(ret);
        g_strfreev(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_selected_text(PyGObject *self)
{
    gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_selected_text");
#endif
    
    ret = moo_edit_get_selected_text(MOO_EDIT(self->obj));
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_selection_end_pos(PyGObject *self)
{
    GtkTextIter ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_selection_end_pos");
#endif
    
    ret = *moo_edit_get_selection_end_pos(MOO_EDIT(self->obj));
    
    return pygtk_text_iter_to_pyobject(&ret);
}

static PyObject *
_wrap_moo_edit_get_selection_start_pos(PyGObject *self)
{
    GtkTextIter ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_selection_start_pos");
#endif
    
    ret = *moo_edit_get_selection_start_pos(MOO_EDIT(self->obj));
    
    return pygtk_text_iter_to_pyobject(&ret);
}

static PyObject *
_wrap_moo_edit_get_start_pos(PyGObject *self)
{
    GtkTextIter ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_start_pos");
#endif
    
    ret = *moo_edit_get_start_pos(MOO_EDIT(self->obj));
    
    return pygtk_text_iter_to_pyobject(&ret);
}

static PyObject *
_wrap_moo_edit_get_status(PyGObject *self)
{
    guint ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_status");
#endif
    
    ret = moo_edit_get_status(MOO_EDIT(self->obj));
    
    return pyg_flags_from_gtype(MOO_TYPE_EDIT_STATUS, ret);
}

static PyObject *
_wrap_moo_edit_get_tab(PyGObject *self)
{
    MooEditTab *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_tab");
#endif
    
    ret = moo_edit_get_tab(MOO_EDIT(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_get_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "start", (char*) "end", NULL };
    GtkTextIter *start = NULL, *end = NULL;
    PyObject *py_start = Py_None, *py_end = Py_None;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|OO:MooEdit.get_text", kwlist, &py_start, &py_end))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_text");
#endif
    if (py_start != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_start, start)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    if (py_end != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_end, end)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    
    ret = moo_edit_get_text(MOO_EDIT(self->obj), start, end);
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_uri(PyGObject *self)
{
    gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_uri");
#endif
    
    ret = moo_edit_get_uri(MOO_EDIT(self->obj));
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_get_view(PyGObject *self)
{
    MooEditView *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_view");
#endif
    
    ret = moo_edit_get_view(MOO_EDIT(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_get_views(PyGObject *self)
{
    MooEditViewArray *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_views");
#endif
    
    ret = moo_edit_get_views(MOO_EDIT(self->obj));
    
    return _moo_object_array_to_pyobject((MooObjectArray*) ret);
}

static PyObject *
_wrap_moo_edit_get_window(PyGObject *self)
{
    MooEditWindow *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_get_window");
#endif
    
    ret = moo_edit_get_window(MOO_EDIT(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_has_selection(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_has_selection");
#endif
    
    ret = moo_edit_has_selection(MOO_EDIT(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_insert_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "text", (char*) "where", NULL };
    char *text;
    GtkTextIter *where = NULL;
    PyObject *py_where = Py_None;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|O:MooEdit.insert_text", kwlist, &text, &py_where))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_insert_text");
#endif
    if (py_where != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_where, where)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    
    moo_edit_insert_text(MOO_EDIT(self->obj), text, where);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_is_empty(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_is_empty");
#endif
    
    ret = moo_edit_is_empty(MOO_EDIT(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_is_modified(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_is_modified");
#endif
    
    ret = moo_edit_is_modified(MOO_EDIT(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_is_untitled(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_is_untitled");
#endif
    
    ret = moo_edit_is_untitled(MOO_EDIT(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_paste(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_paste");
#endif
    
    moo_edit_paste(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_redo(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_redo");
#endif
    
    ret = moo_edit_redo(MOO_EDIT(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_reload(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "info", NULL };
    MooReloadInfo *info = NULL;
    PyGObject *py_info = NULL;
    GError *error = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|O:MooEdit.reload", kwlist, &py_info))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_reload");
#endif
    if ((PyObject *)py_info == Py_None)
        info = NULL;
    else if (py_info && pygobject_check(py_info, &PyMooReloadInfo_Type))
        info = MOO_RELOAD_INFO(py_info->obj);
    else if (py_info) {
        PyErr_SetString(PyExc_TypeError, "info should be a MooReloadInfo or None");
        return NULL;
    }
    
    ret = moo_edit_reload(MOO_EDIT(self->obj), (MooReloadInfo *) info, &error);
    
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_replace_selected_lines(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "replacement", NULL };
    gchar **replacement;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O&:MooEdit.replace_selected_lines", kwlist, _moo_pyobject_to_strv, &replacement))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_replace_selected_lines");
#endif
    
    moo_edit_replace_selected_lines(MOO_EDIT(self->obj), replacement);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_replace_selected_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "replacement", NULL };
    char *replacement;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooEdit.replace_selected_text", kwlist, &replacement))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_replace_selected_text");
#endif
    
    moo_edit_replace_selected_text(MOO_EDIT(self->obj), replacement);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_replace_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "start", (char*) "end", (char*) "text", NULL };
    GtkTextIter *start, *end;
    PyObject *py_start, *py_end;
    char *text;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"OOs:MooEdit.replace_text", kwlist, &py_start, &py_end, &text))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_replace_text");
#endif
    if (py_start != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_start, start)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    if (py_end != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_end, end)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    
    moo_edit_replace_text(MOO_EDIT(self->obj), start, end, text);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_save(PyGObject *self)
{
    GError *error = NULL;
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_save");
#endif
    
    ret = moo_edit_save(MOO_EDIT(self->obj), &error);
    
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_save_as(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "info", NULL };
    MooSaveInfo *info = NULL;
    PyGObject *py_info;
    GError *error = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooEdit.save_as", kwlist, &py_info))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_save_as");
#endif
    if (py_info && pygobject_check(py_info, &PyMooSaveInfo_Type))
        info = MOO_SAVE_INFO(py_info->obj);
    else if ((PyObject *)py_info != Py_None) {
        PyErr_SetString(PyExc_TypeError, "info should be a MooSaveInfo or None");
        return NULL;
    }
    
    ret = moo_edit_save_as(MOO_EDIT(self->obj), (MooSaveInfo *) info, &error);
    
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_save_copy(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "info", NULL };
    PyGObject *info;
    GError *error = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEdit.save_copy", kwlist, &PyMooSaveInfo_Type, &info))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_save_copy");
#endif
    
    ret = moo_edit_save_copy(MOO_EDIT(self->obj), MOO_SAVE_INFO(info->obj), &error);
    
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_select_all(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_select_all");
#endif
    
    moo_edit_select_all(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_select_lines(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "start", (char*) "end", NULL };
    int start, end = -1;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i|i:MooEdit.select_lines", kwlist, &start, &end))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_select_lines");
#endif
    
    moo_edit_select_lines(MOO_EDIT(self->obj), start, end);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_select_lines_at_pos(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "start", (char*) "end", NULL };
    GtkTextIter *start, *end = NULL;
    PyObject *py_start, *py_end = Py_None;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O|O:MooEdit.select_lines_at_pos", kwlist, &py_start, &py_end))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_select_lines_at_pos");
#endif
    if (py_start != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_start, start)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    if (py_end != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_end, end)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    
    moo_edit_select_lines_at_pos(MOO_EDIT(self->obj), start, end);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_select_range(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "start", (char*) "end", NULL };
    GtkTextIter *start, *end;
    PyObject *py_start, *py_end;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"OO:MooEdit.select_range", kwlist, &py_start, &py_end))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_select_range");
#endif
    if (py_start != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_start, start)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    if (py_end != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_end, end)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    
    moo_edit_select_range(MOO_EDIT(self->obj), start, end);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_set_clean(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "clean", NULL };
    int clean;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:MooEdit.set_clean", kwlist, &clean))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_set_clean");
#endif
    
    moo_edit_set_clean(MOO_EDIT(self->obj), clean);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_set_cursor_pos(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "pos", NULL };
    GtkTextIter *pos;
    PyObject *py_pos;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooEdit.set_cursor_pos", kwlist, &py_pos))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_set_cursor_pos");
#endif
    if (py_pos != Py_None) {
        if (!pygtk_text_iter_from_pyobject(py_pos, pos)) {
            PyErr_SetString(PyExc_TypeError, "could not convert to GtkTextIter");
            return NULL;
        }
    }
    
    moo_edit_set_cursor_pos(MOO_EDIT(self->obj), pos);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_set_encoding(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "encoding", NULL };
    char *encoding;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooEdit.set_encoding", kwlist, &encoding))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_set_encoding");
#endif
    
    moo_edit_set_encoding(MOO_EDIT(self->obj), encoding);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_set_line_end_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "le", NULL };
    MooLineEndType le;
    PyObject *py_le = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooEdit.set_line_end_type", kwlist, &py_le))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_set_line_end_type");
#endif
    if (pyg_enum_get_value(MOO_TYPE_LINE_END_TYPE, py_le, (int*)&le))
        return NULL;
    
    moo_edit_set_line_end_type(MOO_EDIT(self->obj), le);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_set_modified(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "modified", NULL };
    int modified;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:MooEdit.set_modified", kwlist, &modified))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_set_modified");
#endif
    
    moo_edit_set_modified(MOO_EDIT(self->obj), modified);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_set_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "text", NULL };
    char *text;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooEdit.set_text", kwlist, &text))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_set_text");
#endif
    
    moo_edit_set_text(MOO_EDIT(self->obj), text);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_uncomment_selection(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_uncomment_selection");
#endif
    
    moo_edit_uncomment_selection(MOO_EDIT(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_undo(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_undo");
#endif
    
    ret = moo_edit_undo(MOO_EDIT(self->obj));
    
    return PyBool_FromLong(ret);

}

static const PyMethodDef _PyMooEdit_methods[] = {
    { "append_text", (PyCFunction)_wrap_moo_edit_append_text, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "begin_non_undoable_action", (PyCFunction)_wrap_moo_edit_begin_non_undoable_action, METH_NOARGS,
      NULL },
    { "begin_user_action", (PyCFunction)_wrap_moo_edit_begin_user_action, METH_NOARGS,
      NULL },
    { "can_redo", (PyCFunction)_wrap_moo_edit_can_redo, METH_NOARGS,
      NULL },
    { "can_undo", (PyCFunction)_wrap_moo_edit_can_undo, METH_NOARGS,
      NULL },
    { "clear", (PyCFunction)_wrap_moo_edit_clear, METH_NOARGS,
      NULL },
    { "close", (PyCFunction)_wrap_moo_edit_close, METH_NOARGS,
      NULL },
    { "comment_selection", (PyCFunction)_wrap_moo_edit_comment_selection, METH_NOARGS,
      NULL },
    { "copy", (PyCFunction)_wrap_moo_edit_copy, METH_NOARGS,
      NULL },
    { "cut", (PyCFunction)_wrap_moo_edit_cut, METH_NOARGS,
      NULL },
    { "delete_selected_lines", (PyCFunction)_wrap_moo_edit_delete_selected_lines, METH_NOARGS,
      NULL },
    { "delete_selected_text", (PyCFunction)_wrap_moo_edit_delete_selected_text, METH_NOARGS,
      NULL },
    { "delete_text", (PyCFunction)_wrap_moo_edit_delete_text, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "end_non_undoable_action", (PyCFunction)_wrap_moo_edit_end_non_undoable_action, METH_NOARGS,
      NULL },
    { "end_user_action", (PyCFunction)_wrap_moo_edit_end_user_action, METH_NOARGS,
      NULL },
    { "get_buffer", (PyCFunction)_wrap_moo_edit_get_buffer, METH_NOARGS,
      NULL },
    { "get_char_at_pos", (PyCFunction)_wrap_moo_edit_get_char_at_pos, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_char_count", (PyCFunction)_wrap_moo_edit_get_char_count, METH_NOARGS,
      NULL },
    { "get_clean", (PyCFunction)_wrap_moo_edit_get_clean, METH_NOARGS,
      NULL },
    { "get_cursor_pos", (PyCFunction)_wrap_moo_edit_get_cursor_pos, METH_NOARGS,
      NULL },
    { "get_display_basename", (PyCFunction)_wrap_moo_edit_get_display_basename, METH_NOARGS,
      NULL },
    { "get_display_name", (PyCFunction)_wrap_moo_edit_get_display_name, METH_NOARGS,
      NULL },
    { "get_editor", (PyCFunction)_wrap_moo_edit_get_editor, METH_NOARGS,
      NULL },
    { "get_encoding", (PyCFunction)_wrap_moo_edit_get_encoding, METH_NOARGS,
      NULL },
    { "get_end_pos", (PyCFunction)_wrap_moo_edit_get_end_pos, METH_NOARGS,
      NULL },
    { "get_file", (PyCFunction)_wrap_moo_edit_get_file, METH_NOARGS,
      NULL },
    { "get_filename", (PyCFunction)_wrap_moo_edit_get_filename, METH_NOARGS,
      NULL },
    { "get_lang_id", (PyCFunction)_wrap_moo_edit_get_lang_id, METH_NOARGS,
      NULL },
    { "get_line_at_cursor", (PyCFunction)_wrap_moo_edit_get_line_at_cursor, METH_NOARGS,
      NULL },
    { "get_line_at_pos", (PyCFunction)_wrap_moo_edit_get_line_at_pos, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_line_count", (PyCFunction)_wrap_moo_edit_get_line_count, METH_NOARGS,
      NULL },
    { "get_line_end_type", (PyCFunction)_wrap_moo_edit_get_line_end_type, METH_NOARGS,
      NULL },
    { "get_line_text", (PyCFunction)_wrap_moo_edit_get_line_text, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_line_text_at_pos", (PyCFunction)_wrap_moo_edit_get_line_text_at_pos, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_n_views", (PyCFunction)_wrap_moo_edit_get_n_views, METH_NOARGS,
      NULL },
    { "get_pos_at_line", (PyCFunction)_wrap_moo_edit_get_pos_at_line, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_pos_at_line_end", (PyCFunction)_wrap_moo_edit_get_pos_at_line_end, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_selected_lines", (PyCFunction)_wrap_moo_edit_get_selected_lines, METH_NOARGS,
      NULL },
    { "get_selected_text", (PyCFunction)_wrap_moo_edit_get_selected_text, METH_NOARGS,
      NULL },
    { "get_selection_end_pos", (PyCFunction)_wrap_moo_edit_get_selection_end_pos, METH_NOARGS,
      NULL },
    { "get_selection_start_pos", (PyCFunction)_wrap_moo_edit_get_selection_start_pos, METH_NOARGS,
      NULL },
    { "get_start_pos", (PyCFunction)_wrap_moo_edit_get_start_pos, METH_NOARGS,
      NULL },
    { "get_status", (PyCFunction)_wrap_moo_edit_get_status, METH_NOARGS,
      NULL },
    { "get_tab", (PyCFunction)_wrap_moo_edit_get_tab, METH_NOARGS,
      NULL },
    { "get_text", (PyCFunction)_wrap_moo_edit_get_text, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_uri", (PyCFunction)_wrap_moo_edit_get_uri, METH_NOARGS,
      NULL },
    { "get_view", (PyCFunction)_wrap_moo_edit_get_view, METH_NOARGS,
      NULL },
    { "get_views", (PyCFunction)_wrap_moo_edit_get_views, METH_NOARGS,
      NULL },
    { "get_window", (PyCFunction)_wrap_moo_edit_get_window, METH_NOARGS,
      NULL },
    { "has_selection", (PyCFunction)_wrap_moo_edit_has_selection, METH_NOARGS,
      NULL },
    { "insert_text", (PyCFunction)_wrap_moo_edit_insert_text, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "is_empty", (PyCFunction)_wrap_moo_edit_is_empty, METH_NOARGS,
      NULL },
    { "is_modified", (PyCFunction)_wrap_moo_edit_is_modified, METH_NOARGS,
      NULL },
    { "is_untitled", (PyCFunction)_wrap_moo_edit_is_untitled, METH_NOARGS,
      NULL },
    { "paste", (PyCFunction)_wrap_moo_edit_paste, METH_NOARGS,
      NULL },
    { "redo", (PyCFunction)_wrap_moo_edit_redo, METH_NOARGS,
      NULL },
    { "reload", (PyCFunction)_wrap_moo_edit_reload, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "replace_selected_lines", (PyCFunction)_wrap_moo_edit_replace_selected_lines, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "replace_selected_text", (PyCFunction)_wrap_moo_edit_replace_selected_text, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "replace_text", (PyCFunction)_wrap_moo_edit_replace_text, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "save", (PyCFunction)_wrap_moo_edit_save, METH_NOARGS,
      NULL },
    { "save_as", (PyCFunction)_wrap_moo_edit_save_as, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "save_copy", (PyCFunction)_wrap_moo_edit_save_copy, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "select_all", (PyCFunction)_wrap_moo_edit_select_all, METH_NOARGS,
      NULL },
    { "select_lines", (PyCFunction)_wrap_moo_edit_select_lines, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "select_lines_at_pos", (PyCFunction)_wrap_moo_edit_select_lines_at_pos, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "select_range", (PyCFunction)_wrap_moo_edit_select_range, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_clean", (PyCFunction)_wrap_moo_edit_set_clean, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_cursor_pos", (PyCFunction)_wrap_moo_edit_set_cursor_pos, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_encoding", (PyCFunction)_wrap_moo_edit_set_encoding, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_line_end_type", (PyCFunction)_wrap_moo_edit_set_line_end_type, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_modified", (PyCFunction)_wrap_moo_edit_set_modified, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_text", (PyCFunction)_wrap_moo_edit_set_text, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "uncomment_selection", (PyCFunction)_wrap_moo_edit_uncomment_selection, METH_NOARGS,
      NULL },
    { "undo", (PyCFunction)_wrap_moo_edit_undo, METH_NOARGS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooEdit_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.Edit",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooEdit_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooEditAction ----------- */

static PyObject *
_wrap_MooEditAction__do_check_sensitive(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditAction.check_sensitive", kwlist, &PyMooEditAction_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_EDIT_ACTION_CLASS(klass)->check_sensitive)
        ret = MOO_EDIT_ACTION_CLASS(klass)->check_sensitive(MOO_EDIT_ACTION(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooEditAction.check_sensitive not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_MooEditAction__do_check_state(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditAction.check_state", kwlist, &PyMooEditAction_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_EDIT_ACTION_CLASS(klass)->check_state)
        MOO_EDIT_ACTION_CLASS(klass)->check_state(MOO_EDIT_ACTION(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooEditAction.check_state not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_MooEditAction__do_check_visible(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditAction.check_visible", kwlist, &PyMooEditAction_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_EDIT_ACTION_CLASS(klass)->check_visible)
        ret = MOO_EDIT_ACTION_CLASS(klass)->check_visible(MOO_EDIT_ACTION(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooEditAction.check_visible not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    return PyBool_FromLong(ret);

}

static const PyMethodDef _PyMooEditAction_methods[] = {
    { "do_check_sensitive", (PyCFunction)_wrap_MooEditAction__do_check_sensitive, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_check_state", (PyCFunction)_wrap_MooEditAction__do_check_state, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_check_visible", (PyCFunction)_wrap_MooEditAction__do_check_visible, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooEditAction_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.EditAction",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooEditAction_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};

static gboolean
_wrap_MooEditAction__proxy_do_check_sensitive(MooEditAction *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    gboolean retval;
    PyObject *py_main_retval;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_check_sensitive");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = Py_BuildValue("(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, "O", &py_main_retval)) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    
    retval = PyObject_IsTrue(py_main_retval)? TRUE : FALSE;
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
    
    return retval;
}
static void
_wrap_MooEditAction__proxy_do_check_state(MooEditAction *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_check_state");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}
static gboolean
_wrap_MooEditAction__proxy_do_check_visible(MooEditAction *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    gboolean retval;
    PyObject *py_main_retval;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_check_visible");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = Py_BuildValue("(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, "O", &py_main_retval)) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    
    retval = PyObject_IsTrue(py_main_retval)? TRUE : FALSE;
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
    
    return retval;
}

static int
__MooEditAction_class_init(G_GNUC_UNUSED gpointer gclass, G_GNUC_UNUSED PyTypeObject *pyclass)
{
    PyObject *o;
    MooEditActionClass *klass = MOO_EDIT_ACTION_CLASS(gclass);
    PyObject *gsignals = PyDict_GetItemString(pyclass->tp_dict, "__gsignals__");

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_check_sensitive");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "check_sensitive")))
            klass->check_sensitive = _wrap_MooEditAction__proxy_do_check_sensitive;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_check_state");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "check_state")))
            klass->check_state = _wrap_MooEditAction__proxy_do_check_state;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_check_visible");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "check_visible")))
            klass->check_visible = _wrap_MooEditAction__proxy_do_check_visible;
        Py_DECREF(o);
    }
    return 0;
}


/* ----------- MooLineMark ----------- */

static int
_wrap_MooLineMark__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.LineMark.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.LineMark object");
        return -1;
    }
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooLineMark_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.LineMark",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooLineMark__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooEditBookmark ----------- */

PyTypeObject G_GNUC_INTERNAL PyMooEditBookmark_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.EditBookmark",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooEditTab ----------- */

static PyObject *
_wrap_moo_edit_tab_get_active_view(PyGObject *self)
{
    MooEditView *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_tab_get_active_view");
#endif
    
    ret = moo_edit_tab_get_active_view(MOO_EDIT_TAB(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_tab_get_doc(PyGObject *self)
{
    MooEdit *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_tab_get_doc");
#endif
    
    ret = moo_edit_tab_get_doc(MOO_EDIT_TAB(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_tab_get_views(PyGObject *self)
{
    MooEditViewArray *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_tab_get_views");
#endif
    
    ret = moo_edit_tab_get_views(MOO_EDIT_TAB(self->obj));
    
    return _moo_object_array_to_pyobject((MooObjectArray*) ret);
}

static PyObject *
_wrap_moo_edit_tab_get_window(PyGObject *self)
{
    MooEditWindow *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_tab_get_window");
#endif
    
    ret = moo_edit_tab_get_window(MOO_EDIT_TAB(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static const PyMethodDef _PyMooEditTab_methods[] = {
    { "get_active_view", (PyCFunction)_wrap_moo_edit_tab_get_active_view, METH_NOARGS,
      NULL },
    { "get_doc", (PyCFunction)_wrap_moo_edit_tab_get_doc, METH_NOARGS,
      NULL },
    { "get_views", (PyCFunction)_wrap_moo_edit_tab_get_views, METH_NOARGS,
      NULL },
    { "get_window", (PyCFunction)_wrap_moo_edit_tab_get_window, METH_NOARGS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooEditTab_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.EditTab",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooEditTab_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooEditView ----------- */

static PyObject *
_wrap_moo_edit_view_get_doc(PyGObject *self)
{
    MooEdit *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_view_get_doc");
#endif
    
    ret = moo_edit_view_get_doc(MOO_EDIT_VIEW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_view_get_editor(PyGObject *self)
{
    MooEditor *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_view_get_editor");
#endif
    
    ret = moo_edit_view_get_editor(MOO_EDIT_VIEW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_view_get_tab(PyGObject *self)
{
    MooEditTab *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_view_get_tab");
#endif
    
    ret = moo_edit_view_get_tab(MOO_EDIT_VIEW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_view_get_window(PyGObject *self)
{
    MooEditWindow *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_view_get_window");
#endif
    
    ret = moo_edit_view_get_window(MOO_EDIT_VIEW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static const PyMethodDef _PyMooEditView_methods[] = {
    { "get_doc", (PyCFunction)_wrap_moo_edit_view_get_doc, METH_NOARGS,
      NULL },
    { "get_editor", (PyCFunction)_wrap_moo_edit_view_get_editor, METH_NOARGS,
      NULL },
    { "get_tab", (PyCFunction)_wrap_moo_edit_view_get_tab, METH_NOARGS,
      NULL },
    { "get_window", (PyCFunction)_wrap_moo_edit_view_get_window, METH_NOARGS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooEditView_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.EditView",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooEditView_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooWindow ----------- */

PyTypeObject G_GNUC_INTERNAL PyMooWindow_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.Window",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooEditWindow ----------- */

static PyObject *
_wrap_moo_edit_window_abort_jobs(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_abort_jobs");
#endif
    
    moo_edit_window_abort_jobs(MOO_EDIT_WINDOW(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_window_add_pane(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "user_id", (char*) "widget", (char*) "label", (char*) "position", NULL };
    char *user_id;
    PyGObject *widget;
    MooPaneLabel *label = NULL;
    PyObject *py_label, *py_position = NULL;
    MooPanePosition position;
    MooPane *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"sO!OO:MooEditWindow.add_pane", kwlist, &user_id, &PyGtkWidget_Type, &widget, &py_label, &py_position))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_add_pane");
#endif
    if (pyg_boxed_check(py_label, MOO_TYPE_PANE_LABEL))
        label = pyg_boxed_get(py_label, MooPaneLabel);
    else {
        PyErr_SetString(PyExc_TypeError, "label should be a MooPaneLabel");
        return NULL;
    }
    if (pyg_enum_get_value(MOO_TYPE_PANE_POSITION, py_position, (int*)&position))
        return NULL;
    
    ret = moo_edit_window_add_pane(MOO_EDIT_WINDOW(self->obj), user_id, GTK_WIDGET(widget->obj), label, position);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_window_add_stop_client(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "client", NULL };
    PyGObject *client;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditWindow.add_stop_client", kwlist, &PyGObject_Type, &client))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_add_stop_client");
#endif
    
    moo_edit_window_add_stop_client(MOO_EDIT_WINDOW(self->obj), G_OBJECT(client->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_window_close(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_close");
#endif
    
    ret = moo_edit_window_close(MOO_EDIT_WINDOW(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_window_close_all(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_close_all");
#endif
    
    ret = moo_edit_window_close_all(MOO_EDIT_WINDOW(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_window_get_active_doc(PyGObject *self)
{
    MooEdit *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_get_active_doc");
#endif
    
    ret = moo_edit_window_get_active_doc(MOO_EDIT_WINDOW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_window_get_active_tab(PyGObject *self)
{
    MooEditTab *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_get_active_tab");
#endif
    
    ret = moo_edit_window_get_active_tab(MOO_EDIT_WINDOW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_window_get_active_view(PyGObject *self)
{
    MooEditView *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_get_active_view");
#endif
    
    ret = moo_edit_window_get_active_view(MOO_EDIT_WINDOW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_window_get_docs(PyGObject *self)
{
    MooEditArray *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_get_docs");
#endif
    
    ret = moo_edit_window_get_docs(MOO_EDIT_WINDOW(self->obj));
    
    return _moo_object_array_to_pyobject((MooObjectArray*) ret);
}

static PyObject *
_wrap_moo_edit_window_get_editor(PyGObject *self)
{
    MooEditor *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_get_editor");
#endif
    
    ret = moo_edit_window_get_editor(MOO_EDIT_WINDOW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_window_get_n_tabs(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_get_n_tabs");
#endif
    
    ret = moo_edit_window_get_n_tabs(MOO_EDIT_WINDOW(self->obj));
    
    return PyLong_FromLong(ret);
}

static PyObject *
_wrap_moo_edit_window_get_output(PyGObject *self)
{
    GtkWidget *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_get_output");
#endif
    
    ret = moo_edit_window_get_output(MOO_EDIT_WINDOW(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_window_get_pane(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "user_id", NULL };
    char *user_id;
    GtkWidget *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooEditWindow.get_pane", kwlist, &user_id))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_get_pane");
#endif
    
    ret = moo_edit_window_get_pane(MOO_EDIT_WINDOW(self->obj), user_id);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_edit_window_get_tabs(PyGObject *self)
{
    MooEditTabArray *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_get_tabs");
#endif
    
    ret = moo_edit_window_get_tabs(MOO_EDIT_WINDOW(self->obj));
    
    return _moo_object_array_to_pyobject((MooObjectArray*) ret);
}

static PyObject *
_wrap_moo_edit_window_get_views(PyGObject *self)
{
    MooEditViewArray *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_get_views");
#endif
    
    ret = moo_edit_window_get_views(MOO_EDIT_WINDOW(self->obj));
    
    return _moo_object_array_to_pyobject((MooObjectArray*) ret);
}

static PyObject *
_wrap_moo_edit_window_present_output(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_present_output");
#endif
    
    moo_edit_window_present_output(MOO_EDIT_WINDOW(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_window_remove_pane(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "user_id", NULL };
    char *user_id;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooEditWindow.remove_pane", kwlist, &user_id))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_remove_pane");
#endif
    
    ret = moo_edit_window_remove_pane(MOO_EDIT_WINDOW(self->obj), user_id);
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_edit_window_remove_stop_client(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "client", NULL };
    PyGObject *client;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditWindow.remove_stop_client", kwlist, &PyGObject_Type, &client))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_remove_stop_client");
#endif
    
    moo_edit_window_remove_stop_client(MOO_EDIT_WINDOW(self->obj), G_OBJECT(client->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_window_set_active_doc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "doc", NULL };
    PyGObject *doc;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditWindow.set_active_doc", kwlist, &PyMooEdit_Type, &doc))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_set_active_doc");
#endif
    
    moo_edit_window_set_active_doc(MOO_EDIT_WINDOW(self->obj), MOO_EDIT(doc->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_window_set_active_tab(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "tab", NULL };
    PyGObject *tab;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditWindow.set_active_tab", kwlist, &PyMooEditTab_Type, &tab))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_set_active_tab");
#endif
    
    moo_edit_window_set_active_tab(MOO_EDIT_WINDOW(self->obj), MOO_EDIT_TAB(tab->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_window_set_active_view(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "view", NULL };
    PyGObject *view;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditWindow.set_active_view", kwlist, &PyMooEditView_Type, &view))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_set_active_view");
#endif
    
    moo_edit_window_set_active_view(MOO_EDIT_WINDOW(self->obj), MOO_EDIT_VIEW(view->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_window_show_pane(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "user_id", NULL };
    char *user_id;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooEditWindow.show_pane", kwlist, &user_id))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_show_pane");
#endif
    
    moo_edit_window_show_pane(MOO_EDIT_WINDOW(self->obj), user_id);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooEditWindow_methods[] = {
    { "abort_jobs", (PyCFunction)_wrap_moo_edit_window_abort_jobs, METH_NOARGS,
      NULL },
    { "add_pane", (PyCFunction)_wrap_moo_edit_window_add_pane, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "add_stop_client", (PyCFunction)_wrap_moo_edit_window_add_stop_client, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "close", (PyCFunction)_wrap_moo_edit_window_close, METH_NOARGS,
      NULL },
    { "close_all", (PyCFunction)_wrap_moo_edit_window_close_all, METH_NOARGS,
      NULL },
    { "get_active_doc", (PyCFunction)_wrap_moo_edit_window_get_active_doc, METH_NOARGS,
      NULL },
    { "get_active_tab", (PyCFunction)_wrap_moo_edit_window_get_active_tab, METH_NOARGS,
      NULL },
    { "get_active_view", (PyCFunction)_wrap_moo_edit_window_get_active_view, METH_NOARGS,
      NULL },
    { "get_docs", (PyCFunction)_wrap_moo_edit_window_get_docs, METH_NOARGS,
      NULL },
    { "get_editor", (PyCFunction)_wrap_moo_edit_window_get_editor, METH_NOARGS,
      NULL },
    { "get_n_tabs", (PyCFunction)_wrap_moo_edit_window_get_n_tabs, METH_NOARGS,
      NULL },
    { "get_output", (PyCFunction)_wrap_moo_edit_window_get_output, METH_NOARGS,
      NULL },
    { "get_pane", (PyCFunction)_wrap_moo_edit_window_get_pane, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_tabs", (PyCFunction)_wrap_moo_edit_window_get_tabs, METH_NOARGS,
      NULL },
    { "get_views", (PyCFunction)_wrap_moo_edit_window_get_views, METH_NOARGS,
      NULL },
    { "present_output", (PyCFunction)_wrap_moo_edit_window_present_output, METH_NOARGS,
      NULL },
    { "remove_pane", (PyCFunction)_wrap_moo_edit_window_remove_pane, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "remove_stop_client", (PyCFunction)_wrap_moo_edit_window_remove_stop_client, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_active_doc", (PyCFunction)_wrap_moo_edit_window_set_active_doc, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_active_tab", (PyCFunction)_wrap_moo_edit_window_set_active_tab, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_active_view", (PyCFunction)_wrap_moo_edit_window_set_active_view, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "show_pane", (PyCFunction)_wrap_moo_edit_window_show_pane, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooEditWindow_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.EditWindow",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooEditWindow_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooEditor ----------- */

static PyObject *
_wrap_moo_editor_close_doc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "doc", NULL };
    PyGObject *doc;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditor.close_doc", kwlist, &PyMooEdit_Type, &doc))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_close_doc");
#endif
    
    ret = moo_editor_close_doc(MOO_EDITOR(self->obj), MOO_EDIT(doc->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_editor_close_docs(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "docs", NULL };
    MooEditArray *docs = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooEditor.close_docs", kwlist, &docs))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_close_docs");
#endif
    
    ret = moo_editor_close_docs(MOO_EDITOR(self->obj), docs);
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_editor_close_window(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "window", NULL };
    PyGObject *window;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditor.close_window", kwlist, &PyMooEditWindow_Type, &window))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_close_window");
#endif
    
    ret = moo_editor_close_window(MOO_EDITOR(self->obj), MOO_EDIT_WINDOW(window->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_editor_create_doc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "filename", (char*) "encoding", NULL };
    char *filename = NULL, *encoding = NULL;
    GError *error = NULL;
    MooEdit *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|zz:MooEditor.create_doc", kwlist, &filename, &encoding))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_create_doc");
#endif
    
    ret = moo_editor_create_doc(MOO_EDITOR(self->obj), filename, encoding, &error);
    
    if (pyg_error_check(&error))
        return NULL;
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_get_active_doc(PyGObject *self)
{
    MooEdit *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_get_active_doc");
#endif
    
    ret = moo_editor_get_active_doc(MOO_EDITOR(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_get_active_view(PyGObject *self)
{
    MooEditView *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_get_active_view");
#endif
    
    ret = moo_editor_get_active_view(MOO_EDITOR(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_get_active_window(PyGObject *self)
{
    MooEditWindow *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_get_active_window");
#endif
    
    ret = moo_editor_get_active_window(MOO_EDITOR(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_get_doc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "filename", NULL };
    char *filename;
    MooEdit *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooEditor.get_doc", kwlist, &filename))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_get_doc");
#endif
    
    ret = moo_editor_get_doc(MOO_EDITOR(self->obj), filename);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_get_doc_for_file(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "file", NULL };
    PyGObject *file;
    MooEdit *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditor.get_doc_for_file", kwlist, &PyGFile_Type, &file))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_get_doc_for_file");
#endif
    
    ret = moo_editor_get_doc_for_file(MOO_EDITOR(self->obj), G_FILE(file->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_get_doc_for_uri(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "uri", NULL };
    char *uri;
    MooEdit *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooEditor.get_doc_for_uri", kwlist, &uri))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_get_doc_for_uri");
#endif
    
    ret = moo_editor_get_doc_for_uri(MOO_EDITOR(self->obj), uri);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_get_doc_ui_xml(PyGObject *self)
{
    MooUiXml *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_get_doc_ui_xml");
#endif
    
    ret = moo_editor_get_doc_ui_xml(MOO_EDITOR(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_get_docs(PyGObject *self)
{
    MooEditArray *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_get_docs");
#endif
    
    ret = moo_editor_get_docs(MOO_EDITOR(self->obj));
    
    return _moo_object_array_to_pyobject((MooObjectArray*) ret);
}

static PyObject *
_wrap_moo_editor_get_ui_xml(PyGObject *self)
{
    MooUiXml *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_get_ui_xml");
#endif
    
    ret = moo_editor_get_ui_xml(MOO_EDITOR(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_get_windows(PyGObject *self)
{
    MooEditWindowArray *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_get_windows");
#endif
    
    ret = moo_editor_get_windows(MOO_EDITOR(self->obj));
    
    return _moo_object_array_to_pyobject((MooObjectArray*) ret);
}

static PyObject *
_wrap_moo_editor_new_doc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "window", NULL };
    MooEditWindow *window = NULL;
    PyGObject *py_window = NULL;
    MooEdit *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|O:MooEditor.new_doc", kwlist, &py_window))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_new_doc");
#endif
    if ((PyObject *)py_window == Py_None)
        window = NULL;
    else if (py_window && pygobject_check(py_window, &PyMooEditWindow_Type))
        window = MOO_EDIT_WINDOW(py_window->obj);
    else if (py_window) {
        PyErr_SetString(PyExc_TypeError, "window should be a MooEditWindow or None");
        return NULL;
    }
    
    ret = moo_editor_new_doc(MOO_EDITOR(self->obj), (MooEditWindow *) window);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_new_file(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "info", (char*) "parent", NULL };
    PyGObject *info, *py_parent = NULL;
    GtkWidget *parent = NULL;
    GError *error = NULL;
    MooEdit *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!|O:MooEditor.new_file", kwlist, &PyMooOpenInfo_Type, &info, &py_parent))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_new_file");
#endif
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWidget_Type))
        parent = GTK_WIDGET(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWidget or None");
        return NULL;
    }
    
    ret = moo_editor_new_file(MOO_EDITOR(self->obj), MOO_OPEN_INFO(info->obj), (GtkWidget *) parent, &error);
    
    if (pyg_error_check(&error))
        return NULL;
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_new_window(PyGObject *self)
{
    MooEditWindow *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_new_window");
#endif
    
    ret = moo_editor_new_window(MOO_EDITOR(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_open_file(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "info", (char*) "parent", NULL };
    PyGObject *info, *py_parent = NULL;
    GtkWidget *parent = NULL;
    GError *error = NULL;
    MooEdit *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!|O:MooEditor.open_file", kwlist, &PyMooOpenInfo_Type, &info, &py_parent))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_open_file");
#endif
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWidget_Type))
        parent = GTK_WIDGET(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWidget or None");
        return NULL;
    }
    
    ret = moo_editor_open_file(MOO_EDITOR(self->obj), MOO_OPEN_INFO(info->obj), (GtkWidget *) parent, &error);
    
    if (pyg_error_check(&error))
        return NULL;
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_open_files(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "files", (char*) "parent", NULL };
    MooOpenInfoArray *files = NULL;
    GtkWidget *parent = NULL;
    PyGObject *py_parent = NULL;
    GError *error = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O|O:MooEditor.open_files", kwlist, &files, &py_parent))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_open_files");
#endif
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWidget_Type))
        parent = GTK_WIDGET(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWidget or None");
        return NULL;
    }
    
    ret = moo_editor_open_files(MOO_EDITOR(self->obj), files, (GtkWidget *) parent, &error);
    
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_editor_open_path(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "path", (char*) "encoding", (char*) "line", (char*) "window", NULL };
    char *path, *encoding = NULL;
    int line = -1;
    MooEditWindow *window = NULL;
    PyGObject *py_window = NULL;
    MooEdit *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|ziO:MooEditor.open_path", kwlist, &path, &encoding, &line, &py_window))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_open_path");
#endif
    if ((PyObject *)py_window == Py_None)
        window = NULL;
    else if (py_window && pygobject_check(py_window, &PyMooEditWindow_Type))
        window = MOO_EDIT_WINDOW(py_window->obj);
    else if (py_window) {
        PyErr_SetString(PyExc_TypeError, "window should be a MooEditWindow or None");
        return NULL;
    }
    
    ret = moo_editor_open_path(MOO_EDITOR(self->obj), path, encoding, line, (MooEditWindow *) window);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_open_uri(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "uri", (char*) "encoding", (char*) "line", (char*) "window", NULL };
    char *uri, *encoding = NULL;
    int line = -1;
    MooEditWindow *window = NULL;
    PyGObject *py_window = NULL;
    MooEdit *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|ziO:MooEditor.open_uri", kwlist, &uri, &encoding, &line, &py_window))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_open_uri");
#endif
    if ((PyObject *)py_window == Py_None)
        window = NULL;
    else if (py_window && pygobject_check(py_window, &PyMooEditWindow_Type))
        window = MOO_EDIT_WINDOW(py_window->obj);
    else if (py_window) {
        PyErr_SetString(PyExc_TypeError, "window should be a MooEditWindow or None");
        return NULL;
    }
    
    ret = moo_editor_open_uri(MOO_EDITOR(self->obj), uri, encoding, line, (MooEditWindow *) window);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_editor_reload(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "doc", (char*) "info", NULL };
    PyGObject *doc, *py_info = NULL;
    MooReloadInfo *info = NULL;
    GError *error = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!|O:MooEditor.reload", kwlist, &PyMooEdit_Type, &doc, &py_info))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_reload");
#endif
    if ((PyObject *)py_info == Py_None)
        info = NULL;
    else if (py_info && pygobject_check(py_info, &PyMooReloadInfo_Type))
        info = MOO_RELOAD_INFO(py_info->obj);
    else if (py_info) {
        PyErr_SetString(PyExc_TypeError, "info should be a MooReloadInfo or None");
        return NULL;
    }
    
    ret = moo_editor_reload(MOO_EDITOR(self->obj), MOO_EDIT(doc->obj), (MooReloadInfo *) info, &error);
    
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_editor_save(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "doc", NULL };
    PyGObject *doc;
    GError *error = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditor.save", kwlist, &PyMooEdit_Type, &doc))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_save");
#endif
    
    ret = moo_editor_save(MOO_EDITOR(self->obj), MOO_EDIT(doc->obj), &error);
    
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_editor_save_as(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "doc", (char*) "info", NULL };
    PyGObject *doc, *py_info = NULL;
    MooSaveInfo *info = NULL;
    GError *error = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!|O:MooEditor.save_as", kwlist, &PyMooEdit_Type, &doc, &py_info))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_save_as");
#endif
    if ((PyObject *)py_info == Py_None)
        info = NULL;
    else if (py_info && pygobject_check(py_info, &PyMooSaveInfo_Type))
        info = MOO_SAVE_INFO(py_info->obj);
    else if (py_info) {
        PyErr_SetString(PyExc_TypeError, "info should be a MooSaveInfo or None");
        return NULL;
    }
    
    ret = moo_editor_save_as(MOO_EDITOR(self->obj), MOO_EDIT(doc->obj), (MooSaveInfo *) info, &error);
    
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_editor_save_copy(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "doc", (char*) "info", NULL };
    PyGObject *doc, *info;
    GError *error = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!O!:MooEditor.save_copy", kwlist, &PyMooEdit_Type, &doc, &PyMooSaveInfo_Type, &info))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_save_copy");
#endif
    
    ret = moo_editor_save_copy(MOO_EDITOR(self->obj), MOO_EDIT(doc->obj), MOO_SAVE_INFO(info->obj), &error);
    
    if (pyg_error_check(&error))
        return NULL;
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_editor_set_active_doc(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "doc", NULL };
    PyGObject *doc;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditor.set_active_doc", kwlist, &PyMooEdit_Type, &doc))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_set_active_doc");
#endif
    
    moo_editor_set_active_doc(MOO_EDITOR(self->obj), MOO_EDIT(doc->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_editor_set_active_view(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "view", NULL };
    PyGObject *view;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditor.set_active_view", kwlist, &PyMooEditView_Type, &view))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_set_active_view");
#endif
    
    moo_editor_set_active_view(MOO_EDITOR(self->obj), MOO_EDIT_VIEW(view->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_editor_set_active_window(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "window", NULL };
    PyGObject *window;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditor.set_active_window", kwlist, &PyMooEditWindow_Type, &window))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_set_active_window");
#endif
    
    moo_editor_set_active_window(MOO_EDITOR(self->obj), MOO_EDIT_WINDOW(window->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_editor_set_doc_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "type", NULL };
    GType type;
    PyObject *py_type = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooEditor.set_doc_type", kwlist, &py_type))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_set_doc_type");
#endif
    if ((type = pyg_type_from_object(py_type)) == 0)
        return NULL;
    
    moo_editor_set_doc_type(MOO_EDITOR(self->obj), type);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_editor_set_ui_xml(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "xml", NULL };
    PyGObject *xml;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooEditor.set_ui_xml", kwlist, &PyMooUiXml_Type, &xml))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_set_ui_xml");
#endif
    
    moo_editor_set_ui_xml(MOO_EDITOR(self->obj), MOO_UI_XML(xml->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_editor_set_window_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "type", NULL };
    GType type;
    PyObject *py_type = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooEditor.set_window_type", kwlist, &py_type))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_set_window_type");
#endif
    if ((type = pyg_type_from_object(py_type)) == 0)
        return NULL;
    
    moo_editor_set_window_type(MOO_EDITOR(self->obj), type);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_editor_create_instance(G_GNUC_UNUSED PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "embedded", NULL };
    int embedded = TRUE;
    MooEditor *ret;
    PyObject *py_ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|i:MooEditor.create_instance", kwlist, &embedded))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_create_instance");
#endif
    
    ret = moo_editor_create_instance(embedded);
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static PyObject *
_wrap_moo_editor_instance(G_GNUC_UNUSED PyGObject *self)
{
    MooEditor *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_editor_instance");
#endif
    
    ret = moo_editor_instance();
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static const PyMethodDef _PyMooEditor_methods[] = {
    { "close_doc", (PyCFunction)_wrap_moo_editor_close_doc, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "close_docs", (PyCFunction)_wrap_moo_editor_close_docs, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "close_window", (PyCFunction)_wrap_moo_editor_close_window, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "create_doc", (PyCFunction)_wrap_moo_editor_create_doc, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_active_doc", (PyCFunction)_wrap_moo_editor_get_active_doc, METH_NOARGS,
      NULL },
    { "get_active_view", (PyCFunction)_wrap_moo_editor_get_active_view, METH_NOARGS,
      NULL },
    { "get_active_window", (PyCFunction)_wrap_moo_editor_get_active_window, METH_NOARGS,
      NULL },
    { "get_doc", (PyCFunction)_wrap_moo_editor_get_doc, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_doc_for_file", (PyCFunction)_wrap_moo_editor_get_doc_for_file, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_doc_for_uri", (PyCFunction)_wrap_moo_editor_get_doc_for_uri, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_doc_ui_xml", (PyCFunction)_wrap_moo_editor_get_doc_ui_xml, METH_NOARGS,
      NULL },
    { "get_docs", (PyCFunction)_wrap_moo_editor_get_docs, METH_NOARGS,
      NULL },
    { "get_ui_xml", (PyCFunction)_wrap_moo_editor_get_ui_xml, METH_NOARGS,
      NULL },
    { "get_windows", (PyCFunction)_wrap_moo_editor_get_windows, METH_NOARGS,
      NULL },
    { "new_doc", (PyCFunction)_wrap_moo_editor_new_doc, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "new_file", (PyCFunction)_wrap_moo_editor_new_file, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "new_window", (PyCFunction)_wrap_moo_editor_new_window, METH_NOARGS,
      NULL },
    { "open_file", (PyCFunction)_wrap_moo_editor_open_file, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "open_files", (PyCFunction)_wrap_moo_editor_open_files, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "open_path", (PyCFunction)_wrap_moo_editor_open_path, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "open_uri", (PyCFunction)_wrap_moo_editor_open_uri, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "reload", (PyCFunction)_wrap_moo_editor_reload, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "save", (PyCFunction)_wrap_moo_editor_save, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "save_as", (PyCFunction)_wrap_moo_editor_save_as, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "save_copy", (PyCFunction)_wrap_moo_editor_save_copy, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_active_doc", (PyCFunction)_wrap_moo_editor_set_active_doc, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_active_view", (PyCFunction)_wrap_moo_editor_set_active_view, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_active_window", (PyCFunction)_wrap_moo_editor_set_active_window, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_doc_type", (PyCFunction)_wrap_moo_editor_set_doc_type, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_ui_xml", (PyCFunction)_wrap_moo_editor_set_ui_xml, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_window_type", (PyCFunction)_wrap_moo_editor_set_window_type, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "create_instance", (PyCFunction)_wrap_moo_editor_create_instance, METH_VARARGS|METH_KEYWORDS|METH_STATIC,
      NULL },
    { "instance", (PyCFunction)_wrap_moo_editor_instance, METH_NOARGS|METH_STATIC,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooEditor_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.Editor",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooEditor_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooEntry ----------- */

static int
_wrap_MooEntry__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.Entry.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.Entry object");
        return -1;
    }
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooEntry_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.Entry",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooEntry__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooFileDialog ----------- */

static int
_wrap_MooFileDialog__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.FileDialog.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.FileDialog object");
        return -1;
    }
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooFileDialog_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.FileDialog",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooFileDialog__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooGladeXml ----------- */

PyTypeObject G_GNUC_INTERNAL PyMooGladeXml_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.GladeXml",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooHistoryCombo ----------- */

static int
_wrap_MooHistoryCombo__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.HistoryCombo.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.HistoryCombo object");
        return -1;
    }
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooHistoryCombo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.HistoryCombo",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooHistoryCombo__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooHistoryList ----------- */

static int
_wrap_MooHistoryList__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.HistoryList.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.HistoryList object");
        return -1;
    }
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooHistoryList_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.HistoryList",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooHistoryList__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooHistoryMgr ----------- */

PyTypeObject G_GNUC_INTERNAL PyMooHistoryMgr_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.HistoryMgr",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooLuaState ----------- */

static int
_wrap_MooLuaState__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.LuaState.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.LuaState object");
        return -1;
    }
    return 0;
}

static PyObject *
_wrap_moo_lua_state_run_string(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "string", NULL };
    char *string;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooLuaState.run_string", kwlist, &string))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_lua_state_run_string");
#endif
    
    ret = moo_lua_state_run_string(MOO_LUA_STATE(self->obj), string);
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooLuaState_methods[] = {
    { "run_string", (PyCFunction)_wrap_moo_lua_state_run_string, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooLuaState_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.LuaState",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooLuaState_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooLuaState__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooMenuAction ----------- */

PyTypeObject G_GNUC_INTERNAL PyMooMenuAction_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.MenuAction",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooMenuMgr ----------- */

static int
_wrap_MooMenuMgr__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.MenuMgr.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.MenuMgr object");
        return -1;
    }
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooMenuMgr_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.MenuMgr",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooMenuMgr__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooMenuToolButton ----------- */

PyTypeObject G_GNUC_INTERNAL PyMooMenuToolButton_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.MenuToolButton",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooNotebook ----------- */

static int
_wrap_MooNotebook__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.Notebook.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.Notebook object");
        return -1;
    }
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooNotebook_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.Notebook",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooNotebook__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooOpenInfo ----------- */

static int
_wrap_moo_open_info_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "path", (char*) "encoding", (char*) "line", (char*) "flags", NULL };
    char *path, *encoding = NULL;
    int line = -1;
    MooOpenFlags flags = (MooOpenFlags) 0;
    PyObject *py_flags = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|ziO:MooOpenInfo.__init__", kwlist, &path, &encoding, &line, &py_flags))
        return -1;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_new");
#endif
    if (py_flags && pyg_flags_get_value(MOO_TYPE_OPEN_FLAGS, py_flags, (guint*)&flags))
        return -1;
    self->obj = (GObject *)moo_open_info_new(path, encoding, line, flags);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create MooOpenInfo object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_moo_open_info_add_flags(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "flags", NULL };
    MooOpenFlags flags;
    PyObject *py_flags = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooOpenInfo.add_flags", kwlist, &py_flags))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_add_flags");
#endif
    if (pyg_flags_get_value(MOO_TYPE_OPEN_FLAGS, py_flags, (guint*)&flags))
        return NULL;
    
    moo_open_info_add_flags(MOO_OPEN_INFO(self->obj), flags);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_open_info_dup(PyGObject *self)
{
    MooOpenInfo *ret;
    PyObject *py_ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_dup");
#endif
    
    ret = moo_open_info_dup(MOO_OPEN_INFO(self->obj));
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static PyObject *
_wrap_moo_open_info_get_encoding(PyGObject *self)
{
    const gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_get_encoding");
#endif
    
    ret = moo_open_info_get_encoding(MOO_OPEN_INFO(self->obj));
    
    if (ret)
        return PyUnicode_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_open_info_get_file(PyGObject *self)
{
    GFile *ret;
    PyObject *py_ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_get_file");
#endif
    
    ret = moo_open_info_get_file(MOO_OPEN_INFO(self->obj));
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static PyObject *
_wrap_moo_open_info_get_filename(PyGObject *self)
{
    gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_get_filename");
#endif
    
    ret = moo_open_info_get_filename(MOO_OPEN_INFO(self->obj));
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_open_info_get_flags(PyGObject *self)
{
    guint ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_get_flags");
#endif
    
    ret = moo_open_info_get_flags(MOO_OPEN_INFO(self->obj));
    
    return pyg_flags_from_gtype(MOO_TYPE_OPEN_FLAGS, ret);
}

static PyObject *
_wrap_moo_open_info_get_line(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_get_line");
#endif
    
    ret = moo_open_info_get_line(MOO_OPEN_INFO(self->obj));
    
    return PyLong_FromLong(ret);
}

static PyObject *
_wrap_moo_open_info_get_uri(PyGObject *self)
{
    gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_get_uri");
#endif
    
    ret = moo_open_info_get_uri(MOO_OPEN_INFO(self->obj));
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_open_info_set_encoding(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "encoding", NULL };
    char *encoding;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"z:MooOpenInfo.set_encoding", kwlist, &encoding))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_set_encoding");
#endif
    
    moo_open_info_set_encoding(MOO_OPEN_INFO(self->obj), encoding);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_open_info_set_flags(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "flags", NULL };
    MooOpenFlags flags;
    PyObject *py_flags = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooOpenInfo.set_flags", kwlist, &py_flags))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_set_flags");
#endif
    if (pyg_flags_get_value(MOO_TYPE_OPEN_FLAGS, py_flags, (guint*)&flags))
        return NULL;
    
    moo_open_info_set_flags(MOO_OPEN_INFO(self->obj), flags);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_open_info_set_line(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "line", NULL };
    int line;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:MooOpenInfo.set_line", kwlist, &line))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_set_line");
#endif
    
    moo_open_info_set_line(MOO_OPEN_INFO(self->obj), line);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_open_info_new_file(G_GNUC_UNUSED PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "file", (char*) "encoding", (char*) "line", (char*) "flags", NULL };
    PyGObject *file;
    char *encoding = NULL;
    int line = -1;
    MooOpenFlags flags = (MooOpenFlags) 0;
    PyObject *py_flags = NULL, *py_ret;
    MooOpenInfo *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!|ziO:MooOpenInfo.new_file", kwlist, &PyGFile_Type, &file, &encoding, &line, &py_flags))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_new_file");
#endif
    if (py_flags && pyg_flags_get_value(MOO_TYPE_OPEN_FLAGS, py_flags, (guint*)&flags))
        return NULL;
    
    ret = moo_open_info_new_file(G_FILE(file->obj), encoding, line, flags);
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static PyObject *
_wrap_moo_open_info_new_uri(G_GNUC_UNUSED PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "uri", (char*) "encoding", (char*) "line", (char*) "flags", NULL };
    char *uri, *encoding = NULL;
    int line = -1;
    MooOpenFlags flags = (MooOpenFlags) 0;
    PyObject *py_flags = NULL, *py_ret;
    MooOpenInfo *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|ziO:MooOpenInfo.new_uri", kwlist, &uri, &encoding, &line, &py_flags))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_open_info_new_uri");
#endif
    if (py_flags && pyg_flags_get_value(MOO_TYPE_OPEN_FLAGS, py_flags, (guint*)&flags))
        return NULL;
    
    ret = moo_open_info_new_uri(uri, encoding, line, flags);
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static const PyMethodDef _PyMooOpenInfo_methods[] = {
    { "add_flags", (PyCFunction)_wrap_moo_open_info_add_flags, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "dup", (PyCFunction)_wrap_moo_open_info_dup, METH_NOARGS,
      NULL },
    { "get_encoding", (PyCFunction)_wrap_moo_open_info_get_encoding, METH_NOARGS,
      NULL },
    { "get_file", (PyCFunction)_wrap_moo_open_info_get_file, METH_NOARGS,
      NULL },
    { "get_filename", (PyCFunction)_wrap_moo_open_info_get_filename, METH_NOARGS,
      NULL },
    { "get_flags", (PyCFunction)_wrap_moo_open_info_get_flags, METH_NOARGS,
      NULL },
    { "get_line", (PyCFunction)_wrap_moo_open_info_get_line, METH_NOARGS,
      NULL },
    { "get_uri", (PyCFunction)_wrap_moo_open_info_get_uri, METH_NOARGS,
      NULL },
    { "set_encoding", (PyCFunction)_wrap_moo_open_info_set_encoding, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_flags", (PyCFunction)_wrap_moo_open_info_set_flags, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_line", (PyCFunction)_wrap_moo_open_info_set_line, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "new_file", (PyCFunction)_wrap_moo_open_info_new_file, METH_VARARGS|METH_KEYWORDS|METH_STATIC,
      NULL },
    { "new_uri", (PyCFunction)_wrap_moo_open_info_new_uri, METH_VARARGS|METH_KEYWORDS|METH_STATIC,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooOpenInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.OpenInfo",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooOpenInfo_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_moo_open_info_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooPane ----------- */

static PyObject *
_wrap_moo_pane_attach(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_attach");
#endif
    
    moo_pane_attach(MOO_PANE(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_detach(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_detach");
#endif
    
    moo_pane_detach(MOO_PANE(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_get_child(PyGObject *self)
{
    GtkWidget *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_get_child");
#endif
    
    ret = moo_pane_get_child(MOO_PANE(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_pane_get_detachable(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_get_detachable");
#endif
    
    ret = moo_pane_get_detachable(MOO_PANE(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_pane_get_id(PyGObject *self)
{
    const gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_get_id");
#endif
    
    ret = moo_pane_get_id(MOO_PANE(self->obj));
    
    if (ret)
        return PyUnicode_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_get_index(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_get_index");
#endif
    
    ret = moo_pane_get_index(MOO_PANE(self->obj));
    
    return PyLong_FromLong(ret);
}

static PyObject *
_wrap_moo_pane_get_label(PyGObject *self)
{
    MooPaneLabel *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_get_label");
#endif
    
    ret = moo_pane_get_label(MOO_PANE(self->obj));
    
    /* pyg_boxed_new handles NULL checking */
    return pyg_boxed_new(MOO_TYPE_PANE_LABEL, ret, TRUE, TRUE);
}

static PyObject *
_wrap_moo_pane_get_params(PyGObject *self)
{
    MooPaneParams *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_get_params");
#endif
    
    ret = moo_pane_get_params(MOO_PANE(self->obj));
    
    /* pyg_boxed_new handles NULL checking */
    return pyg_boxed_new(MOO_TYPE_PANE_PARAMS, ret, TRUE, TRUE);
}

static PyObject *
_wrap_moo_pane_get_removable(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_get_removable");
#endif
    
    ret = moo_pane_get_removable(MOO_PANE(self->obj));
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_pane_open(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_open");
#endif
    
    moo_pane_open(MOO_PANE(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_present(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_present");
#endif
    
    moo_pane_present(MOO_PANE(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_set_detachable(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "detachable", NULL };
    int detachable;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:MooPane.set_detachable", kwlist, &detachable))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_set_detachable");
#endif
    
    moo_pane_set_detachable(MOO_PANE(self->obj), detachable);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_set_drag_dest(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_set_drag_dest");
#endif
    
    moo_pane_set_drag_dest(MOO_PANE(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_set_frame_markup(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "markup", NULL };
    char *markup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"z:MooPane.set_frame_markup", kwlist, &markup))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_set_frame_markup");
#endif
    
    moo_pane_set_frame_markup(MOO_PANE(self->obj), markup);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_set_frame_text(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "text", NULL };
    char *text;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"z:MooPane.set_frame_text", kwlist, &text))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_set_frame_text");
#endif
    
    moo_pane_set_frame_text(MOO_PANE(self->obj), text);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_set_label(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "label", NULL };
    MooPaneLabel *label = NULL;
    PyObject *py_label;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooPane.set_label", kwlist, &py_label))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_set_label");
#endif
    if (pyg_boxed_check(py_label, MOO_TYPE_PANE_LABEL))
        label = pyg_boxed_get(py_label, MooPaneLabel);
    else {
        PyErr_SetString(PyExc_TypeError, "label should be a MooPaneLabel");
        return NULL;
    }
    
    moo_pane_set_label(MOO_PANE(self->obj), label);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_set_params(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "params", NULL };
    MooPaneParams *params = NULL;
    PyObject *py_params;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooPane.set_params", kwlist, &py_params))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_set_params");
#endif
    if (pyg_boxed_check(py_params, MOO_TYPE_PANE_PARAMS))
        params = pyg_boxed_get(py_params, MooPaneParams);
    else {
        PyErr_SetString(PyExc_TypeError, "params should be a MooPaneParams");
        return NULL;
    }
    
    moo_pane_set_params(MOO_PANE(self->obj), params);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_set_removable(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "removable", NULL };
    int removable;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:MooPane.set_removable", kwlist, &removable))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_set_removable");
#endif
    
    moo_pane_set_removable(MOO_PANE(self->obj), removable);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_pane_unset_drag_dest(PyGObject *self)
{
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_pane_unset_drag_dest");
#endif
    
    moo_pane_unset_drag_dest(MOO_PANE(self->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooPane_methods[] = {
    { "attach", (PyCFunction)_wrap_moo_pane_attach, METH_NOARGS,
      NULL },
    { "detach", (PyCFunction)_wrap_moo_pane_detach, METH_NOARGS,
      NULL },
    { "get_child", (PyCFunction)_wrap_moo_pane_get_child, METH_NOARGS,
      NULL },
    { "get_detachable", (PyCFunction)_wrap_moo_pane_get_detachable, METH_NOARGS,
      NULL },
    { "get_id", (PyCFunction)_wrap_moo_pane_get_id, METH_NOARGS,
      NULL },
    { "get_index", (PyCFunction)_wrap_moo_pane_get_index, METH_NOARGS,
      NULL },
    { "get_label", (PyCFunction)_wrap_moo_pane_get_label, METH_NOARGS,
      NULL },
    { "get_params", (PyCFunction)_wrap_moo_pane_get_params, METH_NOARGS,
      NULL },
    { "get_removable", (PyCFunction)_wrap_moo_pane_get_removable, METH_NOARGS,
      NULL },
    { "open", (PyCFunction)_wrap_moo_pane_open, METH_NOARGS,
      NULL },
    { "present", (PyCFunction)_wrap_moo_pane_present, METH_NOARGS,
      NULL },
    { "set_detachable", (PyCFunction)_wrap_moo_pane_set_detachable, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_drag_dest", (PyCFunction)_wrap_moo_pane_set_drag_dest, METH_NOARGS,
      NULL },
    { "set_frame_markup", (PyCFunction)_wrap_moo_pane_set_frame_markup, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_frame_text", (PyCFunction)_wrap_moo_pane_set_frame_text, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_label", (PyCFunction)_wrap_moo_pane_set_label, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_params", (PyCFunction)_wrap_moo_pane_set_params, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_removable", (PyCFunction)_wrap_moo_pane_set_removable, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "unset_drag_dest", (PyCFunction)_wrap_moo_pane_unset_drag_dest, METH_NOARGS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooPane_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.Pane",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooPane_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooPaned ----------- */

static int
_wrap_MooPaned__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.Paned.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.Paned object");
        return -1;
    }
    return 0;
}

PyTypeObject G_GNUC_INTERNAL PyMooPaned_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.Paned",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooPaned__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooPlugin ----------- */

static PyObject *
_wrap_moo_plugin_set_doc_plugin_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "type", NULL };
    GType type;
    PyObject *py_type = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooPlugin.set_doc_plugin_type", kwlist, &py_type))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_plugin_set_doc_plugin_type");
#endif
    if ((type = pyg_type_from_object(py_type)) == 0)
        return NULL;
    
    moo_plugin_set_doc_plugin_type(MOO_PLUGIN(self->obj), type);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_plugin_set_info(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "info", NULL };
    MooPluginInfo *info = NULL;
    PyObject *py_info;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooPlugin.set_info", kwlist, &py_info))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_plugin_set_info");
#endif
    if (pyg_boxed_check(py_info, MOO_TYPE_PLUGIN_INFO))
        info = pyg_boxed_get(py_info, MooPluginInfo);
    else {
        PyErr_SetString(PyExc_TypeError, "info should be a MooPluginInfo");
        return NULL;
    }
    
    moo_plugin_set_info(MOO_PLUGIN(self->obj), info);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_plugin_set_win_plugin_type(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "type", NULL };
    GType type;
    PyObject *py_type = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooPlugin.set_win_plugin_type", kwlist, &py_type))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_plugin_set_win_plugin_type");
#endif
    if ((type = pyg_type_from_object(py_type)) == 0)
        return NULL;
    
    moo_plugin_set_win_plugin_type(MOO_PLUGIN(self->obj), type);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_MooPlugin__do_attach_doc(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", (char*) "doc", (char*) "window", NULL };
    PyGObject *self, *doc, *window;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!O!O!:MooPlugin.attach_doc", kwlist, &PyMooPlugin_Type, &self, &PyMooEdit_Type, &doc, &PyMooEditWindow_Type, &window))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PLUGIN_CLASS(klass)->attach_doc)
        MOO_PLUGIN_CLASS(klass)->attach_doc(MOO_PLUGIN(self->obj), MOO_EDIT(doc->obj), MOO_EDIT_WINDOW(window->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPlugin.attach_doc not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_MooPlugin__do_attach_win(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", (char*) "window", NULL };
    PyGObject *self, *window;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!O!:MooPlugin.attach_win", kwlist, &PyMooPlugin_Type, &self, &PyMooEditWindow_Type, &window))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PLUGIN_CLASS(klass)->attach_win)
        MOO_PLUGIN_CLASS(klass)->attach_win(MOO_PLUGIN(self->obj), MOO_EDIT_WINDOW(window->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPlugin.attach_win not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_MooPlugin__do_create_prefs_page(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;
    GtkWidget *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooPlugin.create_prefs_page", kwlist, &PyMooPlugin_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PLUGIN_CLASS(klass)->create_prefs_page)
        ret = MOO_PLUGIN_CLASS(klass)->create_prefs_page(MOO_PLUGIN(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPlugin.create_prefs_page not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_MooPlugin__do_deinit(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooPlugin.deinit", kwlist, &PyMooPlugin_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PLUGIN_CLASS(klass)->deinit)
        MOO_PLUGIN_CLASS(klass)->deinit(MOO_PLUGIN(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPlugin.deinit not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_MooPlugin__do_detach_doc(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", (char*) "doc", (char*) "window", NULL };
    PyGObject *self, *doc, *window;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!O!O!:MooPlugin.detach_doc", kwlist, &PyMooPlugin_Type, &self, &PyMooEdit_Type, &doc, &PyMooEditWindow_Type, &window))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PLUGIN_CLASS(klass)->detach_doc)
        MOO_PLUGIN_CLASS(klass)->detach_doc(MOO_PLUGIN(self->obj), MOO_EDIT(doc->obj), MOO_EDIT_WINDOW(window->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPlugin.detach_doc not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_MooPlugin__do_detach_win(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", (char*) "window", NULL };
    PyGObject *self, *window;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!O!:MooPlugin.detach_win", kwlist, &PyMooPlugin_Type, &self, &PyMooEditWindow_Type, &window))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PLUGIN_CLASS(klass)->detach_win)
        MOO_PLUGIN_CLASS(klass)->detach_win(MOO_PLUGIN(self->obj), MOO_EDIT_WINDOW(window->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPlugin.detach_win not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_MooPlugin__do_init(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooPlugin.init", kwlist, &PyMooPlugin_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PLUGIN_CLASS(klass)->init)
        ret = MOO_PLUGIN_CLASS(klass)->init(MOO_PLUGIN(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPlugin.init not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    return PyBool_FromLong(ret);

}

static const PyMethodDef _PyMooPlugin_methods[] = {
    { "set_doc_plugin_type", (PyCFunction)_wrap_moo_plugin_set_doc_plugin_type, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_info", (PyCFunction)_wrap_moo_plugin_set_info, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_win_plugin_type", (PyCFunction)_wrap_moo_plugin_set_win_plugin_type, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "do_attach_doc", (PyCFunction)_wrap_MooPlugin__do_attach_doc, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_attach_win", (PyCFunction)_wrap_MooPlugin__do_attach_win, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_create_prefs_page", (PyCFunction)_wrap_MooPlugin__do_create_prefs_page, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_deinit", (PyCFunction)_wrap_MooPlugin__do_deinit, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_detach_doc", (PyCFunction)_wrap_MooPlugin__do_detach_doc, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_detach_win", (PyCFunction)_wrap_MooPlugin__do_detach_win, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_init", (PyCFunction)_wrap_MooPlugin__do_init, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooPlugin_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.Plugin",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooPlugin_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};

static void
_wrap_MooPlugin__proxy_do_attach_doc(MooPlugin *self, MooEdit*doc, MooEditWindow*window)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_doc = NULL;
    PyObject *py_window = NULL;
    PyObject *py_retval;
    PyObject *py_args;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    if (doc)
        py_doc = pygobject_new((GObject *) doc);
    else {
        Py_INCREF(Py_None);
        py_doc = Py_None;
    }
    if (window)
        py_window = pygobject_new((GObject *) window);
    else {
        Py_INCREF(Py_None);
        py_window = Py_None;
    }
    
    py_args = PyTuple_New(2);
    PyTuple_SET_ITEM(py_args, 0, py_doc);
    PyTuple_SET_ITEM(py_args, 1, py_window);
    
    py_method = PyObject_GetAttrString(py_self, "do_attach_doc");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, py_args);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_args);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}
static void
_wrap_MooPlugin__proxy_do_attach_win(MooPlugin *self, MooEditWindow*window)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_window = NULL;
    PyObject *py_retval;
    PyObject *py_args;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    if (window)
        py_window = pygobject_new((GObject *) window);
    else {
        Py_INCREF(Py_None);
        py_window = Py_None;
    }
    
    py_args = PyTuple_New(1);
    PyTuple_SET_ITEM(py_args, 0, py_window);
    
    py_method = PyObject_GetAttrString(py_self, "do_attach_win");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, py_args);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_args);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}
static GtkWidget*
_wrap_MooPlugin__proxy_do_create_prefs_page(MooPlugin *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    GtkWidget* retval;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return NULL;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_create_prefs_page");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return NULL;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return NULL;
    }
    if (!PyObject_TypeCheck(py_retval, &PyGObject_Type)) {
        PyErr_SetString(PyExc_TypeError, "retval should be a GObject");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return NULL;
    }
    retval = (GtkWidget*) pygobject_get(py_retval);
    g_object_ref((GObject *) retval);
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
    
    return retval;
}
static void
_wrap_MooPlugin__proxy_do_deinit(MooPlugin *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_deinit");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}
static void
_wrap_MooPlugin__proxy_do_detach_doc(MooPlugin *self, MooEdit*doc, MooEditWindow*window)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_doc = NULL;
    PyObject *py_window = NULL;
    PyObject *py_retval;
    PyObject *py_args;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    if (doc)
        py_doc = pygobject_new((GObject *) doc);
    else {
        Py_INCREF(Py_None);
        py_doc = Py_None;
    }
    if (window)
        py_window = pygobject_new((GObject *) window);
    else {
        Py_INCREF(Py_None);
        py_window = Py_None;
    }
    
    py_args = PyTuple_New(2);
    PyTuple_SET_ITEM(py_args, 0, py_doc);
    PyTuple_SET_ITEM(py_args, 1, py_window);
    
    py_method = PyObject_GetAttrString(py_self, "do_detach_doc");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, py_args);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_args);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}
static void
_wrap_MooPlugin__proxy_do_detach_win(MooPlugin *self, MooEditWindow*window)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_window = NULL;
    PyObject *py_retval;
    PyObject *py_args;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    if (window)
        py_window = pygobject_new((GObject *) window);
    else {
        Py_INCREF(Py_None);
        py_window = Py_None;
    }
    
    py_args = PyTuple_New(1);
    PyTuple_SET_ITEM(py_args, 0, py_window);
    
    py_method = PyObject_GetAttrString(py_self, "do_detach_win");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, py_args);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_args);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_args);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}
static gboolean
_wrap_MooPlugin__proxy_do_init(MooPlugin *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    gboolean retval;
    PyObject *py_main_retval;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_init");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = Py_BuildValue("(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, "O", &py_main_retval)) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    
    retval = PyObject_IsTrue(py_main_retval)? TRUE : FALSE;
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
    
    return retval;
}

static int
__MooPlugin_class_init(G_GNUC_UNUSED gpointer gclass, G_GNUC_UNUSED PyTypeObject *pyclass)
{
    PyObject *o;
    MooPluginClass *klass = MOO_PLUGIN_CLASS(gclass);
    PyObject *gsignals = PyDict_GetItemString(pyclass->tp_dict, "__gsignals__");

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_attach_doc");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "attach_doc")))
            klass->attach_doc = _wrap_MooPlugin__proxy_do_attach_doc;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_attach_win");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "attach_win")))
            klass->attach_win = _wrap_MooPlugin__proxy_do_attach_win;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_create_prefs_page");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "create_prefs_page")))
            klass->create_prefs_page = _wrap_MooPlugin__proxy_do_create_prefs_page;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_deinit");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "deinit")))
            klass->deinit = _wrap_MooPlugin__proxy_do_deinit;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_detach_doc");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "detach_doc")))
            klass->detach_doc = _wrap_MooPlugin__proxy_do_detach_doc;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_detach_win");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "detach_win")))
            klass->detach_win = _wrap_MooPlugin__proxy_do_detach_win;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_init");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "init")))
            klass->init = _wrap_MooPlugin__proxy_do_init;
        Py_DECREF(o);
    }
    return 0;
}


/* ----------- MooPrefsDialog ----------- */

static int
_wrap_MooPrefsDialog__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.PrefsDialog.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.PrefsDialog object");
        return -1;
    }
    return 0;
}

static PyObject *
_wrap_MooPrefsDialog__do_apply(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooPrefsDialog.apply", kwlist, &PyMooPrefsDialog_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PREFS_DIALOG_CLASS(klass)->apply)
        MOO_PREFS_DIALOG_CLASS(klass)->apply(MOO_PREFS_DIALOG(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPrefsDialog.apply not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_MooPrefsDialog__do_init(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooPrefsDialog.init", kwlist, &PyMooPrefsDialog_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PREFS_DIALOG_CLASS(klass)->init)
        MOO_PREFS_DIALOG_CLASS(klass)->init(MOO_PREFS_DIALOG(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPrefsDialog.init not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooPrefsDialog_methods[] = {
    { "do_apply", (PyCFunction)_wrap_MooPrefsDialog__do_apply, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_init", (PyCFunction)_wrap_MooPrefsDialog__do_init, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooPrefsDialog_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.PrefsDialog",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooPrefsDialog_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooPrefsDialog__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};

static void
_wrap_MooPrefsDialog__proxy_do_apply(MooPrefsDialog *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_apply");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}
static void
_wrap_MooPrefsDialog__proxy_do_init(MooPrefsDialog *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_init");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}

static int
__MooPrefsDialog_class_init(G_GNUC_UNUSED gpointer gclass, G_GNUC_UNUSED PyTypeObject *pyclass)
{
    PyObject *o;
    MooPrefsDialogClass *klass = MOO_PREFS_DIALOG_CLASS(gclass);
    PyObject *gsignals = PyDict_GetItemString(pyclass->tp_dict, "__gsignals__");

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_apply");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "apply")))
            klass->apply = _wrap_MooPrefsDialog__proxy_do_apply;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_init");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "init")))
            klass->init = _wrap_MooPrefsDialog__proxy_do_init;
        Py_DECREF(o);
    }
    return 0;
}


/* ----------- MooPrefsPage ----------- */

static int
_wrap_MooPrefsPage__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.PrefsPage.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.PrefsPage object");
        return -1;
    }
    return 0;
}

static PyObject *
_wrap_MooPrefsPage__do_apply(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooPrefsPage.apply", kwlist, &PyMooPrefsPage_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PREFS_PAGE_CLASS(klass)->apply)
        MOO_PREFS_PAGE_CLASS(klass)->apply(MOO_PREFS_PAGE(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPrefsPage.apply not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_MooPrefsPage__do_init(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooPrefsPage.init", kwlist, &PyMooPrefsPage_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_PREFS_PAGE_CLASS(klass)->init)
        MOO_PREFS_PAGE_CLASS(klass)->init(MOO_PREFS_PAGE(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooPrefsPage.init not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooPrefsPage_methods[] = {
    { "do_apply", (PyCFunction)_wrap_MooPrefsPage__do_apply, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_init", (PyCFunction)_wrap_MooPrefsPage__do_init, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooPrefsPage_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.PrefsPage",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooPrefsPage_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooPrefsPage__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};

static void
_wrap_MooPrefsPage__proxy_do_apply(MooPrefsPage *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_apply");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}
static void
_wrap_MooPrefsPage__proxy_do_init(MooPrefsPage *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_init");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}

static int
__MooPrefsPage_class_init(G_GNUC_UNUSED gpointer gclass, G_GNUC_UNUSED PyTypeObject *pyclass)
{
    PyObject *o;
    MooPrefsPageClass *klass = MOO_PREFS_PAGE_CLASS(gclass);
    PyObject *gsignals = PyDict_GetItemString(pyclass->tp_dict, "__gsignals__");

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_apply");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "apply")))
            klass->apply = _wrap_MooPrefsPage__proxy_do_apply;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_init");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "init")))
            klass->init = _wrap_MooPrefsPage__proxy_do_init;
        Py_DECREF(o);
    }
    return 0;
}


/* ----------- MooReloadInfo ----------- */

static int
_wrap_moo_reload_info_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "encoding", (char*) "line", NULL };
    char *encoding = NULL;
    int line = -1;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|zi:MooReloadInfo.__init__", kwlist, &encoding, &line))
        return -1;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_reload_info_new");
#endif
    self->obj = (GObject *)moo_reload_info_new(encoding, line);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create MooReloadInfo object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_moo_reload_info_dup(PyGObject *self)
{
    MooReloadInfo *ret;
    PyObject *py_ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_reload_info_dup");
#endif
    
    ret = moo_reload_info_dup(MOO_RELOAD_INFO(self->obj));
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static PyObject *
_wrap_moo_reload_info_get_line(PyGObject *self)
{
    int ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_reload_info_get_line");
#endif
    
    ret = moo_reload_info_get_line(MOO_RELOAD_INFO(self->obj));
    
    return PyLong_FromLong(ret);
}

static PyObject *
_wrap_moo_reload_info_set_line(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "line", NULL };
    int line;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:MooReloadInfo.set_line", kwlist, &line))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_reload_info_set_line");
#endif
    
    moo_reload_info_set_line(MOO_RELOAD_INFO(self->obj), line);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooReloadInfo_methods[] = {
    { "dup", (PyCFunction)_wrap_moo_reload_info_dup, METH_NOARGS,
      NULL },
    { "get_line", (PyCFunction)_wrap_moo_reload_info_get_line, METH_NOARGS,
      NULL },
    { "set_line", (PyCFunction)_wrap_moo_reload_info_set_line, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooReloadInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.ReloadInfo",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooReloadInfo_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_moo_reload_info_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooSaveInfo ----------- */

static int
_wrap_moo_save_info_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "path", (char*) "encoding", NULL };
    char *path, *encoding = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|z:MooSaveInfo.__init__", kwlist, &path, &encoding))
        return -1;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_save_info_new");
#endif
    self->obj = (GObject *)moo_save_info_new(path, encoding);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create MooSaveInfo object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_moo_save_info_dup(PyGObject *self)
{
    MooSaveInfo *ret;
    PyObject *py_ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_save_info_dup");
#endif
    
    ret = moo_save_info_dup(MOO_SAVE_INFO(self->obj));
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static PyObject *
_wrap_moo_save_info_new_file(G_GNUC_UNUSED PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "file", (char*) "encoding", NULL };
    PyGObject *file;
    char *encoding = NULL;
    MooSaveInfo *ret;
    PyObject *py_ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!|z:MooSaveInfo.new_file", kwlist, &PyGFile_Type, &file, &encoding))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_save_info_new_file");
#endif
    
    ret = moo_save_info_new_file(G_FILE(file->obj), encoding);
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static PyObject *
_wrap_moo_save_info_new_uri(G_GNUC_UNUSED PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "uri", (char*) "encoding", NULL };
    char *uri, *encoding = NULL;
    MooSaveInfo *ret;
    PyObject *py_ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|z:MooSaveInfo.new_uri", kwlist, &uri, &encoding))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_save_info_new_uri");
#endif
    
    ret = moo_save_info_new_uri(uri, encoding);
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static const PyMethodDef _PyMooSaveInfo_methods[] = {
    { "dup", (PyCFunction)_wrap_moo_save_info_dup, METH_NOARGS,
      NULL },
    { "new_file", (PyCFunction)_wrap_moo_save_info_new_file, METH_VARARGS|METH_KEYWORDS|METH_STATIC,
      NULL },
    { "new_uri", (PyCFunction)_wrap_moo_save_info_new_uri, METH_VARARGS|METH_KEYWORDS|METH_STATIC,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooSaveInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.SaveInfo",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooSaveInfo_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_moo_save_info_new,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooTextBuffer ----------- */

PyTypeObject G_GNUC_INTERNAL PyMooTextBuffer_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.TextBuffer",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)NULL, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooUiXml ----------- */

static int
_wrap_MooUiXml__new__(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char* kwlist[] = { NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     ":moo.UiXml.__init__",
                                     kwlist))
        return -1;

    self->obj = (GObject*)g_object_new(pyg_type_from_object((PyObject*)self), NULL);
    if (!self->obj) {
        PyErr_SetString(
            PyExc_RuntimeError, 
            "could not create moo.UiXml object");
        return -1;
    }
    return 0;
}

static PyObject *
_wrap_moo_ui_xml_add_item(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "merge_id", (char*) "parent_path", (char*) "name", (char*) "action", (char*) "position", NULL };
    guint merge_id = 0;
    PyObject *py_merge_id = NULL;
    char *parent_path, *name = NULL, *action;
    int position = -1;
    MooUiNode *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"Os|zsi:MooUiXml.add_item", kwlist, &py_merge_id, &parent_path, &name, &action, &position))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_add_item");
#endif
    if (py_merge_id) {
        if (PyLong_Check(py_merge_id))
            merge_id = PyLong_AsUnsignedLong(py_merge_id);
        else
            PyErr_SetString(PyExc_TypeError, "Parameter 'merge_id' must be an int");
        if (PyErr_Occurred())
            return NULL;
    }
    
    ret = moo_ui_xml_add_item(MOO_UI_XML(self->obj), merge_id, parent_path, name, action, position);
    
    /* pyg_pointer_new handles NULL checking */
    return pyg_pointer_new(MOO_TYPE_UI_NODE, ret);
}

static PyObject *
_wrap_moo_ui_xml_add_ui_from_string(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "buffer", (char*) "length", NULL };
    char *buffer;
    int length = -1;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|i:MooUiXml.add_ui_from_string", kwlist, &buffer, &length))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_add_ui_from_string");
#endif
    
    moo_ui_xml_add_ui_from_string(MOO_UI_XML(self->obj), buffer, length);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_ui_xml_create_widget(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "type", (char*) "path", (char*) "actions", (char*) "accel_group", NULL };
    MooUiWidgetType type;
    PyObject *py_type = NULL;
    char *path;
    PyGObject *actions, *accel_group;
    GtkWidget *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"OsO!O!:MooUiXml.create_widget", kwlist, &py_type, &path, &PyMooActionCollection_Type, &actions, &PyGtkAccelGroup_Type, &accel_group))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_create_widget");
#endif
    if (pyg_enum_get_value(MOO_TYPE_UI_WIDGET_TYPE, py_type, (int*)&type))
        return NULL;
    
    ret = moo_ui_xml_create_widget(MOO_UI_XML(self->obj), type, path, MOO_ACTION_COLLECTION(actions->obj), GTK_ACCEL_GROUP(accel_group->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_ui_xml_find_placeholder(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "name", NULL };
    char *name;
    MooUiNode *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooUiXml.find_placeholder", kwlist, &name))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_find_placeholder");
#endif
    
    ret = moo_ui_xml_find_placeholder(MOO_UI_XML(self->obj), name);
    
    /* pyg_pointer_new handles NULL checking */
    return pyg_pointer_new(MOO_TYPE_UI_NODE, ret);
}

static PyObject *
_wrap_moo_ui_xml_get_node(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "path", NULL };
    char *path;
    MooUiNode *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:MooUiXml.get_node", kwlist, &path))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_get_node");
#endif
    
    ret = moo_ui_xml_get_node(MOO_UI_XML(self->obj), path);
    
    /* pyg_pointer_new handles NULL checking */
    return pyg_pointer_new(MOO_TYPE_UI_NODE, ret);
}

static PyObject *
_wrap_moo_ui_xml_get_widget(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "widget", (char*) "path", NULL };
    PyGObject *widget;
    char *path;
    GtkWidget *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!s:MooUiXml.get_widget", kwlist, &PyGtkWidget_Type, &widget, &path))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_get_widget");
#endif
    
    ret = moo_ui_xml_get_widget(MOO_UI_XML(self->obj), GTK_WIDGET(widget->obj), path);
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_ui_xml_insert(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "merge_id", (char*) "parent", (char*) "position", (char*) "markup", NULL };
    guint merge_id = 0;
    PyObject *py_merge_id = NULL, *py_parent;
    MooUiNode *parent = NULL;
    int position = -1;
    char *markup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"OO|is:MooUiXml.insert", kwlist, &py_merge_id, &py_parent, &position, &markup))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_insert");
#endif
    if (py_merge_id) {
        if (PyLong_Check(py_merge_id))
            merge_id = PyLong_AsUnsignedLong(py_merge_id);
        else
            PyErr_SetString(PyExc_TypeError, "Parameter 'merge_id' must be an int");
        if (PyErr_Occurred())
            return NULL;
    }
    if (pyg_pointer_check(py_parent, MOO_TYPE_UI_NODE))
        parent = pyg_pointer_get(py_parent, MooUiNode);
    else {
        PyErr_SetString(PyExc_TypeError, "parent should be a MooUiNode");
        return NULL;
    }
    
    moo_ui_xml_insert(MOO_UI_XML(self->obj), merge_id, parent, position, markup);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_ui_xml_insert_after(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "merge_id", (char*) "parent", (char*) "after", (char*) "markup", NULL };
    guint merge_id = 0;
    PyObject *py_merge_id = NULL, *py_parent, *py_after;
    MooUiNode *parent = NULL, *after = NULL;
    char *markup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"OOOs:MooUiXml.insert_after", kwlist, &py_merge_id, &py_parent, &py_after, &markup))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_insert_after");
#endif
    if (py_merge_id) {
        if (PyLong_Check(py_merge_id))
            merge_id = PyLong_AsUnsignedLong(py_merge_id);
        else
            PyErr_SetString(PyExc_TypeError, "Parameter 'merge_id' must be an int");
        if (PyErr_Occurred())
            return NULL;
    }
    if (pyg_pointer_check(py_parent, MOO_TYPE_UI_NODE))
        parent = pyg_pointer_get(py_parent, MooUiNode);
    else {
        PyErr_SetString(PyExc_TypeError, "parent should be a MooUiNode");
        return NULL;
    }
    if (pyg_pointer_check(py_after, MOO_TYPE_UI_NODE))
        after = pyg_pointer_get(py_after, MooUiNode);
    else {
        PyErr_SetString(PyExc_TypeError, "after should be a MooUiNode");
        return NULL;
    }
    
    moo_ui_xml_insert_after(MOO_UI_XML(self->obj), merge_id, parent, after, markup);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_ui_xml_insert_before(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "merge_id", (char*) "parent", (char*) "before", (char*) "markup", NULL };
    guint merge_id = 0;
    PyObject *py_merge_id = NULL, *py_parent, *py_before;
    MooUiNode *parent = NULL, *before = NULL;
    char *markup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"OOOs:MooUiXml.insert_before", kwlist, &py_merge_id, &py_parent, &py_before, &markup))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_insert_before");
#endif
    if (py_merge_id) {
        if (PyLong_Check(py_merge_id))
            merge_id = PyLong_AsUnsignedLong(py_merge_id);
        else
            PyErr_SetString(PyExc_TypeError, "Parameter 'merge_id' must be an int");
        if (PyErr_Occurred())
            return NULL;
    }
    if (pyg_pointer_check(py_parent, MOO_TYPE_UI_NODE))
        parent = pyg_pointer_get(py_parent, MooUiNode);
    else {
        PyErr_SetString(PyExc_TypeError, "parent should be a MooUiNode");
        return NULL;
    }
    if (pyg_pointer_check(py_before, MOO_TYPE_UI_NODE))
        before = pyg_pointer_get(py_before, MooUiNode);
    else {
        PyErr_SetString(PyExc_TypeError, "before should be a MooUiNode");
        return NULL;
    }
    
    moo_ui_xml_insert_before(MOO_UI_XML(self->obj), merge_id, parent, before, markup);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_ui_xml_insert_markup(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "merge_id", (char*) "parent_path", (char*) "position", (char*) "markup", NULL };
    guint merge_id = 0;
    PyObject *py_merge_id = NULL;
    char *parent_path, *markup;
    int position = -1;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"Os|is:MooUiXml.insert_markup", kwlist, &py_merge_id, &parent_path, &position, &markup))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_insert_markup");
#endif
    if (py_merge_id) {
        if (PyLong_Check(py_merge_id))
            merge_id = PyLong_AsUnsignedLong(py_merge_id);
        else
            PyErr_SetString(PyExc_TypeError, "Parameter 'merge_id' must be an int");
        if (PyErr_Occurred())
            return NULL;
    }
    
    moo_ui_xml_insert_markup(MOO_UI_XML(self->obj), merge_id, parent_path, position, markup);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_ui_xml_insert_markup_after(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "merge_id", (char*) "parent_path", (char*) "after_name", (char*) "markup", NULL };
    guint merge_id = 0;
    PyObject *py_merge_id = NULL;
    char *parent_path, *after_name, *markup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"Osss:MooUiXml.insert_markup_after", kwlist, &py_merge_id, &parent_path, &after_name, &markup))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_insert_markup_after");
#endif
    if (py_merge_id) {
        if (PyLong_Check(py_merge_id))
            merge_id = PyLong_AsUnsignedLong(py_merge_id);
        else
            PyErr_SetString(PyExc_TypeError, "Parameter 'merge_id' must be an int");
        if (PyErr_Occurred())
            return NULL;
    }
    
    moo_ui_xml_insert_markup_after(MOO_UI_XML(self->obj), merge_id, parent_path, after_name, markup);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_ui_xml_insert_markup_before(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "merge_id", (char*) "parent_path", (char*) "before_name", (char*) "markup", NULL };
    guint merge_id = 0;
    PyObject *py_merge_id = NULL;
    char *parent_path, *before_name, *markup;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"Osss:MooUiXml.insert_markup_before", kwlist, &py_merge_id, &parent_path, &before_name, &markup))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_insert_markup_before");
#endif
    if (py_merge_id) {
        if (PyLong_Check(py_merge_id))
            merge_id = PyLong_AsUnsignedLong(py_merge_id);
        else
            PyErr_SetString(PyExc_TypeError, "Parameter 'merge_id' must be an int");
        if (PyErr_Occurred())
            return NULL;
    }
    
    moo_ui_xml_insert_markup_before(MOO_UI_XML(self->obj), merge_id, parent_path, before_name, markup);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_ui_xml_new_merge_id(PyGObject *self)
{
    guint ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_new_merge_id");
#endif
    
    ret = moo_ui_xml_new_merge_id(MOO_UI_XML(self->obj));
    
    return PyLong_FromUnsignedLong(ret);
}

static PyObject *
_wrap_moo_ui_xml_remove_node(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "node", NULL };
    MooUiNode *node = NULL;
    PyObject *py_node;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooUiXml.remove_node", kwlist, &py_node))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_remove_node");
#endif
    if (pyg_pointer_check(py_node, MOO_TYPE_UI_NODE))
        node = pyg_pointer_get(py_node, MooUiNode);
    else {
        PyErr_SetString(PyExc_TypeError, "node should be a MooUiNode");
        return NULL;
    }
    
    moo_ui_xml_remove_node(MOO_UI_XML(self->obj), node);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_ui_xml_remove_ui(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "merge_id", NULL };
    guint merge_id = 0;
    PyObject *py_merge_id = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:MooUiXml.remove_ui", kwlist, &py_merge_id))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_ui_xml_remove_ui");
#endif
    if (py_merge_id) {
        if (PyLong_Check(py_merge_id))
            merge_id = PyLong_AsUnsignedLong(py_merge_id);
        else
            PyErr_SetString(PyExc_TypeError, "Parameter 'merge_id' must be an int");
        if (PyErr_Occurred())
            return NULL;
    }
    
    moo_ui_xml_remove_ui(MOO_UI_XML(self->obj), merge_id);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooUiXml_methods[] = {
    { "add_item", (PyCFunction)_wrap_moo_ui_xml_add_item, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "add_ui_from_string", (PyCFunction)_wrap_moo_ui_xml_add_ui_from_string, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "create_widget", (PyCFunction)_wrap_moo_ui_xml_create_widget, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "find_placeholder", (PyCFunction)_wrap_moo_ui_xml_find_placeholder, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_node", (PyCFunction)_wrap_moo_ui_xml_get_node, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_widget", (PyCFunction)_wrap_moo_ui_xml_get_widget, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "insert", (PyCFunction)_wrap_moo_ui_xml_insert, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "insert_after", (PyCFunction)_wrap_moo_ui_xml_insert_after, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "insert_before", (PyCFunction)_wrap_moo_ui_xml_insert_before, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "insert_markup", (PyCFunction)_wrap_moo_ui_xml_insert_markup, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "insert_markup_after", (PyCFunction)_wrap_moo_ui_xml_insert_markup_after, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "insert_markup_before", (PyCFunction)_wrap_moo_ui_xml_insert_markup_before, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "new_merge_id", (PyCFunction)_wrap_moo_ui_xml_new_merge_id, METH_NOARGS,
      NULL },
    { "remove_node", (PyCFunction)_wrap_moo_ui_xml_remove_node, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "remove_ui", (PyCFunction)_wrap_moo_ui_xml_remove_ui, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooUiXml_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.UiXml",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooUiXml_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_MooUiXml__new__,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};



/* ----------- MooWinPlugin ----------- */

static PyObject *
_wrap_moo_win_plugin_get_plugin(PyGObject *self)
{
    MooPlugin *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_win_plugin_get_plugin");
#endif
    
    ret = moo_win_plugin_get_plugin(MOO_WIN_PLUGIN(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_moo_win_plugin_get_window(PyGObject *self)
{
    MooEditWindow *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_win_plugin_get_window");
#endif
    
    ret = moo_win_plugin_get_window(MOO_WIN_PLUGIN(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_MooWinPlugin__do_create(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooWinPlugin.create", kwlist, &PyMooWinPlugin_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_WIN_PLUGIN_CLASS(klass)->create)
        ret = MOO_WIN_PLUGIN_CLASS(klass)->create(MOO_WIN_PLUGIN(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooWinPlugin.create not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_MooWinPlugin__do_destroy(PyObject *cls, PyObject *args, PyObject *kwargs)
{
    gpointer klass;
    static char *kwlist[] = { (char*) "self", NULL };
    PyGObject *self;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:MooWinPlugin.destroy", kwlist, &PyMooWinPlugin_Type, &self))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "None");
#endif
    klass = g_type_class_ref(pyg_type_from_object(cls));
    if (MOO_WIN_PLUGIN_CLASS(klass)->destroy)
        MOO_WIN_PLUGIN_CLASS(klass)->destroy(MOO_WIN_PLUGIN(self->obj));
    else {
        PyErr_SetString(PyExc_NotImplementedError, "virtual method MooWinPlugin.destroy not implemented");
        g_type_class_unref(klass);
        return NULL;
    }
    g_type_class_unref(klass);
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyMooWinPlugin_methods[] = {
    { "get_plugin", (PyCFunction)_wrap_moo_win_plugin_get_plugin, METH_NOARGS,
      NULL },
    { "get_window", (PyCFunction)_wrap_moo_win_plugin_get_window, METH_NOARGS,
      NULL },
    { "do_create", (PyCFunction)_wrap_MooWinPlugin__do_create, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { "do_destroy", (PyCFunction)_wrap_MooWinPlugin__do_destroy, METH_VARARGS|METH_KEYWORDS|METH_CLASS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyMooWinPlugin_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "moo.WinPlugin",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    0,                                 /* tp_vectorcall_offset */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    0,                                 /* tp_as_async */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyMooWinPlugin_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0,             /* tp_is_gc */
    NULL,                              /* tp_bases */
    NULL,                              /* tp_mro */
    NULL,                              /* tp_cache */
    NULL,                              /* tp_subclasses */
    NULL,                              /* tp_weaklist */
    NULL,                              /* tp_del */
    0,                                 /* tp_version_tag */
    NULL,                              /* tp_finalize */
};

static gboolean
_wrap_MooWinPlugin__proxy_do_create(MooWinPlugin *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    gboolean retval;
    PyObject *py_main_retval;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_create");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    py_retval = Py_BuildValue("(N)", py_retval);
    if (!PyArg_ParseTuple(py_retval, "O", &py_main_retval)) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return FALSE;
    }
    
    retval = PyObject_IsTrue(py_main_retval)? TRUE : FALSE;
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
    
    return retval;
}
static void
_wrap_MooWinPlugin__proxy_do_destroy(MooWinPlugin *self)
{
    PyGILState_STATE __py_state;
    PyObject *py_self;
    PyObject *py_retval;
    PyObject *py_method;
    
    __py_state = (PyGILState_STATE) pyg_gil_state_ensure();
    py_self = pygobject_new((GObject *) self);
    if (!py_self) {
        if (PyErr_Occurred())
            PyErr_Print();
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    py_method = PyObject_GetAttrString(py_self, "do_destroy");
    if (!py_method) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    py_retval = PyObject_CallObject(py_method, NULL);
    if (!py_retval) {
        if (PyErr_Occurred())
            PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    if (py_retval != Py_None) {
        PyErr_SetString(PyExc_TypeError, "virtual method should return None");
        PyErr_Print();
        Py_XDECREF(py_retval);
        Py_DECREF(py_method);
        Py_DECREF(py_self);
        pyg_gil_state_release(__py_state);
        return;
    }
    
    
    Py_XDECREF(py_retval);
    Py_DECREF(py_method);
    Py_DECREF(py_self);
    pyg_gil_state_release(__py_state);
}

static int
__MooWinPlugin_class_init(G_GNUC_UNUSED gpointer gclass, G_GNUC_UNUSED PyTypeObject *pyclass)
{
    PyObject *o;
    MooWinPluginClass *klass = MOO_WIN_PLUGIN_CLASS(gclass);
    PyObject *gsignals = PyDict_GetItemString(pyclass->tp_dict, "__gsignals__");

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_create");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "create")))
            klass->create = _wrap_MooWinPlugin__proxy_do_create;
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString((PyObject *) pyclass, "do_destroy");
    if (o == NULL)
        PyErr_Clear();
    else {
        if (!PyObject_TypeCheck(o, &PyCFunction_Type)
            && !(gsignals && PyDict_GetItemString(gsignals, "destroy")))
            klass->destroy = _wrap_MooWinPlugin__proxy_do_destroy;
        Py_DECREF(o);
    }
    return 0;
}


/* ----------- functions ----------- */

static PyObject *
_wrap_moo_dgettext(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "domain", (char*) "string", NULL };
    char *domain, *string;
    const gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"ss:dgettext", kwlist, &domain, &string))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_dgettext");
#endif
    
    ret = moo_dgettext(domain, string);
    
    if (ret)
        return PyUnicode_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_edit_window_set_action_filter(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "action_id", (char*) "type", (char*) "filter_string", NULL };
    char *action_id, *filter_string;
    MooActionCheckType type;
    PyObject *py_type = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"sOs:edit_window_set_action_filter", kwlist, &action_id, &py_type, &filter_string))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_edit_window_set_action_filter");
#endif
    if (pyg_enum_get_value(MOO_TYPE_ACTION_CHECK_TYPE, py_type, (int*)&type))
        return NULL;
    
    moo_edit_window_set_action_filter(action_id, type, filter_string);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_error_dialog(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "text", (char*) "secondary_text", (char*) "parent", NULL };
    char *text, *secondary_text = NULL;
    GtkWidget *parent = NULL;
    PyGObject *py_parent = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|zO:error_dialog", kwlist, &text, &secondary_text, &py_parent))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_error_dialog");
#endif
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWidget_Type))
        parent = GTK_WIDGET(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWidget or None");
        return NULL;
    }
    
    moo_error_dialog(text, secondary_text, (GtkWidget *) parent);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_get_data_and_lib_subdirs(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "subdir", NULL };
    char *subdir;
    gchar **ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:get_data_and_lib_subdirs", kwlist, &subdir))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_get_data_and_lib_subdirs");
#endif
    
    ret = moo_get_data_and_lib_subdirs(subdir);
    
    if (ret) {
        PyObject *py_ret = _moo_strv_to_pyobject(ret);
        g_strfreev(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_get_data_dirs(G_GNUC_UNUSED PyObject *self)
{
    gchar **ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_get_data_dirs");
#endif
    
    ret = moo_get_data_dirs();
    
    if (ret) {
        PyObject *py_ret = _moo_strv_to_pyobject(ret);
        g_strfreev(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_get_data_subdirs(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "subdir", NULL };
    char *subdir;
    gchar **ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:get_data_subdirs", kwlist, &subdir))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_get_data_subdirs");
#endif
    
    ret = moo_get_data_subdirs(subdir);
    
    if (ret) {
        PyObject *py_ret = _moo_strv_to_pyobject(ret);
        g_strfreev(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_get_lib_dirs(G_GNUC_UNUSED PyObject *self)
{
    gchar **ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_get_lib_dirs");
#endif
    
    ret = moo_get_lib_dirs();
    
    if (ret) {
        PyObject *py_ret = _moo_strv_to_pyobject(ret);
        g_strfreev(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_get_lib_subdirs(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "subdir", NULL };
    char *subdir;
    gchar **ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:get_lib_subdirs", kwlist, &subdir))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_get_lib_subdirs");
#endif
    
    ret = moo_get_lib_subdirs(subdir);
    
    if (ret) {
        PyObject *py_ret = _moo_strv_to_pyobject(ret);
        g_strfreev(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_get_named_user_data_file(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "basename", NULL };
    char *basename;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:get_named_user_data_file", kwlist, &basename))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_get_named_user_data_file");
#endif
    
    ret = moo_get_named_user_data_file(basename);
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_get_sys_data_subdirs(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "subdir", NULL };
    char *subdir;
    gchar **ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:get_sys_data_subdirs", kwlist, &subdir))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_get_sys_data_subdirs");
#endif
    
    ret = moo_get_sys_data_subdirs(subdir);
    
    if (ret) {
        PyObject *py_ret = _moo_strv_to_pyobject(ret);
        g_strfreev(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_get_user_cache_file(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "basename", NULL };
    char *basename;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:get_user_cache_file", kwlist, &basename))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_get_user_cache_file");
#endif
    
    ret = moo_get_user_cache_file(basename);
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_get_user_data_dir(G_GNUC_UNUSED PyObject *self)
{
    gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_get_user_data_dir");
#endif
    
    ret = moo_get_user_data_dir();
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_get_user_data_file(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "basename", NULL };
    char *basename;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:get_user_data_file", kwlist, &basename))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_get_user_data_file");
#endif
    
    ret = moo_get_user_data_file(basename);
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_gettext(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "string", NULL };
    char *string;
    const gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:gettext", kwlist, &string))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_gettext");
#endif
    
    ret = moo_gettext(string);
    
    if (ret)
        return PyUnicode_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_info_dialog(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "text", (char*) "secondary_text", (char*) "parent", NULL };
    char *text, *secondary_text = NULL;
    GtkWidget *parent = NULL;
    PyGObject *py_parent = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|zO:info_dialog", kwlist, &text, &secondary_text, &py_parent))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_info_dialog");
#endif
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWidget_Type))
        parent = GTK_WIDGET(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWidget or None");
        return NULL;
    }
    
    moo_info_dialog(text, secondary_text, (GtkWidget *) parent);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_overwrite_file_dialog(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "display_name", (char*) "display_dirname", (char*) "parent", NULL };
    char *display_name, *display_dirname;
    GtkWidget *parent = NULL;
    PyGObject *py_parent = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"ss|O:overwrite_file_dialog", kwlist, &display_name, &display_dirname, &py_parent))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_overwrite_file_dialog");
#endif
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWidget_Type))
        parent = GTK_WIDGET(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWidget or None");
        return NULL;
    }
    
    ret = moo_overwrite_file_dialog(display_name, display_dirname, (GtkWidget *) parent);
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_plugin_register(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "id", (char*) "type", (char*) "info", (char*) "params", NULL };
    char *id;
    GType type;
    PyObject *py_type = NULL, *py_info, *py_params = Py_None;
    MooPluginInfo *info = NULL;
    MooPluginParams *params = NULL;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"sOO|O:plugin_register", kwlist, &id, &py_type, &py_info, &py_params))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_plugin_register");
#endif
    if ((type = pyg_type_from_object(py_type)) == 0)
        return NULL;
    if (pyg_boxed_check(py_info, MOO_TYPE_PLUGIN_INFO))
        info = pyg_boxed_get(py_info, MooPluginInfo);
    else {
        PyErr_SetString(PyExc_TypeError, "info should be a MooPluginInfo");
        return NULL;
    }
    if (pyg_boxed_check(py_params, MOO_TYPE_PLUGIN_PARAMS))
        params = pyg_boxed_get(py_params, MooPluginParams);
    else if (py_params != Py_None) {
        PyErr_SetString(PyExc_TypeError, "params should be a MooPluginParams or None");
        return NULL;
    }
    
    ret = moo_plugin_register(id, type, info, params);
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_prefs_get_bool(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", NULL };
    char *key;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:prefs_get_bool", kwlist, &key))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_get_bool");
#endif
    
    ret = moo_prefs_get_bool(key);
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_prefs_get_file(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", NULL };
    char *key;
    GFile *ret;
    PyObject *py_ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:prefs_get_file", kwlist, &key))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_get_file");
#endif
    
    ret = moo_prefs_get_file(key);
    
    py_ret = pygobject_new((GObject *)ret);
    if (ret != NULL)
        g_object_unref(ret);
    return py_ret;
}

static PyObject *
_wrap_moo_prefs_get_filename(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", NULL };
    char *key;
    const gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:prefs_get_filename", kwlist, &key))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_get_filename");
#endif
    
    ret = moo_prefs_get_filename(key);
    
    if (ret)
        return PyUnicode_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_prefs_get_int(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", NULL };
    char *key;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:prefs_get_int", kwlist, &key))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_get_int");
#endif
    
    ret = moo_prefs_get_int(key);
    
    return PyLong_FromLong(ret);
}

static PyObject *
_wrap_moo_prefs_get_string(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", NULL };
    char *key;
    const gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s:prefs_get_string", kwlist, &key))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_get_string");
#endif
    
    ret = moo_prefs_get_string(key);
    
    if (ret)
        return PyUnicode_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_prefs_new_key_bool(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", (char*) "default_val", NULL };
    char *key;
    int default_val = FALSE;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|i:prefs_new_key_bool", kwlist, &key, &default_val))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_new_key_bool");
#endif
    
    moo_prefs_new_key_bool(key, default_val);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_prefs_new_key_int(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", (char*) "default_val", NULL };
    char *key;
    int default_val = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|i:prefs_new_key_int", kwlist, &key, &default_val))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_new_key_int");
#endif
    
    moo_prefs_new_key_int(key, default_val);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_prefs_new_key_string(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", (char*) "default_val", NULL };
    char *key, *default_val = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|z:prefs_new_key_string", kwlist, &key, &default_val))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_new_key_string");
#endif
    
    moo_prefs_new_key_string(key, default_val);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_prefs_set_bool(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", (char*) "val", NULL };
    char *key;
    int val;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"si:prefs_set_bool", kwlist, &key, &val))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_set_bool");
#endif
    
    moo_prefs_set_bool(key, val);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_prefs_set_file(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", (char*) "val", NULL };
    char *key;
    GFile *val = NULL;
    PyGObject *py_val;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"sO:prefs_set_file", kwlist, &key, &py_val))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_set_file");
#endif
    if (py_val && pygobject_check(py_val, &PyGFile_Type))
        val = G_FILE(py_val->obj);
    else if ((PyObject *)py_val != Py_None) {
        PyErr_SetString(PyExc_TypeError, "val should be a GFile or None");
        return NULL;
    }
    
    moo_prefs_set_file(key, (GFile *) val);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_prefs_set_filename(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", (char*) "val", NULL };
    char *key, *val;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"sz:prefs_set_filename", kwlist, &key, &val))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_set_filename");
#endif
    
    moo_prefs_set_filename(key, val);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_prefs_set_int(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", (char*) "val", NULL };
    char *key;
    int val;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"si:prefs_set_int", kwlist, &key, &val))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_set_int");
#endif
    
    moo_prefs_set_int(key, val);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_prefs_set_string(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "key", (char*) "val", NULL };
    char *key, *val;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"sz:prefs_set_string", kwlist, &key, &val))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_prefs_set_string");
#endif
    
    moo_prefs_set_string(key, val);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_question_dialog(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "text", (char*) "secondary_text", (char*) "parent", (char*) "default_response", NULL };
    char *text, *secondary_text = NULL;
    GtkWidget *parent = NULL;
    PyGObject *py_parent = NULL;
    GtkResponseType default_response = (GtkResponseType)GTK_RESPONSE_OK;
    int ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|zOi:question_dialog", kwlist, &text, &secondary_text, &py_parent, &default_response))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_question_dialog");
#endif
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWidget_Type))
        parent = GTK_WIDGET(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWidget or None");
        return NULL;
    }
    
    ret = moo_question_dialog(text, secondary_text, (GtkWidget *) parent, default_response);
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_save_changes_dialog(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "display_name", (char*) "parent", NULL };
    char *display_name;
    GtkWidget *parent = NULL;
    PyGObject *py_parent = NULL;
    gint ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|O:save_changes_dialog", kwlist, &display_name, &py_parent))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_save_changes_dialog");
#endif
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWidget_Type))
        parent = GTK_WIDGET(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWidget or None");
        return NULL;
    }
    
    ret = moo_save_changes_dialog(display_name, (GtkWidget *) parent);
    
    return pyg_enum_from_gtype(MOO_TYPE_SAVE_CHANGES_RESPONSE, ret);
}

static PyObject *
_wrap_moo_spin_main_loop(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "sec", NULL };
    double sec;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"d:spin_main_loop", kwlist, &sec))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_spin_main_loop");
#endif
    
    moo_spin_main_loop(sec);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_tempdir(G_GNUC_UNUSED PyObject *self)
{
    gchar *ret;

#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_tempdir");
#endif
    
    ret = moo_tempdir();
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_tempnam(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "extension", NULL };
    char *extension = NULL;
    gchar *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"|z:tempnam", kwlist, &extension))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_tempnam");
#endif
    
    ret = moo_tempnam(extension);
    
    if (ret) {
        PyObject *py_ret = PyUnicode_FromString(ret);
        g_free(ret);
        return py_ret;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_test_assert_impl(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "passed", (char*) "text", (char*) "file", (char*) "line", NULL };
    int passed, line = -1;
    char *text, *file = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"is|zi:test_assert_impl", kwlist, &passed, &text, &file, &line))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_test_assert_impl");
#endif
    
    moo_test_assert_impl(passed, text, file, line);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_moo_test_set_silent_messages(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "silent", NULL };
    int silent, ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"i:test_set_silent_messages", kwlist, &silent))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_test_set_silent_messages");
#endif
    
    ret = moo_test_set_silent_messages(silent);
    
    return PyBool_FromLong(ret);

}

static PyObject *
_wrap_moo_warning_dialog(G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "text", (char*) "secondary_text", (char*) "parent", NULL };
    char *text, *secondary_text = NULL;
    GtkWidget *parent = NULL;
    PyGObject *py_parent = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|zO:warning_dialog", kwlist, &text, &secondary_text, &py_parent))
        return NULL;
#ifdef MOO_ENABLE_COVERAGE
    moo_test_coverage_record ("python", "moo_warning_dialog");
#endif
    if ((PyObject *)py_parent == Py_None)
        parent = NULL;
    else if (py_parent && pygobject_check(py_parent, &PyGtkWidget_Type))
        parent = GTK_WIDGET(py_parent->obj);
    else if (py_parent) {
        PyErr_SetString(PyExc_TypeError, "parent should be a GtkWidget or None");
        return NULL;
    }
    
    moo_warning_dialog(text, secondary_text, (GtkWidget *) parent);
    
    Py_INCREF(Py_None);
    return Py_None;
}

#line 19 "mooutils.override"
static GtkAction*
py_action_factory_func (MooWindow  *window,
                        PyObject   *func_n_args)
{
    PyObject *py_window, *args, *func, *result;
    GtkAction *action;

    g_return_val_if_fail (func_n_args != NULL, NULL);
    g_return_val_if_fail (PyTuple_Check (func_n_args), NULL);
    g_return_val_if_fail (PyTuple_GET_SIZE (func_n_args) == 2, NULL);

    func = PyTuple_GET_ITEM (func_n_args, 0);
    args = PyTuple_GET_ITEM (func_n_args, 1);

    g_return_val_if_fail (PyCallable_Check (func), NULL);
    g_return_val_if_fail (PyTuple_Check (args), NULL);
    g_return_val_if_fail (PyTuple_GET_SIZE (args) > 0, NULL);

    py_window = pygobject_new (G_OBJECT (window));
    PyTuple_SET_ITEM (args, 0, py_window);
    result = PyObject_Call (func, args, NULL);
    PyTuple_SET_ITEM (args, 0, NULL);
    Py_DECREF (py_window);

    if (!result)
    {
        PyErr_Print ();
        return NULL;
    }

    if (!PyObject_TypeCheck (result, &PyGtkAction_Type))
    {
        g_critical ("got invalid value");
        Py_DECREF (result);
        return NULL;
    }

    action = GTK_ACTION (pygobject_get (result));
    g_object_ref (action);
    Py_DECREF (result);
    return action;
}

static void
destroy_func_n_args (PyObject *func_n_args)
{
    if (func_n_args)
    {
        PyTuple_SET_ITEM (PyTuple_GET_ITEM (func_n_args, 1), 0, Py_None);
        Py_INCREF (Py_None);
        Py_DECREF (func_n_args);
    }
}

static PyObject *
_wrap_moo_window_class_add_action (G_GNUC_UNUSED PyObject *self, PyObject *args)
{
    PyObject *py_type, *py_id, *py_group, *py_factory_func, *func_n_args;
    GType type;
    MooWindowClass *klass;
    int i, extra;

    extra = PyTuple_GET_SIZE (args) - 4;

    if (extra < 0)
        return_TypeError ("at least three arguments required");

    py_type = PyTuple_GET_ITEM (args, 0);
    py_id = PyTuple_GET_ITEM (args, 1);
    py_group = PyTuple_GET_ITEM (args, 2);
    py_factory_func = PyTuple_GET_ITEM (args, 3);

    type = pyg_type_from_object (py_type);

    if (!type)
        return NULL;

    if (!g_type_is_a (type, MOO_TYPE_WINDOW))
        return_TypeError ("type must be derived from MooWindow");

    if (!PyString_Check (py_id))
        return_TypeError ("name must be a string");

    if (py_group != Py_None && !PyString_Check (py_group))
        return_TypeError ("group must be a string or None");

    if (!PyCallable_Check (py_factory_func))
        return_TypeError ("factory_func must be callable");

    klass = (MooWindowClass*) g_type_class_ref (type);

    func_n_args = PyTuple_New (2);
    PyTuple_SET_ITEM (func_n_args, 0, py_factory_func);
    Py_INCREF (py_factory_func);

    PyTuple_SET_ITEM (func_n_args, 1, PyTuple_New (1 + extra));

    for (i = 0; i < extra; ++i)
    {
        PyTuple_SET_ITEM (PyTuple_GET_ITEM (func_n_args, 1), i + 1,
                          PyTuple_GET_ITEM (args, i + 4));
        Py_INCREF (PyTuple_GET_ITEM (args, i + 4));
    }

    moo_window_class_new_action_custom (klass, PyString_AS_STRING (py_id),
                                        py_group == Py_None ? NULL : PyString_AS_STRING (py_group),
                                        (MooWindowActionFunc) py_action_factory_func,
                                        func_n_args, (GDestroyNotify) destroy_func_n_args);

    g_type_class_unref (klass);
    return_None;
}
#line 10431 "/home/fangq/space/git/Temp/newsrc/mooedit/moo/moopython/pygtk/moo.c"


#line 133 "mooutils.override"
static PyObject *
_wrap_moo_window_class_find_action (G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "cls", (char*) "name", NULL };
    PyObject *py_type;
    GType type;
    const char *action_id;
    MooWindowClass *klass;
    gboolean ret;

    if (!PyArg_ParseTupleAndKeywords (args, kwargs, "Os:window_class_find_action", kwlist, &py_type, &action_id))
        return NULL;

    type = pyg_type_from_object (py_type);

    if (!type)
        return NULL;

    if (!g_type_is_a (type, MOO_TYPE_WINDOW))
        return_TypeError ("type must be derived from MooWindow");

    klass = (MooWindowClass*) g_type_class_ref (type);
    ret = moo_window_class_find_action (klass, action_id);
    g_type_class_unref (klass);

    return_Bool (ret);
}
#line 10462 "/home/fangq/space/git/Temp/newsrc/mooedit/moo/moopython/pygtk/moo.c"


#line 162 "mooutils.override"
static PyObject *
_wrap_moo_window_class_remove_action (G_GNUC_UNUSED PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { (char*) "cls", (char*) "name", NULL };
    PyObject *py_type;
    GType type;
    const char *action_id;
    MooWindowClass *klass;

    if (!PyArg_ParseTupleAndKeywords (args, kwargs, "Os:window_class_remove_action", kwlist, &py_type, &action_id))
        return NULL;

    type = pyg_type_from_object (py_type);

    if (!type)
        return NULL;

    if (!g_type_is_a (type, MOO_TYPE_WINDOW))
        return_TypeError ("type must be derived from MooWindow");

    klass = (MooWindowClass*) g_type_class_ref (type);
    moo_window_class_remove_action (klass, action_id);
    g_type_class_unref (klass);

    return_None;
}
#line 10492 "/home/fangq/space/git/Temp/newsrc/mooedit/moo/moopython/pygtk/moo.c"


const PyMethodDef _moo_functions[] = {
    { "dgettext", (PyCFunction)_wrap_moo_dgettext, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "edit_window_set_action_filter", (PyCFunction)_wrap_moo_edit_window_set_action_filter, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "error_dialog", (PyCFunction)_wrap_moo_error_dialog, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_data_and_lib_subdirs", (PyCFunction)_wrap_moo_get_data_and_lib_subdirs, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_data_dirs", (PyCFunction)_wrap_moo_get_data_dirs, METH_NOARGS,
      NULL },
    { "get_data_subdirs", (PyCFunction)_wrap_moo_get_data_subdirs, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_lib_dirs", (PyCFunction)_wrap_moo_get_lib_dirs, METH_NOARGS,
      NULL },
    { "get_lib_subdirs", (PyCFunction)_wrap_moo_get_lib_subdirs, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_named_user_data_file", (PyCFunction)_wrap_moo_get_named_user_data_file, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_sys_data_subdirs", (PyCFunction)_wrap_moo_get_sys_data_subdirs, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_user_cache_file", (PyCFunction)_wrap_moo_get_user_cache_file, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_user_data_dir", (PyCFunction)_wrap_moo_get_user_data_dir, METH_NOARGS,
      NULL },
    { "get_user_data_file", (PyCFunction)_wrap_moo_get_user_data_file, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "gettext", (PyCFunction)_wrap_moo_gettext, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "info_dialog", (PyCFunction)_wrap_moo_info_dialog, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "overwrite_file_dialog", (PyCFunction)_wrap_moo_overwrite_file_dialog, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "plugin_register", (PyCFunction)_wrap_moo_plugin_register, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_get_bool", (PyCFunction)_wrap_moo_prefs_get_bool, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_get_file", (PyCFunction)_wrap_moo_prefs_get_file, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_get_filename", (PyCFunction)_wrap_moo_prefs_get_filename, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_get_int", (PyCFunction)_wrap_moo_prefs_get_int, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_get_string", (PyCFunction)_wrap_moo_prefs_get_string, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_new_key_bool", (PyCFunction)_wrap_moo_prefs_new_key_bool, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_new_key_int", (PyCFunction)_wrap_moo_prefs_new_key_int, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_new_key_string", (PyCFunction)_wrap_moo_prefs_new_key_string, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_set_bool", (PyCFunction)_wrap_moo_prefs_set_bool, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_set_file", (PyCFunction)_wrap_moo_prefs_set_file, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_set_filename", (PyCFunction)_wrap_moo_prefs_set_filename, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_set_int", (PyCFunction)_wrap_moo_prefs_set_int, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "prefs_set_string", (PyCFunction)_wrap_moo_prefs_set_string, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "question_dialog", (PyCFunction)_wrap_moo_question_dialog, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "save_changes_dialog", (PyCFunction)_wrap_moo_save_changes_dialog, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "spin_main_loop", (PyCFunction)_wrap_moo_spin_main_loop, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "tempdir", (PyCFunction)_wrap_moo_tempdir, METH_NOARGS,
      NULL },
    { "tempnam", (PyCFunction)_wrap_moo_tempnam, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "test_assert_impl", (PyCFunction)_wrap_moo_test_assert_impl, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "test_set_silent_messages", (PyCFunction)_wrap_moo_test_set_silent_messages, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "warning_dialog", (PyCFunction)_wrap_moo_warning_dialog, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "window_class_add_action", (PyCFunction)_wrap_moo_window_class_add_action, METH_VARARGS,
      NULL },
    { "window_class_find_action", (PyCFunction)_wrap_moo_window_class_find_action, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "window_class_remove_action", (PyCFunction)_wrap_moo_window_class_remove_action, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};


/* ----------- enums and flags ----------- */

void
_moo_add_constants(PyObject *module, const gchar *strip_prefix)
{
#ifdef VERSION
    PyModule_AddStringConstant(module, "__version__", VERSION);
#endif
  pyg_enum_add(module, "ActionCheckType", strip_prefix, MOO_TYPE_ACTION_CHECK_TYPE);
  pyg_enum_add(module, "CloseResponse", strip_prefix, MOO_TYPE_CLOSE_RESPONSE);
  pyg_flags_add(module, "EditStatus", strip_prefix, MOO_TYPE_EDIT_STATUS);
  pyg_enum_add(module, "LineEndType", strip_prefix, MOO_TYPE_LINE_END_TYPE);
  pyg_flags_add(module, "OpenFlags", strip_prefix, MOO_TYPE_OPEN_FLAGS);
  pyg_enum_add(module, "PanePosition", strip_prefix, MOO_TYPE_PANE_POSITION);
  pyg_enum_add(module, "SaveChangesResponse", strip_prefix, MOO_TYPE_SAVE_CHANGES_RESPONSE);
  pyg_enum_add(module, "SaveResponse", strip_prefix, MOO_TYPE_SAVE_RESPONSE);
  pyg_enum_add(module, "UiWidgetType", strip_prefix, MOO_TYPE_UI_WIDGET_TYPE);

  if (PyErr_Occurred())
    PyErr_Print();
}

/* initialise stuff extension classes */
void
_moo_register_classes(PyObject *d)
{

#line 10609 "/home/fangq/space/git/Temp/newsrc/mooedit/moo/moopython/pygtk/moo.c"
    pyg_register_boxed(d, "PaneLabel", MOO_TYPE_PANE_LABEL, &PyMooPaneLabel_Type);
    pyg_register_boxed(d, "PaneParams", MOO_TYPE_PANE_PARAMS, &PyMooPaneParams_Type);
    pyg_register_boxed(d, "PluginInfo", MOO_TYPE_PLUGIN_INFO, &PyMooPluginInfo_Type);
    pyg_register_boxed(d, "PluginParams", MOO_TYPE_PLUGIN_PARAMS, &PyMooPluginParams_Type);
    pyg_register_pointer(d, "UiNode", MOO_TYPE_UI_NODE, &PyMooUiNode_Type);
    pygobject_register_class(d, "MooAction", MOO_TYPE_ACTION, &PyMooAction_Type, Py_BuildValue("(O)", &PyGtkAction_Type));
    pygobject_register_class(d, "MooActionCollection", MOO_TYPE_ACTION_COLLECTION, &PyMooActionCollection_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooApp", MOO_TYPE_APP, &PyMooApp_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooBigPaned", MOO_TYPE_BIG_PANED, &PyMooBigPaned_Type, Py_BuildValue("(O)", &PyGtkFrame_Type));
    pygobject_register_class(d, "MooCombo", MOO_TYPE_COMBO, &PyMooCombo_Type, Py_BuildValue("(O)", &PyGtkTable_Type));
    pygobject_register_class(d, "MooDocPlugin", MOO_TYPE_DOC_PLUGIN, &PyMooDocPlugin_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pyg_register_class_init(MOO_TYPE_DOC_PLUGIN, __MooDocPlugin_class_init);
    pygobject_register_class(d, "MooEdit", MOO_TYPE_EDIT, &PyMooEdit_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooEditAction", MOO_TYPE_EDIT_ACTION, &PyMooEditAction_Type, Py_BuildValue("(O)", &PyMooAction_Type));
    pyg_register_class_init(MOO_TYPE_EDIT_ACTION, __MooEditAction_class_init);
    pygobject_register_class(d, "MooEditTab", MOO_TYPE_EDIT_TAB, &PyMooEditTab_Type, Py_BuildValue("(O)", &PyGtkVBox_Type));
    pygobject_register_class(d, "MooEditor", MOO_TYPE_EDITOR, &PyMooEditor_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooEntry", MOO_TYPE_ENTRY, &PyMooEntry_Type, Py_BuildValue("(O)", &PyGtkEntry_Type));
    pygobject_register_class(d, "MooFileDialog", MOO_TYPE_FILE_DIALOG, &PyMooFileDialog_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooGladeXml", MOO_TYPE_GLADE_XML, &PyMooGladeXml_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooHistoryCombo", MOO_TYPE_HISTORY_COMBO, &PyMooHistoryCombo_Type, Py_BuildValue("(O)", &PyMooCombo_Type));
    pygobject_register_class(d, "MooHistoryList", MOO_TYPE_HISTORY_LIST, &PyMooHistoryList_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooHistoryMgr", MOO_TYPE_HISTORY_MGR, &PyMooHistoryMgr_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooLineMark", MOO_TYPE_LINE_MARK, &PyMooLineMark_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooEditBookmark", MOO_TYPE_EDIT_BOOKMARK, &PyMooEditBookmark_Type, Py_BuildValue("(O)", &PyMooLineMark_Type));
    pygobject_register_class(d, "MooLuaState", MOO_TYPE_LUA_STATE, &PyMooLuaState_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooMenuAction", MOO_TYPE_MENU_ACTION, &PyMooMenuAction_Type, Py_BuildValue("(O)", &PyMooAction_Type));
    pygobject_register_class(d, "MooMenuMgr", MOO_TYPE_MENU_MGR, &PyMooMenuMgr_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooMenuToolButton", MOO_TYPE_MENU_TOOL_BUTTON, &PyMooMenuToolButton_Type, Py_BuildValue("(O)", &PyGtkToggleToolButton_Type));
    pygobject_register_class(d, "MooNotebook", MOO_TYPE_NOTEBOOK, &PyMooNotebook_Type, Py_BuildValue("(O)", &PyGtkNotebook_Type));
    pygobject_register_class(d, "MooOpenInfo", MOO_TYPE_OPEN_INFO, &PyMooOpenInfo_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooPane", MOO_TYPE_PANE, &PyMooPane_Type, Py_BuildValue("(O)", &PyGtkObject_Type));
    pygobject_register_class(d, "MooPaned", MOO_TYPE_PANED, &PyMooPaned_Type, Py_BuildValue("(O)", &PyGtkBin_Type));
    pygobject_register_class(d, "MooPlugin", MOO_TYPE_PLUGIN, &PyMooPlugin_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pyg_register_class_init(MOO_TYPE_PLUGIN, __MooPlugin_class_init);
    pygobject_register_class(d, "MooPrefsDialog", MOO_TYPE_PREFS_DIALOG, &PyMooPrefsDialog_Type, Py_BuildValue("(O)", &PyGtkDialog_Type));
    pyg_register_class_init(MOO_TYPE_PREFS_DIALOG, __MooPrefsDialog_class_init);
    pygobject_register_class(d, "MooPrefsPage", MOO_TYPE_PREFS_PAGE, &PyMooPrefsPage_Type, Py_BuildValue("(O)", &PyGtkVBox_Type));
    pyg_register_class_init(MOO_TYPE_PREFS_PAGE, __MooPrefsPage_class_init);
    pygobject_register_class(d, "MooReloadInfo", MOO_TYPE_RELOAD_INFO, &PyMooReloadInfo_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooSaveInfo", MOO_TYPE_SAVE_INFO, &PyMooSaveInfo_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooTextBuffer", MOO_TYPE_TEXT_BUFFER, &PyMooTextBuffer_Type, Py_BuildValue("(O)", &PyGtkTextBuffer_Type));
    pygobject_register_class(d, "MooTextView", MOO_TYPE_TEXT_VIEW, &PyMooTextView_Type, Py_BuildValue("(O)", &PyGtkTextView_Type));
    pygobject_register_class(d, "MooLineView", MOO_TYPE_LINE_VIEW, &PyMooLineView_Type, Py_BuildValue("(O)", &PyMooTextView_Type));
    pygobject_register_class(d, "MooCmdView", MOO_TYPE_CMD_VIEW, &PyMooCmdView_Type, Py_BuildValue("(O)", &PyMooLineView_Type));
    pygobject_register_class(d, "MooEditView", MOO_TYPE_EDIT_VIEW, &PyMooEditView_Type, Py_BuildValue("(O)", &PyMooTextView_Type));
    pygobject_register_class(d, "MooUiXml", MOO_TYPE_UI_XML, &PyMooUiXml_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pygobject_register_class(d, "MooWinPlugin", MOO_TYPE_WIN_PLUGIN, &PyMooWinPlugin_Type, Py_BuildValue("(O)", &PyGObject_Type));
    pyg_register_class_init(MOO_TYPE_WIN_PLUGIN, __MooWinPlugin_class_init);
    pygobject_register_class(d, "MooWindow", MOO_TYPE_WINDOW, &PyMooWindow_Type, Py_BuildValue("(O)", &PyGtkWindow_Type));
    pygobject_register_class(d, "MooEditWindow", MOO_TYPE_EDIT_WINDOW, &PyMooEditWindow_Type, Py_BuildValue("(O)", &PyMooWindow_Type));
}

#ifdef __cplusplus
}
#endif
