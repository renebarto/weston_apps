project(weston)

set(WESTON_VERSION_MAJOR 1)
set(WESTON_VERSION_MINOR 12)
set(WESTON_VERSION_MICRO 0)
set(WESTON_VERSION ${WESTON_VERSION_MAJOR}.${WESTON_VERSION_MINOR}.${WESTON_VERSION_MICRO})
set(WESTON_REQUIRED_VERSION ${WESTON_VERSION})
set(WESTON_NAME ${PROJECT_NAME})
set(WESTON_BASE ${WESTON_NAME}-${WESTON_VERSION})

find_package(Pixman REQUIRED)
find_package(Weston QUIET)

set(WESTON_COMPILE_DEFINITIONS HAVE_CONFIG_H)
set(WESTON_COMPILER_OPTIONS)
set(WESTON_INCLUDES . .. libweston shared ${CMAKE_INSTALL_PREFIX}/include)
message(STATUS "WESTON_INCLUDES: ${WESTON_INCLUDES}")

# weston-desktop-shell
set(WESTON_DESKTOP_SHELL_COMPILE_DEFINITIONS)
set(WESTON_DESKTOP_SHELL_COMPILER_OPTIONS ${WESTON_COMPILER_OPTIONS})
set(WESTON_DESKTOP_SHELL_SOURCES
    desktop-shell/exposay.c
    desktop-shell/input-panel.c
    desktop-shell/shell.c
    desktop-shell/shell.h)
set(WESTON_DESKTOP_SHELL_SOURCES_NODIST)
set(WESTON_DESKTOP_SHELL_INCLUDE_DIRS
    ${WESTON_INCLUDES}
    ${PIXMAN_INCLUDE_DIR})
set(WESTON_DESKTOP_SHELL_LINK_OPTIONS
    )
set(WESTON_DESKTOP_SHELL_LIBS
    )
message(STATUS "WESTON_DESKTOP_SHELL_INCLUDE_DIRS: ${WESTON_DESKTOP_SHELL_INCLUDE_DIRS}")

add_executable(weston-desktop-shell
    ${WESTON_DESKTOP_SHELL_SOURCES} ${WESTON_DESKTOP_SHELL_SOURCES_NODIST})
target_compile_definitions(weston-desktop-shell PRIVATE ${WESTON_DESKTOP_SHELL_COMPILE_DEFINITIONS})
target_compile_options(weston-desktop-shell PRIVATE ${WESTON_DESKTOP_SHELL_COMPILER_OPTIONS})
target_include_directories(weston-desktop-shell PRIVATE ${WESTON_DESKTOP_SHELL_INCLUDE_DIRS})
set_target_properties(weston-desktop-shell PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(weston-desktop-shell PRIVATE ${WESTON_DESKTOP_SHELL_LIBS})
if(NOT "${WESTON_DESKTOP_SHELL_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(weston-desktop-shell PROPERTIES LINK_FLAGS ${WESTON_DESKTOP_SHELL_LINK_OPTIONS})
endif()

# weston-fullscreen-shell
set(WESTON_FULLSCREEN_SHELL_COMPILE_DEFINITIONS)
set(WESTON_FULLSCREEN_SHELL_COMPILER_OPTIONS ${WESTON_COMPILER_OPTIONS})
set(WESTON_FULLSCREEN_SHELL_SOURCES
    fullscreen-shell/fullscreen-shell.c)
set(WESTON_FULLSCREEN_SHELL_SOURCES_NODIST)
set(WESTON_FULLSCREEN_SHELL_INCLUDE_DIRS
    ${WESTON_INCLUDES}
    ${PIXMAN_INCLUDE_DIR})
set(WESTON_FULLSCREEN_SHELL_LINK_OPTIONS
    )
set(WESTON_FULLSCREEN_SHELL_LIBS
    )

add_executable(weston-fullscreen-shell
    ${WESTON_FULLSCREEN_SHELL_SOURCES} ${WESTON_FULLSCREEN_SHELL_SOURCES_NODIST})
target_compile_definitions(weston-fullscreen-shell PRIVATE ${WESTON_FULLSCREEN_SHELL_COMPILE_DEFINITIONS})
target_compile_options(weston-fullscreen-shell PRIVATE ${WESTON_FULLSCREEN_SHELL_COMPILER_OPTIONS})
target_include_directories(weston-fullscreen-shell PRIVATE ${WESTON_FULLSCREEN_SHELL_INCLUDE_DIRS})
set_target_properties(weston-fullscreen-shell PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(weston-fullscreen-shell PRIVATE ${WESTON_FULLSCREEN_SHELL_LIBS})
if(NOT "${WESTON_FULLSCREEN_SHELL_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(weston-fullscreen-shell PROPERTIES LINK_FLAGS ${WESTON_FULLSCREEN_SHELL_LINK_OPTIONS})
endif()

add_custom_target(weston)

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

add_custom_target(${WESTON_BASE}
    DEPENDS weston-fullscreen-shell weston-desktop-shell)

add_dependencies(install_${PROJECT_NAME}
    ${WESTON_BASE})

set(bindir "${CMAKE_INSTALL_PREFIX}/bin")
set(abs_top_builddir "${CMAKE_INSTALL_PREFIX}/bin")
set(libexecdir "${CMAKE_INSTALL_PREFIX}/libexec")

configure_file(weston.ini.in ${CMAKE_CURRENT_SOURCE_DIR}/weston.ini @ONLY)

set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix "\${prefix}")
set(libdir "\${exec_prefix}/lib")
set(includedir "\${prefix}/include")
set(datarootdir "\${prefix}/share")
set(libexecdir "\${exec_prefix}/libexec")
set(PACKAGE "${PROJECT_NAME}")
set(LIBWESTON_MAJOR ${WESTON_VERSION_MAJOR})

configure_file(compositor/weston.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/compositor/weston.pc @ONLY)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/weston.ini
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
    COMPONENT ${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/compositor/wayland-client.pc
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
    COMPONENT ${PROJECT_NAME})

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/data/background.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/border.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/fullscreen.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/home.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_editor.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_flower.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_ivi_clickdot.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_ivi_flower.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_ivi_simple-egl.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_ivi_simple-shm.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_ivi_smoke.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_terminal.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_window.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/panel.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/pattern.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/random.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/sidebyside.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/sign_close.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/sign_maximize.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/sign_minimize.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/terminal.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/tiling.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/wayland.png
    ${CMAKE_CURRENT_SOURCE_DIR}/data/wayland.svg
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/weston
    COMPONENT ${PROJECT_NAME})
