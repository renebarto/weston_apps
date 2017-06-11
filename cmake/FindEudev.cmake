# - Try to find EUDEV library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  EUDEV_FOUND - System has Eudev
#  EUDEV_INCLUDE_DIR - The Eudev include directories
#  EUDEV_LIBRARIES - The libraries needed to use Eudev
#  EUDEV_DEFINITIONS - Compiler switches required for using Eudev

find_package(PkgConfig)
pkg_check_modules(PC_EUDEV QUIET libudev)

if(PC_EUDEV_FOUND)
    if(EUDEV_REQUIRED_VERSION)
        if (NOT "${EUDEV_REQUIRED_VERSION}" STREQUAL "${PC_EUDEV_VERSION}")
            message(WARNING "Incorrect version, please install libudev-${EUDEV_REQUIRED_VERSION}")
            set(EUDEV_FOUND_TEXT "Found incorrect version")
            unset(PC_EUDEV_FOUND)
        endif()
    endif()
else()
    set(EUDEV_FOUND_TEXT "Not found")
endif()

if(PC_EUDEV_FOUND)
    find_path(EUDEV_INCLUDE_DIRS NAMES libudev.h
        HINTS ${PC_EUDEV_INCLUDE_DIRS})

    find_library(EUDEV_LIBRARY NAMES udev
        HINTS ${PC_EUDEV_LIBRARY} ${PC_EUDEV_LIBRARY_DIRS})

    find_program(EUDEV_EXECUTABLES udevadm udevd
        HINTS ${CMAKE_INSTALL_PREFIX}/bin)

    if("${EUDEV_INCLUDE_DIRS}" STREQUAL "" OR "${EUDEV_LIBRARY}" STREQUAL "")
        set(EUDEV_FOUND_TEXT "Not found")
    else()
        set(EUDEV_FOUND_TEXT "Found")
    endif()
else()
    set(EUDEV_FOUND_TEXT "Not found")
endif()

message(STATUS "eudev          : ${EUDEV_FOUND_TEXT}")
message(STATUS "  version      : ${PC_EUDEV_VERSION}")
message(STATUS "  cflags       : ${PC_EUDEV_CFLAGS}")
message(STATUS "  cflags other : ${PC_EUDEV_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_EUDEV_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_EUDEV_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_EUDEV_LIBRARIES}")

set(EUDEV_DEFINITIONS ${PC_EUDEV_CFLAGS_OTHER})
set(EUDEV_INCLUDE_DIR ${EUDEV_INCLUDE_DIRS})
set(EUDEV_LIBRARIES ${EUDEV_LIBRARY})
set(EUDEV_LIBRARY_DIRS ${PC_EUDEV_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EUDEV DEFAULT_MSG
    EUDEV_LIBRARIES EUDEV_INCLUDE_DIRS EUDEV_EXECUTABLES)

if(EUDEV_FOUND)
else()
    message(WARNING "Could not find libudev, please install: sudo apt-get install libudev-dev")
endif()

mark_as_advanced(EUDEV_DEFINITIONS EUDEV_INCLUDE_DIRS EUDEV_LIBRARIES)
