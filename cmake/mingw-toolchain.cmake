# cmake/mingw-toolchain.cmake
#
# CMake toolchain file for cross-compiling medit for Windows 32-bit
# using the MinGW-w64 toolchain on a Linux host.
#
# ── USAGE ─────────────────────────────────────────────────────────────────────
#
#   cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-toolchain.cmake \
#         -DMINGW_SYSROOT=/opt/gtk-win32 \
#         -DCMAKE_INSTALL_PREFIX=/opt/medit-win32 \
#         [-DMOO_WITH_PYTHON=no] \
#         [-DPYTHON_INCLUDES="-I/opt/gtk-win32/include/python3.9"] \
#         [-DPYTHON_LIBS="-lpython39"] \
#         [-DPYTHON_VERSION="3.9"] \
#         -DCMAKE_BUILD_TYPE=Release \
#         ..
#
# Prerequisites on the Linux host:
#   sudo apt install gcc-mingw-w64-i686 g++-mingw-w64-i686 mingw-w64-tools \
#                    mingw-w64-i686-dev
#
# The MinGW sysroot (MINGW_SYSROOT) should contain:
#   bin/, lib/, include/, lib/pkgconfig/  with GTK3, GLib, libxml2, etc.
#   You can obtain one from:
#     https://github.com/tschoonj/GTK-for-Windows-Runtime-Environment-Installer
#   or build with MXE (https://mxe.cc):
#     make MXE_TARGETS=i686-w64-mingw32.static gtk3 libxml2
# ─────────────────────────────────────────────────────────────────────────────

# ── Target system ─────────────────────────────────────────────────────────────
set(CMAKE_SYSTEM_NAME    Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)

# ── MinGW compiler prefix ─────────────────────────────────────────────────────
# Adjust if your distro uses a different prefix (e.g. i586-mingw32msvc).
set(MINGW_PREFIX "i686-w64-mingw32")

find_program(CMAKE_C_COMPILER   ${MINGW_PREFIX}-gcc)
find_program(CMAKE_CXX_COMPILER ${MINGW_PREFIX}-g++)
find_program(CMAKE_RC_COMPILER  ${MINGW_PREFIX}-windres)

if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR
        "MinGW C compiler '${MINGW_PREFIX}-gcc' not found.\n"
        "Install with: sudo apt install gcc-mingw-w64-i686")
endif()

# ── Sysroot / search paths ────────────────────────────────────────────────────
# MINGW_SYSROOT must point to a directory containing the GTK3-for-Windows bundle.
if(NOT DEFINED MINGW_SYSROOT)
    # Try a few common locations before giving up.
    foreach(_candidate
            /opt/gtk-win32
            /usr/i686-w64-mingw32
            $ENV{HOME}/mingw-sysroot)
        if(EXISTS "${_candidate}/lib/pkgconfig")
            set(MINGW_SYSROOT "${_candidate}")
            break()
        endif()
    endforeach()
endif()

if(NOT DEFINED MINGW_SYSROOT OR NOT EXISTS "${MINGW_SYSROOT}")
    message(WARNING
        "MINGW_SYSROOT not set or does not exist.\n"
        "Pass -DMINGW_SYSROOT=/path/to/gtk-win32-bundle to cmake.\n"
        "Continuing anyway — pkg-config searches may fail.")
else()
    message(STATUS "MinGW sysroot: ${MINGW_SYSROOT}")
endif()

set(CMAKE_FIND_ROOT_PATH  "${MINGW_SYSROOT}" "/usr/${MINGW_PREFIX}")
set(CMAKE_SYSROOT         "${MINGW_SYSROOT}")

# Tell CMake to search only in the cross-compile target paths.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)   # host tools (python, windres...)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# ── pkg-config: point at Windows pkg-config files ─────────────────────────────
if(DEFINED MINGW_SYSROOT AND EXISTS "${MINGW_SYSROOT}/lib/pkgconfig")
    set(ENV{PKG_CONFIG_LIBDIR} "${MINGW_SYSROOT}/lib/pkgconfig")
    set(ENV{PKG_CONFIG_PATH}   "${MINGW_SYSROOT}/lib/pkgconfig")
    # Prevent pkg-config from mixing in host system libraries.
    set(ENV{PKG_CONFIG_SYSROOT_DIR} "${MINGW_SYSROOT}")
endif()

# Use the pkg-config wrapper that restricts paths to the target sysroot.
find_program(_PKG_CONFIG_EXEC
    NAMES ${MINGW_PREFIX}-pkg-config pkg-config
    NO_CMAKE_FIND_ROOT_PATH)   # look on host PATH
if(_PKG_CONFIG_EXEC)
    set(PKG_CONFIG_EXECUTABLE "${_PKG_CONFIG_EXEC}" CACHE FILEPATH
        "pkg-config for MinGW target" FORCE)
endif()

# ── Windows-specific compiler flags ──────────────────────────────────────────
set(CMAKE_C_FLAGS_INIT   "-mms-bitfields -march=i686")
set(CMAKE_CXX_FLAGS_INIT "-mms-bitfields -march=i686")

# ── Linker flags: add GTK bundle lib dir ─────────────────────────────────────
if(DEFINED MINGW_SYSROOT)
    set(CMAKE_EXE_LINKER_FLAGS_INIT    "-L${MINGW_SYSROOT}/lib")
    set(CMAKE_MODULE_LINKER_FLAGS_INIT "-L${MINGW_SYSROOT}/lib")
    set(CMAKE_SHARED_LINKER_FLAGS_INIT "-L${MINGW_SYSROOT}/lib")
    include_directories("${MINGW_SYSROOT}/include")
endif()
