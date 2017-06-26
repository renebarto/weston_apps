# - Try to find GBM library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBGBM_INCLUDE_DIRS - the gbm include directories
#  LIBGBM_LIBRARIES - link these to use gbm.
#
# Copyright (C) 2015 Igalia S.L.
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
pkg_check_modules(PC_LIBGBM gbm)

if(PC_LIBGBM_FOUND)
    if(LIBGBM_REQUIRED_VERSION)
        if (NOT "${LIBGBM_REQUIRED_VERSION}" STREQUAL "${PC_LIBGBM_VERSION}")
            message(WARNING "Incorrect version, please install libgbm-${LIBGBM_REQUIRED_VERSION}")
            set(LIBGBM_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBGBM_FOUND)
        endif()
    endif()
else()
    set(LIBGBM_FOUND_TEXT "Not found")
endif()

if(PC_LIBGBM_FOUND)
    find_path(LIBGBM_INCLUDE_DIRS NAMES gbm.h
        HINTS ${PC_LIBGBM_INCLUDE_DIRS})

    find_library(LIBGBM_LIBRARY NAMES gbm
        HINTS ${PC_LIBGBM_LIBRARY} ${PC_LIBGBM_LIBRARY_DIRS})

    if("${LIBGBM_INCLUDE_DIRS}" STREQUAL "" OR "${LIBGBM_LIBRARY}" STREQUAL "")
        set(LIBGBM_FOUND_TEXT "Not found")
    else()
        set(LIBGBM_FOUND_TEXT "Found")
    endif()
else()
    set(LIBGBM_FOUND_TEXT "Not found")
endif()

message(STATUS "gbm            : ${LIBGBM_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBGBM_VERSION}")
message(STATUS "  cflags       : ${PC_LIBGBM_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBGBM_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBGBM_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBGBM_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBGBM_LIBRARIES}")

set(LIBGBM_DEFINITIONS ${PC_LIBGBM_CFLAGS_OTHER})
set(LIBGBM_INCLUDE_DIR ${LIBGBM_INCLUDE_DIRS})
set(LIBGBM_LIBRARIES ${LIBGBM_LIBRARY})
set(LIBGBM_LIBRARY_DIRS ${PC_LIBGBM_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBGBM DEFAULT_MSG
    LIBGBM_LIBRARIES LIBGBM_INCLUDE_DIRS)

if(LIBGBM_FOUND)
else()
    message(WARNING "Could not find libgbm, please install: sudo apt-get install libgbm-dev")
endif()

mark_as_advanced(LIBGBM_DEFINITIONS LIBGBM_INCLUDE_DIRS LIBGBM_LIBRARIES)
