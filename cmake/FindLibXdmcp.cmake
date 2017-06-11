# - Try to find Xdmcp library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBXDMCP_FOUND - System has LibXdmcp
#  LIBXDMCP_INCLUDE_DIR - The LibXdmcp include directories
#  LIBXDMCP_LIBRARIES - The libraries needed to use LibXdmcp
#  LIBXDMCP_DEFINITIONS - Compiler switches required for using LibXdmcp

find_package(PkgConfig)
pkg_check_modules(PC_LIBXDMCP QUIET xdmcp)

if(PC_LIBXDMCP_FOUND)
    if(LIBXDMCP_REQUIRED_VERSION)
        if (NOT "${LIBXDMCP_REQUIRED_VERSION}" STREQUAL "${PC_LIBXDMCP_VERSION}")
            message(WARNING "Incorrect version, please install libxdmcp-${LIBXDMCP_REQUIRED_VERSION}")
            set(LIBXDMCP_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBXDMCP_FOUND)
        endif()
    endif()
else()
    set(LIBXDMCP_FOUND_TEXT "Not found")
endif()

if(PC_LIBXDMCP_FOUND)
    find_path(LIBXDMCP_INCLUDE_DIRS NAMES X11/Xdmcp.h
        HINTS ${PC_LIBXDMCP_INCLUDE_DIRS})

    find_library(LIBXDMCP_LIBRARY NAMES Xdmcp
        HINTS ${PC_LIBXDMCP_LIBRARY} ${PC_LIBXDMCP_LIBRARY_DIRS})

    if("${LIBXDMCP_INCLUDE_DIRS}" STREQUAL "" OR "${LIBXDMCP_LIBRARY}" STREQUAL "")
        set(LIBXDMCP_FOUND_TEXT "Not found")
    else()
        set(LIBXDMCP_FOUND_TEXT "Found")
    endif()
else()
    set(LIBXDMCP_FOUND_TEXT "Not found")
endif()

message(STATUS "libxdmcp       : ${LIBXDMCP_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBXDMCP_VERSION}")
message(STATUS "  cflags       : ${PC_LIBXDMCP_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBXDMCP_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBXDMCP_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBXDMCP_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBXDMCP_LIBRARIES}")

set(LIBXDMCP_DEFINITIONS ${PC_LIBXDMCP_CFLAGS_OTHER})
set(LIBXDMCP_INCLUDE_DIR ${LIBXDMCP_INCLUDE_DIRS})
set(LIBXDMCP_LIBRARIES ${LIBXDMCP_LIBRARY})
set(LIBXDMCP_LIBRARY_DIRS ${PC_LIBXDMCP_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBXDMCP DEFAULT_MSG
    LIBXDMCP_LIBRARIES LIBXDMCP_INCLUDE_DIRS)

if(LIBXDMCP_FOUND)
else()
    message(WARNING "Could not find libxdmcp, please install: sudo apt-get install libxdmcp-dev")
endif()

mark_as_advanced(LIBXDMCP_DEFINITIONS LIBXDMCP_INCLUDE_DIRS LIBXDMCP_LIBRARIES)
