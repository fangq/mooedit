# po-gsv/CMakeLists.txt
# Equivalent of po-gsv/Makefile.am
#
# Same structure as po/CMakeLists.txt but uses GETTEXT_PACKAGE_GSV
# (i.e. "medit-1-gsv") for the GtkSourceView language-spec translations.

find_program(MSGFMT  msgfmt)
find_program(INTLTOOL_UPDATE intltool-update)
find_program(INTLTOOL_EXTRACT intltool-extract)

# ── Read language list ────────────────────────────────────────────────────────
set(_linguas_file "${CMAKE_CURRENT_SOURCE_DIR}/LINGUAS")
if(NOT EXISTS "${_linguas_file}")
    message(WARNING "po-gsv/LINGUAS not found – no GSV translations will be built")
    return()
endif()

file(STRINGS "${_linguas_file}" _linguas_raw)
set(LINGUAS_GSV "")
foreach(_line ${_linguas_raw})
    string(REGEX REPLACE "^#.*" "" _line "${_line}")
    string(STRIP "${_line}" _line)
    if(_line)
        list(APPEND LINGUAS_GSV "${_line}")
    endif()
endforeach()

if(NOT LINGUAS_GSV)
    message(STATUS "po-gsv/LINGUAS: no languages listed")
    return()
endif()
message(STATUS "po-gsv languages: ${LINGUAS_GSV}")

# ── Compile .po → .gmo ───────────────────────────────────────────────────────
set(_gmo_files "")

if(ENABLE_NLS AND MSGFMT)
    foreach(_lang ${LINGUAS_GSV})
        set(_po  "${CMAKE_CURRENT_SOURCE_DIR}/${_lang}.po")
        set(_gmo "${CMAKE_CURRENT_BINARY_DIR}/${_lang}.gmo")

        add_custom_command(
            OUTPUT  "${_gmo}"
            COMMAND "${MSGFMT}" -o "${_gmo}" "${_po}"
            DEPENDS "${_po}"
            COMMENT "Compiling ${_lang}.po → ${_lang}.gmo [${GETTEXT_PACKAGE_GSV}]"
            VERBATIM
        )
        list(APPEND _gmo_files "${_gmo}")
    endforeach()
endif()

add_custom_target(po_gsv_catalogs ALL DEPENDS ${_gmo_files})

# ── Install ───────────────────────────────────────────────────────────────────
if(ENABLE_NLS)
    foreach(_lang ${LINGUAS_GSV})
        set(_gmo "${CMAKE_CURRENT_BINARY_DIR}/${_lang}.gmo")
        install(
            FILES       "${_gmo}"
            DESTINATION "${CMAKE_INSTALL_LOCALEDIR}/${_lang}/LC_MESSAGES"
            RENAME      "${GETTEXT_PACKAGE_GSV}.mo"
        )
    endforeach()
endif()

# ── pot / merge helpers ───────────────────────────────────────────────────────
if(INTLTOOL_UPDATE AND INTLTOOL_EXTRACT)
    add_custom_target(po_gsv_update_pot
        COMMAND
            ${CMAKE_COMMAND} -E env
            "INTLTOOL_EXTRACT=${INTLTOOL_EXTRACT}"
            "srcdir=${CMAKE_CURRENT_SOURCE_DIR}"
            "${INTLTOOL_UPDATE}"
            --gettext-package "${GETTEXT_PACKAGE_GSV}"
            --pot
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Regenerating ${GETTEXT_PACKAGE_GSV}.pot"
        VERBATIM
    )

    add_custom_target(po_gsv_merge
        COMMAND
            ${CMAKE_COMMAND} -E env
            "INTLTOOL_EXTRACT=${INTLTOOL_EXTRACT}"
            "srcdir=${CMAKE_CURRENT_SOURCE_DIR}"
            "${INTLTOOL_UPDATE}"
            --gettext-package "${GETTEXT_PACKAGE_GSV}"
            --dist
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Merging translations for ${GETTEXT_PACKAGE_GSV}"
        VERBATIM
    )
endif()
