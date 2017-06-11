# - Try to find xcb-dri2 library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBXCB_DRI2_FOUND - System has LibXcb
#  LIBXCB_DRI2_INCLUDE_DIRS - The LibXcb include directories
#  LIBXCB_DRI2_LIBRARIES - The libraries needed to use LibXcb
#  LIBXCB_DRI2_DEFINITIONS - Compiler switches required for using LibXcb

find_package(PkgConfig)
pkg_check_modules(PC_LIBXCB_DRI2 QUIET xcb-dri2)

if(PC_LIBXCB_DRI2_FOUND)
    if(LIBXCB_DRI2_REQUIRED_VERSION)
        if (NOT "${LIBXCB_DRI2_REQUIRED_VERSION}" STREQUAL "${PC_LIBXCB_DRI2_VERSION}")
            message(WARNING "Incorrect version, please install libxcb-dri2-${LIBXCB_DRI2_REQUIRED_VERSION}")
            set(LIBXCB_DRI2_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBXCB_DRI2_FOUND)
        endif()
    endif()
else()
    set(LIBXCB_DRI2_FOUND_TEXT "Not found")
endif()

if(PC_LIBXCB_DRI2_FOUND)
    find_path(LIBXCB_DRI2_INCLUDE_DIRS NAMES xcb/dri2.h
        HINTS ${PC_LIBXCB_DRI2_INCLUDE_DIRS})

    find_library(LIBXCB_DRI2_LIBRARY NAMES LIBXCB_DRI2 xcb-dri2
        HINTS ${PC_LIBXCB_DRI2_LIBRARY} ${PC_LIBXCB_DRI2_LIBRARY_DIRS})

    if("${LIBXCB_DRI2_INCLUDE_DIRS}" STREQUAL "" OR "${LIBXCB_DRI2_LIBRARY}" STREQUAL "")
        set(LIBXCB_DRI2_FOUND_TEXT "Not found")
    else()
        set(LIBXCB_DRI2_FOUND_TEXT "Found")
    endif()
else()
    set(LIBXCB_DRI2_FOUND_TEXT "Not found")
endif()

message(STATUS "libxcb-dri2  : ${LIBXCB_DRI2_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBXCB_DRI2_VERSION}")
message(STATUS "  cflags       : ${PC_LIBXCB_DRI2_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBXCB_DRI2_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBXCB_DRI2_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBXCB_DRI2_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBXCB_DRI2_LIBRARIES}")

set(LIBXCB_DRI2_DEFINITIONS ${PC_LIBXCB_DRI2_CFLAGS_OTHER})
set(LIBXCB_DRI2_INCLUDE_DIR ${LIBXCB_DRI2_INCLUDE_DIRS})
set(LIBXCB_DRI2_LIBRARIES ${LIBXCB_DRI2_LIBRARY})
set(LIBXCB_DRI2_LIBRARY_DIRS ${PC_LIBXCB_DRI2_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBXCB_DRI2 DEFAULT_MSG
    LIBXCB_DRI2_LIBRARIES LIBXCB_DRI2_INCLUDE_DIRS)

if(LIBXCB_DRI2_FOUND)
else()
    message(WARNING "Could not find xcb-dri2, please install: sudo apt-get install libxcb-dri20-dev")
endif()

mark_as_advanced(LIBXCB_DRI2_DEFINITIONS LIBXCB_DRI2_INCLUDE_DIRS LIBXCB_DRI2_LIBRARIES)
