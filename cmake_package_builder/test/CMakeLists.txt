project(cmake-package-builder-test)

find_package(GTEST REQUIRED)

set(CMAKE_PACKAGE_BUILDER_TEST_SOURCES
    GeneratorTest.cpp
    ProjectTest.cpp
    ExecutableTest.cpp
    LibraryTest.cpp
    ObjectSetTest.cpp)
set(CMAKE_PACKAGE_BUILDER_TEST_INCLUDE_DIRS
    .
    ..
    ${GTEST_INCLUDE_DIRS})
set(CMAKE_PACKAGE_BUILDER_TEST_LIBS
    ${GTEST_LIBRARIES}
    ${GTEST_EXECUTABLE}
    cmake-package-lib
    pthread)

add_executable(${PROJECT_NAME} ${CMAKE_PACKAGE_BUILDER_TEST_SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE TEST_ROOT="${CMAKE_SOURCE_DIR}/testdata" TEMPLATE_DIR="${CMAKE_SOURCE_DIR}/testdata/templates")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_PACKAGE_BUILDER_TEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PACKAGE_BUILDER_TEST_LIBS})
