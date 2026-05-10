# cmake/MooNLS.cmake
# Equivalent of MOO_INTL / _MOO_INTLTOOL from moo-intltool.m4
# Handles gettext + intltool setup

option(ENABLE_NLS "Enable Native Language Support (translations)" ON)

if(ENABLE_NLS)
    # Find intltool scripts
    find_program(INTLTOOL_UPDATE  intltool-update)
    find_program(INTLTOOL_MERGE   intltool-merge)
    find_program(INTLTOOL_EXTRACT intltool-extract)

    if(NOT INTLTOOL_UPDATE OR NOT INTLTOOL_MERGE OR NOT INTLTOOL_EXTRACT)
        message(FATAL_ERROR
            "intltool scripts not found. "
            "Install intltool or configure with -DENABLE_NLS=OFF")
    endif()

    message(STATUS "intltool-update:  ${INTLTOOL_UPDATE}")
    message(STATUS "intltool-merge:   ${INTLTOOL_MERGE}")
    message(STATUS "intltool-extract: ${INTLTOOL_EXTRACT}")

    # Command used to merge .desktop / .ini files with translations
    # (replaces MOO_INTLTOOL_INI_CMD / MOO_INTLTOOL_INI_DEPS substitution vars)
    set(MOO_INTLTOOL_INI_DEPS "${INTLTOOL_MERGE}")
    set(MOO_INTLTOOL_INI_CMD
        "LC_ALL=C ${INTLTOOL_MERGE} -d -u -c <BUILDDIR>/po/.intltool-merge-cache <SRCDIR>/po <INPUT> <OUTPUT>")

    find_package(Gettext REQUIRED)
    add_compile_definitions(ENABLE_NLS=1)

    message(STATUS "NLS: enabled")
else()
    # No NLS – strip translation markers from .ini.in files with sed
    set(MOO_INTLTOOL_INI_DEPS "")
    set(MOO_INTLTOOL_INI_CMD
        "sed -e 's/^_//g' <INPUT> > <OUTPUT>.tmp && mv <OUTPUT>.tmp <OUTPUT>")
    message(STATUS "NLS: disabled")
endif()

# ── Helper function: merge a single .ini.in → .ini (or .desktop.in → .desktop)
# Usage: moo_intltool_merge(INPUT foo.ini.in OUTPUT foo.ini)
function(moo_intltool_merge)
    cmake_parse_arguments(_a "" "INPUT;OUTPUT" "" ${ARGN})
    # intltool-merge does not create the output directory; CMake source-tree
    # subdirs (e.g. moo/medit-app/) only exist in the build tree if a target
    # has already produced something there, which isn't the case for files
    # consumed solely by install().
    get_filename_component(_a_OUTDIR "${_a_OUTPUT}" DIRECTORY)
    if(ENABLE_NLS)
        add_custom_command(
            OUTPUT  "${_a_OUTPUT}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${_a_OUTDIR}"
            COMMAND LC_ALL=C ${INTLTOOL_MERGE}
                        -d -u
                        -c "${CMAKE_BINARY_DIR}/po/.intltool-merge-cache"
                        "${CMAKE_SOURCE_DIR}/po"
                        "${_a_INPUT}"
                        "${_a_OUTPUT}"
            DEPENDS "${_a_INPUT}" ${INTLTOOL_MERGE}
            COMMENT "Merging translations into ${_a_OUTPUT}"
        )
    else()
        add_custom_command(
            OUTPUT  "${_a_OUTPUT}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${_a_OUTDIR}"
            COMMAND sed -e "s/^_//g" "${_a_INPUT}" > "${_a_OUTPUT}.tmp"
            COMMAND ${CMAKE_COMMAND} -E rename "${_a_OUTPUT}.tmp" "${_a_OUTPUT}"
            DEPENDS "${_a_INPUT}"
            COMMENT "Stripping translation markers from ${_a_OUTPUT}"
        )
    endif()
endfunction()
