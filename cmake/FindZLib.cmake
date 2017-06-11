# - Try to find ZLIB library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  ZLIB_FOUND - System has LibFFI
#  ZLIB_INCLUDE_DIRS - The LibFFI include directories
#  ZLIB_LIBRARIES - The libraries needed to use LibFFI
#  ZLIB_DEFINITIONS - Compiler switches required for using LibFFI

find_package(PkgConfig)
pkg_check_modules(PC_ZLIB QUIET zlib)

if(PC_ZLIB_FOUND)
    if(ZLIB_REQUIRED_VERSION)
        if (NOT "${ZLIB_REQUIRED_VERSION}" STREQUAL "${PC_ZLIB_VERSION}")
            message(WARNING "Incorrect version, please install libxkbcommon-${ZLIB_REQUIRED_VERSION}")
            set(ZLIB_FOUND_TEXT "Found incorrect version")
            unset(PC_ZLIB_FOUND)
        endif()
    endif()
else()
    set(ZLIB_FOUND_TEXT "Not found")
endif()

if(PC_ZLIB_FOUND)
    find_path(ZLIB_INCLUDE_DIRS NAMES zlib.h
        HINTS ${PC_ZLIB_INCLUDE_DIRS})

    find_library(ZLIB_LIBRARY NAMES z
        HINTS ${PC_ZLIB_LIBRARY} ${PC_ZLIB_LIBRARY_DIRS})

    if("${ZLIB_INCLUDE_DIRS}" STREQUAL "" OR "${ZLIB_LIBRARY}" STREQUAL "")
        set(ZLIB_FOUND_TEXT "Not found")
    else()
        set(ZLIB_FOUND_TEXT "Found")
    endif()
else()
    set(ZLIB_FOUND_TEXT "Not found")
endif()

message(STATUS "zlib           : ${ZLIB_FOUND_TEXT}")
message(STATUS "  version      : ${PC_ZLIB_VERSION}")
message(STATUS "  cflags       : ${PC_ZLIB_CFLAGS}")
message(STATUS "  cflags other : ${PC_ZLIB_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_ZLIB_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_ZLIB_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_ZLIB_LIBRARIES}")

set(ZLIB_DEFINITIONS ${PC_ZLIB_CFLAGS_OTHER})
set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIRS})
set(ZLIB_LIBRARIES ${ZLIB_LIBRARY})
set(ZLIB_LIBRARY_DIRS ${PC_ZLIB_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZLIB DEFAULT_MSG
    ZLIB_LIBRARIES ZLIB_INCLUDE_DIRS)

if(ZLIB_FOUND)
else()
    message(WARNING "Could not find egl, please install: sudo apt-get install libegl1-mesa-dev")
endif()

mark_as_advanced(ZLIB_DEFINITIONS ZLIB_INCLUDE_DIRS ZLIB_LIBRARIES)

