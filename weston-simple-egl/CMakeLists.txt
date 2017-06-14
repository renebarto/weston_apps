project(weston-simple-egl)

#find_package(GLEW REQUIRED)
if (${KYLIN})
    set(OPENGL_LIBRARY mali)
else()
    find_package(OpenGL REQUIRED)
endif()
find_package(GLES REQUIRED)
find_package(EGL REQUIRED)
find_package(Wayland REQUIRED)
find_package(WaylandEGL REQUIRED)

message(STATUS "EGL_INCLUDE_DIR ${EGL_INCLUDE_DIRS}")
message(STATUS "EGL_LIBRARY ${EGL_LIBRARIES}")

set(SOURCE_FILES
    main.cpp
    Application.cpp)
set(HEADER_FILES
    Application.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${EGL_INCLUDE_DIRS}
    ${WAYLAND_EGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}
    ${GLEW_LIBRARY}
    ${OPENGL_LIBRARY}
    ${EGL_LIBRARIES}
    wayland-classes
    wayland-client-shared
    ${WAYLAND_EGL_LIBRARIES})
add_dependencies(${PROJECT_NAME}
    wayland-classes
    wayland-client-shared)

include(show_target_properties)
show_target_properties(${PROJECT_NAME})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake
    IMMEDIATE @ONLY)

add_custom_target(uninstall_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${PROJECT_NAME} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake
    COMMENT "Uninstalling ${PROJECT_NAME}")

add_custom_target(install_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${PROJECT_NAME} -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMENT "Installing ${PROJECT_NAME}")

add_dependencies(install-components install_${PROJECT_NAME})

add_dependencies(install_${PROJECT_NAME}
    ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    COMPONENT ${PROJECT_NAME})
