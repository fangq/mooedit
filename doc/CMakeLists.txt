# doc/CMakeLists.txt
# Equivalent of doc/Makefile.am
#
# In dev-mode: regenerates docbook sources, HTML help, and the man page.
# Always: installs pre-built help/ tree and man page.

set(_doc_src  "${CMAKE_CURRENT_SOURCE_DIR}")
set(_api_src  "${CMAKE_SOURCE_DIR}/api")
set(_top_src  "${CMAKE_SOURCE_DIR}")
set(_top_bin  "${CMAKE_BINARY_DIR}")

# ── Install pre-built help files (always) ────────────────────────────────────
install(
    DIRECTORY   "${_doc_src}/help/"
    DESTINATION "${MOO_HELP_DIR}"
    FILES_MATCHING
        PATTERN "*.html"
        PATTERN "*.css"
)
install(
    DIRECTORY   "${_doc_src}/help/script/"
    DESTINATION "${MOO_HELP_DIR}/script"
    FILES_MATCHING PATTERN "*.html"
)
install(
    DIRECTORY   "${_doc_src}/help/img/"
    DESTINATION "${MOO_HELP_DIR}/img"
    FILES_MATCHING PATTERN "*.png"
)

# Man page (Unix + app build only)
if(MOO_OS_UNIX AND MOO_BUILD_APP)
    install(
        FILES       "${_doc_src}/built/medit.1"
        DESTINATION "${CMAKE_INSTALL_MANDIR}/man1"
    )
endif()

# ── Dev-mode: regenerate everything from source ───────────────────────────────
if(MOO_DEV_MODE)

    # gendocbook helper scripts
    set(_gendocbook_files
        "${_api_src}/gendocbook.py"
        "${_api_src}/mpi/__init__.py"
        "${_api_src}/mpi/module.py"
        "${_api_src}/mpi/docbookwriter.py"
    )

    # ── medit-defines.ent (configure-time substitution) ──────────────────────
    configure_file(
        "${_doc_src}/medit-defines.ent.in"
        "${CMAKE_CURRENT_BINARY_DIR}/medit-defines.ent"
        @ONLY
    )
    add_custom_command(
        OUTPUT  "${_doc_src}/built/medit-defines.ent"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_doc_src}/built"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_BINARY_DIR}/medit-defines.ent"
                "${_doc_src}/built/medit-defines.ent"
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/medit-defines.ent"
        COMMENT "Copying medit-defines.ent to built/"
    )

    # ── lgpl.no-fancy-chars ───────────────────────────────────────────────────
    add_custom_command(
        OUTPUT  "${_doc_src}/built/lgpl.no-fancy-chars"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_doc_src}/built"
        COMMAND bash -c
            "tr -d '\\014' < '${_top_src}/COPYING' > lgpl.no-fancy-chars.tmp && mv lgpl.no-fancy-chars.tmp '${_doc_src}/built/lgpl.no-fancy-chars'"
        DEPENDS "${_top_src}/COPYING"
        COMMENT "Stripping form-feeds from COPYING"
    )

    # ── script-python.docbook ─────────────────────────────────────────────────
    add_custom_command(
        OUTPUT  "${_doc_src}/built/script-python.docbook"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_doc_src}/built"
        COMMAND "${MOO_PYTHON}" "${_api_src}/gendocbook.py"
                --python
                --template "${_doc_src}/script-python.tmpl.docbook"
                "${_api_src}/moo.xml"
                > "${CMAKE_CURRENT_BINARY_DIR}/script-python.docbook.tmp"
        COMMAND ${CMAKE_COMMAND} -E rename
                "${CMAKE_CURRENT_BINARY_DIR}/script-python.docbook.tmp"
                "${_doc_src}/built/script-python.docbook"
        DEPENDS ${_gendocbook_files}
                "${_doc_src}/script-python.tmpl.docbook"
                "${_api_src}/moo.xml"
        COMMENT "Generating script-python.docbook"
        VERBATIM
    )

    # ── script-lua.docbook ────────────────────────────────────────────────────
    add_custom_command(
        OUTPUT  "${_doc_src}/built/script-lua.docbook"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_doc_src}/built"
        COMMAND "${MOO_PYTHON}" "${_api_src}/gendocbook.py"
                --lua
                --template "${_doc_src}/script-lua.tmpl.docbook"
                --import "${_api_src}/gtk.xml"
                "${_api_src}/moo.xml"
                > "${CMAKE_CURRENT_BINARY_DIR}/script-lua.docbook.tmp"
        COMMAND ${CMAKE_COMMAND} -E rename
                "${CMAKE_CURRENT_BINARY_DIR}/script-lua.docbook.tmp"
                "${_doc_src}/built/script-lua.docbook"
        DEPENDS ${_gendocbook_files}
                "${_doc_src}/script-lua.tmpl.docbook"
                "${_api_src}/moo.xml"
                "${_api_src}/gtk.xml"
        COMMENT "Generating script-lua.docbook"
        VERBATIM
    )

    # ── script-lua-gtk.docbook ────────────────────────────────────────────────
    add_custom_command(
        OUTPUT  "${_doc_src}/built/script-lua-gtk.docbook"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_doc_src}/built"
        COMMAND "${MOO_PYTHON}" "${_api_src}/gendocbook.py"
                --lua
                --template "${_doc_src}/script-lua-gtk.tmpl.docbook"
                "${_api_src}/gtk.xml"
                > "${CMAKE_CURRENT_BINARY_DIR}/script-lua-gtk.docbook.tmp"
        COMMAND ${CMAKE_COMMAND} -E rename
                "${CMAKE_CURRENT_BINARY_DIR}/script-lua-gtk.docbook.tmp"
                "${_doc_src}/built/script-lua-gtk.docbook"
        DEPENDS ${_gendocbook_files}
                "${_doc_src}/script-lua-gtk.tmpl.docbook"
                "${_api_src}/gtk.xml"
        COMMENT "Generating script-lua-gtk.docbook"
        VERBATIM
    )

    # ── HTML help (xsltproc) ──────────────────────────────────────────────────
    set(_docbook_sources
        "${_doc_src}/medit.docbook"
        "${_doc_src}/prefs.docbook"
        "${_doc_src}/regex.docbook"
        "${_doc_src}/user-tools.docbook"
        "${_doc_src}/license.docbook"
        "${_doc_src}/built/lgpl.no-fancy-chars"
        "${_doc_src}/built/medit-defines.ent"
    )
    set(_script_docbook_sources
        "${_doc_src}/built/medit-defines.ent"
        "${_doc_src}/built/script-python.docbook"
        "${_doc_src}/built/script-lua.docbook"
        "${_doc_src}/built/script-lua-gtk.docbook"
    )

    add_custom_command(
        OUTPUT  "${_doc_src}/help/index.html"
        COMMAND "${XSLTPROC}" --xinclude
                "${_doc_src}/medit.xsl" "${_doc_src}/medit.docbook"
        WORKING_DIRECTORY "${_doc_src}"
        DEPENDS ${_docbook_sources} "${_doc_src}/medit.xsl" "${_doc_src}/medit-common.xsl"
        COMMENT "Generating help/index.html"
        VERBATIM
    )

    add_custom_command(
        OUTPUT  "${_doc_src}/help/help.html"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_doc_src}/help"
        COMMAND "${XSLTPROC}" --xinclude --output
                "${CMAKE_CURRENT_BINARY_DIR}/help.html.tmp"
                "${_doc_src}/medit-single.xsl" "${_doc_src}/medit.docbook"
        COMMAND ${CMAKE_COMMAND} -E rename
                "${CMAKE_CURRENT_BINARY_DIR}/help.html.tmp"
                "${_doc_src}/help/help.html"
        DEPENDS ${_docbook_sources}
                "${_doc_src}/medit-single.xsl"
                "${_doc_src}/medit-common.xsl"
        COMMENT "Generating help/help.html"
        VERBATIM
    )

    add_custom_command(
        OUTPUT  "${_doc_src}/help/script/index.html"
        COMMAND "${XSLTPROC}" --xinclude
                "${_doc_src}/script-book.xsl" "${_doc_src}/script.docbook"
        WORKING_DIRECTORY "${_doc_src}"
        DEPENDS ${_script_docbook_sources}
                "${_doc_src}/script-book.xsl"
        COMMENT "Generating help/script/index.html"
        VERBATIM
    )

    add_custom_command(
        OUTPUT  "${_doc_src}/help/medit.css"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_doc_src}/help"
        COMMAND ${CMAKE_COMMAND} -E copy
                "${_doc_src}/medit.css" "${_doc_src}/help/medit.css"
        DEPENDS "${_doc_src}/medit.css"
        COMMENT "Copying medit.css to help/"
    )

    # ── PNG images ────────────────────────────────────────────────────────────
    set(_png_files
        prefs-file-filters.png
        prefs-file-selector.png
    )
    set(_dest_png_files "")
    foreach(_png ${_png_files})
        set(_dest "${_doc_src}/help/img/${_png}")
        add_custom_command(
            OUTPUT  "${_dest}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${_doc_src}/help/img"
            COMMAND ${CMAKE_COMMAND} -E copy
                    "${_doc_src}/img/${_png}" "${_dest}"
            DEPENDS "${_doc_src}/img/${_png}"
            COMMENT "Copying ${_png} to help/img/"
        )
        list(APPEND _dest_png_files "${_dest}")
    endforeach()

    # ── toc.xml + moo-help-sections.h ────────────────────────────────────────
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/toc.xml"
        COMMAND "${XSLTPROC}" --output "${CMAKE_CURRENT_BINARY_DIR}/toc.xml"
                --xinclude
                --stringparam chunk.first.sections 1
                "http://docbook.sourceforge.net/release/xsl/current/html/maketoc.xsl"
                "${_doc_src}/medit.docbook"
        DEPENDS ${_docbook_sources}
        COMMENT "Generating toc.xml"
        VERBATIM
    )

    add_custom_command(
        OUTPUT  "${_doc_src}/built/moo-help-sections.h"
                "${CMAKE_CURRENT_BINARY_DIR}/moo-help-sections.h.stamp"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_doc_src}/built"
        COMMAND "${MOO_PYTHON}" "${_doc_src}/genhelpsectionsh.py"
                "--toc=${CMAKE_CURRENT_BINARY_DIR}/toc.xml"
                "--srcdir=${_doc_src}"
                ${_docbook_files}
                > "${CMAKE_CURRENT_BINARY_DIR}/moo-help-sections.h.tmp"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_BINARY_DIR}/moo-help-sections.h.tmp"
                "${_doc_src}/built/moo-help-sections.h"
        COMMAND ${CMAKE_COMMAND} -E touch
                "${CMAKE_CURRENT_BINARY_DIR}/moo-help-sections.h.stamp"
        DEPENDS ${_docbook_sources}
                "${CMAKE_CURRENT_BINARY_DIR}/toc.xml"
                "${_doc_src}/genhelpsectionsh.py"
        COMMENT "Generating built/moo-help-sections.h"
        VERBATIM
    )

    # ── man page via txt2tags ─────────────────────────────────────────────────
    configure_file(
        "${_doc_src}/man-medit.t2t.in"
        "${CMAKE_CURRENT_BINARY_DIR}/man-medit.t2t"
        @ONLY
    )
    add_custom_command(
        OUTPUT  "${_doc_src}/built/man-medit.t2t"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_doc_src}/built"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_BINARY_DIR}/man-medit.t2t"
                "${_doc_src}/built/man-medit.t2t"
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/man-medit.t2t"
        COMMENT "Copying man-medit.t2t to built/"
    )

    add_custom_command(
        OUTPUT  "${_doc_src}/built/medit.1"
        COMMAND bash -c
            "'${TXT2TAGS}' --target=man --outfile=- '${_doc_src}/built/man-medit.t2t' | grep -v 'cmdline: txt2tags' > medit.1.tmp && mv medit.1.tmp '${_doc_src}/built/medit.1'"
        DEPENDS "${_doc_src}/built/man-medit.t2t"
        COMMENT "Generating medit.1 man page"
        VERBATIM
    )

    # ── Top-level 'doc' target ────────────────────────────────────────────────
    add_custom_target(doc ALL
        DEPENDS
            "${_doc_src}/help/index.html"
            "${_doc_src}/help/help.html"
            "${_doc_src}/help/script/index.html"
            "${_doc_src}/help/medit.css"
            "${_doc_src}/built/medit.1"
            "${_doc_src}/built/moo-help-sections.h"
            ${_dest_png_files}
    )

endif() # MOO_DEV_MODE
