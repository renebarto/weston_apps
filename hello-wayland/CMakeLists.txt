project(hello-wayland)

find_package(Wayland REQUIRED)

if (NOT WAYLAND_CLIENT_FOUND)
    message(FATAL_ERROR "Could not find wayland-client")
endif()

message(STATUS ${WAYLAND_CLIENT_INCLUDE_DIR})
message(STATUS ${WAYLAND_CLIENT_LIBRARIES})

set(SOURCE_FILES
    main.cpp
    Registry.cpp
    Display.cpp
    ShmPool.cpp
    Surface.cpp
    Buffer.cpp
    Pointer.cpp
    helpers.c)
set(HEADER_FILES
    Registry.h
    Display.h
    ShmPool.h
    Surface.h
    Buffer.h
    Pointer.h
    helpers.h)
set(DATA_FILES
        images.bin)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${WAYLAND_CLIENT_LIBRARIES})
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${DATA_FILES} $<TARGET_FILE_DIR:${PROJECT_NAME}>)

