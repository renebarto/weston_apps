# - Try to find expat
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
# EXPAT_INCLUDE_DIRS - where to find expat.h, etc.
# EXPAT_LIBRARIES    - List of libraries when using expat.
# EXPAT_FOUND        - True if expat found.

find_package(PkgConfig QUIET)
pkg_check_modules(PC_EXPAT QUIET expat)

if(PC_EXPAT_FOUND)
    if(EXPAT_REQUIRED_VERSION)
        if (NOT "${EXPAT_REQUIRED_VERSION}" STREQUAL "${PC_EXPAT_VERSION}")
            message(WARNING "Incorrect version, please install expat-${EXPAT_REQUIRED_VERSION}")
            set(EXPAT_FOUND_TEXT "Found incorrect version")
            unset(PC_EXPAT_FOUND)
        endif()
    endif()
else()
    set(EXPAT_FOUND_TEXT "Not found")
endif()

if(PC_EXPAT_FOUND)
    # Look for the header file.
    find_path(EXPAT_INCLUDE_DIR NAMES expat.h HINTS ${PC_EXPAT_INCLUDE_DIRS})

    # Look for the library.
    find_library(EXPAT_LIBRARY NAMES expat libexpat HINTS ${PC_EXPAT_LIBRARY_DIRS})

    if (EXPAT_INCLUDE_DIR AND EXISTS "${EXPAT_INCLUDE_DIR}/expat.h")
        file(STRINGS "${EXPAT_INCLUDE_DIR}/expat.h" expat_version_str
            REGEX "^#[\t ]*define[\t ]+XML_(MAJOR|MINOR|MICRO)_VERSION[\t ]+[0-9]+$")

        unset(EXPAT_VERSION_STRING)
        foreach(VPART MAJOR MINOR MICRO)
            foreach(VLINE ${expat_version_str})
                if(VLINE MATCHES "^#[\t ]*define[\t ]+XML_${VPART}_VERSION[\t ]+([0-9]+)$")
                    set(EXPAT_VERSION_PART "${CMAKE_MATCH_1}")
                    if(EXPAT_VERSION_STRING)
                        string(APPEND EXPAT_VERSION_STRING ".${EXPAT_VERSION_PART}")
                    else()
                        set(EXPAT_VERSION_STRING "${EXPAT_VERSION_PART}")
                    endif()
                endif()
            endforeach()
        endforeach()
    endif ()
    if("${EXPAT_INCLUDE_DIR}" STREQUAL "" OR "${EXPAT_LIBRARY}" STREQUAL "" OR
       "${EXPAT_VERSION_STRING}" STREQUAL "")
        set(EXPAT_FOUND_TEXT "Not found")
    else()
        set(EXPAT_FOUND_TEXT "Found")
    endif ()
else()
    set(EXPAT_FOUND_TEXT "Not found")
endif()

message(STATUS "expat          : ${EXPAT_FOUND_TEXT}")
message(STATUS "  version      : ${PC_EXPAT_VERSION}")
message(STATUS "  cflags       : ${PC_EXPAT_CFLAGS}")
message(STATUS "  cflags other : ${PC_EXPAT_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_EXPAT_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_EXPAT_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_EXPAT_LIBRARIES}")

set(EXPAT_LIBRARIES ${EXPAT_LIBRARY})
set(EXPAT_INCLUDE_DIRS ${EXPAT_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EXPAT
    REQUIRED_VARS EXPAT_LIBRARIES EXPAT_INCLUDE_DIRS
    VERSION_VAR EXPAT_VERSION_STRING)

if(EXPAT_FOUND)
else()
    message(WARNING "Could not find expat, please install: sudo apt install libexpat1-dev")
endif()

mark_as_advanced(EXPAT_INCLUDE_DIRS EXPAT_LIBRARIES)
