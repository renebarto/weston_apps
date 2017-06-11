# - Try to find input library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#   LIBINPUT_FOUND         - True if libinput is available
#   LIBINPUT_INCLUDE_DIRS  - Include directories for libinput
#   LIBINPUT_LIBRARIES     - List of libraries for libinput
#   LIBINPUT_DEFINITIONS   - List of definitions for libinput
#
# and also the following more fine grained variables
#
# ::
#
#   LIBINPUT_VERSION
#   LIBINPUT_VERSION_MAJOR
#   LIBINPUT_VERSION_MINOR
#   LIBINPUT_VERSION_MICRO
#
#=============================================================================
# Copyright (c) 2015 Jari Vetoniemi
#
# Distributed under the OSI-approved BSD License (the "License");
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================

include(FeatureSummary)
set_package_properties(LibInput PROPERTIES
    URL "http://freedesktop.org/wiki/Software/libinput/"
    DESCRIPTION "Library to handle input devices")

find_package(PkgConfig)
pkg_check_modules(PC_LIBINPUT QUIET libinput)

if(PC_LIBINPUT_FOUND)
    if(LIBINPUT_REQUIRED_VERSION)
        if (NOT "${LIBINPUT_REQUIRED_VERSION}" STREQUAL "${PC_LIBINPUT_VERSION}")
            message(WARNING "Incorrect version, please install libinput-${LIBINPUT_REQUIRED_VERSION}")
            set(LIBINPUT_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBINPUT_FOUND)
        endif()
    endif()
else()
    set(LIBINPUT_FOUND_TEXT "Not found")
endif()

if(PC_LIBINPUT_FOUND)
    find_path(LIBINPUT_INCLUDE_DIRS NAMES libinput.h
        HINTS ${PC_LIBINPUT_INCLUDE_DIRS})

    find_library(LIBINPUT_LIBRARY NAMES input
        HINTS ${PC_LIBINPUT_LIBRARY} ${PC_LIBINPUT_LIBRARY_DIRS})

    if("${LIBINPUT_INCLUDE_DIRS}" STREQUAL "" OR "${LIBINPUT_LIBRARY}" STREQUAL "")
        set(LIBINPUT_FOUND_TEXT "Not found")
    else()
        set(LIBINPUT_FOUND_TEXT "Found")
    endif()
else()
    set(LIBINPUT_FOUND_TEXT "Not found")
endif()

message(STATUS "libinput       : ${LIBINPUT_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBINPUT_VERSION}")
message(STATUS "  cflags       : ${PC_LIBINPUT_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBINPUT_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBINPUT_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBINPUT_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBINPUT_LIBRARIES}")

set(LIBINPUT_VERSION ${PC_LIBINPUT_VERSION})
string(REPLACE "." ";" VERSION_LIST "${PC_LIBINPUT_VERSION}")

LIST(LENGTH VERSION_LIST n)
if (n EQUAL 3)
    list(GET VERSION_LIST 0 LIBINPUT_VERSION_MAJOR)
    list(GET VERSION_LIST 1 LIBINPUT_VERSION_MINOR)
    list(GET VERSION_LIST 2 LIBINPUT_VERSION_MICRO)
else ()
    set(LIBINPUT_VERSION "9999.9999.9999")
    set(LIBINPUT_VERSION_MAJOR 9999)
    set(LIBINPUT_VERSION_MINOR 9999)
    set(LIBINPUT_VERSION_MICRO 9999)
    message(WARNING "Could not detect libinput version, assuming you have recent one")
endif ()

# This is compatible with libinput-version.h that exists in upstream
# but isn't in distribution (probably forgotten)
set(LIBINPUT_DEFINITIONS ${PC_LIBINPUT_CFLAGS_OTHER}
    -DLIBINPUT_VERSION=\"${LIBINPUT_VERSION}\"
    -DLIBINPUT_VERSION_MAJOR=${LIBINPUT_VERSION_MAJOR}
    -DLIBINPUT_VERSION_MINOR=${LIBINPUT_VERSION_MINOR}
    -DLIBINPUT_VERSION_MICRO=${LIBINPUT_VERSION_MICRO})

set(LIBINPUT_INCLUDE_DIR ${LIBINPUT_INCLUDE_DIRS})
set(LIBINPUT_LIBRARIES ${LIBINPUT_LIBRARY})
set(LIBINPUT_LIBRARY_DIRS ${PC_LIBINPUT_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBINPUT DEFAULT_MSG
    LIBINPUT_INCLUDE_DIRS LIBINPUT_LIBRARIES)

if (LIBINPUT_FOUND)
else()
    message(WARNING "Could not find libinput, please install: sudo apt-get install libinput-dev")
endif()

mark_as_advanced(LIBINPUT_INCLUDE_DIRS LIBINPUT_LIBRARIES LIBINPUT_DEFINITIONS
    LIBINPUT_VERSION LIBINPUT_VERSION_MAJOR LIBINPUT_VERSION_MICRO LIBINPUT_VERSION_MINOR)