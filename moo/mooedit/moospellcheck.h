/*
 *   moospellcheck.h
 *
 *   GTK 3 spell-checker integration for MooEditView, wrapping gspell.
 *   All functions are no-ops at compile time when MOO_BUILD_SPELL is
 *   not defined, so callers don't need to ifdef every site.
 *
 *   Copyright (C) 2026 — part of medit.
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#ifndef MOO_SPELL_CHECK_H
#define MOO_SPELL_CHECK_H

#include "mooedit/mooeditview.h"

G_BEGIN_DECLS

/* Attach a spell-checker to a MooEditView.  Idempotent; safe to call
 * before prefs are loaded.  When MOO_BUILD_SPELL is not defined this
 * is a no-op.  Lifetime: detach via _moo_spell_check_detach() in
 * MooEditView::dispose. */
void    _moo_spell_check_attach        (MooEditView    *view);

void    _moo_spell_check_detach        (MooEditView    *view);

/* Live-reapply preferences (enabled / language / scope mode).  Reads
 * the current MOO_EDIT_PREFS_SPELL_* values and reconfigures the
 * attached checker; cheap to call repeatedly. */
void    _moo_spell_check_apply_prefs   (MooEditView    *view);

G_END_DECLS

#endif /* MOO_SPELL_CHECK_H */
