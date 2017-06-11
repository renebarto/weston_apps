# - Try to find xcb-xfixes library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBXCB_XFIXES_FOUND - System has LibXcb
#  LIBXCB_XFIXES_INCLUDE_DIRS - The LibXcb include directories
#  LIBXCB_XFIXES_LIBRARIES - The libraries needed to use LibXcb
#  LIBXCB_XFIXES_DEFINITIONS - Compiler switches required for using LibXcb

find_package(PkgConfig)
pkg_check_modules(PC_LIBXCB_XFIXES QUIET xcb-xfixes)

if(PC_LIBXCB_XFIXES_FOUND)
    if(LIBXCB_XFIXES_REQUIRED_VERSION)
        if (NOT "${LIBXCB_XFIXES_REQUIRED_VERSION}" STREQUAL "${PC_LIBXCB_XFIXES_VERSION}")
            message(WARNING "Incorrect version, please install libxcb-xfixes-${LIBXCB_XFIXES_REQUIRED_VERSION}")
            set(LIBXCB_XFIXES_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBXCB_XFIXES_FOUND)
        endif()
    endif()
else()
    set(LIBXCB_XFIXES_FOUND_TEXT "Not found")
endif()

if(PC_LIBXCB_XFIXES_FOUND)
    find_path(LIBXCB_XFIXES_INCLUDE_DIRS NAMES xcb/xfixes.h
        HINTS ${PC_LIBXCB_XFIXES_INCLUDE_DIRS})

    find_library(LIBXCB_XFIXES_LIBRARY NAMES LIBXCB_XFIXES xcb-xfixes
        HINTS ${PC_LIBXCB_XFIXES_LIBRARY} ${PC_LIBXCB_XFIXES_LIBRARY_DIRS})

    if("${LIBXCB_XFIXES_INCLUDE_DIRS}" STREQUAL "" OR "${LIBXCB_XFIXES_LIBRARY}" STREQUAL "")
        set(LIBXCB_XFIXES_FOUND_TEXT "Not found")
    else()
        set(LIBXCB_XFIXES_FOUND_TEXT "Found")
    endif()
else()
    set(LIBXCB_XFIXES_FOUND_TEXT "Not found")
endif()

message(STATUS "libxcb-xfixes  : ${LIBXCB_XFIXES_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBXCB_XFIXES_VERSION}")
message(STATUS "  cflags       : ${PC_LIBXCB_XFIXES_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBXCB_XFIXES_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBXCB_XFIXES_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBXCB_XFIXES_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBXCB_XFIXES_LIBRARIES}")

set(LIBXCB_XFIXES_DEFINITIONS ${PC_LIBXCB_XFIXES_CFLAGS_OTHER})
set(LIBXCB_XFIXES_INCLUDE_DIR ${LIBXCB_XFIXES_INCLUDE_DIRS})
set(LIBXCB_XFIXES_LIBRARIES ${LIBXCB_XFIXES_LIBRARY})
set(LIBXCB_XFIXES_LIBRARY_DIRS ${PC_LIBXCB_XFIXES_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBXCB_XFIXES DEFAULT_MSG
    LIBXCB_XFIXES_LIBRARIES LIBXCB_XFIXES_INCLUDE_DIRS)

if(LIBXCB_XFIXES_FOUND)
else()
    message(WARNING "Could not find xcb-xfixes, please install: sudo apt-get install libxcb-xfixes0-dev")
endif()

mark_as_advanced(LIBXCB_XFIXES_DEFINITIONS LIBXCB_XFIXES_INCLUDE_DIRS LIBXCB_XFIXES_LIBRARIES)
