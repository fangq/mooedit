/*
 *   moogdb-json.h
 *
 *   Minimal hand-rolled JSON parser, just enough to read VS Code's
 *   `.vscode/launch.json` and `.vscode/tasks.json`.  Supports the
 *   standard six value kinds (null, bool, number, string, array,
 *   object), plus C-style line and block comments — VS Code accepts
 *   "JSON with Comments" in those files and users rely on it.
 *
 *   Strict-JSON callers can ignore comments; they're skipped during
 *   tokenization so a strict JSON document parses fine too.
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#ifndef MOO_GDB_JSON_H
#define MOO_GDB_JSON_H

#include <glib.h>

G_BEGIN_DECLS

typedef enum {
    MOO_JSON_NULL,
    MOO_JSON_BOOL,
    MOO_JSON_NUMBER,
    MOO_JSON_STRING,
    MOO_JSON_ARRAY,
    MOO_JSON_OBJECT
} MooJsonKind;

typedef struct _MooJsonValue MooJsonValue;

/* Parse a complete JSON document.  Returns NULL on parse error with
 * a GError describing the location and reason.  Caller owns the
 * returned value and must free it with moo_json_value_free. */
MooJsonValue *moo_json_parse        (const char *text, GError **error);
void          moo_json_value_free   (MooJsonValue *v);

MooJsonKind   moo_json_kind         (MooJsonValue *v);

/* Scalar accessors.  Return zero/NULL/FALSE on type mismatch. */
gboolean      moo_json_bool         (MooJsonValue *v);
double        moo_json_number       (MooJsonValue *v);
const char   *moo_json_string       (MooJsonValue *v);

/* Object accessors.  moo_json_object_get returns a borrowed
 * MooJsonValue (owned by the parent), or NULL if the key is absent. */
MooJsonValue *moo_json_object_get   (MooJsonValue *v, const char *key);

/* Array accessors. */
guint         moo_json_array_len    (MooJsonValue *v);
MooJsonValue *moo_json_array_get    (MooJsonValue *v, guint index);

/* Convenience: get a string field on an object, returning a default
 * if the field is absent or has the wrong type.  The returned
 * pointer is borrowed (lifetime tied to the parent value). */
const char   *moo_json_object_string (MooJsonValue *v, const char *key,
                                       const char   *fallback);

G_END_DECLS

#endif /* MOO_GDB_JSON_H */
