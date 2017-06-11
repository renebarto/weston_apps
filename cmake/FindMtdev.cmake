# - Try to find mtdev library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  MTDEV_FOUND - System has Mtdev
#  MTDEV_INCLUDE_DIR - The Mtdev include directories
#  MTDEV_LIBRARIES - The libraries needed to use Mtdev
#  MTDEV_DEFINITIONS - Compiler switches required for using Mtdev

find_package(PkgConfig)
pkg_check_modules(PC_MTDEV QUIET mtdev)

if(PC_MTDEV_FOUND)
    if(MTDEV_REQUIRED_VERSION)
        if (NOT "${MTDEV_REQUIRED_VERSION}" STREQUAL "${PC_MTDEV_VERSION}")
            message(WARNING "Incorrect version, please install mtdev-${MTDEV_REQUIRED_VERSION}")
            set(MTDEV_FOUND_TEXT "Found incorrect version")
            unset(PC_MTDEV_FOUND)
        endif()
    endif()
else()
    set(MTDEV_FOUND_TEXT "Not found")
endif()

if(PC_MTDEV_FOUND)
    find_path(MTDEV_INCLUDE_DIRS NAMES mtdev.h mtdev-mapping.h mtdev-plumbing.h
        HINTS ${PC_MTDEV_INCLUDE_DIRS})

    find_library(MTDEV_LIBRARY NAMES mtdev
        HINTS ${PC_MTDEV_LIBRARY} ${PC_MTDEV_LIBRARY_DIRS})

    if("${MTDEV_INCLUDE_DIRS}" STREQUAL "" OR "${MTDEV_LIBRARY}" STREQUAL "")
        set(MTDEV_FOUND_TEXT "Not found")
    else()
        set(MTDEV_FOUND_TEXT "Found")
    endif()
else()
    set(MTDEV_FOUND_TEXT "Not found")
endif()

message(STATUS "mtdev          : ${MTDEV_FOUND_TEXT}")
message(STATUS "  version      : ${PC_MTDEV_VERSION}")
message(STATUS "  cflags       : ${PC_MTDEV_CFLAGS}")
message(STATUS "  cflags other : ${PC_MTDEV_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_MTDEV_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_MTDEV_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_MTDEV_LIBRARIES}")

set(MTDEV_DEFINITIONS ${PC_MTDEV_CFLAGS_OTHER})
set(MTDEV_INCLUDE_DIR ${MTDEV_INCLUDE_DIRS})
set(MTDEV_LIBRARIES ${MTDEV_LIBRARY})
set(MTDEV_LIBRARY_DIRS ${PC_MTDEV_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MTDEV DEFAULT_MSG
    MTDEV_LIBRARIES MTDEV_INCLUDE_DIRS)

if(MTDEV_FOUND)
else()
    message(WARNING "Could not find mtdev, please install: sudo apt-get install mtdev-dev")
endif()

mark_as_advanced(MTDEV_DEFINITIONS MTDEV_INCLUDE_DIRS MTDEV_LIBRARIES)
