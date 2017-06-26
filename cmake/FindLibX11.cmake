# - Try to find X11 library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  LIBX11_FOUND - System has LibX11
#  LIBX11_INCLUDE_DIRS - The LibX11 include directories
#  LIBX11_LIBRARIES - The libraries needed to use LibX11
#  LIBX11_DEFINITIONS - Compiler switches required for using LibX11

find_package(PkgConfig)
pkg_check_modules(PC_LIBX11 QUIET x11)

if(PC_LIBX11_FOUND)
    if(LIBX11_REQUIRED_VERSION)
        if (NOT "${LIBX11_REQUIRED_VERSION}" STREQUAL "${PC_LIBX11_VERSION}")
            message(WARNING "Incorrect version, please install libX11-${LIBX11_REQUIRED_VERSION}")
            set(LIBX11_FOUND_TEXT "Found incorrect version")
            unset(PC_LIBX11_FOUND)
        endif()
    endif()
else()
    set(LIBX11_FOUND_TEXT "Not found")
endif()

if(PC_LIBX11_FOUND)
    find_path(LIBX11_INCLUDE_DIRS X11/XlibConf.h X11/Xlib.h
        HINTS ${PC_LIBX11_INCLUDEDIR} ${PC_LIBX11_INCLUDE_DIRS})

    find_library(LIBX11_LIBRARY NAMES X11 X11-xcb
        HINTS ${PC_LIBX11_LIBDIR} ${PC_LIBX11_LIBRARY_DIRS})

    if("${LIBX11_INCLUDE_DIRS}" STREQUAL "" OR "${LIBX11_LIBRARY}" STREQUAL "")
        set(LIBX11_FOUND_TEXT "Not found")
    else()
        set(LIBX11_FOUND_TEXT "Found")
    endif()
else()
    set(LIBX11_FOUND_TEXT "Not found")
endif()

message(STATUS "libx11         : ${LIBX11_FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBX11_VERSION}")
message(STATUS "  cflags       : ${PC_LIBX11_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBX11_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBX11_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBX11_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBX11_LIBRARIES}")
message(STATUS "  include      : ${LIBX11_INCLUDE_DIRS}")
message(STATUS "  library      : ${LIBX11_LIBRARY}")

set(LIBX11_DEFINITIONS ${PC_LIBX11_CFLAGS_OTHER})
set(LIBX11_LIBRARIES ${LIBX11_LIBRARY} )
set(LIBX11_INCLUDE_DIR ${LIBX11_INCLUDE_DIRS} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBX11 DEFAULT_MSG
    LIBX11_LIBRARY LIBX11_INCLUDE_DIR)

if (LIBX11_FOUND)
else()
    message(WARNING "Could not find libx11, please install: sudo apt-get install libx11-dev")
endif()

mark_as_advanced(LIBX11_DEFINITIONS LIBX11_INCLUDE_DIRS LIBX11_LIBRARIES)

