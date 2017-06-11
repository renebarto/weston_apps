# - Try to find EGL library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBDRM_FOUND - System has LIBDRM
#  LIBDRM_INCLUDE_DIRS - The LIBDRM include directories
#  LIBDRM_LIBRARIES - The libraries needed to use LIBDRM
#  LIBDRM_DEFINITIONS - Compiler switches required for using LIBDRM

find_package(PkgConfig)
pkg_check_modules(PC_LIBDRM QUIET libdrm)

if(PC_LIBDRM_FOUND)
    if(LIBDRM_REQUIRED_VERSION)
        if (NOT "${LIBDRM_REQUIRED_VERSION}" STREQUAL "${PC_LIBDRM_VERSION}")
            message(WARNING "Incorrect version, please install libdrm-dev-${LIBDRM_REQUIRED_VERSION}")
            set(LIBDRM_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBDRM_FOUND)
        endif()
    endif()
else()
    set(LIBDRM_FOUND_TEXT "Not found")
endif()

if(PC_LIBDRM_FOUND)
    find_path(LIBDRM_INCLUDE_DIRS NAMES drm.h libsync.h xf86drm.h xf86drmMode.h
        HINTS ${PC_LIBDRM_INCLUDE_DIRS})
    list(APPEND LIBDRM_INCLUDE_DIRS ${PC_LIBDRM_INCLUDE_DIRS})
    list(REMOVE_DUPLICATES LIBDRM_INCLUDE_DIRS)

    find_library(LIBDRM_LIBRARY NAMES drm
        HINTS ${PC_LIBDRM_LIBRARY} ${PC_LIBDRM_LIBRARY_DIRS})

    if("${LIBDRM_INCLUDE_DIRS}" STREQUAL "" OR "${LIBDRM_LIBRARY}" STREQUAL "")
        set(LIBDRM_FOUND_TEXT "Not found")
    else()
        set(LIBDRM_FOUND_TEXT "Found")
    endif()
else()
    set(LIBDRM_FOUND_TEXT "Not found")
endif()

message(STATUS "libdrm         : ${LIBDRM_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBDRM_VERSION}")
message(STATUS "  cflags       : ${PC_LIBDRM_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBDRM_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBDRM_INCLUDE_DIRS}")
message(STATUS "  include dirs : ${LIBDRM_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBDRM_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBDRM_LIBRARIES}")

set(LIBDRM_DEFINITIONS ${PC_LIBDRM_CFLAGS_OTHER})
set(LIBDRM_INCLUDE_DIR ${LIBDRM_INCLUDE_DIRS})
set(LIBDRM_LIBRARIES ${LIBDRM_LIBRARY})
set(LIBDRM_LIBRARY_DIRS ${PC_LIBDRM_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBDRM DEFAULT_MSG
    LIBDRM_LIBRARIES LIBDRM_INCLUDE_DIRS)

if(LIBDRM_FOUND)
else()
    message(WARNING "Could not find libdrm, please install: sudo apt-get install libdrm-dev")
endif()

mark_as_advanced(LIBDRM_DEFINITIONS LIBDRM_LIBRARIES LIBDRM_INCLUDE_DIRS)
