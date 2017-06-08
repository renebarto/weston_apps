project(wayland-protocols-1.7)


set(WAYLAND_SCANNER_VERSION 1.13.0)
set(WAYLAND_SCANNER_REQUIRED_VERSION ${WAYLAND_PROTOCOLS_VERSION})
find_package(WaylandScanner REQUIRED)

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

SET(stable_protocols
    stable/presentation-time/presentation-time.xml
    stable/viewporter/viewporter.xml)

function(wayland_scanner in)
    foreach(VAL ${${in}})
        message(STATUS "${VAL}")
        install(FILES ${VAL} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/wayland-protocols)
    endforeach()
endfunction()

wayland_scanner(unstable_protocols)
wayland_scanner(stable_protocols)

#set(SOURCE_FILES main.cpp)
#add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#target_include_directories(${PROJECT_NAME} PRIVATE ${EGL_INCLUDE_DIRS} ${WAYLAND_CLIENT_INCLUDE_DIR} ${WAYLAND_EGL_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARY} ${OPENGL_LIBRARY} ${EGL_LIBRARIES} ${WAYLAND_CLIENT_LIBRARIES} ${WAYLAND_EGL_LIBRARIES})
#
#message(STATUS "Installing targets ${PROJECT_NAME}")
#install(TARGETS ${PROJECT_NAME}
#    RUNTIME DESTINATION bin
#    LIBRARY DESTINATION lib
#    ARCHIVE DESTINATION lib)

