# - Try to find xcb-glx library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBXCB_GLX_FOUND - System has LibXcb
#  LIBXCB_GLX_INCLUDE_DIRS - The LibXcb include directories
#  LIBXCB_GLX_LIBRARIES - The libraries needed to use LibXcb
#  LIBXCB_GLX_DEFINITIONS - Compiler switches required for using LibXcb

find_package(PkgConfig)
pkg_check_modules(PC_LIBXCB_GLX QUIET xcb-glx)

if(PC_LIBXCB_GLX_FOUND)
    if(LIBXCB_GLX_REQUIRED_VERSION)
        if (NOT "${LIBXCB_GLX_REQUIRED_VERSION}" STREQUAL "${PC_LIBXCB_GLX_VERSION}")
            message(WARNING "Incorrect version, please install libxcb-glx-${LIBXCB_GLX_REQUIRED_VERSION}")
            set(LIBXCB_GLX_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBXCB_GLX_FOUND)
        endif()
    endif()
else()
    set(LIBXCB_GLX_FOUND_TEXT "Not found")
endif()

if(PC_LIBXCB_GLX_FOUND)
    find_path(LIBXCB_GLX_INCLUDE_DIRS NAMES xcb/glx.h
        HINTS ${PC_LIBXCB_GLX_INCLUDE_DIRS})

    find_library(LIBXCB_GLX_LIBRARY NAMES LIBXCB_GLX xcb-glx
        HINTS ${PC_LIBXCB_GLX_LIBRARY} ${PC_LIBXCB_GLX_LIBRARY_DIRS})

    if("${LIBXCB_GLX_INCLUDE_DIRS}" STREQUAL "" OR "${LIBXCB_GLX_LIBRARY}" STREQUAL "")
        set(LIBXCB_GLX_FOUND_TEXT "Not found")
    else()
        set(LIBXCB_GLX_FOUND_TEXT "Found")
    endif()
else()
    set(LIBXCB_GLX_FOUND_TEXT "Not found")
endif()

message(STATUS "libxcb-glx  : ${LIBXCB_GLX_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBXCB_GLX_VERSION}")
message(STATUS "  cflags       : ${PC_LIBXCB_GLX_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBXCB_GLX_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBXCB_GLX_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBXCB_GLX_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBXCB_GLX_LIBRARIES}")

set(LIBXCB_GLX_DEFINITIONS ${PC_LIBXCB_GLX_CFLAGS_OTHER})
set(LIBXCB_GLX_INCLUDE_DIR ${LIBXCB_GLX_INCLUDE_DIRS})
set(LIBXCB_GLX_LIBRARIES ${LIBXCB_GLX_LIBRARY})
set(LIBXCB_GLX_LIBRARY_DIRS ${PC_LIBXCB_GLX_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBXCB_GLX DEFAULT_MSG
    LIBXCB_GLX_LIBRARIES LIBXCB_GLX_INCLUDE_DIRS)

if(LIBXCB_GLX_FOUND)
else()
    message(WARNING "Could not find xcb-glx, please install: sudo apt-get install libxcb-glx0-dev")
endif()

mark_as_advanced(LIBXCB_GLX_DEFINITIONS LIBXCB_GLX_INCLUDE_DIRS LIBXCB_GLX_LIBRARIES)
