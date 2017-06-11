# - Try to find freetype library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindFreetype
# ------------
#
# Locate FreeType library
#
# This module defines
#
# ::
#
#   FREETYPE_LIBRARIES, the library to link against
#   FREETYPE_FOUND, if false, do not try to link to FREETYPE
#   FREETYPE_INCLUDE_DIRS, where to find headers.
#   FREETYPE_VERSION, the version of freetype found (since CMake 2.8.8)
#   This is the concatenation of the paths:
#   FREETYPE_INCLUDE_DIR_ft2build
#   FREETYPE_INCLUDE_DIR_freetype2
#
#
#
# $FREETYPE_DIR is an environment variable that would correspond to the
# ./configure --prefix=$FREETYPE_DIR used in building FREETYPE.

# Created by Eric Wing.
# Modifications by Alexander Neundorf.
# This file has been renamed to "FindFreetype.cmake" instead of the correct
# "FindFreeType.cmake" in order to be compatible with the one from KDE4, Alex.

# Ugh, FreeType seems to use some #include trickery which
# makes this harder than it should be. It looks like they
# put ft2build.h in a common/easier-to-find location which
# then contains a #include to a more specific header in a
# more specific location (#include <freetype/config/ftheader.h>).
# Then from there, they need to set a bunch of #define's
# so you can do something like:
# #include FT_FREETYPE_H
# Unfortunately, using CMake's mechanisms like include_directories()
# wants explicit full paths and this trickery doesn't work too well.
# I'm going to attempt to cut out the middleman and hope
# everything still works.

find_package(PkgConfig)
pkg_check_modules(PC_FREETYPE QUIET freetype2)

if(PC_FREETYPE_FOUND)
    find_path(FREETYPE_INCLUDE_DIRS NAMES freetype.h
        PATH_SUFFIXES freetype2/freetype
        HINTS ${PC_FREETYPE_INCLUDE_DIRS})

    find_library(FREETYPE_LIBRARY NAMES freetype
        HINTS ${PC_FREETYPE_LIBRARY} ${PC_FREETYPE_LIBRARY_DIRS})

    set(FREETYPE_H "${FREETYPE_INCLUDE_DIRS}/freetype.h")

    if(EXISTS "${FREETYPE_H}")
        file(STRINGS "${FREETYPE_H}" freetype_version_str
            REGEX "^#[\t ]*define[\t ]+FREETYPE_(MAJOR|MINOR|PATCH)[\t ]+[0-9]+$")

        unset(FREETYPE_VERSION)
        foreach(VPART MAJOR MINOR PATCH)
            foreach(VLINE ${freetype_version_str})
                if(VLINE MATCHES "^#[\t ]*define[\t ]+FREETYPE_${VPART}[\t ]+([0-9]+)$")
                    set(FREETYPE_VERSION_PART "${CMAKE_MATCH_1}")
                    if(FREETYPE_VERSION)
                        string(APPEND FREETYPE_VERSION ".${FREETYPE_VERSION_PART}")
                    else()
                        set(FREETYPE_VERSION "${FREETYPE_VERSION_PART}")
                    endif()
                    unset(FREETYPE_VERSION_PART)
                endif()
            endforeach()
        endforeach()
    endif()

    if(FREETYPE_REQUIRED_VERSION)
        if (NOT "${FREETYPE_REQUIRED_VERSION}" STREQUAL "${FREETYPE_VERSION}")
            message(WARNING "Incorrect version, please install freetype-${FREETYPE_REQUIRED_VERSION}")
            set(FREETYPE_FOUND_TEXT "Found incorrect version")
            unset(PC_FREETYPE_FOUND)
        endif()
    endif()
    if("${FREETYPE_INCLUDE_DIRS}" STREQUAL "" OR "${FREETYPE_LIBRARY}" STREQUAL "")
        set(FREETYPE_FOUND_TEXT "Not found")
    else()
        set(FREETYPE_FOUND_TEXT "Found")
    endif()
else()
    set(FREETYPE_FOUND_TEXT "Not found")
endif()

message(STATUS "freetype       : ${FREETYPE_FOUND_TEXT}")
message(STATUS "  version      : ${FREETYPE_VERSION}")
message(STATUS "  cflags       : ${PC_FREETYPE_CFLAGS}")
message(STATUS "  cflags other : ${PC_FREETYPE_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_FREETYPE_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_FREETYPE_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_FREETYPE_LIBRARIES}")

set(FREETYPE_DEFINITIONS ${PC_FREETYPE_CFLAGS_OTHER})
set(FREETYPE_INCLUDE_DIR ${FREETYPE_INCLUDE_DIRS})
set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARY})
set(FREETYPE_LIBRARY_DIRS ${PC_FREETYPE_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FREETYPE DEFAULT_MSG
    FREETYPE_LIBRARIES FREETYPE_INCLUDE_DIRS FREETYPE_VERSION)

if(FREETYPE_FOUND)
else()
    message(WARNING "Could not find freetype, please install: sudo apt-get install freetype-dev")
endif()

mark_as_advanced(FREETYPE_DEFINITIONS FREETYPE_INCLUDE_DIRS FREETYPE_LIBRARIES)
