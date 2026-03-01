# po/CMakeLists.txt
# Equivalent of po/Makefile.am
#
# Handles .po → .gmo compilation and installation of message catalogs.
# When ENABLE_NLS is OFF the all target is a no-op and install is skipped.

find_program(MSGFMT  msgfmt)
find_program(GMSGFMT msgfmt)   # same binary on most systems
find_program(INTLTOOL_UPDATE intltool-update)
find_program(INTLTOOL_EXTRACT intltool-extract)

# ── Read the list of languages from po/LINGUAS ───────────────────────────────
set(_linguas_file "${CMAKE_CURRENT_SOURCE_DIR}/LINGUAS")
if(NOT EXISTS "${_linguas_file}")
    message(WARNING "po/LINGUAS not found – no translations will be built")
    return()
endif()

file(STRINGS "${_linguas_file}" _linguas_raw)
set(LINGUAS "")
foreach(_line ${_linguas_raw})
    # strip comments
    string(REGEX REPLACE "^#.*" "" _line "${_line}")
    string(STRIP "${_line}" _line)
    if(_line)
        list(APPEND LINGUAS "${_line}")
    endif()
endforeach()

if(NOT LINGUAS)
    message(STATUS "po/LINGUAS: no languages listed")
    return()
endif()
message(STATUS "po languages: ${LINGUAS}")

# ── Compile .po → .gmo for each language ─────────────────────────────────────
set(_gmo_files "")

if(ENABLE_NLS AND MSGFMT)
    foreach(_lang ${LINGUAS})
        set(_po  "${CMAKE_CURRENT_SOURCE_DIR}/${_lang}.po")
        set(_gmo "${CMAKE_CURRENT_BINARY_DIR}/${_lang}.gmo")

        add_custom_command(
            OUTPUT  "${_gmo}"
            COMMAND "${MSGFMT}" -o "${_gmo}" "${_po}"
            DEPENDS "${_po}"
            COMMENT "Compiling ${_lang}.po → ${_lang}.gmo [${GETTEXT_PACKAGE}]"
            VERBATIM
        )
        list(APPEND _gmo_files "${_gmo}")
    endforeach()
endif()

add_custom_target(po_catalogs ALL DEPENDS ${_gmo_files})

# ── Install .gmo files as <locale>/LC_MESSAGES/<package>.mo ──────────────────
if(ENABLE_NLS)
    foreach(_lang ${LINGUAS})
        set(_gmo "${CMAKE_CURRENT_BINARY_DIR}/${_lang}.gmo")
        install(
            FILES       "${_gmo}"
            DESTINATION "${CMAKE_INSTALL_LOCALEDIR}/${_lang}/LC_MESSAGES"
            RENAME      "${GETTEXT_PACKAGE}.mo"
        )
    endforeach()
endif()

# ── pot / merge helpers (equivalent of GENPOT / MSGMERGE targets) ─────────────
if(INTLTOOL_UPDATE AND INTLTOOL_EXTRACT)
    add_custom_target(po_update_pot
        COMMAND
            ${CMAKE_COMMAND} -E env
            "INTLTOOL_EXTRACT=${INTLTOOL_EXTRACT}"
            "srcdir=${CMAKE_CURRENT_SOURCE_DIR}"
            "${INTLTOOL_UPDATE}"
            --gettext-package "${GETTEXT_PACKAGE}"
            --pot
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Regenerating ${GETTEXT_PACKAGE}.pot"
        VERBATIM
    )

    add_custom_target(po_merge
        COMMAND
            ${CMAKE_COMMAND} -E env
            "INTLTOOL_EXTRACT=${INTLTOOL_EXTRACT}"
            "srcdir=${CMAKE_CURRENT_SOURCE_DIR}"
            "${INTLTOOL_UPDATE}"
            --gettext-package "${GETTEXT_PACKAGE}"
            --dist
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Merging translations for ${GETTEXT_PACKAGE}"
        VERBATIM
    )
endif()
