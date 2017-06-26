# - Try to find GLEW library
#
# Copyright (C) 2017 Rene Barto
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Will be defined:
#  GLEW_FOUND - System has LibGLEW
#  GLEW_INCLUDE_DIRS - The LibGLEW include directories
#  GLEW_LIBRARIES - The libraries needed to use LibGLEW
#  GLEW_DEFINITIONS - Compiler switches required for using LibGLEW

find_package(PkgConfig)
pkg_check_modules(PC_GLEW QUIET glew)

if(PC_GLEW_FOUND)
    if(GLEW_REQUIRED_VERSION)
        if (NOT "${GLEW_REQUIRED_VERSION}" STREQUAL "${PC_GLEW_VERSION}")
            message(WARNING "Incorrect version, please install libglew-${GLEW_REQUIRED_VERSION}")
            set(GLEW_FOUND_TEXT "Found incorrect version")
            unset(PC_GLEW_FOUND)
        endif()
    endif()
else()
    set(GLEW_FOUND_TEXT "Not found")
endif()

if(PC_GLEW_FOUND)
    find_path(GLEW_INCLUDE_DIRS GL/glew.h
        HINTS ${PC_GLEW_INCLUDEDIR} ${PC_GLEW_INCLUDE_DIRS})

    find_library(GLEW_LIBRARY NAMES glew GLEW
        HINTS ${PC_GLEW_LIBDIR} ${PC_GLEW_LIBRARY_DIRS} )

    if("${GLEW_INCLUDE_DIRS}" STREQUAL "" OR "${GLEW_LIBRARY}" STREQUAL "")
        set(GLEW_FOUND_TEXT "Not found")
    else()
        set(GLEW_FOUND_TEXT "Found")
    endif()
else()
    set(GLEW_FOUND_TEXT "Not found")
endif()

message(STATUS "glew           : ${GLEW_FOUND_TEXT}")
message(STATUS "  version      : ${PC_GLEW_VERSION}")
message(STATUS "  cflags       : ${PC_GLEW_CFLAGS}")
message(STATUS "  cflags other : ${PC_GLEW_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_GLEW_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_GLEW_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_GLEW_LIBRARIES}")
message(STATUS "  include      : ${GLEW_INCLUDE_DIRS}")
message(STATUS "  library      : ${GLEW_LIBRARY}")

set(GLEW_DEFINITIONS ${PC_GLEW_CFLAGS_OTHER})
set(GLEW_LIBRARIES ${GLEW_LIBRARY} )
set(GLEW_INCLUDE_DIR ${GLEW_INCLUDE_DIRS} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW DEFAULT_MSG
    GLEW_LIBRARY GLEW_INCLUDE_DIR)

if (GLEW_FOUND)
else()
    message(WARNING "Could not find libglew, please install: sudo apt-get install libglew-dev")
endif()

mark_as_advanced(GLEW_DEFINITIONS GLEW_INCLUDE_DIRS GLEW_LIBRARIES)
