#!/bin/sh
# plat/win32/gtk-win/config.sh
#
# MinGW cross-compilation environment configuration.
# Sourced by plat/win32/mingw-configure.
#
# ── HOW TO USE ────────────────────────────────────────────────────────────────
# 1. Download (or build) a GTK3-for-Windows bundle, e.g.:
#      https://github.com/tschoonj/GTK-for-Windows-Runtime-Environment-Installer
#    or install via msys2/mingw-w64 packages and copy the sysroot.
# 2. Set mgwtargetdir below to the root of that bundle (the directory that
#    contains bin/, lib/, include/, share/).
# 3. Set mgwpythonver / mgwpythondotver if you want Python plugin support;
#    leave them empty to build without Python.
# 4. Set mgwconfig to: debug | reldbg | release
# 5. Run:  plat/win32/mingw-configure [--en] [--python]
# ─────────────────────────────────────────────────────────────────────────────

# Path to the MinGW GTK3 bundle sysroot (contains lib/pkgconfig, include/, …)
# Example: /opt/gtk-win32  or  /home/user/mingw-sysroot
mgwtargetdir=/opt/gtk-win32

# Install prefix for the finished medit build
mgwdestdir=/opt/medit-win32

# Build type: debug | reldbg | release
mgwconfig=release

# Python version numbers (leave empty to disable Python plugin)
# e.g. for Python 3.9: mgwpythonver=39  mgwpythondotver=3.9
mgwpythonver=39
mgwpythondotver=3.9

# Set to true when cross-compiling from Linux; false on Cygwin
mgwlinux=true
mgwcygwin=false
