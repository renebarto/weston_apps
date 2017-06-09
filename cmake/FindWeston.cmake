# - Try to find weston
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  WESTON_FOUND - System has Weston
#  WESTON_INCLUDE_DIR - The Weston include directories
#  WESTON_LIBRARIES - The libraries needed to use Weston
#  WESTON_DEFINITIONS - Compiler switches required for using Weston

find_package(PkgConfig)
pkg_check_modules(PC_WESTON QUIET weston)

if(PC_WESTON_FOUND)
    if (WESTON_REQUIRED_VERSION)
        if (NOT "${WESTON_REQUIRED_VERSION}" STREQUAL "${PC_WESTON_VERSION}")
            message(WARNING "Incorrect version, please install weston-${WESTON_REQUIRED_VERSION}")
            unset(WESTON_FOUND)
            set(WESTON_FOUND_TEXT "Incorrect version")
        else()
            set(WESTON_FOUND TRUE)
            set(WESTON_FOUND_TEXT "Found")
        endif()
    else()
        set(WESTON_FOUND TRUE)
        set(WESTON_FOUND_TEXT "Found")
    endif()
else()
    message(WARNING "Could not find weston, please install: sudo apt install weston")
    set(WESTON_FOUND_TEXT "Not found")
    unset(WESTON_FOUND)
endif()

message(STATUS "weston         : ${WESTON_FOUND_TEXT}")
message(STATUS "  version      : ${PC_WESTON_VERSION}")
message(STATUS "  cflags       : ${PC_WESTON_CFLAGS}")
message(STATUS "  cflags other : ${PC_WESTON_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_WESTON_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_WESTON_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_WESTON_LIBRARIES}")

find_path(WESTON_INCLUDE_DIRS ffi.h
        HINTS ${PC_WESTON_INCLUDEDIR} ${PC_WESTON_INCLUDE_DIRS})

find_library(WESTON_LIBRARY NAMES libweston-1 libweston-desktop-1
        HINTS ${PC_WESTON_LIBDIR} ${PC_WESTON_LIBRARY_DIRS} )

find_program(WESTON_EXECUTABLE NAMES weston
    HINTS ${PC_WESTON_LIBDIR} ${PC_WESTON_PREFIX}/bin )

set(WESTON_DEFINITIONS ${PC_WESTON_CFLAGS_OTHER})
set(WESTON_LIBRARIES ${WESTON_LIBRARY} )
set(WESTON_INCLUDE_DIR ${WESTON_INCLUDE_DIRS} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WESTON DEFAULT_MSG
    WESTON_EXECUTABLE WESTON_INCLUDE_DIR)

if (WESTON_FOUND)
else()
    message(WARNING "Could not find weston, please install: sudo apt install weston")
endif()

mark_as_advanced(WESTON_INCLUDE_DIR WESTON_LIBRARIES WESTON_EXECUTABLE WESTON_DEFINITIONS)
