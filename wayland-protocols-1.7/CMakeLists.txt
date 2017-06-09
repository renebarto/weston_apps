project(wayland-protocols)

set(WAYLAND_SCANNER_VERSION 1.13.0)
set(WAYLAND_SCANNER_REQUIRED_VERSION ${WAYLAND_SCANNER_VERSION})
set(WAYLAND_VERSION 1.13.0)
set(WAYLAND_REQUIRED_VERSION ${WAYLAND_VERSION})

set(WAYLAND_PROTOCOLS_VERSION 1.7)
set(WAYLAND_PROTOCOLS_REQUIRED_VERSION ${WAYLAND_PROTOCOLS_VERSION})
set(WAYLAND_PROTOCOLS_NAME ${PROJECT_NAME})
set(WAYLAND_PROTOCOLS_BASE ${WAYLAND_PROTOCOLS_NAME}-${WAYLAND_PROTOCOLS_VERSION})

find_package(Wayland REQUIRED)
find_package(WaylandScanner REQUIRED)
find_package(WaylandProtocols QUIET)

set (unstable_protocols
    unstable/pointer-gestures/pointer-gestures-unstable-v1.xml
    unstable/fullscreen-shell/fullscreen-shell-unstable-v1.xml
    unstable/linux-dmabuf/linux-dmabuf-unstable-v1.xml
    unstable/text-input/text-input-unstable-v1.xml
    unstable/input-method/input-method-unstable-v1.xml
    unstable/xdg-shell/xdg-shell-unstable-v5.xml
    unstable/xdg-shell/xdg-shell-unstable-v6.xml
    unstable/relative-pointer/relative-pointer-unstable-v1.xml
    unstable/pointer-constraints/pointer-constraints-unstable-v1.xml
    unstable/tablet/tablet-unstable-v1.xml
    unstable/tablet/tablet-unstable-v2.xml
    unstable/xdg-foreign/xdg-foreign-unstable-v1.xml
    unstable/idle-inhibit/idle-inhibit-unstable-v1.xml)

set(stable_protocols
    stable/presentation-time/presentation-time.xml
    stable/viewporter/viewporter.xml)

function(wayland_scanner in)
    foreach(VAL ${${in}})
        message(STATUS "${VAL}")
        install(FILES ${VAL} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/wayland-protocols)
    endforeach()
endfunction()

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

set(prefix ${CMAKE_INSTALL_PREFIX})
set(datarootdir "\${prefix}/share")
set(datadir "\${datarootdir}")
set(PACKAGE "${PROJECT_NAME}")

configure_file(wayland-protocols.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/wayland-protocols.pc)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/wayland-protocols.pc
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pkgconfig
    COMPONENT ${PROJECT_NAME})

wayland_scanner(unstable_protocols)
wayland_scanner(stable_protocols)

add_custom_target(${WAYLAND_PROTOCOLS_BASE})

add_dependencies(install_${PROJECT_NAME}
    ${WAYLAND_PROTOCOLS_BASE})
