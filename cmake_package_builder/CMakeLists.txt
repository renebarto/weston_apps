project(cmake-package-builder)

set(CMAKE_PACKAGE_LIB_SOURCES
    GenCMakeLists.cpp)
add_library(cmake-package-lib ${CMAKE_PACKAGE_LIB_SOURCES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} cmake-package-lib)