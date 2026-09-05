/*
 *   moogdb-project.h
 *
 *   Lightweight project model for the GDB plugin.  Searches the
 *   active document's directory tree for `.medit/launch.json`
 *   first, then `.vscode/launch.json` — the medit-specific name
 *   takes precedence so a project can ship both a generic VS Code
 *   launch.json and a medit-tuned override without conflict.
 *   The matching `tasks.json` (optional) is read from the same
 *   subdirectory so paths stay consistent.
 *
 *   Schema: a subset of VS Code's launch.json — the fields a
 *   cppdbg-style configuration uses (name, program, args, cwd,
 *   environment, preLaunchTask).  Configs whose `type` and
 *   `request` don't look like a gdb-compatible launch are
 *   filtered out so the user's other configs (pwa-chrome, etc.)
 *   don't pollute the dropdown.
 *
 *   Substitution variables resolved at use-time (not parse-time)
 *   because ${file} depends on the active document, which may
 *   change while a project is loaded:
 *
 *     ${workspaceFolder}              project root
 *     ${file}                         absolute path of active doc
 *     ${fileBasename}                 basename
 *     ${fileBasenameNoExtension}      basename without ext
 *     ${fileDirname}                  containing directory
 *     ${env:VARNAME}                  environment variable
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#ifndef MOO_GDB_PROJECT_H
#define MOO_GDB_PROJECT_H

#include <glib.h>

G_BEGIN_DECLS

/* One launch configuration.  All string fields are stored as the
 * raw text from launch.json — call moo_gdb_project_resolve to
 * expand ${...} variables in context. */
typedef struct {
    char       *name;             /* "Debug" / "Release" / ...     */
    char       *program;          /* path to the binary             */
    char      **args;             /* NULL-terminated argv (no prog) */
    char       *cwd;              /* working dir                    */
    GHashTable *environment;      /* char*name → char*value         */
    char       *pre_launch_task;  /* label, or NULL                 */
    /* If preLaunchTask resolves through tasks.json to a shell
     * command, build_command holds that resolved command line.
     * Falls back to the config's own "build" key if a vanilla
     * (medit-only) launch.json uses that simpler shape. */
    char       *build_command;
} MooGdbConfig;

typedef struct _MooGdbProject MooGdbProject;

/* Discover the project root.  Walks up from start_path looking for
 * a directory containing `.vscode/launch.json`.  Returns NULL with
 * error set if no project file found or it failed to parse. */
MooGdbProject *moo_gdb_project_load     (const char *start_path,
                                          GError    **error);
void           moo_gdb_project_free     (MooGdbProject *p);

const char    *moo_gdb_project_root        (MooGdbProject *p);
const char    *moo_gdb_project_launch_path (MooGdbProject *p);
guint          moo_gdb_project_n_configs   (MooGdbProject *p);

/* Borrowed pointer — lifetime tied to the project. */
const MooGdbConfig *moo_gdb_project_config (MooGdbProject *p, guint i);

/* Expand VS Code-style variables.  `active_file` may be NULL.
 * Returned string is newly-allocated; caller frees with g_free. */
char          *moo_gdb_project_resolve  (MooGdbProject *p,
                                          const char    *raw,
                                          const char    *active_file);

G_END_DECLS

#endif /* MOO_GDB_PROJECT_H */
