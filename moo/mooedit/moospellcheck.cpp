/*
 *   moospellcheck.cpp
 *
 *   gspell-based spell-checker integration for MooEditView.  This file
 *   is the skeleton from commit #1 of the spell-check series; the real
 *   gspell calls land in commit #2.  All entry points are no-ops here
 *   so the rest of the tree can already use them.
 *
 *   Copyright (C) 2026 — part of medit.
 *
 *   This file is part of medit.  medit is free software; you can
 *   redistribute it and/or modify it under the terms of the
 *   GNU Lesser General Public License as published by the
 *   Free Software Foundation; either version 2.1 of the License,
 *   or (at your option) any later version.
 */

#include "config.h"
#include "mooedit/moospellcheck.h"

#ifdef MOO_BUILD_SPELL
#  include <gspell/gspell.h>
#endif

void
_moo_spell_check_attach (G_GNUC_UNUSED MooEditView *view)
{
#ifdef MOO_BUILD_SPELL
    /* TODO (commit #2): create GspellChecker for en_US, attach to
     * the view's GtkTextBuffer via gspell_text_buffer_get_from_*,
     * and call gspell_text_view_basic_setup() on the view side. */
#endif
}

void
_moo_spell_check_detach (G_GNUC_UNUSED MooEditView *view)
{
#ifdef MOO_BUILD_SPELL
    /* TODO (commit #2): drop the checker reference; gspell auto-removes
     * its highlight tag and signal handlers when the buffer/view is
     * destroyed, but explicit detach lets us re-attach with new prefs. */
#endif
}

void
_moo_spell_check_apply_prefs (G_GNUC_UNUSED MooEditView *view)
{
#ifdef MOO_BUILD_SPELL
    /* TODO (commit #3): read MOO_EDIT_PREFS_SPELL_* and reconfigure. */
#endif
}
