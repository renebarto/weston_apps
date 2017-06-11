# - Try to find Xau library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBXAU_FOUND - System has LibXau
#  LIBXAU_INCLUDE_DIR - The LibXau include directories
#  LIBXAU_LIBRARIES - The libraries needed to use LibXau
#  LIBXAU_DEFINITIONS - Compiler switches required for using LibXau

find_package(PkgConfig)
pkg_check_modules(PC_LIBXAU QUIET xau)

if(PC_LIBXAU_FOUND)
    if(LIBXAU_REQUIRED_VERSION)
        if (NOT "${LIBXAU_REQUIRED_VERSION}" STREQUAL "${PC_LIBXAU_VERSION}")
            message(WARNING "Incorrect version, please install libxau-${LIBXAU_REQUIRED_VERSION}")
            set(LIBXAU_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBXAU_FOUND)
        endif()
    endif()
else()
    set(LIBXAU_FOUND_TEXT "Not found")
endif()

if(PC_LIBXAU_FOUND)
    find_path(LIBXAU_INCLUDE_DIRS NAMES X11/Xauth.h
        HINTS ${PC_LIBXAU_INCLUDE_DIRS})

    find_library(LIBXAU_LIBRARY NAMES Xau
        HINTS ${PC_LIBXAU_LIBRARY} ${PC_LIBXAU_LIBRARY_DIRS})

    if("${LIBXAU_INCLUDE_DIRS}" STREQUAL "" OR "${LIBXAU_LIBRARY}" STREQUAL "")
        set(LIBXAU_FOUND_TEXT "Not found")
    else()
        set(LIBXAU_FOUND_TEXT "Found")
    endif()
else()
    set(LIBXAU_FOUND_TEXT "Not found")
endif()

message(STATUS "libxau         : ${LIBXAU_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBXAU_VERSION}")
message(STATUS "  cflags       : ${PC_LIBXAU_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBXAU_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBXAU_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBXAU_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBXAU_LIBRARIES}")

set(LIBXAU_DEFINITIONS ${PC_LIBXAU_CFLAGS_OTHER})
set(LIBXAU_INCLUDE_DIR ${LIBXAU_INCLUDE_DIRS})
set(LIBXAU_LIBRARIES ${LIBXAU_LIBRARY})
set(LIBXAU_LIBRARY_DIRS ${PC_LIBXAU_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBXAU DEFAULT_MSG
    LIBXAU_LIBRARIES LIBXAU_INCLUDE_DIRS)

if(LIBXAU_FOUND)
else()
    message(WARNING "Could not find libxau, please install: sudo apt-get install libxau-dev")
endif()

mark_as_advanced(LIBXAU_DEFINITIONS LIBXAU_INCLUDE_DIRS LIBXAU_LIBRARIES)
