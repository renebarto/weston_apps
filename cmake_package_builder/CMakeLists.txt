project(cmake-package-builder)

set(CMAKE_PACKAGE_LIB_SOURCES
    Generator.cpp Generator.h
    Project.cpp Project.h
    Util.cpp Util.h
    Target.cpp Target.h
    ObjectSet.cpp ObjectSet.h
    Library.cpp Library.h
    Executable.cpp Executable.h)
add_library(cmake-package-lib SHARED ${CMAKE_PACKAGE_LIB_SOURCES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} cmake-package-lib)

add_subdirectory(test)