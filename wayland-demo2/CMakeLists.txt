project(wayland-demo2)

#find_package(Wayland REQUIRED)
#
#if (NOT WAYLAND_CLIENT_FOUND)
#    message(FATAL_ERROR "Could not find wayland-client")
#endif()
#
#message(STATUS ${WAYLAND_CLIENT_INCLUDE_DIR})
#message(STATUS ${WAYLAND_CLIENT_LIBRARIES})

set(WAYLAND_DEMO2_SOURCE_FILES
    main.cpp
    Application.cpp)
set(WAYLAND_DEMO2_HEADER_FILES
    Application.h)
set(WAYLAND_DEMO2_LIBS
    wayland-classes
    wayland-client-shared)

add_executable(${PROJECT_NAME} ${WAYLAND_DEMO2_SOURCE_FILES} ${WAYLAND_DEMO2_HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${WAYLAND_DEMO2_LIBS})
add_dependencies(${PROJECT_NAME} ${WAYLAND_DEMO2_LIBS})

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
