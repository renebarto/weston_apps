# - Try to find evdev library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBEVDEV_FOUND - System has libevdev
#  LIBEVDEV_INCLUDE_DIRS - The libevdev include directories
#  LIBEVDEV_LIBRARIES - The libraries needed to use libevdev

find_package(PkgConfig)
pkg_check_modules(PC_LIBEVDEV QUIET libevdev)

if(PC_LIBEVDEV_FOUND)
    if(LIBEVDEV_REQUIRED_VERSION)
        if (NOT "${LIBEVDEV_REQUIRED_VERSION}" STREQUAL "${PC_LIBEVDEV_VERSION}")
            message(WARNING "Incorrect version, please install libevdev-${LIBEVDEV_REQUIRED_VERSION}")
            set(LIBEVDEV_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBEVDEV_FOUND)
        endif()
    endif()
else()
    set(LIBEVDEV_FOUND_TEXT "Not found")
endif()

if(PC_LIBEVDEV_FOUND)
    find_path(LIBEVDEV_INCLUDE_DIRS NAMES libevdev/libevdev.h
        HINTS ${PC_LIBEVDEV_INCLUDE_DIRS})

    find_library(LIBEVDEV_LIBRARY NAMES evdev libevdev
        HINTS ${PC_LIBEVDEV_LIBRARY} ${PC_LIBEVDEV_LIBRARY_DIRS})

    if("${LIBEVDEV_INCLUDE_DIRS}" STREQUAL "" OR "${LIBEVDEV_LIBRARY}" STREQUAL "")
        set(LIBEVDEV_FOUND_TEXT "Not found")
    else()
        set(LIBEVDEV_FOUND_TEXT "Found")
    endif()
else()
    set(LIBEVDEV_FOUND_TEXT "Not found")
endif()

message(STATUS "evdev          : ${LIBEVDEV_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBEVDEV_VERSION}")
message(STATUS "  cflags       : ${PC_LIBEVDEV_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBEVDEV_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBEVDEV_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBEVDEV_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBEVDEV_LIBRARIES}")

set(LIBEVDEV_DEFINITIONS ${PC_LIBEVDEV_CFLAGS_OTHER})
set(LIBEVDEV_INCLUDE_DIR ${LIBEVDEV_INCLUDE_DIRS})
set(LIBEVDEV_LIBRARIES ${LIBEVDEV_LIBRARY})
set(LIBEVDEV_LIBRARY_DIRS ${PC_LIBEVDEV_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBEVDEV DEFAULT_MSG
    LIBEVDEV_LIBRARIES LIBEVDEV_INCLUDE_DIRS)

if(LIBEVDEV_FOUND)
else()
    message(WARNING "Could not find libevdev, please install: sudo apt-get install libevdev-dev")
endif()

mark_as_advanced(LIBEVDEV_DEFINITIONS LIBEVDEV_INCLUDE_DIRS LIBEVDEV_LIBRARIES)
