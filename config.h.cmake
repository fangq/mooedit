#ifndef __CONFIG_H__
#define __CONFIG_H__

#define MOO_CONFIG_H_INCLUDED 1

/* ── Version ────────────────────────────────────────────────────────────── */
#define MOO_VERSION         "@MOO_VERSION@"
#define MOO_DISPLAY_VERSION "@MOO_DISPLAY_VERSION@"
#define MOO_MAJOR_VERSION    @MOO_MAJOR_VERSION@
#define MOO_MINOR_VERSION    @MOO_MINOR_VERSION@
#define MOO_MICRO_VERSION    @MOO_MICRO_VERSION@
#define MOO_MODULE_MAJOR_VERSION @MOO_MODULE_MAJOR_VERSION@
#define MOO_MODULE_MINOR_VERSION @MOO_MODULE_MINOR_VERSION@

/* ── Contact / copyright ─────────────────────────────────────────────────── */
#define MOO_EMAIL       "@MOO_EMAIL@"
#define MOO_COPYRIGHT   "@MOO_COPYRIGHT@"
#define MOO_WEBSITE     "@MOO_WEBSITE@"
#define MOO_WEB_CONTACT "@MOO_WEB_CONTACT@"
#define PACKAGE_BUGREPORT "@MOO_EMAIL@"

/* ── Package / gettext ───────────────────────────────────────────────────── */
#define MOO_PACKAGE_NAME  "@MOO_PACKAGE_NAME@"
#define GETTEXT_PACKAGE   "@GETTEXT_PACKAGE@"

/* ── File-name constants ─────────────────────────────────────────────────── */
#define MOO_PREFS_XML_FILE_NAME         "@MOO_PREFS_XML_FILE_NAME@"
#define MOO_STATE_XML_FILE_NAME         "@MOO_STATE_XML_FILE_NAME@"
#define MOO_SESSION_XML_FILE_NAME       "@MOO_SESSION_XML_FILE_NAME@"
#define MOO_NAMED_SESSION_XML_FILE_NAME "@MOO_NAMED_SESSION_XML_FILE_NAME@"
#define MEDIT_PORTABLE_MAGIC_FILE_NAME  "@MEDIT_PORTABLE_MAGIC_FILE_NAME@"
#define MEDIT_PORTABLE_DATA_DIR         "@MEDIT_PORTABLE_DATA_DIR@"
#define MEDIT_PORTABLE_CACHE_DIR        "@MEDIT_PORTABLE_CACHE_DIR@"

/* ── Install dirs (Unix only; on Win32 these are runtime-computed) ────────── */
#cmakedefine MOO_DATA_DIR   "@MOO_DATA_DIR@"
#cmakedefine MOO_LIB_DIR    "@MOO_LIB_DIR@"
#cmakedefine MOO_LOCALE_DIR "@MOO_LOCALE_DIR@"
#cmakedefine MOO_HELP_DIR   "@MOO_HELP_DIR@"

/* ── Feature flags ───────────────────────────────────────────────────────── */
#cmakedefine01 ENABLE_NLS
/* Sources test this with #ifdef, so it must be undefined (not 0) when
   Python is disabled.  Use #cmakedefine, not #cmakedefine01. */
#cmakedefine MOO_ENABLE_PYTHON 1
#cmakedefine01 MOO_BUILD_CTAGS
#cmakedefine01 MOO_ENABLE_COVERAGE
#cmakedefine01 MOO_BROKEN_GTK_THEME

/* ── OS flags ────────────────────────────────────────────────────────────── */
#cmakedefine MOO_OS_WIN32
#cmakedefine MOO_OS_UNIX
#cmakedefine MOO_OS_DARWIN
#cmakedefine MOO_OS_FREEBSD
#cmakedefine MOO_OS_LINUX

/* ── Debug flags ─────────────────────────────────────────────────────────── */
/* moo-config.h requires DEBUG, MOO_DEBUG, and ENABLE_DEBUG to be in sync.   */
/* We define all three together based on the single MOO_ENABLE_DEBUG option.  */
#cmakedefine01 MOO_ENABLE_DEBUG
#if MOO_ENABLE_DEBUG
#  ifndef DEBUG
#    define DEBUG 1
#  endif
#  ifndef MOO_DEBUG
#    define MOO_DEBUG 1
#  endif
#  ifndef ENABLE_DEBUG
#    define ENABLE_DEBUG 1
#  endif
#else
/* Non-debug build: ensure none of the three flags are defined. */
#  undef  DEBUG
#  undef  MOO_DEBUG
#  undef  ENABLE_DEBUG
#endif

/* ── Header availability (replaces autoconf AC_CHECK_HEADERS) ───────────── */
#cmakedefine01 HAVE_DLFCN_H
#cmakedefine01 HAVE_INTTYPES_H
#cmakedefine01 HAVE_LOCALE_H
#cmakedefine01 HAVE_SIGNAL_H
#cmakedefine01 HAVE_STDINT_H
#cmakedefine01 HAVE_STDIO_H
#cmakedefine01 HAVE_STDLIB_H
#cmakedefine01 HAVE_STRINGS_H
#cmakedefine01 HAVE_STRING_H
#cmakedefine01 HAVE_SYS_STAT_H
#cmakedefine01 HAVE_SYS_TYPES_H
#cmakedefine01 HAVE_SYS_UTSNAME_H
#cmakedefine01 HAVE_SYS_WAIT_H
#cmakedefine01 HAVE_UNISTD_H
#cmakedefine01 HAVE_WCHAR_H
#cmakedefine01 HAVE_GETC_UNLOCKED
#cmakedefine01 HAVE_MMAP

#include <moo-config.h>
#endif /* __CONFIG_H__ */
