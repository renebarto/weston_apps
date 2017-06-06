# - Try to Find GLES
# Once done, this will define
#
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

pkg_check_modules(PC_GLES glesv2)

if (PC_GLES_FOUND)
    set(GLES_DEFINITIONS ${PC_GLES_CFLAGS_OTHER})
endif ()

find_path(GLES_INCLUDE_DIRS NAMES GLES2/gl2.h
        HINTS ${PC_GLES_INCLUDEDIR} ${PC_GLES_INCLUDE_DIRS}
        )

set(GLES_NAMES ${GLES_NAMES} gles GLESv2 GLESv1_CM)
find_library(GLES_LIBRARIES NAMES ${GLES_NAMES}
        HINTS ${PC_GLES_LIBDIR} ${PC_GLES_LIBRARY_DIRS}
        )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLES DEFAULT_MSG GLES_INCLUDE_DIRS GLES_LIBRARIES)

mark_as_advanced(GLES_INCLUDE_DIRS GLES_LIBRARIES)