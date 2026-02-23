AC_DEFUN([_MOO_AC_PYTHON_DEVEL],[
  python_found=no
  if test "$cross_compiling" = yes; then
    test -z "$PYTHON_INCLUDES" || python_found=yes
  else
    AC_MSG_CHECKING([for the distutils Python package])
    $PYTHON -c "import distutils" 2>/dev/null || $PYTHON -c "import sysconfig" 2>/dev/null
    if test $? -eq 0; then
        python_found=yes
        AC_MSG_RESULT([yes])
    else
        python_found=no
        AC_MSG_RESULT([no])
    fi
  fi
  if test $python_found = yes; then
      AC_MSG_CHECKING([for Python include path])
      if test -z "$PYTHON_INCLUDES"; then
          python_path=`$PYTHON -c "
try:
    import distutils.sysconfig
    print(distutils.sysconfig.get_python_inc())
except ImportError:
    import sysconfig
    print(sysconfig.get_path('include'))
"`
          if test -n "${python_path}"; then
              python_path="-I$python_path"
          fi
          PYTHON_INCLUDES=$python_path
      fi
      AC_MSG_RESULT([$PYTHON_INCLUDES])
      AC_SUBST([PYTHON_INCLUDES])
  fi
  if test $python_found = yes; then
      AC_MSG_CHECKING([Python linker flags])
      if test "x$PYTHON_LIBS" = "x"; then
          PYTHON_LIBS=`$PYTHON -c "
import sys
try:
    from distutils import sysconfig as sc
    libdir = sc.get_config_var('LIBDIR') or (sys.prefix + '/lib')
    ver = sc.get_config_var('VERSION') or (str(sys.version_info.major)+'.'+str(sys.version_info.minor))
except ImportError:
    import sysconfig as sc
    libdir = sc.get_config_var('LIBDIR') or (sys.prefix + '/lib')
    ver = sc.get_config_var('VERSION') or (str(sys.version_info.major)+'.'+str(sys.version_info.minor))
print('-L' + libdir + ' -lpython' + ver)
" 2>/dev/null`
      fi
      AC_MSG_RESULT([$PYTHON_LIBS])
      AC_SUBST([PYTHON_LIBS])
  fi
  if test $python_found = yes; then
      m4_if([$1],[],[:],[$1])
  else
      m4_if([$2],[],[:],[$2])
  fi
])
AC_DEFUN([MOO_AC_CHECK_PYTHON_NATIVE],[
    m4_define_default([_AM_PYTHON_INTERPRETER_LIST],
        [python3 python3.13 python3.12 python3.11 python3.10 python3.9 python3.8 python3.7 python3.6 python])
    AM_PATH_PYTHON([$1],[
        _MOO_AC_PYTHON_DEVEL([python_found=yes],[
            AC_MSG_WARN([Found python but no dev headers])
            python_found=no
        ])
    ],[python_found=no])
    if test x$python_found = xyes; then
        m4_if([$2],[],[:],[$2])
    else
        PYTHON_INCLUDES=""
        PYTHON_LIBS=""
        m4_if([$3],[],[:],[$3])
    fi
])
AC_DEFUN([MOO_AM_PYTHON_DEVEL_CROSS_MINGW],[
  if test x"$PYTHON_INCLUDES" = x -o x"$PYTHON_LIBS" = x -o x"$PYTHON_VERSION" = x; then
    AC_MSG_ERROR([Set PYTHON_INCLUDES, PYTHON_LIBS, PYTHON_VERSION for cross build])
  fi
  AC_ARG_VAR([PYTHON_INCLUDES], [python preprocessor flags])
  AC_ARG_VAR([PYTHON_LIBS], [python linker flags])
  AC_ARG_VAR([PYTHON_VERSION], [python version])
  AC_SUBST(PYTHON_INCLUDES)
  AC_SUBST(PYTHON_LIBS)
  AC_SUBST([PYTHON_VERSION],[$PYTHON_VERSION])
  AC_SUBST([PYTHON_PREFIX], ['${prefix}'])
  AC_SUBST([PYTHON_EXEC_PREFIX], ['${exec_prefix}'])
  AC_SUBST([PYTHON_PLATFORM], [nt])
  AC_SUBST([pythondir], [$PYTHON_PREFIX/lib/python$PYTHON_VERSION/site-packages])
  AC_SUBST([pyexecdir], [$PYTHON_EXEC_PREFIX/lib/python$PYTHON_VERSION/site-packages])
  $1
])
AC_DEFUN([MOO_AC_CHECK_PYTHON],[
  AC_REQUIRE([MOO_AC_CHECK_OS])
  if test "$cross_compiling" = yes -a "$MOO_OS_WIN32" = true; then
    MOO_AM_PYTHON_DEVEL_CROSS_MINGW([$2],[$3])
  else
    MOO_AC_CHECK_PYTHON_NATIVE([$1],[$2],[$3])
  fi
])
