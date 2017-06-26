project(wayland-classes)

set(WAYLAND_CLASSES_DEFINES
    WAYLAND_CLASSES_DEBUG)
set(WAYLAND_CLASSES_SOURCE_FILES
    Compositor.cpp
    Cursor.cpp
    Registry.cpp
    Display.cpp
    Shm.cpp
    ShmPool.cpp
    Surface.cpp
    Buffer.cpp
    Pointer.cpp
    Keyboard.cpp
    Touch.cpp
    Seat.cpp
    Region.cpp
    Callback.cpp)
set(WAYLAND_CLASSES_HEADER_FILES
    Compositor.h
    Cursor.h
    Registry.h
    Display.h
    Shm.h
    ShmPool.h
    Surface.h
    Buffer.h
    Pointer.h
    Keyboard.h
    Touch.h
    Seat.h
    Region.h
    Callback.h
    IRegistryListener.h
    IPointerListener.h
    IKeyboardListener.h
    ITouchListener.h
    ISeatListener.h)
set(WAYLAND_CLASSES_INCLUDE_DIRS
    .
    ${SYSTEM_INCLUDES})
set(WAYLAND_CLASSES_LIBS
    wayland-client-shared
    wayland-cursor-shared)

add_library(${PROJECT_NAME} SHARED ${WAYLAND_CLASSES_SOURCE_FILES} ${WAYLAND_CLASSES_HEADER_FILES})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${WAYLAND_CLASSES_DEFINES})
target_include_directories(${PROJECT_NAME} PUBLIC ${WAYLAND_CLASSES_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${WAYLAND_CLASSES_LIBS})
add_dependencies(${PROJECT_NAME} wayland-client-shared)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "${LINK_RPATH}")

include(show_target_properties)
show_target_properties(${PROJECT_NAME})

add_library(${PROJECT_NAME}-static STATIC ${WAYLAND_CLASSES_SOURCE_FILES} ${WAYLAND_CLASSES_HEADER_FILES})
target_compile_definitions(${PROJECT_NAME}-static PUBLIC ${WAYLAND_CLASSES_DEFINES})
target_include_directories(${PROJECT_NAME}-static PUBLIC ${WAYLAND_CLASSES_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}-static ${WAYLAND_CLASSES_LIBS})
add_dependencies(${PROJECT_NAME}-static wayland-client-shared)

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
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})
