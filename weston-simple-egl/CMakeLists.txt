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

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/xdg-shell-unstable-v6-protocol.c
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> code < ../wayland-protocols-1.7/unstable/xdg-shell/xdg-shell-unstable-v6.xml > protocol/xdg-shell-unstable-v6-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/xdg-shell-unstable-v6-server-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> server-header < ../wayland-protocols-1.7/unstable/xdg-shell/xdg-shell-unstable-v6.xml > protocol/xdg-shell-unstable-v6-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/xdg-shell-unstable-v6-client-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> client-header < ../wayland-protocols-1.7/unstable/xdg-shell/xdg-shell-unstable-v6.xml > protocol/xdg-shell-unstable-v6-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/ivi-application-protocol.c
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> code < ../weston-2.0.0/protocol/ivi-application.xml > protocol/ivi-application-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/ivi-application-server-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> server-header < ../weston-2.0.0/protocol/ivi-application.xml > protocol/ivi-application-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/ivi-application-client-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> client-header < ../weston-2.0.0/protocol/ivi-application.xml > protocol/ivi-application-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

set(WESTON_SIMPL_EGL_DEFINES
    ENABLE_EGL)
set(WESTON_SIMPL_EGL_SOURCE_FILES
    main.cpp
    Application.cpp
    protocol/xdg-shell-unstable-v6-protocol.c
    protocol/ivi-application-protocol.c)
set(WESTON_SIMPL_EGL_HEADER_FILES
    Application.h
    protocol/xdg-shell-unstable-v6-client-protocol.h
    protocol/ivi-application-client-protocol.h)
add_executable(${PROJECT_NAME} ${WESTON_SIMPL_EGL_SOURCE_FILES} ${WESTON_SIMPL_EGL_HEADER_FILES})
target_compile_definitions(${PROJECT_NAME} PRIVATE
    ${WESTON_SIMPL_EGL_DEFINES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${EGL_INCLUDE_DIRS}
    ${WAYLAND_EGL_INCLUDE_DIR}
    ${SYSTEM_INCLUDES})
target_link_libraries(${PROJECT_NAME}
    ${GLEW_LIBRARY}
    ${OPENGL_LIBRARY}
    ${EGL_LIBRARIES}
    wayland-classes
    wayland-client-shared
    wayland-cursor-shared
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
