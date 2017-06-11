# - Try to find xcb library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBXCB_FOUND - System has LibXcb
#  LIBXCB_INCLUDE_DIR - The LibXcb include directories
#  LIBXCB_LIBRARIES - The libraries needed to use LibXcb
#  LIBXCB_DEFINITIONS - Compiler switches required for using LibXcb

find_package(PkgConfig)
pkg_check_modules(PC_LIBXCB QUIET xcb)

if(PC_LIBXCB_FOUND)
if(LIBXCB_REQUIRED_VERSION)
if (NOT "${LIBXCB_REQUIRED_VERSION}" STREQUAL "${PC_LIBXCB_VERSION}")
message(WARNING "Incorrect version, please install libxcb-${LIBXCB_REQUIRED_VERSION}")
set(LIBXCB_FOUND_TEXT "Found incorrect version")
unset(PC_LIBXCB_FOUND)
endif()
endif()
else()
set(LIBXCB_FOUND_TEXT "Not found")
endif()

if(PC_LIBXCB_FOUND)
find_path(LIBXCB_INCLUDE_DIRS NAMES xcb/xcb.h
HINTS ${PC_LIBXCB_INCLUDE_DIRS})

find_library(LIBXCB_LIBRARY NAMES xcb
HINTS ${PC_LIBXCB_LIBRARY} ${PC_LIBXCB_LIBRARY_DIRS})

if("${LIBXCB_INCLUDE_DIRS}" STREQUAL "" OR "${LIBXCB_LIBRARY}" STREQUAL "")
set(LIBXCB_FOUND_TEXT "Not found")
else()
set(LIBXCB_FOUND_TEXT "Found")
endif()
else()
set(LIBXCB_FOUND_TEXT "Not found")
endif()

message(STATUS "libxcb         : ${LIBXCB_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBXCB_VERSION}")
message(STATUS "  cflags       : ${PC_LIBXCB_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBXCB_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBXCB_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBXCB_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBXCB_LIBRARIES}")

set(LIBXCB_DEFINITIONS ${PC_LIBXCB_CFLAGS_OTHER})
set(LIBXCB_INCLUDE_DIR ${LIBXCB_INCLUDE_DIRS})
set(LIBXCB_LIBRARIES ${LIBXCB_LIBRARY})
set(LIBXCB_LIBRARY_DIRS ${PC_LIBXCB_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBXCB DEFAULT_MSG
    LIBXCB_LIBRARIES LIBXCB_INCLUDE_DIRS)

if(LIBXCB_FOUND)
else()
message(WARNING "Could not find libxcb, please install: sudo apt-get install libxcb1-dev")
endif()

mark_as_advanced(LIBXCB_DEFINITIONS LIBXCB_INCLUDE_DIRS LIBXCB_LIBRARIES)
