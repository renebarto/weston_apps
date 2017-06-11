# - Try to find EGL library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  EGL_FOUND - system has EGL installed.
#  EGL_INCLUDE_DIRS - directories which contain the EGL headers.
#  EGL_LIBRARIES - libraries required to link against EGL.
#  EGL_DEFINITIONS - Compiler switches required for using EGL.
#
# Copyright (C) 2012 Intel Corporation. All rights reserved.
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
pkg_check_modules(PC_EGL egl)

if(PC_EGL_FOUND)
    if(EGL_REQUIRED_VERSION)
        if (NOT "${EGL_REQUIRED_VERSION}" STREQUAL "${PC_EGL_VERSION}")
            message(WARNING "Incorrect version, please install libxkbcommon-${EGL_REQUIRED_VERSION}")
            set(EGL_FOUND_TEXT "Found incorrect version")
            unset(PC_EGL_FOUND)
        endif()
    endif()
else()
    set(EGL_FOUND_TEXT "Not found")
endif()

if(PC_EGL_FOUND)
    find_path(EGL_INCLUDE_DIRS NAMES EGL/egl.h
        HINTS ${PC_EGL_INCLUDE_DIRS})

    find_library(EGL_LIBRARY NAMES EGL egl
        HINTS ${PC_EGL_LIBRARY} ${PC_EGL_LIBRARY_DIRS})

    if("${EGL_INCLUDE_DIRS}" STREQUAL "" OR "${EGL_LIBRARY}" STREQUAL "")
        set(EGL_FOUND_TEXT "Not found")
    else()
        set(EGL_FOUND_TEXT "Found")
    endif()
else()
    set(EGL_FOUND_TEXT "Not found")
endif()

message(STATUS "egl            : ${EGL_FOUND_TEXT}")
message(STATUS "  version      : ${PC_EGL_VERSION}")
message(STATUS "  cflags       : ${PC_EGL_CFLAGS}")
message(STATUS "  cflags other : ${PC_EGL_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_EGL_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_EGL_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_EGL_LIBRARIES}")

set(EGL_DEFINITIONS ${PC_EGL_CFLAGS_OTHER})
set(EGL_INCLUDE_DIR ${EGL_INCLUDE_DIRS})
set(EGL_LIBRARIES ${EGL_LIBRARY})
set(EGL_LIBRARY_DIRS ${PC_EGL_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EGL DEFAULT_MSG
    EGL_LIBRARIES EGL_INCLUDE_DIRS)

if(EGL_FOUND)
else()
    message(WARNING "Could not find egl, please install: sudo apt-get install libegl1-mesa-dev")
endif()

mark_as_advanced(EGL_DEFINITIONS EGL_INCLUDE_DIRS EGL_LIBRARIES)
