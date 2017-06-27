# - Try to find GLES V1 library
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
pkg_check_modules(PC_GLESV1 glesv1_cm)

if(PC_GLESV1_FOUND)
    if(GLESV1_REQUIRED_VERSION)
        if (NOT "${GLESV1_REQUIRED_VERSION}" STREQUAL "${PC_GLESV1_VERSION}")
            message(WARNING "Incorrect version, please install libgles1-mesa-dev-${GLESV1_REQUIRED_VERSION}")
            set(GLESV1_FOUND_TEXT "Found incorrect version")
            unset(PC_GLESV1_FOUND)
        endif()
    endif()
else()
    set(GLESV1_FOUND_TEXT "Not found")
endif()

if(PC_GLESV1_FOUND)
    find_path(GLESV1_INCLUDE_DIRS NAMES GLES/gl.h GLES/glext.h GLES/glplatform.h
        HINTS ${PC_GLESV1_INCLUDE_DIRS})

    find_library(GLESV1_LIBRARY NAMES GLESv1_CM
        HINTS ${PC_GLESV1_LIBRARY} ${PC_GLESV1_LIBRARY_DIRS})

    if("${GLESV1_INCLUDE_DIRS}" STREQUAL "" OR "${GLESV1_LIBRARY}" STREQUAL "")
        set(GLESV1_FOUND_TEXT "Not found")
    else()
        set(GLESV1_FOUND_TEXT "Found")
    endif()
else()
    set(GLESV1_FOUND_TEXT "Not found")
endif()

message(STATUS "glesv1         : ${GLESV1_FOUND_TEXT}")
message(STATUS "  version      : ${PC_GLESV1_VERSION}")
message(STATUS "  cflags       : ${PC_GLESV1_CFLAGS}")
message(STATUS "  cflags other : ${PC_GLESV1_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GLESV1_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GLESV1_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GLESV1_LIBRARIES}")

set(GLESV1_DEFINITIONS ${PC_GLESV1_CFLAGS_OTHER})
set(GLESV1_INCLUDE_DIR ${GLESV1_INCLUDE_DIRS})
set(GLESV1_LIBRARIES ${GLESV1_LIBRARY})
set(GLESV1_LIBRARY_DIRS ${PC_GLESV1_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLESV1 DEFAULT_MSG
    GLESV1_LIBRARIES GLESV1_INCLUDE_DIRS)

if(GLESV1_FOUND)
else()
    message(WARNING "Could not find glesv1, please install: sudo apt-get install libgles1-mesa-dev")
endif()

mark_as_advanced(
    GLESV1_DEFINITIONS GLESV1_LIBRARIES GLESV1_INCLUDE_DIRS)

