# cmake/macos-arm64.cmake
#
# CMake build-settings file for native Apple Silicon (arm64) builds of medit.
#
# This is NOT a cross-compilation toolchain file — it is a settings helper
# for native builds on an Apple Silicon Mac where Homebrew lives at
# /opt/homebrew.  Load it with:
#
#   cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/macos-arm64.cmake \
#         -DCMAKE_BUILD_TYPE=Release \
#         ..
#
# ── PREREQUISITES ─────────────────────────────────────────────────────────────
#
#   # 1. Install Xcode Command Line Tools
#   xcode-select --install
#
#   # 2. Install dependencies via Homebrew (arm64 native)
#   brew install gtk+3 libxml2 intltool pkg-config python3 \
#                vte3 adwaita-icon-theme
#
#   # 3. Optional — for dock integration:
#   brew install gtk-mac-integration
#
#   # 4. Configure and build
#   mkdir build-arm64 && cd build-arm64
#   cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/macos-arm64.cmake \
#         -DCMAKE_BUILD_TYPE=Release ..
#   make -j$(sysctl -n hw.logicalcpu)
#
# ── UNIVERSAL BINARY (arm64 + x86_64) ────────────────────────────────────────
#
#   All Homebrew dependencies must be available as universal or matching-arch
#   bottles.  To build a universal medit binary:
#
#   cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/macos-arm64.cmake \
#         -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
#         -DCMAKE_BUILD_TYPE=Release ..
#
# ─────────────────────────────────────────────────────────────────────────────

# ── Target architecture ───────────────────────────────────────────────────────
# Force arm64.  Remove or change to "x86_64;arm64" for a universal build.
if(NOT DEFINED CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING
        "Target architecture(s): arm64, x86_64, or arm64;x86_64 for universal")
endif()

# Minimum deployment target — GTK3 Homebrew bottles require 11.0+.
if(NOT DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING
        "Minimum macOS version (11.0 = Big Sur, required for Apple Silicon)")
endif()

# ── Homebrew prefix (Apple Silicon) ──────────────────────────────────────────
set(_homebrew_arm64 "/opt/homebrew")

if(NOT EXISTS "${_homebrew_arm64}/bin/brew")
    message(WARNING
        "${_homebrew_arm64}/bin/brew not found.\n"
        "This toolchain file is intended for Apple Silicon Macs with Homebrew "
        "installed at /opt/homebrew.\n"
        "On Intel Macs, omit this toolchain file and use "
        "-DCMAKE_PREFIX_PATH=/usr/local instead.")
endif()

# Prepend Homebrew arm64 prefix so find_package / pkg_check_modules find
# arm64 packages before anything in /usr/local (which may be Intel).
list(PREPEND CMAKE_PREFIX_PATH "${_homebrew_arm64}")

# Expose pkg-config files from Homebrew's arm64 tree.
set(ENV{PKG_CONFIG_PATH}
    "${_homebrew_arm64}/lib/pkgconfig:${_homebrew_arm64}/share/pkgconfig:$ENV{PKG_CONFIG_PATH}")

# Ensure pkg-config itself is the arm64 Homebrew one.
set(PKG_CONFIG_EXECUTABLE "${_homebrew_arm64}/bin/pkg-config" CACHE FILEPATH
    "pkg-config from Homebrew arm64 prefix" FORCE)

# ── Compiler flags ────────────────────────────────────────────────────────────
# -arch arm64 is implied by CMAKE_OSX_ARCHITECTURES; no need to add manually.
# Adding -mmacosx-version-min here would conflict with CMAKE_OSX_DEPLOYMENT_TARGET.
