# - Try to find xkbcommon library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#   LIBXKBCOMMON_FOUND - System has XKBCommon
#   LIBXKBCOMMON_INCLUDE_DIRS - The XKBCommon include directories
#   LIBXKBCOMMON_LIBRARIES - The libraries needed to use XKBCommon
#   LIBXKBCOMMON_DEFINITIONS - Compiler switches required for using XKBCommon

find_package(PkgConfig)
pkg_check_modules(PC_LIBXKBCOMMON QUIET xkbcommon)

if(PC_LIBXKBCOMMON_FOUND)
    if(LIBXKBCOMMON_REQUIRED_VERSION)
        if (NOT "${LIBXKBCOMMON_REQUIRED_VERSION}" STREQUAL "${PC_LIBXKBCOMMON_VERSION}")
            message(WARNING "Incorrect version, please install libxkbcommon-${LIBXKBCOMMON_REQUIRED_VERSION}")
            set(LIBXKBCOMMON_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBXKBCOMMON_FOUND)
        endif()
    endif()
else()
    set(LIBXKBCOMMON_FOUND_TEXT "Not found")
endif()

if(PC_LIBXKBCOMMON_FOUND)
    find_path(LIBXKBCOMMON_INCLUDE_DIRS NAMES xkbcommon/xkbcommon.h
        HINTS ${PC_LIBXKBCOMMON_INCLUDE_DIRS})

    find_library(LIBXKBCOMMON_LIBRARY NAMES xkbcommon
        HINTS ${PC_LIBXKBCOMMON_LIBRARY} ${PC_LIBXKBCOMMON_LIBRARY_DIRS})

    if("${LIBXKBCOMMON_INCLUDE_DIRS}" STREQUAL "" OR "${LIBXKBCOMMON_LIBRARY}" STREQUAL "")
        set(LIBXKBCOMMON_FOUND_TEXT "Not found")
    else()
        set(LIBXKBCOMMON_FOUND_TEXT "Found")
    endif()
else()
    set(LIBXKBCOMMON_FOUND_TEXT "Not found")
endif()

message(STATUS "libxkbcommon   : ${LIBXKBCOMMON_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBXKBCOMMON_VERSION}")
message(STATUS "  cflags       : ${PC_LIBXKBCOMMON_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBXKBCOMMON_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBXKBCOMMON_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBXKBCOMMON_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBXKBCOMMON_LIBRARIES}")

set(LIBXKBCOMMON_DEFINITIONS ${PC_LIBXKBCOMMON_CFLAGS_OTHER})
set(LIBXKBCOMMON_INCLUDE_DIR ${LIBXKBCOMMON_INCLUDE_DIRS})
set(LIBXKBCOMMON_LIBRARIES ${LIBXKBCOMMON_LIBRARY})
set(LIBXKBCOMMON_LIBRARY_DIRS ${PC_LIBXKBCOMMON_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBXKBCOMMON DEFAULT_MSG
    LIBXKBCOMMON_LIBRARIES LIBXKBCOMMON_INCLUDE_DIRS    )

if(LIBXKBCOMMON_FOUND)
else()
    message(WARNING "Could not find libxkbcommon, please install: sudo apt-get install libxkbcommon-dev")
endif()

mark_as_advanced(LIBXKBCOMMON_DEFINITIONS LIBXKBCOMMON_LIBRARIES LIBXKBCOMMON_INCLUDE_DIRS)
