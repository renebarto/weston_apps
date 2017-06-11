# - Try to find wayland-scanner
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
# WAYLAND_SCANNER_FOUND
# WAYLAND_SCANNER_PATH
#

find_package(PkgConfig)

pkg_check_modules(PC_WAYLAND_SCANNER QUIET wayland-scanner)

if(PC_WAYLAND_SCANNER_FOUND)
    if (WAYLAND_SCANNER_REQUIRED_VERSION)
        if (NOT "${WAYLAND_SCANNER_REQUIRED_VERSION}" STREQUAL "${PC_WAYLAND_SCANNER_VERSION}")
            message(WARNING "Incorrect version, please install wayland-${WAYLAND_SCANNER_REQUIRED_VERSION}")
            set(WAYLAND_SCANNER_FOUND_TEXT "Found incorrect version")
            unset(PC_WAYLAND_SCANNER_FOUND)
        endif()
    endif()
else()
    set(WAYLAND_SCANNER_FOUND_TEXT "Not found")
endif()

if(PC_WAYLAND_SCANNER_FOUND)
    find_program(WAYLAND_SCANNER_PATH wayland-scanner ${CMAKE_INSTALL_PREFIX}/bin)
    if (NOT "${WAYLAND_SCANNER_PATH}" STREQUAL "")
        set(WAYLAND_SCANNER_FOUND_TEXT "Found")
    else()
        set(WAYLAND_SCANNER_FOUND_TEXT "Not found")
        unset(WAYLAND_SCANNER_PATH)
    endif()
endif()

message(STATUS "wayland-scanner: ${WAYLAND_SCANNER_FOUND_TEXT}")
message(STATUS "  version      : ${PC_WAYLAND_SCANNER_VERSION}")
message(STATUS "  prefix       : ${PC_WAYLAND_SCANNER_PREFIX}")
message(STATUS "  path         : ${WAYLAND_SCANNER_PATH}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WAYLAND_SCANNER
    REQUIRED_VARS WAYLAND_SCANNER_PATH)

if (NOT WAYLAND_SCANNER_FOUND)
    message(WARNING "Could not find wayland-scanner, please install: sudo apt install libwayland-dev")
endif()

mark_as_advanced(
    WAYLAND_SCANNER_PATH)
