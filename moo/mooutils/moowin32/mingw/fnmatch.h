/*
 * fnmatch.h — minimal POSIX-style shell-glob matching for MinGW.
 *
 * MinGW's libc does not ship <fnmatch.h>.  xdgmime uses fnmatch() with
 * flags=0 to test names against shell-glob patterns ("*.png", "[Mm]ake*"),
 * which is exactly what Windows' PathMatchSpecA provides.  Wrap that.
 *
 * Only the bits xdgmime needs are implemented.  FNM_PATHNAME / FNM_PERIOD
 * are accepted as no-ops because xdgmime never sets them.
 */
#ifndef MOO_MINGW_FNMATCH_H
#define MOO_MINGW_FNMATCH_H

#include <shlwapi.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FNM_NOMATCH  1
#define FNM_PATHNAME 0x01
#define FNM_NOESCAPE 0x02
#define FNM_PERIOD   0x04

static inline int
fnmatch (const char *pattern, const char *string, int flags)
{
    (void) flags;
    return PathMatchSpecA (string, pattern) ? 0 : FNM_NOMATCH;
}

#ifdef __cplusplus
}
#endif

#endif /* MOO_MINGW_FNMATCH_H */
