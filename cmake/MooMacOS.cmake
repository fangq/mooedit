# cmake/MooMacOS.cmake
# macOS-specific build configuration for medit.
# Included only when MOO_OS_DARWIN is TRUE.
#
# Sets:
#   MOO_HOMEBREW_PREFIX      – detected Homebrew prefix (/opt/homebrew or /usr/local)
#   MOO_HAVE_IGE_MAC         – TRUE if ige-mac-integration is found
#   MOO_USE_QUARTZ           – TRUE if GDK Quartz backend + ige-mac-integration
#
# The Homebrew prefix is appended to CMAKE_PREFIX_PATH so that
# find_package() and pkg_check_modules() locate Homebrew packages on
# both Intel Macs (/usr/local) and Apple Silicon (/opt/homebrew).

# ── Homebrew prefix detection ─────────────────────────────────────────────────
set(MOO_HOMEBREW_PREFIX "")

# Apple Silicon Homebrew lives at /opt/homebrew; Intel at /usr/local.
foreach(_prefix "/opt/homebrew" "/usr/local")
    if(EXISTS "${_prefix}/bin/brew")
        set(MOO_HOMEBREW_PREFIX "${_prefix}")
        break()
    endif()
endforeach()

if(MOO_HOMEBREW_PREFIX)
    message(STATUS "Homebrew prefix: ${MOO_HOMEBREW_PREFIX}")
    # Make CMake's find_* commands search Homebrew first.
    list(PREPEND CMAKE_PREFIX_PATH "${MOO_HOMEBREW_PREFIX}")
    # Also add to pkg-config search path (in case PKG_CONFIG_PATH is not set).
    set(ENV{PKG_CONFIG_PATH}
        "${MOO_HOMEBREW_PREFIX}/lib/pkgconfig:${MOO_HOMEBREW_PREFIX}/share/pkgconfig:$ENV{PKG_CONFIG_PATH}")
else()
    message(STATUS "Homebrew not found — relying on system or MacPorts paths")
endif()

# ── ige-mac-integration (optional — dock icon / open-with support) ────────────
# Modern replacement: gtk-mac-integration-gtk3 (same pkg-config name on Homebrew)
set(MOO_HAVE_IGE_MAC   FALSE)
set(MOO_USE_QUARTZ     FALSE)

if(GDK_QUARTZ)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(IGE_MAC IMPORTED_TARGET ige-mac-integration)
    if(NOT IGE_MAC_FOUND)
        # Homebrew ships it as gtk-mac-integration
        pkg_check_modules(IGE_MAC IMPORTED_TARGET gtk-mac-integration-gtk3)
    endif()

    if(IGE_MAC_FOUND)
        set(MOO_HAVE_IGE_MAC TRUE)
        set(MOO_USE_QUARTZ   TRUE)
        message(STATUS "Found ige-mac-integration: ${IGE_MAC_VERSION} — dock integration enabled")
    else()
        message(STATUS "ige-mac-integration not found — dock integration disabled")
        message(STATUS "  Install with: brew install gtk-mac-integration")
    endif()
endif()
