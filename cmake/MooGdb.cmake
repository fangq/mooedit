# cmake/MooGdb.cmake
# GDB-based C/C++ debugger plugin.  No compile-time library
# dependency — the plugin drives a `gdb` subprocess via its Machine
# Interface (mi3), so the only requirement is that gdb is on the
# user's runtime PATH.  We try to locate it at configure time as a
# friendly heads-up, but its absence isn't fatal: users can install
# gdb later and the plugin will pick it up.
#
# Sets:
#   MOO_BUILD_GDB   – TRUE unless the user explicitly disabled it
#
# User option (defined in the top-level CMakeLists.txt):
#   MOO_WITH_GDB = auto | yes | no   (default: auto)

set(MOO_BUILD_GDB FALSE)

if(MOO_WITH_GDB STREQUAL "no")
    message(STATUS "GDB debugger: disabled by user")
    return()
endif()

find_program(GDB_EXECUTABLE gdb)
if(GDB_EXECUTABLE)
    message(STATUS "GDB debugger: enabled (configure-time gdb: ${GDB_EXECUTABLE})")
else()
    message(STATUS "GDB debugger: enabled (gdb not on PATH at configure "
                   "time; users will need to install gdb to use the plugin)")
endif()

set(MOO_BUILD_GDB TRUE)
