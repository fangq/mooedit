# cmake/MooSpell.cmake
# Detect gspell-1 (GTK 3 spell-check) for the in-editor spell-checker.
# gspell uses hunspell under the hood; the hunspell DLL/.so and at least
# one dictionary (e.g. en_US) must be available at runtime too, but those
# come in as transitive dependencies — we only need to find gspell here.
#
# Sets:
#   MOO_BUILD_SPELL    – TRUE if gspell-1 is found and not explicitly disabled
#   PkgConfig::GSPELL  – imported target for linking
#
# User option (defined in the top-level CMakeLists.txt):
#   MOO_WITH_SPELL = auto | yes | no   (default: auto)

set(MOO_BUILD_SPELL FALSE)

if(MOO_WITH_SPELL STREQUAL "no")
    message(STATUS "Spell-check: disabled by user")
    return()
endif()

find_package(PkgConfig REQUIRED)

# Mark REQUIRED only when the user explicitly asked for it; in "auto"
# mode let configure succeed without spell-check support.
if(MOO_WITH_SPELL STREQUAL "yes")
    pkg_check_modules(GSPELL REQUIRED IMPORTED_TARGET gspell-1>=1.8)
else()
    pkg_check_modules(GSPELL IMPORTED_TARGET gspell-1>=1.8)
endif()

if(GSPELL_FOUND)
    set(MOO_BUILD_SPELL TRUE)
    message(STATUS "Found gspell: ${GSPELL_VERSION} — spell-check enabled")
else()
    message(STATUS "gspell-1 not found — spell-check disabled")
endif()
