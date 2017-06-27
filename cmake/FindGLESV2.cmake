# - Try to find GLES V2 library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  GLES_FOUND - system has EGL installed.
#  GLES_INCLUDE_DIRS - directories which contain the EGL headers.
#  GLES_LIBRARIES - libraries required to link against EGL.
#  GLES_DEFINITIONS - Compiler switches required for using EGL.
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
pkg_check_modules(PC_GLESV2 glesv2)

if(PC_GLESV2_FOUND)
    if(GLESV2_REQUIRED_VERSION)
        if (NOT "${GLESV2_REQUIRED_VERSION}" STREQUAL "${PC_GLESV2_VERSION}")
            message(WARNING "Incorrect version, please install libgles2-mesa-dev-${GLESV2_REQUIRED_VERSION}")
            set(GLESV2_FOUND_TEXT "Found incorrect version")
            unset(PC_GLESV2_FOUND)
        endif()
    endif()
else()
    set(GLESV2_FOUND_TEXT "Not found")
endif()

if(PC_GLESV2_FOUND)
    find_path(GLESV2_INCLUDE_DIRS NAMES GLES2/gl2.h GLES2/gl2ext.h GLES2/gl2platform.h
        HINTS ${PC_GLESV2_INCLUDE_DIRS})

    find_library(GLESV2_LIBRARY NAMES GLESv2
        HINTS ${PC_GLESV2_LIBRARY} ${PC_GLESV2_LIBRARY_DIRS})

    if("${GLESV2_INCLUDE_DIRS}" STREQUAL "" OR "${GLESV2_LIBRARY}" STREQUAL "")
        set(GLESV2_FOUND_TEXT "Not found")
    else()
        set(GLESV2_FOUND_TEXT "Found")
    endif()
else()
    set(GLESV2_FOUND_TEXT "Not found")
endif()

message(STATUS "glesv2         : ${GLESV2_FOUND_TEXT}")
message(STATUS "  version      : ${PC_GLESV2_VERSION}")
message(STATUS "  cflags       : ${PC_GLESV2_CFLAGS}")
message(STATUS "  cflags other : ${PC_GLESV2_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GLESV2_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GLESV2_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GLESV2_LIBRARIES}")

set(GLESV2_DEFINITIONS ${PC_GLESV2_CFLAGS_OTHER})
set(GLESV2_INCLUDE_DIR ${GLESV2_INCLUDE_DIRS})
set(GLESV2_LIBRARIES ${GLESV2_LIBRARY})
set(GLESV2_LIBRARY_DIRS ${PC_GLESV2_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLESV2 DEFAULT_MSG
    GLESV2_LIBRARIES GLESV2_INCLUDE_DIRS)

if(GLESV2_FOUND)
else()
    message(WARNING "Could not find glesv2, please install: sudo apt-get install libgles2-mesa-dev")
endif()

mark_as_advanced(
    GLESV2_DEFINITIONS GLESV2_LIBRARIES GLESV2_INCLUDE_DIRS)

