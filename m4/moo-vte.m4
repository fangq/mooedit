dnl moo-vte.m4 — VTE terminal support (optional, auto-detected)

AC_DEFUN([MOO_AC_VTE],[
AC_ARG_WITH([vte],
    AS_HELP_STRING([--with-vte], [Build with native VTE terminal (auto/yes/no)]),
    [], [with_vte=auto])

have_vte=no
if test "x$with_vte" != "xno"; then
    PKG_CHECK_MODULES(VTE, [vte-2.91], [have_vte=yes], [
        PKG_CHECK_MODULES(VTE, [vte-2.90], [have_vte=yes], [have_vte=no])
    ])

    if test "x$have_vte" = "xyes"; then
        AC_DEFINE([HAVE_VTE], [1], [Have VTE terminal library])
        MOO_CFLAGS="$MOO_CFLAGS $VTE_CFLAGS"
        MOO_LIBS="$MOO_LIBS $VTE_LIBS"
    elif test "x$with_vte" = "xyes"; then
        AC_MSG_ERROR([VTE terminal requested but vte-2.91 not found])
    fi
fi

AM_CONDITIONAL([MOO_BUILD_TERMINAL], [test "x$have_vte" = "xyes"])
AC_MSG_NOTICE([VTE terminal support: $have_vte])
])
