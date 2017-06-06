project(weston-texture)

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

set(SOURCE_FILES tutorial05.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${EGL_INCLUDE_DIRS} ${WAYLAND_CLIENT_INCLUDE_DIR} ${WAYLAND_EGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARY} ${OPENGL_LIBRARY} ${EGL_LIBRARIES} ${WAYLAND_CLIENT_LIBRARIES} ${WAYLAND_EGL_LIBRARIES})

message(STATUS "Installing targets ${PROJECT_NAME}")
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

