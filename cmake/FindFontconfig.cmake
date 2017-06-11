# - Try to find fontconfig
#
# Copyright (C) 2017 Rene Barto
#
# Once done this will define
#
#  FONTCONFIG_FOUND - system has Fontconfig
#  FONTCONFIG_INCLUDE_DIR - The include directory to use for the fontconfig headers
#  FONTCONFIG_LIBRARY - Link these to use FONTCONFIG
#  FONTCONFIG_DEFINITIONS - Compiler switches required for using FONTCONFIG

# Copyright (c) 2006,2007 Laurent Montel, <montel@kde.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

find_package(PkgConfig)
pkg_check_modules(PC_FONTCONFIG fontconfig)

if(PC_FONTCONFIG_FOUND)
    if(FONTCONFIG_REQUIRED_VERSION)
        if (NOT "${FONTCONFIG_REQUIRED_VERSION}" STREQUAL "${PC_FONTCONFIG_VERSION}")
            message(WARNING "Incorrect version, please install fontconfig-${FONTCONFIG_REQUIRED_VERSION}")
            set(FONTCONFIG_FOUND_TEXT "Found incorrect version")
            unset(PC_FONTCONFIG_FOUND)
        endif()
    endif()
else()
    set(FONTCONFIG_FOUND_TEXT "Not found")
endif()

if(PC_FONTCONFIG_FOUND)
    find_path(FONTCONFIG_INCLUDE_DIRS NAMES fontconfig/fontconfig.h
        HINTS ${PC_FONTCONFIG_INCLUDE_DIRS} /usr/X11/include)

    find_library(FONTCONFIG_LIBRARY NAMES fontconfig
        HINTS ${PC_FONTCONFIG_LIBRARY} ${PC_FONTCONFIG_LIBRARY_DIRS})

    if("${FONTCONFIG_INCLUDE_DIRS}" STREQUAL "" OR "${FONTCONFIG_LIBRARY}" STREQUAL "")
        set(FONTCONFIG_FOUND_TEXT "Not found")
    else()
        set(FONTCONFIG_FOUND_TEXT "Found")
    endif()
else()
    set(FONTCONFIG_FOUND_TEXT "Not found")
endif()

message(STATUS "fontconfig     : ${FONTCONFIG_FOUND_TEXT}")
message(STATUS "  version      : ${PC_FONTCONFIG_VERSION}")
message(STATUS "  cflags       : ${PC_FONTCONFIG_CFLAGS}")
message(STATUS "  cflags other : ${PC_FONTCONFIG_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_FONTCONFIG_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_FONTCONFIG_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_FONTCONFIG_LIBRARIES}")

set(FONTCONFIG_DEFINITIONS ${PC_FONTCONFIG_CFLAGS_OTHER})
set(FONTCONFIG_INCLUDE_DIR ${FONTCONFIG_INCLUDE_DIRS})
set(FONTCONFIG_LIBRARIES ${FONTCONFIG_LIBRARY})
set(FONTCONFIG_LIBRARY_DIRS ${PC_FONTCONFIG_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FONTCONFIG DEFAULT_MSG
    FONTCONFIG_LIBRARIES FONTCONFIG_INCLUDE_DIRS)

if(FONTCONFIG_FOUND)
else()
    message(WARNING "Could not find fontconfig, please install: sudo apt-get install fontconfig-dev")
endif()

mark_as_advanced(FONTCONFIG_DEFINITIONS FONTCONFIG_INCLUDE_DIRS FONTCONFIG_LIBRARIES)
