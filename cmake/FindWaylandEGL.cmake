# - Try to Find Wayland EGL
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
# WAYLAND_EGL_FOUND
# WAYLAND_EGL_INCLUDE_DIR
# WAYLAND_EGL_LIBRARIES
#

find_package(PkgConfig)
pkg_check_modules(PC_WAYLAND_EGL QUIET wayland-egl)

if(PC_WAYLAND_EGL_FOUND)
    if(WAYLAND_EGL_REQUIRED_VERSION)
        if (NOT "${WAYLAND_EGL_REQUIRED_VERSION}" STREQUAL "${PC_WAYLAND_EGL_VERSION}")
            message(WARNING "Incorrect version, please install wayland-egl-${WAYLAND_EGL_REQUIRED_VERSION}")
            set(WAYLAND_EGL_FOUND_TEXT "Found incorrect version")
            unset(PC_WAYLAND_EGL_FOUND)
        endif()
    endif()
else()
    set(WAYLAND_EGL_FOUND_TEXT "Not found")
endif()

if(PC_WAYLAND_EGL_FOUND)
    find_path(WAYLAND_EGL_INCLUDE_DIRS NAMES wayland-egl.h
        HINTS ${PC_WAYLAND_EGL_INCLUDE_DIRS})

    set(WAYLAND_EGL_LIBRARY )
    foreach(LIB ${PC_WAYLAND_EGL_LIBRARIES})
        find_library(WAYLAND_EGL_LIBRARY_${LIB} NAMES ${LIB}
            HINTS ${PC_WAYLAND_EGL_LIBDIR} ${PC_WAYLAND_EGL_LIBRARY_DIRS})
        list(APPEND WAYLAND_EGL_LIBRARY ${WAYLAND_EGL_LIBRARY_${LIB}})
    endforeach()

    if("${WAYLAND_EGL_INCLUDE_DIRS}" STREQUAL "" OR "${WAYLAND_EGL_LIBRARY}" STREQUAL "")
        set(WAYLAND_EGL_FOUND_TEXT "Not found")
    else()
        set(WAYLAND_EGL_FOUND_TEXT "Found")
    endif()
else()
    set(WAYLAND_EGL_FOUND_TEXT "Not found")
endif()

message(STATUS "wayland-egl    : ${WAYLAND_EGL_FOUND_TEXT}")
message(STATUS "  version      : ${PC_WAYLAND_EGL_VERSION}")
message(STATUS "  cflags       : ${PC_WAYLAND_EGL_CFLAGS}")
message(STATUS "  cflags other : ${PC_WAYLAND_EGL_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_WAYLAND_EGL_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_WAYLAND_EGL_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_WAYLAND_EGL_LIBRARIES}")

set(WAYLAND_EGL_DEFINITIONS ${PC_WAYLAND_EGL_CFLAGS_OTHER})
set(WAYLAND_EGL_INCLUDE_DIR ${WAYLAND_EGL_INCLUDE_DIRS})
set(WAYLAND_EGL_LIBRARIES ${WAYLAND_EGL_LIBRARY})
set(WAYLAND_EGL_LIBRARY_DIRS ${PC_WAYLAND_EGL_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WAYLAND_EGL DEFAULT_MSG
    WAYLAND_EGL_LIBRARIES WAYLAND_EGL_INCLUDE_DIRS)

if(WAYLAND_EGL_FOUND)
else()
    message(WARNING "Could not find wayland-egl, please install: sudo apt-get install libwayland-egl1-mesa")
endif()

mark_as_advanced(WAYLAND_EGL_DEFINITIONS WAYLAND_EGL_INCLUDE_DIRS WAYLAND_EGL_LIBRARIES)
