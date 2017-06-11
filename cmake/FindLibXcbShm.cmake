# - Try to find xcb-shm library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBXCB_SHM_FOUND - System has LibXcb
#  LIBXCB_SHM_INCLUDE_DIRS - The LibXcb include directories
#  LIBXCB_SHM_LIBRARIES - The libraries needed to use LibXcb
#  LIBXCB_SHM_DEFINITIONS - Compiler switches required for using LibXcb

find_package(PkgConfig)
pkg_check_modules(PC_LIBXCB_SHM QUIET xcb-shm)

if(PC_LIBXCB_SHM_FOUND)
    if(LIBXCB_SHM_REQUIRED_VERSION)
        if (NOT "${LIBXCB_SHM_REQUIRED_VERSION}" STREQUAL "${PC_LIBXCB_SHM_VERSION}")
            message(WARNING "Incorrect version, please install libxcb-shm-${LIBXCB_SHM_REQUIRED_VERSION}")
            set(LIBXCB_SHM_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBXCB_SHM_FOUND)
        endif()
    endif()
else()
    set(LIBXCB_SHM_FOUND_TEXT "Not found")
endif()

if(PC_LIBXCB_SHM_FOUND)
    find_path(LIBXCB_SHM_INCLUDE_DIRS NAMES xcb/shm.h
        HINTS ${PC_LIBXCB_SHM_INCLUDE_DIRS})

    find_library(LIBXCB_SHM_LIBRARY NAMES LIBXCB_SHM xcb-shm
        HINTS ${PC_LIBXCB_SHM_LIBRARY} ${PC_LIBXCB_SHM_LIBRARY_DIRS})

    if("${LIBXCB_SHM_INCLUDE_DIRS}" STREQUAL "" OR "${LIBXCB_SHM_LIBRARY}" STREQUAL "")
        set(LIBXCB_SHM_FOUND_TEXT "Not found")
    else()
        set(LIBXCB_SHM_FOUND_TEXT "Found")
    endif()
else()
    set(LIBXCB_SHM_FOUND_TEXT "Not found")
endif()

message(STATUS "libxcb-shm  : ${LIBXCB_SHM_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBXCB_SHM_VERSION}")
message(STATUS "  cflags       : ${PC_LIBXCB_SHM_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBXCB_SHM_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBXCB_SHM_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBXCB_SHM_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBXCB_SHM_LIBRARIES}")

set(LIBXCB_SHM_DEFINITIONS ${PC_LIBXCB_SHM_CFLAGS_OTHER})
set(LIBXCB_SHM_INCLUDE_DIR ${LIBXCB_SHM_INCLUDE_DIRS})
set(LIBXCB_SHM_LIBRARIES ${LIBXCB_SHM_LIBRARY})
set(LIBXCB_SHM_LIBRARY_DIRS ${PC_LIBXCB_SHM_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBXCB_SHM DEFAULT_MSG
    LIBXCB_SHM_LIBRARIES LIBXCB_SHM_INCLUDE_DIRS)

if(LIBXCB_SHM_FOUND)
else()
    message(WARNING "Could not find xcb-shm, please install: sudo apt-get install libxcb-shm0-dev")
endif()

mark_as_advanced(LIBXCB_SHM_DEFINITIONS LIBXCB_SHM_INCLUDE_DIRS LIBXCB_SHM_LIBRARIES)
