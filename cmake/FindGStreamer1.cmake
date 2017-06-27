# - Try to find GStreamer1 library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  GSTREAMER_FOUND - System has GStreamer1
#  GSTREAMER_INCLUDE_DIRS - The GStreamer1 include directories
#  GSTREAMER_LIBRARIES - The libraries needed to use GStreamer1
#  GSTREAMER_DEFINITIONS - Compiler switches required for using GStreamer1

find_package(PkgConfig)
pkg_check_modules(PC_GSTREAMER gstreamer-1.0)
pkg_check_modules(PC_GSTREAMER_BASE gstreamer-base-1.0)
pkg_check_modules(PC_GSTREAMER_CHECK gstreamer-check-1.0)
pkg_check_modules(PC_GSTREAMER_CONTROLLER gstreamer-controller-1.0)
pkg_check_modules(PC_GSTREAMER_NET gstreamer-net-1.0)

message(STATUS "libgstreamer1.0: ${PC_GSTREAMER_FOUND}")
message(STATUS "  version      : ${PC_GSTREAMER_VERSION}")
message(STATUS "  cflags       : ${PC_GSTREAMER_CFLAGS}")
message(STATUS "  cflags other : ${PC_GSTREAMER_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GSTREAMER_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GSTREAMER_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GSTREAMER_LIBRARIES}")
message(STATUS "  include dirs : ${GSTREAMER_INCLUDE_DIRS}")
message(STATUS "  libs         : ${GSTREAMER_LIBRARY}")

message(STATUS "libgstreamer-base1.0: ${PC_GSTREAMER_BASE_FOUND}")
message(STATUS "  version      : ${PC_GSTREAMER_BASE_VERSION}")
message(STATUS "  cflags       : ${PC_GSTREAMER_BASE_CFLAGS}")
message(STATUS "  cflags other : ${PC_GSTREAMER_BASE_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GSTREAMER_BASE_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GSTREAMER_BASE_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GSTREAMER_BASE_LIBRARIES}")

message(STATUS "libgstreamer-check1.0: ${PC_GSTREAMER_CHECK_FOUND}")
message(STATUS "  version      : ${PC_GSTREAMER_CHECK_VERSION}")
message(STATUS "  cflags       : ${PC_GSTREAMER_CHECK_CFLAGS}")
message(STATUS "  cflags other : ${PC_GSTREAMER_CHECK_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GSTREAMER_CHECK_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GSTREAMER_CHECK_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GSTREAMER_CHECK_LIBRARIES}")

message(STATUS "libgstreamer-controller1.0: ${PC_GSTREAMER_CONTROLLER_FOUND}")
message(STATUS "  version      : ${PC_GSTREAMER_CONTROLLER_VERSION}")
message(STATUS "  cflags       : ${PC_GSTREAMER_CONTROLLER_CFLAGS}")
message(STATUS "  cflags other : ${PC_GSTREAMER_CONTROLLER_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GSTREAMER_CONTROLLER_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GSTREAMER_CONTROLLER_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GSTREAMER_CONTROLLER_LIBRARIES}")

message(STATUS "libgstreamer-net1.0: ${PC_GSTREAMER_NET_FOUND}")
message(STATUS "  version      : ${PC_GSTREAMER_NET_VERSION}")
message(STATUS "  cflags       : ${PC_GSTREAMER_NET_CFLAGS}")
message(STATUS "  cflags other : ${PC_GSTREAMER_NET_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GSTREAMER_NET_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GSTREAMER_NET_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GSTREAMER_NET_LIBRARIES}")

if(PC_GSTREAMER_FOUND)
    if(GSTREAMER_REQUIRED_VERSION)
        if (NOT "${GSTREAMER_REQUIRED_VERSION}" STREQUAL "${PC_GSTREAMER_VERSION}")
            message(WARNING "Incorrect version, please install gstreamer-1.0-${GSTREAMER_REQUIRED_VERSION}")
            set(GSTREAMER_FOUND_TEXT "Found incorrect version")
            unset(PC_GSTREAMER_FOUND)
        endif()
    endif()
else()
    set(GSTREAMER_FOUND_TEXT "Not found")
endif()

if(PC_GSTREAMER_FOUND)
    find_path(GSTREAMER_INCLUDE_DIRS gst/gst.h
        PATHS ${PC_GSTREAMER_INCLUDEDIR} ${PC_GSTREAMER_INCLUDE_DIRS})

    set(GSTREAMER_LIBRARY )
    foreach(LIB ${PC_GSTREAMER_LIBRARIES})
        find_library(GSTREAMER_LIBRARY_${LIB} NAMES ${LIB}
            HINTS ${PC_GSTREAMER_LIBDIR} ${PC_GSTREAMER_LIBRARY_DIRS})
        list(APPEND GSTREAMER_LIBRARY ${GSTREAMER_LIBRARY_${LIB}})
    endforeach()

    if("${GSTREAMER_INCLUDE_DIRS}" STREQUAL "" OR "${GSTREAMER_LIBRARY}" STREQUAL "")
        set(GSTREAMER_FOUND_TEXT "Not found")
    else()
        set(GSTREAMER_FOUND_TEXT "Found")
    endif()
else()
    set(GSTREAMER_FOUND_TEXT "Not found")
endif()

if(PC_GSTREAMER_BASE_FOUND)
    if(GSTREAMER_BASE_REQUIRED_VERSION)
        if (NOT "${GSTREAMER_BASE_REQUIRED_VERSION}" STREQUAL "${PC_GSTREAMER_BASE_VERSION}")
            message(WARNING "Incorrect version, please install gstreamer-base-1.0-${GSTREAMER_BASE_REQUIRED_VERSION}")
            set(GSTREAMER_BASE_FOUND_TEXT "Found incorrect version")
            unset(PC_GSTREAMER_BASE_FOUND)
        endif()
    endif()
else()
    set(GSTREAMER_BASE_FOUND_TEXT "Not found")
endif()

if(PC_GSTREAMER_BASE_FOUND)
    find_path(GSTREAMER_BASE_INCLUDE_DIRS gstreamer-1.0/gst/base/base.h
        HINTS ${PC_GSTREAMER_BASE_INCLUDEDIR} ${PC_GSTREAMER_BASE_INCLUDE_DIRS})

    find_library(GSTREAMER_BASE_LIBRARY NAMES gstbase-1.0
        HINTS ${PC_GSTREAMER_BASE_LIBDIR} ${PC_GSTREAMER_BASE_LIBRARY_DIRS})

    if("${GSTREAMER_BASE_INCLUDE_DIRS}" STREQUAL "" OR "${GSTREAMER_BASE_LIBRARY}" STREQUAL "")
        set(GSTREAMER_BASE_FOUND_TEXT "Not found")
    else()
        set(GSTREAMER_BASE_FOUND_TEXT "Found")
    endif()
else()
    set(GSTREAMER_BASE_FOUND_TEXT "Not found")
endif()

if(PC_GSTREAMER_CHECK_FOUND)
    if(GSTREAMER_CHECK_REQUIRED_VERSION)
        if (NOT "${GSTREAMER_CHECK_REQUIRED_VERSION}" STREQUAL "${PC_GSTREAMER_CHECK_VERSION}")
            message(WARNING "Incorrect version, please install gstreamer-check-1.0-${GSTREAMER_CHECK_REQUIRED_VERSION}")
            set(GSTREAMER_CHECK_FOUND_TEXT "Found incorrect version")
            unset(PC_GSTREAMER_CHECK_FOUND)
        endif()
    endif()
else()
    set(GSTREAMER_CHECK_FOUND_TEXT "Not found")
endif()

if(PC_GSTREAMER_CHECK_FOUND)
    find_path(GSTREAMER_CHECK_INCLUDE_DIRS gstreamer-1.0/gst/check/check.h
        HINTS ${PC_GSTREAMER_CHECK_INCLUDEDIR} ${PC_GSTREAMER_CHECK_INCLUDE_DIRS})

    find_library(GSTREAMER_CHECK_LIBRARY NAMES gstcheck-1.0
        HINTS ${PC_GSTREAMER_CHECK_LIBDIR} ${PC_GSTREAMER_CHECK_LIBRARY_DIRS})

    if("${GSTREAMER_CHECK_INCLUDE_DIRS}" STREQUAL "" OR "${GSTREAMER_CHECK_LIBRARY}" STREQUAL "")
        set(GSTREAMER_CHECK_FOUND_TEXT "Not found")
    else()
        set(GSTREAMER_CHECK_FOUND_TEXT "Found")
    endif()
else()
    set(GSTREAMER_CHECK_FOUND_TEXT "Not found")
endif()

if(PC_GSTREAMER_CONTROLLER_FOUND)
    if(GSTREAMER_CONTROLLER_REQUIRED_VERSION)
        if (NOT "${GSTREAMER_CONTROLLER_REQUIRED_VERSION}" STREQUAL "${PC_GSTREAMER_CONTROLLER_VERSION}")
            message(WARNING "Incorrect version, please install gstreamer-controller-1.0-${GSTREAMER_CONTROLLER_REQUIRED_VERSION}")
            set(GSTREAMER_CONTROLLER_FOUND_TEXT "Found incorrect version")
            unset(PC_GSTREAMER_CONTROLLER_FOUND)
        endif()
    endif()
else()
    set(GSTREAMER_CONTROLLER_FOUND_TEXT "Not found")
endif()

if(PC_GSTREAMER_CONTROLLER_FOUND)
    find_path(GSTREAMER_CONTROLLER_INCLUDE_DIRS gstreamer-1.0/gst/controller/controller.h
        HINTS ${PC_GSTREAMER_CONTROLLER_INCLUDEDIR} ${PC_GSTREAMER_CONTROLLER_INCLUDE_DIRS})

    find_library(GSTREAMER_CONTROLLER_LIBRARY NAMES gstcontroller-1.0
        HINTS ${PC_GSTREAMER_CONTROLLER_LIBDIR} ${PC_GSTREAMER_CONTROLLER_LIBRARY_DIRS})

    if("${GSTREAMER_CONTROLLER_INCLUDE_DIRS}" STREQUAL "" OR "${GSTREAMER_CONTROLLER_LIBRARY}" STREQUAL "")
        set(GSTREAMER_CONTROLLER_FOUND_TEXT "Not found")
    else()
        set(GSTREAMER_CONTROLLER_FOUND_TEXT "Found")
    endif()
else()
    set(GSTREAMER_CONTROLLER_FOUND_TEXT "Not found")
endif()

if(PC_GSTREAMER_NET_FOUND)
    if(GSTREAMER_NET_REQUIRED_VERSION)
        if (NOT "${GSTREAMER_NET_REQUIRED_VERSION}" STREQUAL "${PC_GSTREAMER_NET_VERSION}")
            message(WARNING "Incorrect version, please install gstreamer-net-1.0-${GSTREAMER_NET_REQUIRED_VERSION}")
            set(GSTREAMER_NET_FOUND_TEXT "Found incorrect version")
            unset(PC_GSTREAMER_NET_FOUND)
        endif()
    endif()
else()
    set(GSTREAMER_NET_FOUND_TEXT "Not found")
endif()

if(PC_GSTREAMER_NET_FOUND)
    find_path(GSTREAMER_NET_INCLUDE_DIRS gst/net/gstnet.h
        HINTS ${PC_GSTREAMER_NET_INCLUDEDIR} ${PC_GSTREAMER_NET_INCLUDE_DIRS})

    find_library(GSTREAMER_NET_LIBRARY NAMES gstnet-1.0
        HINTS ${PC_GSTREAMER_NET_LIBDIR} ${PC_GSTREAMER_NET_LIBRARY_DIRS})

    if("${GSTREAMER_NET_INCLUDE_DIRS}" STREQUAL "" OR "${GSTREAMER_NET_LIBRARY}" STREQUAL "")
        set(GSTREAMER_NET_FOUND_TEXT "Not found")
    else()
        set(GSTREAMER_NET_FOUND_TEXT "Found")
    endif()
else()
    set(GSTREAMER_NET_FOUND_TEXT "Not found")
endif()

message(STATUS "libgstreamer1.0: ${GSTREAMER_FOUND_TEXT}")
message(STATUS "  version      : ${PC_GSTREAMER_VERSION}")
message(STATUS "  cflags       : ${PC_GSTREAMER_CFLAGS}")
message(STATUS "  cflags other : ${PC_GSTREAMER_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GSTREAMER_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GSTREAMER_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GSTREAMER_LIBRARIES}")
message(STATUS "  include dirs : ${GSTREAMER_INCLUDE_DIRS}")
message(STATUS "  libs         : ${GSTREAMER_LIBRARY}")

message(STATUS "libgstreamer-base1.0: ${GSTREAMER_BASE_FOUND_TEXT}")
message(STATUS "  version      : ${PC_GSTREAMER_BASE_VERSION}")
message(STATUS "  cflags       : ${PC_GSTREAMER_BASE_CFLAGS}")
message(STATUS "  cflags other : ${PC_GSTREAMER_BASE_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GSTREAMER_BASE_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GSTREAMER_BASE_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GSTREAMER_BASE_LIBRARIES}")

message(STATUS "libgstreamer-check1.0: ${GSTREAMER_CHECK_FOUND_TEXT}")
message(STATUS "  version      : ${PC_GSTREAMER_CHECK_VERSION}")
message(STATUS "  cflags       : ${PC_GSTREAMER_CHECK_CFLAGS}")
message(STATUS "  cflags other : ${PC_GSTREAMER_CHECK_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GSTREAMER_CHECK_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GSTREAMER_CHECK_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GSTREAMER_CHECK_LIBRARIES}")

message(STATUS "libgstreamer-controller1.0: ${GSTREAMER_CONTROLLER_FOUND_TEXT}")
message(STATUS "  version      : ${PC_GSTREAMER_CONTROLLER_VERSION}")
message(STATUS "  cflags       : ${PC_GSTREAMER_CONTROLLER_CFLAGS}")
message(STATUS "  cflags other : ${PC_GSTREAMER_CONTROLLER_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GSTREAMER_CONTROLLER_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GSTREAMER_CONTROLLER_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GSTREAMER_CONTROLLER_LIBRARIES}")

message(STATUS "libgstreamer-net1.0: ${GSTREAMER_NET_FOUND_TEXT}")
message(STATUS "  version      : ${PC_GSTREAMER_NET_VERSION}")
message(STATUS "  cflags       : ${PC_GSTREAMER_NET_CFLAGS}")
message(STATUS "  cflags other : ${PC_GSTREAMER_NET_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GSTREAMER_NET_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GSTREAMER_NET_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GSTREAMER_NET_LIBRARIES}")

set(GSTREAMER_DEFINITIONS ${PC_GSTREAMER_CFLAGS_OTHER})
set(GSTREAMER_LIBRARIES ${GSTREAMER_LIBRARY} )
set(GSTREAMER_INCLUDE_DIRS ${PC_GSTREAMER_INCLUDE_DIRS} )

set(GSTREAMER_BASE_DEFINITIONS ${PC_GSTREAMER_BASE_CFLAGS_OTHER})
set(GSTREAMER_BASE_LIBRARIES ${PC_GSTREAMER_BASE_LIBRARIES} )
set(GSTREAMER_BASE_INCLUDE_DIRS ${PC_GSTREAMER_BASE_INCLUDE_DIRS} )

set(GSTREAMER_CHECK_DEFINITIONS ${PC_GSTREAMER_CHECK_CFLAGS_OTHER})
set(GSTREAMER_CHECK_LIBRARIES ${PC_GSTREAMER_CHECK_LIBRARIES} )
set(GSTREAMER_CHECK_INCLUDE_DIRS ${PC_GSTREAMER_CHECK_INCLUDE_DIRS} )

set(GSTREAMER_CONTROLLER_DEFINITIONS ${PC_GSTREAMER_CONTROLLER_CFLAGS_OTHER})
set(GSTREAMER_CONTROLLER_LIBRARIES ${PC_GSTREAMER_CONTROLLER_LIBRARIES} )
set(GSTREAMER_CONTROLLER_INCLUDE_DIRS ${PC_GSTREAMER_CONTROLLER_INCLUDE_DIRS} )

set(GSTREAMER_NET_DEFINITIONS ${PC_GSTREAMER_NETCFLAGS_OTHER})
set(GSTREAMER_NET_LIBRARIES ${PC_GSTREAMER_NET_LIBRARIES} )
set(GSTREAMER_NET_INCLUDE_DIRS ${PC_GSTREAMER_NET_INCLUDE_DIRS} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GSTREAMER DEFAULT_MSG
    GSTREAMER_LIBRARIES GSTREAMER_INCLUDE_DIRS)
find_package_handle_standard_args(GSTREAMER_BASE DEFAULT_MSG
    GSTREAMER_BASE_LIBRARIES GSTREAMER_BASE_INCLUDE_DIRS)
find_package_handle_standard_args(GSTREAMER_CHECK DEFAULT_MSG
    GSTREAMER_CHECK_LIBRARIES GSTREAMER_CHECK_INCLUDE_DIRS)
find_package_handle_standard_args(GSTREAMER_CONTROLLER DEFAULT_MSG
    GSTREAMER_CONTROLLER_LIBRARIES GSTREAMER_CONTROLLER_INCLUDE_DIRS)
find_package_handle_standard_args(GSTREAMER_NET DEFAULT_MSG
    GSTREAMER_NET_LIBRARIES GSTREAMER_NET_INCLUDE_DIRS)

mark_as_advanced(
    GSTREAMER_INCLUDE_DIRS GSTREAMER_LIBRARIES
    GSTREAMER_BASE_INCLUDE_DIRS GSTREAMER_BASE_LIBRARIES
    GSTREAMER_CHECK_INCLUDE_DIRS GSTREAMER_CHECK_LIBRARIES
    GSTREAMER_CONTROLLER_INCLUDE_DIRS GSTREAMER_CONTROLLER_LIBRARv
    GSTREAMER_NET_INCLUDE_DIRS GSTREAMER_NET_LIBRARIES)
