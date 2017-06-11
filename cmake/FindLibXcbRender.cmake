# - Try to find xcb-render library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBXCB_RENDER_FOUND - System has LibXcb
#  LIBXCB_RENDER_INCLUDE_DIRS - The LibXcb include directories
#  LIBXCB_RENDER_LIBRARIES - The libraries needed to use LibXcb
#  LIBXCB_RENDER_DEFINITIONS - Compiler switches required for using LibXcb

find_package(PkgConfig)
pkg_check_modules(PC_LIBXCB_RENDER QUIET xcb-render)

if(PC_LIBXCB_RENDER_FOUND)
    if(LIBXCB_RENDER_REQUIRED_VERSION)
        if (NOT "${LIBXCB_RENDER_REQUIRED_VERSION}" STREQUAL "${PC_LIBXCB_RENDER_VERSION}")
            message(WARNING "Incorrect version, please install libxcb-render-${LIBXCB_RENDER_REQUIRED_VERSION}")
            set(LIBXCB_RENDER_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBXCB_RENDER_FOUND)
        endif()
    endif()
else()
    set(LIBXCB_RENDER_FOUND_TEXT "Not found")
endif()

if(PC_LIBXCB_RENDER_FOUND)
    find_path(LIBXCB_RENDER_INCLUDE_DIRS NAMES xcb/render.h
        HINTS ${PC_LIBXCB_RENDER_INCLUDE_DIRS})

    find_library(LIBXCB_RENDER_LIBRARY NAMES LIBXCB_RENDER xcb-render
        HINTS ${PC_LIBXCB_RENDER_LIBRARY} ${PC_LIBXCB_RENDER_LIBRARY_DIRS})

    if("${LIBXCB_RENDER_INCLUDE_DIRS}" STREQUAL "" OR "${LIBXCB_RENDER_LIBRARY}" STREQUAL "")
        set(LIBXCB_RENDER_FOUND_TEXT "Not found")
    else()
        set(LIBXCB_RENDER_FOUND_TEXT "Found")
    endif()
else()
    set(LIBXCB_RENDER_FOUND_TEXT "Not found")
endif()

message(STATUS "libxcb-render  : ${LIBXCB_RENDER_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBXCB_RENDER_VERSION}")
message(STATUS "  cflags       : ${PC_LIBXCB_RENDER_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBXCB_RENDER_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBXCB_RENDER_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBXCB_RENDER_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBXCB_RENDER_LIBRARIES}")

set(LIBXCB_RENDER_DEFINITIONS ${PC_LIBXCB_RENDER_CFLAGS_OTHER})
set(LIBXCB_RENDER_INCLUDE_DIR ${LIBXCB_RENDER_INCLUDE_DIRS})
set(LIBXCB_RENDER_LIBRARIES ${LIBXCB_RENDER_LIBRARY})
set(LIBXCB_RENDER_LIBRARY_DIRS ${PC_LIBXCB_RENDER_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBXCB_RENDER DEFAULT_MSG
    LIBXCB_RENDER_LIBRARIES LIBXCB_RENDER_INCLUDE_DIRS)

if(LIBXCB_RENDER_FOUND)
else()
    message(WARNING "Could not find xcb-render, please install: sudo apt-get install libxcb-render0-dev")
endif()

mark_as_advanced(LIBXCB_RENDER_DEFINITIONS LIBXCB_RENDER_INCLUDE_DIRS LIBXCB_RENDER_LIBRARIES)
