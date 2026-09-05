/*
 *   moogdb-mi-parser.h
 *
 *   Line-at-a-time parser for the GDB Machine Interface protocol
 *   (the `--interpreter=mi3` output).  Kept in its own translation
 *   unit so the session code stays focused on lifecycle/dispatch
 *   and the parser is easy to test in isolation.
 *
 *   Spec reference: GDB manual chapter "The GDB/MI Interface".
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#ifndef MOO_GDB_MI_PARSER_H
#define MOO_GDB_MI_PARSER_H

#include <glib.h>

G_BEGIN_DECLS

/* Eight MI record types.  Phase 1 only handles RESULT (^done /
 * ^error), CONSOLE/LOG/TARGET text streams, and PROMPT; EXEC and
 * NOTIFY land in Phase 2 with the dispatcher.  Including all eight
 * here keeps the parser future-proof. */
typedef enum {
    MOO_GDB_MI_RESULT,       /* ^done / ^running / ^connected / ^error / ^exit */
    MOO_GDB_MI_EXEC,         /* *running / *stopped                            */
    MOO_GDB_MI_STATUS,       /* +download                                       */
    MOO_GDB_MI_NOTIFY,       /* =breakpoint-modified / =thread-created / ...   */
    MOO_GDB_MI_CONSOLE,      /* ~"text"   — output of CLI commands             */
    MOO_GDB_MI_TARGET,       /* @"text"   — inferior's stdout                  */
    MOO_GDB_MI_LOG,          /* &"text"   — gdb's internal log                 */
    MOO_GDB_MI_PROMPT        /* (gdb) at end of a response group               */
} MooGdbMiKind;

/* Opaque types — the implementation uses GHashTable/GPtrArray
 * internally, but callers only see typed accessors. */
typedef struct _MooGdbMiValue  MooGdbMiValue;
typedef struct _MooGdbMiRecord MooGdbMiRecord;

/* Parse one line of MI output.  The caller is responsible for the
 * line buffering — feed in one logical line (no trailing newline).
 * Returns NULL if the line is empty.  Caller frees the returned
 * record with moo_gdb_mi_record_free. */
MooGdbMiRecord *moo_gdb_mi_parse           (const char *line);
void           moo_gdb_mi_record_free      (MooGdbMiRecord *r);

/* Record accessors. */
MooGdbMiKind   moo_gdb_mi_record_kind      (MooGdbMiRecord *r);

/* For RESULT/EXEC/STATUS/NOTIFY records that were prefixed by a
 * numeric token; -1 if no token. */
int            moo_gdb_mi_record_token     (MooGdbMiRecord *r);

/* For RESULT records, the class string ("done", "running", "error",
 * etc.); for EXEC/NOTIFY records, the async-class string ("stopped",
 * "breakpoint-modified", etc.); NULL for stream records. */
const char    *moo_gdb_mi_record_class     (MooGdbMiRecord *r);

/* For CONSOLE/TARGET/LOG records, the C-string payload with escape
 * sequences expanded.  NULL for non-stream records. */
const char    *moo_gdb_mi_record_text      (MooGdbMiRecord *r);

/* Result-tuple field access.  Records like ^done,bkpt={...} or
 * *stopped,reason="...",frame={...} expose their named fields here.
 * Returns NULL if the field is absent. */
MooGdbMiValue *moo_gdb_mi_record_field     (MooGdbMiRecord *r,
                                            const char     *name);

/* MI values are one of:
 *   - C-string                 (`"text"` — escapes already expanded)
 *   - tuple of named values    (`{name=value,...}`)
 *   - list of unnamed values   (`[value,value,...]`)
 *   - list of named values     (`[name=value,...]`)
 *
 * Accessors return NULL for type-mismatched queries. */
const char    *moo_gdb_mi_value_string     (MooGdbMiValue *v);
MooGdbMiValue *moo_gdb_mi_value_tuple_get  (MooGdbMiValue *v,
                                            const char    *name);
guint          moo_gdb_mi_value_list_len   (MooGdbMiValue *v);
MooGdbMiValue *moo_gdb_mi_value_list_nth   (MooGdbMiValue *v,
                                            guint          i);

G_END_DECLS

#endif /* MOO_GDB_MI_PARSER_H */
