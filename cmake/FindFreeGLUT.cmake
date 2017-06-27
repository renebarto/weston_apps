# - Try to find FreeGLUT library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  FREEGLUT_FOUND - System has libglut
#  FREEGLUT_INCLUDE_DIRS - The LibFREEGLUT include directories
#  FREEGLUT_LIBRARIES - The libraries needed to use LibFREEGLUT
#  FREEGLUT_DEFINITIONS - Compiler switches required for using LibFREEGLUT

find_package(PkgConfig)
pkg_check_modules(PC_FREEGLUT QUIET glut)

#if(PC_FREEGLUT_FOUND)
#    if(FREEGLUT_REQUIRED_VERSION)
#        if (NOT "${FREEGLUT_REQUIRED_VERSION}" STREQUAL "${PC_FREEGLUT_VERSION}")
#            message(WARNING "Incorrect version, please install libfreeglut-${FREEGLUT_REQUIRED_VERSION}")
#            set(FREEGLUT_FOUND_TEXT "Found incorrect version")
#            unset(PC_FREEGLUT_FOUND)
#        endif()
#    endif()
#else()
#    set(FREEGLUT_FOUND_TEXT "Not found")
#endif()
#
#if(PC_FREEGLUT_FOUND)
    find_path(FREEGLUT_INCLUDE_DIRS GL/glut.h GL/freeglut.h GL/freeglut_ext.h GL/freeglut_std.h
        HINTS ${PC_FREEGLUT_INCLUDEDIR} ${PC_FREEGLUT_INCLUDE_DIRS})

    find_library(FREEGLUT_LIBRARY NAMES glut
        HINTS ${PC_FREEGLUT_LIBDIR} ${PC_FREEGLUT_LIBRARY_DIRS} )

    if("${FREEGLUT_INCLUDE_DIRS}" STREQUAL "" OR "${FREEGLUT_LIBRARY}" STREQUAL "")
        set(FREEGLUT_FOUND_TEXT "Not found")
    else()
        set(FREEGLUT_FOUND_TEXT "Found")
    endif()
#else()
#    set(FREEGLUT_FOUND_TEXT "Not found")
#endif()

message(STATUS "freeglut       : ${FREEGLUT_FOUND_TEXT}")
message(STATUS "  version      : ${PC_FREEGLUT_VERSION}")
message(STATUS "  cflags       : ${PC_FREEGLUT_CFLAGS}")
message(STATUS "  cflags other : ${PC_FREEGLUT_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_FREEGLUT_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_FREEGLUT_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_FREEGLUT_LIBRARIES}")
message(STATUS "  include      : ${FREEGLUT_INCLUDE_DIRS}")
message(STATUS "  library      : ${FREEGLUT_LIBRARY}")

set(FREEGLUT_DEFINITIONS ${PC_FREEGLUT_CFLAGS_OTHER})
set(FREEGLUT_LIBRARIES ${FREEGLUT_LIBRARY} )
set(FREEGLUT_INCLUDE_DIR ${FREEGLUT_INCLUDE_DIRS} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FREEGLUT DEFAULT_MSG
    FREEGLUT_LIBRARY FREEGLUT_INCLUDE_DIR)

if (FREEGLUT_FOUND)
else()
    message(WARNING "Could not find libfreeglut, please install: sudo apt install freeglut3-dev")
endif()

mark_as_advanced(FREEGLUT_DEFINITIONS FREEGLUT_INCLUDE_DIRS FREEGLUT_LIBRARIES)
