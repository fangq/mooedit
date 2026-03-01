# api/CMakeLists.txt
# Equivalent of api/Makefile.am
#
# The api/ directory contains only Python scripts used during the build
# (parsedocs.py, gendefs.py, genlua.py, gendocs.py and their modules).
# No compiled library or executable is produced here.
# In dev-mode the scripts are run to regenerate moo.xml and gtk.xml.

set(_api_dir "${CMAKE_CURRENT_SOURCE_DIR}")
set(_moo_dir "${CMAKE_SOURCE_DIR}/moo")

# ── moo.xml stamp (dev-mode only) ────────────────────────────────────────────
if(MOO_DEV_MODE)
    # Collect source dirs that parsedocs.py scans
    set(_source_dir_args
        --source-dir "${_moo_dir}/mooapp"
        --source-dir "${_moo_dir}/mooedit"
        --source-dir "${_moo_dir}/moofileview"
        --source-dir "${_moo_dir}/mooutils"
        --source-dir "${_moo_dir}/moopython"
        --source-dir "${_moo_dir}/plugins/usertools"
        --source-dir "${_moo_dir}/plugins/support"
        --source-file "${_moo_dir}/moolua/medit-lua.cpp"
        --source-file "${_moo_dir}/moolua/medit-lua.h"
        --skip "moofontsel.*"
    )

    add_custom_command(
        OUTPUT  "${_api_dir}/moo.xml"
                "${CMAKE_CURRENT_BINARY_DIR}/moo.xml.stamp"
        COMMAND "${MOO_PYTHON}" "${_api_dir}/parsedocs.py"
                ${_source_dir_args}
                --output "${CMAKE_CURRENT_BINARY_DIR}/moo.xml.tmp"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_BINARY_DIR}/moo.xml.tmp"
                "${_api_dir}/moo.xml"
        COMMAND ${CMAKE_COMMAND} -E remove
                "${CMAKE_CURRENT_BINARY_DIR}/moo.xml.tmp"
        COMMAND ${CMAKE_COMMAND} -E touch
                "${CMAKE_CURRENT_BINARY_DIR}/moo.xml.stamp"
        COMMENT "Generating api/moo.xml"
        VERBATIM
    )

    # gtk.xml stamp
    add_custom_command(
        OUTPUT  "${_api_dir}/gtk.xml"
                "${CMAKE_CURRENT_BINARY_DIR}/gtk.xml.stamp"
        COMMAND "${MOO_PYTHON}" "${_api_dir}/parsedocs.py"
                --source-file "${_moo_dir}/moolua/gtk-api.c"
                --source-file "${_moo_dir}/moolua/gtk-api.h"
                --module Gtk
                --output "${CMAKE_CURRENT_BINARY_DIR}/gtk.xml.tmp"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_BINARY_DIR}/gtk.xml.tmp"
                "${_api_dir}/gtk.xml"
        COMMAND ${CMAKE_COMMAND} -E remove
                "${CMAKE_CURRENT_BINARY_DIR}/gtk.xml.tmp"
        COMMAND ${CMAKE_COMMAND} -E touch
                "${CMAKE_CURRENT_BINARY_DIR}/gtk.xml.stamp"
        COMMENT "Generating api/gtk.xml"
        VERBATIM
    )

    add_custom_target(api_xml ALL
        DEPENDS
            "${CMAKE_CURRENT_BINARY_DIR}/moo.xml.stamp"
            "${CMAKE_CURRENT_BINARY_DIR}/gtk.xml.stamp"
    )
endif()
