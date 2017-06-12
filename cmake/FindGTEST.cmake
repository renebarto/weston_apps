#
# Find the Google test includes and library
#
# This module defines
# GTEST_INCLUDE_DIR, where to find gtest.h, etc.
# GTEST_LIBRARIES, the libraries to link against to use Google test.
# GTEST_FOUND, If false, do not try to use Google test.

# also defined, but not for general use are
# GTEST_LIBRARY, where to find the Google test library.
# GTEST_LIBRARY_MAIN, where to find the Google test library for the main() function.

MESSAGE(STATUS "Looking for GTEST")

find_path(GTEST_INCLUDE_DIRS
          NAMES gtest/gtest.h
          HINTS ${CMAKE_INSTALL_PREFIX}/include /usr/include /usr/local/include)

set(GTEST_NAMES gtest)
find_library(GTEST_LIBRARIES
             NAMES ${GTEST_NAMES}
             HINTS ${CMAKE_INSTALL_PREFIX}/lib /usr/lib /usr/local/lib)
set(GTEST_MAIN_NAMES gtest_main)
find_library(GTEST_EXECUTABLE
             NAMES ${GTEST_MAIN_NAMES}
             HINTS ${CMAKE_INSTALL_PREFIX}/lib /usr/lib /usr/local/lib)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set GTEST_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(GTEST "Please install google test:\ngit clone https://github.com/google/googletest.git\ncd googletest; mkdir build; cd build\ncmake ..\nmake; sudo make install\n"
    GTEST_INCLUDE_DIRS
    GTEST_LIBRARIES
    GTEST_EXECUTABLE)

if(NOT GTEST_FOUND)
    MESSAGE(SEND_ERROR  "Could not find library Google test.")
endif()

mark_as_advanced(GTEST_INCLUDE_DIRS GTEST_LIBRARIES GTEST_EXECUTABLE)
