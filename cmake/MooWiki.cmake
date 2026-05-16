# cmake/MooWiki.cmake
# In-editor Wiki preview — renders Habitat / UseMod-style wiki syntax
# to HTML for the MooHtml preview pane.  The converter is implemented
# entirely in-tree (~400 LOC of plain C++), so there's no external
# library to detect — this file only honours the user-facing
# MOO_WITH_WIKI option.
#
# Sets:
#   MOO_BUILD_WIKI   – TRUE unless user disabled it
#
# User option (defined in top-level CMakeLists.txt):
#   MOO_WITH_WIKI = auto | yes | no   (default: auto)

set(MOO_BUILD_WIKI FALSE)

if(MOO_WITH_WIKI STREQUAL "no")
    message(STATUS "Wiki preview: disabled by user")
    return()
endif()

# No external deps, so "auto" and "yes" always succeed.
set(MOO_BUILD_WIKI TRUE)
message(STATUS "Wiki preview: enabled (in-tree converter)")
