# - Try to Find Wayland EGL
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBJPEGTURBO_FOUND - System has LibJPEGTurbo
#  LIBJPEGTURBO_INCLUDE_DIR - The LibJPEGTurbo include directories
#  LIBJPEGTURBO_LIBRARIES - The libraries needed to use LibJPEGTurbo
#  LIBJPEGTURBO_DEFINITIONS - Compiler switches required for using LibJPEGTurbo

find_package(PkgConfig)
pkg_check_modules(PC_LIBJPEGTURBO QUIET libturbojpeg)

if(PC_LIBJPEGTURBO_FOUND)
    if(LIBJPEGTURBO_REQUIRED_VERSION)
        if (NOT "${LIBJPEGTURBO_REQUIRED_VERSION}" STREQUAL "${PC_LIBJPEGTURBO_VERSION}")
            message(WARNING "Incorrect version, please install libjpegturbo-${LIBJPEGTURBO_REQUIRED_VERSION}")
            set(LIBJPEGTURBO_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBJPEGTURBO_FOUND)
        endif()
    endif()
else()
    set(LIBJPEGTURBO_FOUND_TEXT "Not found")
endif()

if(PC_LIBJPEGTURBO_FOUND)
    find_path(LIBJPEGTURBO_INCLUDE_DIRS NAMES turbojpeg.h
        HINTS ${PC_LIBJPEGTURBO_INCLUDE_DIRS})

    find_library(LIBJPEGTURBO_LIBRARY NAMES turbojpeg
        HINTS ${PC_LIBJPEGTURBO_LIBRARY} ${PC_LIBJPEGTURBO_LIBRARY_DIRS})

    if("${LIBJPEGTURBO_INCLUDE_DIRS}" STREQUAL "" OR "${LIBJPEGTURBO_LIBRARY}" STREQUAL "")
        set(LIBJPEGTURBO_FOUND_TEXT "Not found")
    else()
        set(LIBJPEGTURBO_FOUND_TEXT "Found")
    endif()
else()
    set(LIBJPEGTURBO_FOUND_TEXT "Not found")
endif()

message(STATUS "libjpegturbo   : ${LIBJPEGTURBO_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBJPEGTURBO_VERSION}")
message(STATUS "  cflags       : ${PC_LIBJPEGTURBO_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBJPEGTURBO_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBJPEGTURBO_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBJPEGTURBO_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBJPEGTURBO_LIBRARIES}")

set(LIBJPEGTURBO_DEFINITIONS ${PC_LIBJPEGTURBO_CFLAGS_OTHER})
set(LIBJPEGTURBO_INCLUDE_DIR ${LIBJPEGTURBO_INCLUDE_DIRS})
set(LIBJPEGTURBO_LIBRARIES ${LIBJPEGTURBO_LIBRARY})
set(LIBJPEGTURBO_LIBRARY_DIRS ${PC_LIBJPEGTURBO_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBJPEGTURBO DEFAULT_MSG
    LIBJPEGTURBO_LIBRARIES LIBJPEGTURBO_INCLUDE_DIRS)

if(LIBJPEGTURBO_FOUND)
else()
    message(WARNING "Could not find libjpegturbo, please install: sudo apt-get install libjpegturbo-dev")
endif()

mark_as_advanced(LIBJPEGTURBO_DEFINITIONS LIBJPEGTURBO_INCLUDE_DIRS LIBJPEGTURBO_LIBRARIES)
