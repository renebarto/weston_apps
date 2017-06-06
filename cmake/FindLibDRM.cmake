# - Try to find LIBDRM
# Once done this will define
#  LIBDRM_FOUND - System has LIBDRM
#  LIBDRM_INCLUDE_DIR - The LIBDRM include directories
#  LIBDRM_LIBRARIES - The libraries needed to use LIBDRM
#  LIBDRM_DEFINITIONS - Compiler switches required for using LIBDRM

find_package(PkgConfig)
pkg_check_modules(PC_LIBDRM QUIET libdrm)
set(LIBDRM_DEFINITIONS ${PC_LIBDRM_CFLAGS_OTHER})

if(PC_LIBDRM_FOUND)
    set(FOUND_TEXT "Found")
else()
    set(FOUND_TEXT "Not found")
endif()

message(STATUS "libdrm         : ${FOUND_TEXT}")
message(STATUS "  version      : ${PC_LIBDRM_VERSION}")
message(STATUS "  cflags       : ${PC_LIBDRM_CFLAGS}")
message(STATUS "  cflags other : ${PC_LIBDRM_CFLAGS_OTHER}")
message(STATUS "  include dirs : ${PC_LIBDRM_INCLUDE_DIRS}")
message(STATUS "  lib dirs     : ${PC_LIBDRM_LIBRARY_DIRS}")
message(STATUS "  libs         : ${PC_LIBDRM_LIBRARIES}")

find_path(LIBDRM_INCLUDE_DIRS libdrm/drm.h libsync.h xf86drm.h xf86drmMode.h
        HINTS ${PC_LIBDRM_INCLUDEDIR} ${PC_LIBDRM_INCLUDE_DIRS})

find_library(LIBDRM_LIBRARY NAMES drm
        HINTS ${PC_LIBDRM_LIBDIR} ${PC_LIBDRM_LIBRARY_DIRS} )

set(LIBDRM_LIBRARIES ${LIBDRM_LIBRARY} )
set(LIBDRM_INCLUDE_DIR ${LIBDRM_INCLUDE_DIRS} )

include(FindPackageHandleStandardArgs)
# handle the QUIET and REQUIRED arguments and set LIBDRM_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LIBDRM DEFAULT_MSG
        LIBDRM_LIBRARY LIBDRM_INCLUDE_DIR)

if (LIBDRM_FOUND)
    if(LIBDRM_REQUIRED_VERSION)
        if (NOT "${LIBDRM_REQUIRED_VERSION}" STREQUAL "${PC_LIBDRM_VERSION}")
            message(WARNING "Incorrect version, please install libdrm-${LIBDRM_REQUIRED_VERSION}")
            unset(LIBDRM_FOUND)
        endif()
    else()
        message(STATUS "Found libdrm")
    endif()
else()
    message(WARNING "Could not find libdrm, please install: sudo apt-get install libdrm-dev")
endif()

mark_as_advanced(LIBDRM_INCLUDE_DIR LIBDRM_LIBRARY)
