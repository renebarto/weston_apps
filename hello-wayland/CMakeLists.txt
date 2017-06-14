project(hello-wayland)

#find_package(Wayland REQUIRED)
#
#if (NOT WAYLAND_CLIENT_FOUND)
#    message(FATAL_ERROR "Could not find wayland-client")
#endif()
#
#message(STATUS ${WAYLAND_CLIENT_INCLUDE_DIR})
#message(STATUS ${WAYLAND_CLIENT_LIBRARIES})

set(HELLO_WAYLAND_SOURCE_FILES
    main.cpp
    Application.cpp)
set(HELLO_WAYLAND_HEADER_FILES
    Application.h)
set(HELLO_WAYLAND_DATA_FILES
    images.bin)
set(HELLO_WAYLAND_LIBS
    wayland-classes
    wayland-client-shared)

add_executable(${PROJECT_NAME} ${HELLO_WAYLAND_SOURCE_FILES} ${HELLO_WAYLAND_HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${HELLO_WAYLAND_LIBS})
add_dependencies(${PROJECT_NAME} wayland-classes)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${DATA_FILES} $<TARGET_FILE_DIR:${PROJECT_NAME}>)

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
