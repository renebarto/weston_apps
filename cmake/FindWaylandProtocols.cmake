# - Try to find wayland-protocols
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
# WAYLAND_PROTOCOLS_FOUND
# WAYLAND_PROTOCOLS_PATH
#

find_package(PkgConfig)
pkg_check_modules(PC_WAYLAND_PROTOCOLS QUIET wayland-protocols)

if(PC_WAYLAND_PROTOCOLS_FOUND)
    if (WAYLAND_PROTOCOLS_REQUIRED_VERSION)
        if (NOT "${WAYLAND_PROTOCOLS_REQUIRED_VERSION}" STREQUAL "${PC_WAYLAND_PROTOCOLS_VERSION}")
            message(WARNING "Incorrect version, please install wayland-${WAYLAND_PROTOCOLS_REQUIRED_VERSION}")
            set(WAYLAND_PROTOCOLS_FOUND_TEXT "Found incorrect version")
            unset(PC_WAYLAND_PROTOCOLS_FOUND)
        endif()
    endif()
else()
    set(WAYLAND_PROTOCOLS_FOUND_TEXT "Not found")
endif()

if (PC_WAYLAND_PROTOCOLS_FOUND)
    find_path(WAYLAND_PROTOCOLS_PATH NAMES
        unstable/pointer-gestures/pointer-gestures-unstable-v1.xml
        unstable/fullscreen-shell/fullscreen-shell-unstable-v1.xml
        unstable/linux-dmabuf/linux-dmabuf-unstable-v1.xml
        unstable/text-input/text-input-unstable-v1.xml
        unstable/input-method/input-method-unstable-v1.xml
        unstable/xdg-shell/xdg-shell-unstable-v5.xml
        unstable/xdg-shell/xdg-shell-unstable-v6.xml
        unstable/relative-pointer/relative-pointer-unstable-v1.xml
        unstable/pointer-constraints/pointer-constraints-unstable-v1.xml
        unstable/tablet/tablet-unstable-v1.xml
        unstable/tablet/tablet-unstable-v2.xml
        unstable/xdg-foreign/xdg-foreign-unstable-v1.xml
        unstable/idle-inhibit/idle-inhibit-unstable-v1.xml
        PATHS ${PC_WAYLAND_PROTOCOLS_PREFIX}/share/wayland-protocols)
    if (NOT "${WAYLAND_PROTOCOLS_PATH}" STREQUAL "")
        set(WAYLAND_PROTOCOLS_FOUND_TEXT "Found")
    else()
        set(WAYLAND_PROTOCOLS_FOUND_TEXT "Not found")
        unset(WAYLAND_PROTOCOLS_PATH)
    endif()
else()
    unset(WAYLAND_PROTOCOLS_PATH)
endif()

message(STATUS "wayland-protocols: ${WAYLAND_PROTOCOLS_FOUND_TEXT}")
message(STATUS "  version        : ${PC_WAYLAND_PROTOCOLS_VERSION}")
message(STATUS "  prefix         : ${PC_WAYLAND_PROTOCOLS_PREFIX}")
message(STATUS "  path           : ${WAYLAND_PROTOCOLS_PATH}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WAYLAND_PROTOCOLS
    REQUIRED_VARS WAYLAND_PROTOCOLS_PATH)

if (NOT WAYLAND_PROTOCOLS_FOUND)
    message(WARNING "Could not find wayland-protocols, please install: sudo apt install bwayland-protocols")
endif()

mark_as_advanced(
    WAYLAND_PROTOCOLS_PATH)
