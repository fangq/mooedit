/* PyGTK -> PyGObject 3 / Python 3 compatibility */
#ifndef MOO_PYGTK_COMPAT_H
#define MOO_PYGTK_COMPAT_H

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
      if (b->boxed && b->gtype == GTK_TYPE_TEXT_ITER) {
          *iter = *(GtkTextIter*)(b->boxed); return 1;
      }
    }
    PyErr_SetString(PyExc_TypeError, "expected Gtk.TextIter or None");
    return 0;
}

static PyObject* pygtk_text_iter_to_pyobject(GtkTextIter *i) {
    (void)i; Py_RETURN_NONE;
}

static int pygdk_rectangle_from_pyobject(PyObject *obj, GdkRectangle *r) {
    if (!obj || obj == Py_None) { r->x=r->y=r->width=r->height=0; return 1; }
    if (PyTuple_Check(obj) && PyTuple_Size(obj)==4) {
        r->x=(int)PyLong_AsLong(PyTuple_GET_ITEM(obj,0));
        r->y=(int)PyLong_AsLong(PyTuple_GET_ITEM(obj,1));
        r->width=(int)PyLong_AsLong(PyTuple_GET_ITEM(obj,2));
        r->height=(int)PyLong_AsLong(PyTuple_GET_ITEM(obj,3));
        return !PyErr_Occurred();
    }
    PyErr_SetString(PyExc_TypeError, "expected (x,y,w,h) tuple");
    return 0;
}

#endif /* MOO_PYGTK_COMPAT_H */
