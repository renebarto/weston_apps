# - Try to find EGL library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  CAIRO_FOUND - system has Cairo
#  CAIRO_INCLUDE_DIR - the Cairo include directories
#  CAIRO_LIBRARY - link these to use Cairo
#
# Copyright (C) 2012 Raphael Kubo da Costa <rakuco@webkit.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1.  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 2.  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND ITS CONTRIBUTORS ``AS
# IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR ITS
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

find_package(PkgConfig)
pkg_check_modules(PC_CAIRO cairo)

if(PC_CAIRO_FOUND)
    find_path(CAIRO_INCLUDE_DIRS
        NAMES cairo.h
        HINTS ${PC_CAIRO_INCLUDEDIR}
        ${PC_CAIRO_INCLUDE_DIR}
        PATH_SUFFIXES cairo)

    find_library(CAIRO_LIBRARY
        NAMES cairo
        HINTS ${PC_CAIRO_LIBDIR}
        ${PC_CAIRO_LIBRARY_DIRS})

    if(CAIRO_INCLUDE_DIRS)
        if(EXISTS "${CAIRO_INCLUDE_DIRS}/cairo-version.h")
            FILE(READ "${CAIRO_INCLUDE_DIRS}/cairo-version.h" CAIRO_VERSION_CONTENT)

            STRING(REGEX MATCH "#define +CAIRO_VERSION_MAJOR +([0-9]+)" _dummy "${CAIRO_VERSION_CONTENT}")
            set(CAIRO_VERSION_MAJOR "${CMAKE_MATCH_1}")

            STRING(REGEX MATCH "#define +CAIRO_VERSION_MINOR +([0-9]+)" _dummy "${CAIRO_VERSION_CONTENT}")
            set(CAIRO_VERSION_MINOR "${CMAKE_MATCH_1}")

            STRING(REGEX MATCH "#define +CAIRO_VERSION_MICRO +([0-9]+)" _dummy "${CAIRO_VERSION_CONTENT}")
            set(CAIRO_VERSION_MICRO "${CMAKE_MATCH_1}")

            set(CAIRO_VERSION "${CAIRO_VERSION_MAJOR}.${CAIRO_VERSION_MINOR}.${CAIRO_VERSION_MICRO}")
        endif()
    endif()

    if(CAIRO_REQUIRED_VERSION)
        if (NOT "${CAIRO_REQUIRED_VERSION}" STREQUAL "${CAIRO_VERSION}")
            message(WARNING "Incorrect version, please install cairo-${CAIRO_REQUIRED_VERSION}")
            set(CAIRO_FOUND_TEXT "Found incorrect version")
            unset(PC_CAIRO_FOUND)
        endif()
    endif()
else()
    set(CAIRO_FOUND_TEXT "Not found")
endif()

message(STATUS "cairo          : ${CAIRO_FOUND_TEXT}")
message(STATUS "  version      : ${CAIRO_VERSION}")
message(STATUS "  cflags       : ${PC_CAIRO_CFLAGS}")
message(STATUS "  cflags other : ${PC_CAIRO_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_CAIRO_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_CAIRO_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_CAIRO_LIBRARIES}")

set(CAIRO_DEFINITIONS ${PC_CAIRO_CFLAGS_OTHER})
set(CAIRO_INCLUDE_DIR ${CAIRO_INCLUDE_DIRS})
set(CAIRO_LIBRARIES ${CAIRO_LIBRARY})
set(CAIRO_LIBRARY_DIRS ${PC_CAIRO_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CAIRO DEFAULT_MSG
    CAIRO_LIBRARIES CAIRO_INCLUDE_DIRS CAIRO_VERSION)

if(CAIRO_FOUND)
else()
    message(WARNING "Could not find cairo, please install: sudo apt-get install libcairo2-dev")
endif()

mark_as_advanced(CAIRO_DEFINITIONS CAIRO_INCLUDE_DIRS CAIRO_LIBRARIES CAIRO_VERSION)
