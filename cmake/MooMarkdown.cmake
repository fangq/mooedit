# cmake/MooMarkdown.cmake
# Detect md4c + md4c-html (https://github.com/mity/md4c) — used by the
# in-editor Markdown preview pane.
#
# md4c is a fast C CommonMark parser; md4c-html is the HTML renderer
# shipped with the same project.  Both are required.  Available on all
# three CI platforms:
#   * Ubuntu/Debian: libmd4c-dev + libmd4c-html0-dev
#   * Homebrew:      md4c (ships both)
#   * MSYS2 MINGW64: mingw-w64-x86_64-md4c
#
# Sets:
#   MOO_BUILD_MARKDOWN     – TRUE if md4c + md4c-html were found
#   PkgConfig::MD4C        – imported target (parser)
#   PkgConfig::MD4C_HTML   – imported target (renderer)
#
# User option (defined in top-level CMakeLists.txt):
#   MOO_WITH_MARKDOWN = auto | yes | no   (default: auto)

set(MOO_BUILD_MARKDOWN FALSE)

if(MOO_WITH_MARKDOWN STREQUAL "no")
    message(STATUS "Markdown preview: disabled by user")
    return()
endif()

find_package(PkgConfig REQUIRED)

# REQUIRED only when explicitly requested; auto mode degrades silently.
if(MOO_WITH_MARKDOWN STREQUAL "yes")
    pkg_check_modules(MD4C       REQUIRED IMPORTED_TARGET md4c>=0.4)
    pkg_check_modules(MD4C_HTML  REQUIRED IMPORTED_TARGET md4c-html>=0.4)
else()
    pkg_check_modules(MD4C       IMPORTED_TARGET md4c>=0.4)
    pkg_check_modules(MD4C_HTML  IMPORTED_TARGET md4c-html>=0.4)
endif()

if(MD4C_FOUND AND MD4C_HTML_FOUND)
    set(MOO_BUILD_MARKDOWN TRUE)
    message(STATUS "Found md4c: ${MD4C_VERSION} (+ md4c-html ${MD4C_HTML_VERSION}) "
                   "— Markdown preview enabled")
else()
    message(STATUS "md4c not found — Markdown preview disabled")
endif()
