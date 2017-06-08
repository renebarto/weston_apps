project(hello-wayland-org)

find_package(Wayland REQUIRED)

if (NOT WAYLAND_CLIENT_FOUND)
    message(FATAL_ERROR "Could not find wayland-client")
endif()

message(STATUS ${WAYLAND_CLIENT_INCLUDE_DIR})
message(STATUS ${WAYLAND_CLIENT_LIBRARIES})

set(SOURCE_FILES
        hello_wayland.c helpers.c)
set(HEADER_FILES
        helpers.h)
set(DATA_FILES
        images.bin)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${WAYLAND_CLIENT_LIBRARIES})
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${DATA_FILES} $<TARGET_FILE_DIR:${PROJECT_NAME}>)

include(show_target_properties)
show_target_properties(${PROJECT_NAME})