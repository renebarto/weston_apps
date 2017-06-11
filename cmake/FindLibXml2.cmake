# - Try to find libxml2
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#   LIBXML2_FOUND - System has LibXml2
#   LIBXML2_INCLUDE_DIRS - The LibXml2 include directory
#   LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#   LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2
#   LIBXML2_XMLLINT_EXECUTABLE - The XML checking tool xmllint coming with LibXml2
#   LIBXML2_VERSION_STRING - the version of LibXml2 found (since CMake 2.8.8)

#=============================================================================
# Copyright 2006-2009 Kitware, Inc.
# Copyright 2006 Alexander Neundorf <neundorf@kde.org>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

find_package(PkgConfig QUIET)
PKG_CHECK_MODULES(PC_LIBXML2 QUIET libxml-2.0)

if(PC_LIBXML2_FOUND)
    if (LIBXML2_REQUIRED_VERSION)
        if (NOT "${LIBXML2_REQUIRED_VERSION}" STREQUAL "${PC_LIBXML2_VERSION}")
            message(WARNING "Incorrect version, please install libxml2-${LIBXML2_REQUIRED_VERSION}")
            set(LIBXML2_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBXML2_FOUND)
        endif()
    endif()
else()
    set(LIBXML2_FOUND_TEXT "Not found")
endif()

if(PC_LIBXML2_FOUND)
    find_path(LIBXML2_INCLUDE_DIRS NAMES libxml/xpath.h
        HINTS
        ${PC_LIBXML2_INCLUDEDIR}
        ${PC_LIBXML2_INCLUDE_DIRS}
        PATH_SUFFIXES libxml2)

    find_library(LIBXML2_LIBRARY NAMES xml2 libxml2
        HINTS
        ${PC_LIBXML2_LIBDIR}
        ${PC_LIBXML2_LIBRARY_DIRS}
        )

    find_program(LIBXML2_XMLLINT_EXECUTABLE xmllint)
    # for backwards compat. with KDE 4.0.x:
    set(XMLLINT_EXECUTABLE "${LIBXML2_XMLLINT_EXECUTABLE}")

    if(PC_LIBXML2_VERSION)
        set(LIBXML2_VERSION_STRING ${PC_LIBXML2_VERSION})
    elseif(LIBXML2_INCLUDE_DIR AND EXISTS "${LIBXML2_INCLUDE_DIR}/libxml/xmlversion.h")
        file(STRINGS "${LIBXML2_INCLUDE_DIR}/libxml/xmlversion.h" libxml2_version_str
            REGEX "^#define[\t ]+LIBXML2_DOTTED_VERSION[\t ]+\".*\"")

        string(REGEX REPLACE "^#define[\t ]+LIBXML2_DOTTED_VERSION[\t ]+\"([^\"]*)\".*" "\\1"
            LIBXML2_VERSION_STRING "${libxml2_version_str}")
        unset(libxml2_version_str)
    endif()

    if("${LIBXML2_INCLUDE_DIR}" STREQUAL "" OR "${LIBXML2_LIBRARIES}" STREQUAL "" OR
       "${LIBXML2_XMLLINT_EXECUTABLE}" STREQUAL "" OR "${LIBXML2_VERSION_STRING}" STREQUAL "")
        set(LIBXML2_FOUND_TEXT "Not found")
    else()
        set(LIBXML2_FOUND_TEXT "Found")
    endif()
else()
    set(LIBXML2_FOUND_TEXT "Not found")
endif()

message(STATUS "libxml2        : ${LIBXML2_FOUND_TEXT}")
message(STATUS "  version      : ${LIBXML2_VERSION_STRING}")
message(STATUS "  cflags       : ${PC_LIBXML2_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBXML2_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBXML2_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBXML2_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBXML2_LIBRARIES}")

set(LIBXML2_DEFINITIONS ${PC_LIBXML2_CFLAGS_OTHER})
set(LIBXML2_LIBRARIES ${LIBXML2_LIBRARY} )
set(LIBXML2_INCLUDE_DIR ${LIBXML2_INCLUDE_DIRS} )

# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibXml2
    REQUIRED_VARS LIBXML2_LIBRARIES LIBXML2_INCLUDE_DIRS
    VERSION_VAR LIBXML2_VERSION_STRING)

if (LIBXML2_FOUND)
else()
    message(WARNING "Could not find libxml2, please install: sudo apt-get install libxml2-dev")
endif()

mark_as_advanced(LIBXML2_DEFINITIONS LIBXML2_INCLUDE_DIRS LIBXML2_LIBRARIES LIBXML2_XMLLINT_EXECUTABLE LIBXML2_VERSION_STRING)
