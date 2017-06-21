# - Try to find libffi
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBFFI_FOUND - System has LibFFI
#  LIBFFI_INCLUDE_DIRS - The LibFFI include directories
#  LIBFFI_LIBRARIES - The libraries needed to use LibFFI
#  LIBFFI_DEFINITIONS - Compiler switches required for using LibFFI

find_package(PkgConfig)
pkg_check_modules(PC_LIBFFI QUIET libffi)

if(PC_LIBFFI_FOUND)
    if(LIBFFI_REQUIRED_VERSION)
        if (NOT "${LIBFFI_REQUIRED_VERSION}" STREQUAL "${PC_LIBFFI_VERSION}")
            message(WARNING "Incorrect version, please install libffi-${LIBFFI_REQUIRED_VERSION}")
            set(LIBFFI_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBFFI_FOUND)
        endif()
    endif()
else()
    set(LIBFFI_FOUND_TEXT "Not found")
endif()

if(PC_LIBFFI_FOUND)
    find_path(LIBFFI_INCLUDE_DIRS ffi.h
        HINTS ${PC_LIBFFI_INCLUDEDIR} ${PC_LIBFFI_INCLUDE_DIRS})

    find_library(LIBFFI_LIBRARY NAMES ffi
        HINTS ${PC_LIBFFI_LIBDIR} ${PC_LIBFFI_LIBRARY_DIRS} )

    if("${LIBFFI_INCLUDE_DIRS}" STREQUAL "" OR "${LIBFFI_LIBRARY}" STREQUAL "")
        set(LIBFFI_FOUND_TEXT "Not found")
    else()
        set(LIBFFI_FOUND_TEXT "Found")
    endif()
else()
    set(LIBFFI_FOUND_TEXT "Not found")
endif()

message(STATUS "libffi         : ${LIBFFI_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBFFI_VERSION}")
message(STATUS "  cflags       : ${PC_LIBFFI_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBFFI_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBFFI_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBFFI_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBFFI_LIBRARIES}")

set(LIBFFI_DEFINITIONS ${PC_LIBFFI_CFLAGS_OTHER})
set(LIBFFI_LIBRARIES ${LIBFFI_LIBRARY} )
set(LIBFFI_INCLUDE_DIR ${LIBFFI_INCLUDE_DIRS} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibFFI
    REQUIRED_VARS LIBFFI_LIBRARIES LIBFFI_INCLUDE_DIRS)

if (LIBFFI_FOUND)
else()
    message(WARNING "Could not find libffi, please install: sudo apt-get install libffi-dev")
endif()

mark_as_advanced(LIBFFI_DEFINITIONS LIBFFI_INCLUDE_DIRS LIBFFI_LIBRARIES)
