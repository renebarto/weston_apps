project(westeros)

set(WESTEROS_VERSION_MAJOR 1)
set(WESTEROS_VERSION_MINOR 0)
set(WESTEROS_VERSION_MICRO 0)
set(WESTEROS_VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
set(WESTEROS_REQUIRED_VERSION ${WESTEROS_VERSION})
set(WESTEROS_NAME ${PROJECT_NAME})
set(WESTEROS_BASE ${WESTEROS_NAME}-${WESTEROS_VERSION})

# Version for a.o. libwesteros_gl
set(WESTEROS_DUMMY_VERSION_MAJOR 0)
set(WESTEROS_DUMMY_VERSION_MINOR 0)
set(WESTEROS_DUMMY_VERSION_MICRO 0)

set(ENABLE_XDG_V5 ON)
set(ENABLE_WESTEROS_APP ON)
set(ENABLE_WESTEROS_TEST ON)
set(ENABLE_WESTEROS_PLAYER OFF)
set(ENABLE_WESTEROS_SBPROTOCOL ON)
set(ENABLE_WESTEROS_RENDERGL ON)

include(show_target_properties)

if (${WESTEROS_PLATFORM_KYLIN})
    set(OPENGL_LIBRARY mali)
else()
    find_package(OpenGL REQUIRED)
endif()
#find_package(Pixman REQUIRED)
find_package(LibXKBCommon REQUIRED)
#find_package(LibInput REQUIRED)
find_package(EGL REQUIRED)
find_package(GLES REQUIRED)
find_package(FreeGLUT REQUIRED)
#find_package(Eudev REQUIRED)
find_package(LibDRM REQUIRED)
find_package(LibGBM REQUIRED)
#find_package(Mtdev REQUIRED)
#find_package(LibFFI REQUIRED)
#find_package(LibEvdev REQUIRED)
find_package(GLEW QUIET)
find_package(Wayland QUIET)
find_package(WaylandEGL QUIET)
find_package(WaylandScanner QUIET)
find_package(LibX11 QUIET)
#find_package(Cairo REQUIRED)
#find_package(Fontconfig REQUIRED)
#find_package(Freetype REQUIRED)
#find_package(LibPNG REQUIRED)
#find_package(LibJPEGTurbo REQUIRED)
#find_package(LibGlib2 REQUIRED)
#find_package(EXPAT REQUIRED)
#find_package(LibXcb REQUIRED)
#find_package(LibXcbDri2 REQUIRED)
#find_package(LibXcbGlx REQUIRED)
#find_package(LibXcbRender REQUIRED)
#find_package(LibXcbShm REQUIRED)
#find_package(LibXcbXfixes REQUIRED)
#find_package(LibXau REQUIRED)
#find_package(LibXdmcp REQUIRED)
#find_package(Weston QUIET)
find_package(GStreamer1 QUIET)

if (NOT WAYLAND_FOUND)
    set(WAYLAND_CLIENT_LIBRARIES wayland-client-shared)
    set(WAYLAND_SERVER_LIBRARIES wayland-server-shared)
    set(WAYLAND_CURSOR_LIBRARIES wayland-cursor-shared)
endif()
if (NOT WAYLAND_SCANNER_FOUND)
    set(WAYLAND_SCANNER_PATH $<TARGET_FILE:wayland-scanner>)
endif()

# Create protocol sources
# simplebuffer/protocol/simple-buffer.xml
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simplebuffer/protocol/simplebuffer-client-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} client-header < simplebuffer/protocol/simple-buffer.xml > simplebuffer/protocol/simplebuffer-client-protocol.h
#    COMMAND $<TARGET_FILE:wayland-scanner> client-header < simplebuffer/protocol/simple-buffer.xml > simplebuffer/protocol/simplebuffer-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simplebuffer/protocol/simplebuffer-server-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} server-header < simplebuffer/protocol/simple-buffer.xml > simplebuffer/protocol/simplebuffer-server-protocol.h
#    COMMAND $<TARGET_FILE:wayland-scanner> server-header < simplebuffer/protocol/simple-buffer.xml > simplebuffer/protocol/simplebuffer-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simplebuffer/protocol/simplebuffer-protocol.c
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} code < simplebuffer/protocol/simple-buffer.xml > simplebuffer/protocol/simplebuffer-protocol.c
#    COMMAND $<TARGET_FILE:wayland-scanner> code < simplebuffer/protocol/simple-buffer.xml > simplebuffer/protocol/simplebuffer-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

# simpleshell/protocol/simple-buffer.xml
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simpleshell/protocol/simpleshell-client-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} client-header < simpleshell/protocol/simpleshell.xml > simpleshell/protocol/simpleshell-client-protocol.h
#    COMMAND $<TARGET_FILE:wayland-scanner> client-header < simpleshell/protocol/simpleshell.xml > simpleshell/protocol/simpleshell-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simpleshell/protocol/simpleshell-server-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} server-header < simpleshell/protocol/simpleshell.xml > simpleshell/protocol/simpleshell-server-protocol.h
#    COMMAND $<TARGET_FILE:wayland-scanner> server-header < simpleshell/protocol/simpleshell.xml > simpleshell/protocol/simpleshell-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simpleshell/protocol/simpleshell-protocol.c
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} code < simpleshell/protocol/simpleshell.xml > simpleshell/protocol/simpleshell-protocol.c
#    COMMAND $<TARGET_FILE:wayland-scanner> code < simpleshell/protocol/simpleshell.xml > simpleshell/protocol/simpleshell-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

# version4/xdg-shell.xml
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/version4/xdg-shell-client-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} client-header < protocol/version4/xdg-shell.xml > protocol/version4/xdg-shell-client-protocol.h
#    COMMAND $<TARGET_FILE:wayland-scanner> client-header < protocol/version4/xdg-shell.xml > protocol/version4/xdg-shell-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/version4/xdg-shell-server-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} server-header < protocol/version4/xdg-shell.xml > protocol/version4/xdg-shell-server-protocol.h
#    COMMAND $<TARGET_FILE:wayland-scanner> server-header < protocol/version4/xdg-shell.xml > protocol/version4/xdg-shell-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/version4/xdg-shell-protocol.c
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} code < protocol/version4/xdg-shell.xml > protocol/version4/xdg-shell-protocol.c
#    COMMAND $<TARGET_FILE:wayland-scanner> code < protocol/version4/xdg-shell.xml > protocol/version4/xdg-shell-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

# version5/xdg-shell.xml
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/version5/xdg-shell-client-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} client-header < protocol/version5/xdg-shell.xml > protocol/version5/xdg-shell-client-protocol.h
#    COMMAND $<TARGET_FILE:wayland-scanner> client-header < protocol/version5/xdg-shell.xml > protocol/version5/xdg-shell-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/version5/xdg-shell-server-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} server-header < protocol/version5/xdg-shell.xml > protocol/version5/xdg-shell-server-protocol.h
#    COMMAND $<TARGET_FILE:wayland-scanner> server-header < protocol/version5/xdg-shell.xml > protocol/version5/xdg-shell-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/version5/xdg-shell-protocol.c
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} code < protocol/version5/xdg-shell.xml > protocol/version5/xdg-shell-protocol.c
#    COMMAND $<TARGET_FILE:wayland-scanner> code < protocol/version5/xdg-shell.xml > protocol/version5/xdg-shell-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

# vpc.xml
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/vpc-client-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} client-header < protocol/vpc.xml > protocol/vpc-client-protocol.h
#    COMMAND $<TARGET_FILE:wayland-scanner> client-header < protocol/vpc.xml > protocol/vpc-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/vpc-server-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} server-header < protocol/vpc.xml > protocol/vpc-server-protocol.h
#    COMMAND $<TARGET_FILE:wayland-scanner> server-header < protocol/vpc.xml > protocol/vpc-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/vpc-protocol.c
#    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND ${WAYLAND_SCANNER_PATH} code < protocol/vpc.xml > protocol/vpc-protocol.c
#    COMMAND $<TARGET_FILE:wayland-scanner> code < protocol/vpc.xml > protocol/vpc-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

set(WESTEROS_COMPILE_DEFINITIONS
    ${WAYLAND_COMPILE_DEFINITIONS}
    _GNU_SOURCE
    )
set(WESTEROS_COMPILER_OPTIONS -Wall -Wextra
    ${WAYLAND_COMPILER_OPTIONS}
#    -Wno-unused-parameter -Wno-shift-negative-value -Wno-missing-field-initializers
#    -fvisibility=hidden -Wstrict-prototypes -Wmissing-prototypes -Wsign-compare

    )
set(WESTEROS_INCLUDES
    .
    simplebuffer/protocol
    simplebuffer
    simpleshell/protocol
    simpleshell
    protocol
    ${SYSTEM_INCLUDES})

if (GLEW_FOUND AND GLESV2_FOUND AND WESTEROS_PLATFORM_RPI)
    list(APPEND WESTEROS_COMPILE_DEFINITIONS WESTEROS_PLATFORM_RPI)
    list(APPEND WESTEROS_INCLUDES rpi/westeros-gl)
    set(WESTEROS_OPENGL_LIBS
        westeros_gl
        )
elseif (GLEW_FOUND AND GLESV2_FOUND AND WESTEROS_PLATFORM_KYLIN)
    list(APPEND WESTEROS_COMPILE_DEFINITIONS WESTEROS_PLATFORM_KYLIN WESTEROS_PLATFORM_EMBEDDED)
    list(APPEND WESTEROS_INCLUDES kylin/westeros-gl)
    set(WESTEROS_OPENGL_LIBS
        westeros_gl
        )
else()
    list(APPEND WESTEROS_COMPILE_DEFINITIONS WESTEROS_PLATFORM_EMBEDDED)
    list(APPEND WESTEROS_INCLUDES
        drm/westeros-gl
        ${LIBDRM_INCLUDE_DIRS}
        ${LIBGBM_INCLUDE_DIRS})
    set(WESTEROS_OPENGL_LIBS
        westeros_gl
        ${FREEGLUT_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${LIBDRM_LIBRARIES}
        ${LIBGBM_LIBRARIES}
        )
endif()

if (WAYLAND_EGL_FOUND)
    message(STATUS "Building with Wayland-EGL: ${WAYLAND_EGL_LIBRARIES} ${GLESV2_LIBRARIES}")
    list(APPEND WESTEROS_COMPILE_DEFINITIONS WESTEROS_HAVE_WAYLAND_EGL)
    set(WESTEROS_EGL_LIBS
        ${WAYLAND_EGL_LIBRARIES} ${GLESV2_LIBRARIES})
else()
    set(WESTEROS_EGL_LIBS
        westeros_egl)
endif()

if(ENABLE_XDG_V4)
    list(APPEND WESTEROS_COMPILE_DEFINITIONS USE_XDG_VERSION4)
    list(APPEND WESTEROS_INCLUDES protocol/version4)
    list(APPEND WESTEROS_XDG_PROTOCOL_SOURCES protocol/version4/xdg-shell-server-protocol.h protocol/version4/xdg-shell-protocol.c)
endif()

if(ENABLE_XDG_V5)
    list(APPEND WESTEROS_COMPILE_DEFINITIONS USE_XDG_VERSION5)
    list(APPEND WESTEROS_INCLUDES protocol/version5)
    list(APPEND WESTEROS_XDG_PROTOCOL_SOURCES protocol/version5/xdg-shell-server-protocol.h protocol/version5/xdg-shell-protocol.c)
endif()

if (ENABLE_WESTEROS_SBPROTOCOL)
    list(APPEND WESTEROS_COMPILE_DEFINITIONS ENABLE_SBPROTOCOL)
endif()

if (ENABLE_WESTEROS_RENDERGL)
endif()

message(STATUS "WESTEROS_COMPILE_DEFINITIONS: ${WESTEROS_COMPILE_DEFINITIONS}")
message(STATUS "WESTEROS_INCLUDES           : ${WESTEROS_INCLUDES}")
message(STATUS "WESTEROS_EGL_LIBS           : ${WESTEROS_EGL_LIBS}")

# westeros_simplebuffer_client
set(WESTEROS_SIMPLEBUFFER_CLIENT_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_SIMPLEBUFFER_CLIENT_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_SIMPLEBUFFER_CLIENT_SOURCES
    simplebuffer/protocol/simplebuffer-client-protocol.h
    simplebuffer/protocol/simplebuffer-protocol.c
    )
set(WESTEROS_SIMPLEBUFFER_CLIENT_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    )
set(WESTEROS_SIMPLEBUFFER_CLIENT_LIBS
    ${WAYLAND_CLIENT_LIBRARIES}
    )

message(STATUS "WESTEROS_SIMPLEBUFFER_CLIENT_INCLUDE_DIRS: ${WESTEROS_SIMPLEBUFFER_CLIENT_INCLUDE_DIRS}")
message(STATUS "WESTEROS_SIMPLEBUFFER_CLIENT_LIBS: ${WESTEROS_SIMPLEBUFFER_CLIENT_LIBS}")

add_library(westeros_simplebuffer_client STATIC ${WESTEROS_SIMPLEBUFFER_CLIENT_SOURCES})
target_compile_definitions(westeros_simplebuffer_client PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_COMPILE_DEFINITIONS})
target_compile_options(westeros_simplebuffer_client PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_COMPILER_OPTIONS})
target_include_directories(westeros_simplebuffer_client PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_INCLUDE_DIRS})
target_link_libraries(westeros_simplebuffer_client PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_LIBS})
set_target_properties(westeros_simplebuffer_client PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_simplebuffer_client PROPERTIES LINK_FLAGS "-rpath ../lib")

show_target_properties(westeros_simplebuffer_client)

add_library(westeros_simplebuffer_client-shared SHARED ${WESTEROS_SIMPLEBUFFER_CLIENT_SOURCES})
target_compile_definitions(westeros_simplebuffer_client-shared PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_COMPILE_DEFINITIONS})
target_compile_options(westeros_simplebuffer_client-shared PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_COMPILER_OPTIONS})
target_include_directories(westeros_simplebuffer_client-shared PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_INCLUDE_DIRS})
target_link_libraries(westeros_simplebuffer_client-shared PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_LIBS})
set_target_properties(westeros_simplebuffer_client-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_simplebuffer_client-shared PROPERTIES LINK_FLAGS "${LINK_RPATH}")
#set_target_properties(westeros_simplebuffer_client-shared PROPERTIES LINK_FLAGS "${LINK_WHOLE_LIB} ${CMAKE_CURRENT_BINARY_DIR}/libshared.a ${LINK_NO_WHOLE_LIB} ${LINK_RPATH}")
set_property(TARGET westeros_simplebuffer_client-shared PROPERTY VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
set_property(TARGET westeros_simplebuffer_client-shared PROPERTY SOVERSION ${WESTEROS_VERSION_MAJOR})
set_property(TARGET westeros_simplebuffer_client-shared PROPERTY OUTPUT_NAME westeros_simplebuffer_client)

show_target_properties(westeros_simplebuffer_client-shared)

# westeros_simplebuffer_server
set(WESTEROS_SIMPLEBUFFER_SERVER_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_SIMPLEBUFFER_SERVER_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_SIMPLEBUFFER_SERVER_SOURCES
    simplebuffer/protocol/simplebuffer-server-protocol.h
    simplebuffer/protocol/simplebuffer-protocol.c
    simplebuffer/westeros-simplebuffer.cpp
    simplebuffer/westeros-simplebuffer.h
    )
set(WESTEROS_SIMPLEBUFFER_SERVER_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    )
set(WESTEROS_SIMPLEBUFFER_SERVER_LIBS
    ${WAYLAND_SERVER_LIBRARIES}
    )
message(STATUS "WESTEROS_SIMPLEBUFFER_SERVER_INCLUDE_DIRS: ${WESTEROS_SIMPLEBUFFER_SERVER_INCLUDE_DIRS}")
message(STATUS "WESTEROS_SIMPLEBUFFER_SERVER_LIBS: ${WESTEROS_SIMPLEBUFFER_SERVER_LIBS}")

add_library(westeros_simplebuffer_server STATIC ${WESTEROS_SIMPLEBUFFER_SERVER_SOURCES})
target_compile_definitions(westeros_simplebuffer_server PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_COMPILE_DEFINITIONS})
target_compile_options(westeros_simplebuffer_server PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_COMPILER_OPTIONS})
target_include_directories(westeros_simplebuffer_server PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_INCLUDE_DIRS})
target_link_libraries(westeros_simplebuffer_server PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_LIBS})
set_target_properties(westeros_simplebuffer_server PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_simplebuffer_server PROPERTIES LINK_FLAGS "-rpath ../lib")

show_target_properties(westeros_simplebuffer_server)

add_library(westeros_simplebuffer_server-shared SHARED ${WESTEROS_SIMPLEBUFFER_SERVER_SOURCES})
target_compile_definitions(westeros_simplebuffer_server-shared PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_COMPILE_DEFINITIONS})
target_compile_options(westeros_simplebuffer_server-shared PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_COMPILER_OPTIONS})
target_include_directories(westeros_simplebuffer_server-shared PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_INCLUDE_DIRS})
target_link_libraries(westeros_simplebuffer_server-shared PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_LIBS})
set_target_properties(westeros_simplebuffer_server-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_simplebuffer_server-shared PROPERTIES LINK_FLAGS "${LINK_RPATH}")
#set_target_properties(westeros_simplebuffer_server-shared PROPERTIES LINK_FLAGS "${LINK_WHOLE_LIB} ${CMAKE_CURRENT_BINARY_DIR}/libshared.a ${LINK_NO_WHOLE_LIB} ${LINK_RPATH}")
set_property(TARGET westeros_simplebuffer_server-shared PROPERTY VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
set_property(TARGET westeros_simplebuffer_server-shared PROPERTY SOVERSION ${WESTEROS_VERSION_MAJOR})
set_property(TARGET westeros_simplebuffer_server-shared PROPERTY OUTPUT_NAME westeros_simplebuffer_server)

show_target_properties(westeros_simplebuffer_server-shared)

# westeros_simpleshell_client
set(WESTEROS_SIMPLESHELL_CLIENT_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_SIMPLESHELL_CLIENT_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_SIMPLESHELL_CLIENT_SOURCES
    simpleshell/protocol/simpleshell-client-protocol.h
    simpleshell/protocol/simpleshell-protocol.c
    )
set(WESTEROS_SIMPLESHELL_CLIENT_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    )
set(WESTEROS_SIMPLESHELL_CLIENT_LIBS
    ${WAYLAND_CLIENT_LIBRARIES}
    )
message(STATUS "WESTEROS_SIMPLESHELL_CLIENT_INCLUDE_DIRS: ${WESTEROS_SIMPLESHELL_CLIENT_INCLUDE_DIRS}")
message(STATUS "WESTEROS_SIMPLESHELL_CLIENT_LIBS: ${WESTEROS_SIMPLESHELL_CLIENT_LIBS}")

add_library(westeros_simpleshell_client STATIC ${WESTEROS_SIMPLESHELL_CLIENT_SOURCES})
target_compile_definitions(westeros_simpleshell_client PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_COMPILE_DEFINITIONS})
target_compile_options(westeros_simpleshell_client PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_COMPILER_OPTIONS})
target_include_directories(westeros_simpleshell_client PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_INCLUDE_DIRS})
target_link_libraries(westeros_simpleshell_client PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_LIBS})
set_target_properties(westeros_simpleshell_client PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_simpleshell_client PROPERTIES LINK_FLAGS "-rpath ../lib")

show_target_properties(westeros_simpleshell_client)

add_library(westeros_simpleshell_client-shared SHARED ${WESTEROS_SIMPLESHELL_CLIENT_SOURCES})
target_compile_definitions(westeros_simpleshell_client-shared PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_COMPILE_DEFINITIONS})
target_compile_options(westeros_simpleshell_client-shared PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_COMPILER_OPTIONS})
target_include_directories(westeros_simpleshell_client-shared PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_INCLUDE_DIRS})
target_link_libraries(westeros_simpleshell_client-shared PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_LIBS})
set_target_properties(westeros_simpleshell_client-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_simpleshell_client-shared PROPERTIES LINK_FLAGS "${LINK_RPATH}")
#set_target_properties(westeros_simpleshell_client-shared PROPERTIES LINK_FLAGS "${LINK_WHOLE_LIB} ${CMAKE_CURRENT_BINARY_DIR}/libshared.a ${LINK_NO_WHOLE_LIB} ${LINK_RPATH}")
set_property(TARGET westeros_simpleshell_client-shared PROPERTY VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
set_property(TARGET westeros_simpleshell_client-shared PROPERTY SOVERSION ${WESTEROS_VERSION_MAJOR})
set_property(TARGET westeros_simpleshell_client-shared PROPERTY OUTPUT_NAME westeros_simpleshell_client)

show_target_properties(westeros_simpleshell_client-shared)

# westeros_simpleshell_server
set(WESTEROS_SIMPLESHELL_SERVER_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_SIMPLESHELL_SERVER_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_SIMPLESHELL_SERVER_SOURCES
    simpleshell/protocol/simpleshell-server-protocol.h
    simpleshell/protocol/simpleshell-protocol.c
    simpleshell/westeros-simpleshell.cpp
    simpleshell/westeros-simpleshell.h
    )
set(WESTEROS_SIMPLESHELL_SERVER_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    )
set(WESTEROS_SIMPLESHELL_SERVER_LIBS
    ${WAYLAND_SERVER_LIBRARIES}
    )
message(STATUS "WESTEROS_SIMPLESHELL_SERVER_INCLUDE_DIRS: ${WESTEROS_SIMPLESHELL_SERVER_INCLUDE_DIRS}")
message(STATUS "WESTEROS_SIMPLESHELL_SERVER_LIBS: ${WESTEROS_SIMPLESHELL_SERVER_LIBS}")

add_library(westeros_simpleshell_server STATIC ${WESTEROS_SIMPLESHELL_SERVER_SOURCES})
target_compile_definitions(westeros_simpleshell_server PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_COMPILE_DEFINITIONS})
target_compile_options(westeros_simpleshell_server PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_COMPILER_OPTIONS})
target_include_directories(westeros_simpleshell_server PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_INCLUDE_DIRS})
target_link_libraries(westeros_simpleshell_server PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_LIBS})
set_target_properties(westeros_simpleshell_server PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_simpleshell_server PROPERTIES LINK_FLAGS "-rpath ../lib")

show_target_properties(westeros_simpleshell_server)

add_library(westeros_simpleshell_server-shared SHARED ${WESTEROS_SIMPLESHELL_SERVER_SOURCES})
target_compile_definitions(westeros_simpleshell_server-shared PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_COMPILE_DEFINITIONS})
target_compile_options(westeros_simpleshell_server-shared PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_COMPILER_OPTIONS})
target_include_directories(westeros_simpleshell_server-shared PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_INCLUDE_DIRS})
target_link_libraries(westeros_simpleshell_server-shared PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_LIBS})
set_target_properties(westeros_simpleshell_server-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_simpleshell_server-shared PROPERTIES LINK_FLAGS "${LINK_RPATH}")
#set_target_properties(westeros_simpleshell_server-shared PROPERTIES LINK_FLAGS "${LINK_WHOLE_LIB} ${CMAKE_CURRENT_BINARY_DIR}/libshared.a ${LINK_NO_WHOLE_LIB} ${LINK_RPATH}")
set_property(TARGET westeros_simpleshell_server-shared PROPERTY VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
set_property(TARGET westeros_simpleshell_server-shared PROPERTY SOVERSION ${WESTEROS_VERSION_MAJOR})
set_property(TARGET westeros_simpleshell_server-shared PROPERTY OUTPUT_NAME westeros_simpleshell_server)

show_target_properties(westeros_simpleshell_server-shared)

if (WESTEROS_PLATFORM_RPI)
# westeros_gl-rpi
set(WESTEROS_GL_RPI_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_GL_RPI_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_GL_RPI_SOURCES
    rpi/westeros-gl/westeros-gl.cpp
    rpi/westeros-gl/westeros-gl.h
    rpi/westeros-render-dispmanx/westeros-render-dispmanx.cpp)
set(WESTEROS_GL_RPI_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    )
set(WESTEROS_GL_RPI_LIBS
    )
message(STATUS "WESTEROS_GL_RPI_COMPILE_DEFINITIONS : ${WESTEROS_GL_RPI_COMPILE_DEFINITIONS}")
message(STATUS "WESTEROS_GL_RPI_COMPILER_OPTIONS    : ${WESTEROS_GL_RPI_COMPILER_OPTIONS}")
message(STATUS "WESTEROS_GL_RPI_INCLUDE_DIRS        : ${WESTEROS_GL_RPI_INCLUDE_DIRS}")
message(STATUS "WESTEROS_GL_RPI_LIBS                : ${WESTEROS_GL_RPI_LIBS}")

add_library(westeros_gl SHARED ${WESTEROS_GL_RPI_SOURCES})
target_compile_definitions(westeros_gl PRIVATE ${WESTEROS_GL_RPI_COMPILE_DEFINITIONS})
target_compile_options(westeros_gl PRIVATE ${WESTEROS_GL_RPI_COMPILER_OPTIONS})
target_include_directories(westeros_gl PRIVATE ${WESTEROS_GL_RPI_INCLUDE_DIRS})
target_link_libraries(westeros_gl PRIVATE ${WESTEROS_GL_RPI_LIBS})
set_target_properties(westeros_gl PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_gl PROPERTIES LINK_FLAGS "${LINK_RPATH}")
set_property(TARGET westeros_gl PROPERTY VERSION ${WESTEROS_DUMMY_VERSION_MAJOR}.${WESTEROS_DUMMY_VERSION_MINOR}.${WESTEROS_DUMMY_VERSION_MICRO})
set_property(TARGET westeros_gl PROPERTY SOVERSION ${WESTEROS_DUMMY_VERSION_MAJOR})

elseif(WESTEROS_PLATFORM_KYLIN)

# westeros_gl-kylin
set(WESTEROS_GL_KYLIN_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_GL_KYLIN_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_GL_KYLIN_SOURCES
    kylin/westeros-gl/westeros-gl.cpp
    kylin/westeros-gl/westeros-gl.h)
set(WESTEROS_GL_KYLIN_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    )
set(WESTEROS_GL_KYLIN_LIBS
    )
message(STATUS "WESTEROS_GL_KYLIN_COMPILE_DEFINITIONS : ${WESTEROS_GL_KYLIN_COMPILE_DEFINITIONS}")
message(STATUS "WESTEROS_GL_KYLIN_COMPILER_OPTIONS    : ${WESTEROS_GL_KYLIN_COMPILER_OPTIONS}")
message(STATUS "WESTEROS_GL_KYLIN_INCLUDE_DIRS        : ${WESTEROS_GL_KYLIN_INCLUDE_DIRS}")
message(STATUS "WESTEROS_GL_KYLIN_LIBS                : ${WESTEROS_GL_KYLIN_LIBS}")

add_library(westeros_gl SHARED ${WESTEROS_GL_KYLIN_SOURCES})
target_compile_definitions(westeros_gl PRIVATE ${WESTEROS_GL_KYLIN_COMPILE_DEFINITIONS})
target_compile_options(westeros_gl PRIVATE ${WESTEROS_GL_KYLIN_COMPILER_OPTIONS})
target_include_directories(westeros_gl PRIVATE ${WESTEROS_GL_KYLIN_INCLUDE_DIRS})
target_link_libraries(westeros_gl PRIVATE ${WESTEROS_GL_KYLIN_LIBS})
set_target_properties(westeros_gl PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_gl PROPERTIES LINK_FLAGS "${LINK_RPATH}")
set_property(TARGET westeros_gl PROPERTY VERSION ${WESTEROS_DUMMY_VERSION_MAJOR}.${WESTEROS_DUMMY_VERSION_MINOR}.${WESTEROS_DUMMY_VERSION_MICRO})
set_property(TARGET westeros_gl PROPERTY SOVERSION ${WESTEROS_DUMMY_VERSION_MAJOR})

else()
    
# westeros_gl-drm
set(WESTEROS_GL_DRM_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_GL_DRM_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_GL_DRM_SOURCES
    drm/westeros-gl/westeros-gl.c
    drm/westeros-gl/westeros-gl.h)
set(WESTEROS_GL_DRM_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    )
set(WESTEROS_GL_DRM_LIBS
    )
message(STATUS "WESTEROS_GL_DRM_COMPILE_DEFINITIONS : ${WESTEROS_GL_DRM_COMPILE_DEFINITIONS}")
message(STATUS "WESTEROS_GL_DRM_COMPILER_OPTIONS    : ${WESTEROS_GL_DRM_COMPILER_OPTIONS}")
message(STATUS "WESTEROS_GL_DRM_INCLUDE_DIRS        : ${WESTEROS_GL_DRM_INCLUDE_DIRS}")
message(STATUS "WESTEROS_GL_DRM_LIBS                : ${WESTEROS_GL_DRM_LIBS}")

add_library(westeros_gl SHARED ${WESTEROS_GL_DRM_SOURCES})
target_compile_definitions(westeros_gl PRIVATE ${WESTEROS_GL_DRM_COMPILE_DEFINITIONS})
target_compile_options(westeros_gl PRIVATE ${WESTEROS_GL_DRM_COMPILER_OPTIONS})
target_include_directories(westeros_gl PRIVATE ${WESTEROS_GL_DRM_INCLUDE_DIRS})
target_link_libraries(westeros_gl PRIVATE ${WESTEROS_GL_DRM_LIBS})
set_target_properties(westeros_gl PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_gl PROPERTIES LINK_FLAGS "${LINK_RPATH}")
set_property(TARGET westeros_gl PROPERTY VERSION ${WESTEROS_DUMMY_VERSION_MAJOR}.${WESTEROS_DUMMY_VERSION_MINOR}.${WESTEROS_DUMMY_VERSION_MICRO})
set_property(TARGET westeros_gl PROPERTY SOVERSION ${WESTEROS_DUMMY_VERSION_MAJOR})

endif()

show_target_properties(westeros_gl)

# westeros_render_gl
set(WESTEROS_RENDER_GL_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_RENDER_GL_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_RENDER_GL_SOURCES
    westeros-render-gl.cpp
    )
set(WESTEROS_RENDER_GL_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    )
set(WESTEROS_RENDER_GL_LIBS
    ${WESTEROS_EGL_LIBS}
    ${EGL_LIBRARIES}
    ${WESTEROS_OPENGL_LIBS}
    ${WAYLAND_SERVER_LIBRARIES}
    westeros_simplebuffer_server
    )

message(STATUS "WESTEROS_RENDER_GL_COMPILE_DEFINITIONS  : ${WESTEROS_RENDER_GL_COMPILE_DEFINITIONS}")
message(STATUS "WESTEROS_RENDER_GL_COMPILER_OPTIONS     : ${WESTEROS_RENDER_GL_COMPILER_OPTIONS}")
message(STATUS "WESTEROS_RENDER_GL_INCLUDE_DIRS         : ${WESTEROS_RENDER_GL_INCLUDE_DIRS}")
message(STATUS "WESTEROS_RENDER_GL_LIBS                 : ${WESTEROS_RENDER_GL_LIBS}")

add_library(westeros_render_gl STATIC ${WESTEROS_RENDER_GL_SOURCES})
target_compile_definitions(westeros_render_gl PRIVATE ${WESTEROS_RENDER_GL_COMPILE_DEFINITIONS})
target_compile_options(westeros_render_gl PRIVATE ${WESTEROS_RENDER_GL_COMPILER_OPTIONS})
target_include_directories(westeros_render_gl PRIVATE ${WESTEROS_RENDER_GL_INCLUDE_DIRS})
target_link_libraries(westeros_render_gl PRIVATE ${WESTEROS_RENDER_GL_LIBS})
set_target_properties(westeros_render_gl PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_render_gl PROPERTIES LINK_FLAGS "-rpath ../lib")

show_target_properties(westeros_render_gl)

add_library(westeros_render_gl-shared SHARED ${WESTEROS_RENDER_GL_SOURCES})
target_compile_definitions(westeros_render_gl-shared PRIVATE ${WESTEROS_RENDER_GL_COMPILE_DEFINITIONS})
target_compile_options(westeros_render_gl-shared PRIVATE ${WESTEROS_RENDER_GL_COMPILER_OPTIONS})
target_include_directories(westeros_render_gl-shared PRIVATE ${WESTEROS_RENDER_GL_INCLUDE_DIRS})
target_link_libraries(westeros_render_gl-shared PRIVATE ${WESTEROS_RENDER_GL_LIBS})
set_target_properties(westeros_render_gl-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_render_gl-shared PROPERTIES LINK_FLAGS "${LINK_RPATH}")
set_property(TARGET westeros_render_gl-shared PROPERTY VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
set_property(TARGET westeros_render_gl-shared PROPERTY SOVERSION ${WESTEROS_VERSION_MAJOR})
set_property(TARGET westeros_render_gl-shared PROPERTY OUTPUT_NAME westeros_render_gl)

show_target_properties(westeros_render_gl-shared)

# westeros_render_embedded
set(WESTEROS_RENDER_EMBEDDED_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_RENDER_EMBEDDED_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_RENDER_EMBEDDED_SOURCES
    westeros-render-embedded.cpp
    )
set(WESTEROS_RENDER_EMBEDDED_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    )
set(WESTEROS_RENDER_EMBEDDED_LIBS
    ${WESTEROS_EGL_LIBS}
    ${EGL_LIBRARIES}
    ${WESTEROS_OPENGL_LIBS}
    ${WAYLAND_SERVER_LIBRARIES}
    westeros_simplebuffer_server
    )

message(STATUS "WESTEROS_RENDER_EMBEDDED_COMPILE_DEFINITIONS: ${WESTEROS_RENDER_EMBEDDED_COMPILE_DEFINITIONS}")
message(STATUS "WESTEROS_RENDER_EMBEDDED_COMPILER_OPTIONS   : ${WESTEROS_RENDER_EMBEDDED_COMPILER_OPTIONS}")
message(STATUS "WESTEROS_RENDER_EMBEDDED_INCLUDE_DIRS       : ${WESTEROS_RENDER_EMBEDDED_INCLUDE_DIRS}")
message(STATUS "WESTEROS_RENDER_EMBEDDED_LIBS               : ${WESTEROS_RENDER_EMBEDDED_LIBS}")

add_library(westeros_render_embedded STATIC ${WESTEROS_RENDER_EMBEDDED_SOURCES})
target_compile_definitions(westeros_render_embedded PRIVATE ${WESTEROS_RENDER_EMBEDDED_COMPILE_DEFINITIONS})
target_compile_options(westeros_render_embedded PRIVATE ${WESTEROS_RENDER_EMBEDDED_COMPILER_OPTIONS})
target_include_directories(westeros_render_embedded PRIVATE ${WESTEROS_RENDER_EMBEDDED_INCLUDE_DIRS})
target_link_libraries(westeros_render_embedded PRIVATE ${WESTEROS_RENDER_EMBEDDED_LIBS})
set_target_properties(westeros_render_embedded PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_render_embedded PROPERTIES LINK_FLAGS "-rpath ../lib")

show_target_properties(westeros_render_embedded)

add_library(westeros_render_embedded-shared SHARED ${WESTEROS_RENDER_EMBEDDED_SOURCES})
target_compile_definitions(westeros_render_embedded-shared PRIVATE ${WESTEROS_RENDER_EMBEDDED_COMPILE_DEFINITIONS})
target_compile_options(westeros_render_embedded-shared PRIVATE ${WESTEROS_RENDER_EMBEDDED_COMPILER_OPTIONS})
target_include_directories(westeros_render_embedded-shared PRIVATE ${WESTEROS_RENDER_EMBEDDED_INCLUDE_DIRS})
target_link_libraries(westeros_render_embedded-shared PRIVATE ${WESTEROS_RENDER_EMBEDDED_LIBS})
set_target_properties(westeros_render_embedded-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_render_embedded-shared PROPERTIES LINK_FLAGS "${LINK_RPATH}")
set_property(TARGET westeros_render_embedded-shared PROPERTY VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
set_property(TARGET westeros_render_embedded-shared PROPERTY SOVERSION ${WESTEROS_VERSION_MAJOR})
set_property(TARGET westeros_render_embedded-shared PROPERTY OUTPUT_NAME westeros_render_embedded)

show_target_properties(westeros_render_embedded-shared)

# westeros_compositor
set(WESTEROS_COMPOSITOR_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_COMPOSITOR_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_COMPOSITOR_SOURCES
    westeros-compositor.cpp
    westeros-compositor.h
    westeros-nested.cpp
    westeros-nested.h
    westeros-render.cpp
    westeros-render.h
    protocol/vpc-protocol.c
    protocol/vpc-server-protocol.h
    ${WESTEROS_XDG_PROTOCOL_SOURCES}
    )
set(WESTEROS_COMPOSITOR_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    ${LIBXKBCOMMON_INCLUDE_DIRS}
    )
set(WESTEROS_COMPOSITOR_LIBS
    ${WAYLAND_SERVER_LIBRARIES}
    ${WAYLAND_CLIENT_LIBRARIES}
    ${WESTEROS_EGL_LIBS}
    ${LIBXKBCOMMON_LIBRARIES}
    westeros_simpleshell_server
    pthread
    dl
    westeros_simplebuffer_server
    )
message(STATUS "WESTEROS_COMPOSITOR_COMPILE_DEFINITIONS : ${WESTEROS_COMPOSITOR_COMPILE_DEFINITIONS}")
message(STATUS "WESTEROS_COMPOSITOR_COMPILER_OPTIONS    : ${WESTEROS_COMPOSITOR_COMPILER_OPTIONS}")
message(STATUS "WESTEROS_COMPOSITOR_INCLUDE_DIRS        : ${WESTEROS_COMPOSITOR_INCLUDE_DIRS}")
message(STATUS "WESTEROS_COMPOSITOR_LIBS                : ${WESTEROS_COMPOSITOR_LIBS}")

add_library(westeros_compositor STATIC ${WESTEROS_COMPOSITOR_SOURCES})
target_compile_definitions(westeros_compositor PRIVATE ${WESTEROS_COMPOSITOR_COMPILE_DEFINITIONS})
target_compile_options(westeros_compositor PRIVATE ${WESTEROS_COMPOSITOR_COMPILER_OPTIONS})
target_include_directories(westeros_compositor PRIVATE ${WESTEROS_COMPOSITOR_INCLUDE_DIRS})
target_link_libraries(westeros_compositor PRIVATE ${WESTEROS_COMPOSITOR_LIBS})
set_target_properties(westeros_compositor PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_compositor PROPERTIES LINK_FLAGS "-rpath ../lib")

show_target_properties(westeros_compositor)

add_library(westeros_compositor-shared SHARED ${WESTEROS_COMPOSITOR_SOURCES})
target_compile_definitions(westeros_compositor-shared PRIVATE ${WESTEROS_COMPOSITOR_COMPILE_DEFINITIONS})
target_compile_options(westeros_compositor-shared PRIVATE ${WESTEROS_COMPOSITOR_COMPILER_OPTIONS})
target_include_directories(westeros_compositor-shared PRIVATE ${WESTEROS_COMPOSITOR_INCLUDE_DIRS})
target_link_libraries(westeros_compositor-shared PRIVATE ${WESTEROS_COMPOSITOR_LIBS})
set_target_properties(westeros_compositor-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_compositor-shared PROPERTIES LINK_FLAGS "${LINK_RPATH}")
#set_target_properties(westeros_compositor-shared PROPERTIES LINK_FLAGS "${LINK_WHOLE_LIB} ${CMAKE_CURRENT_BINARY_DIR}/libshared.a ${LINK_NO_WHOLE_LIB} ${LINK_RPATH}")
set_property(TARGET westeros_compositor-shared PROPERTY VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
set_property(TARGET westeros_compositor-shared PROPERTY SOVERSION ${WESTEROS_VERSION_MAJOR})
set_property(TARGET westeros_compositor-shared PROPERTY OUTPUT_NAME westeros_compositor)

show_target_properties(westeros_compositor-shared)

# westeros
set(WESTEROS_APP_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_APP_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_APP_SOURCES
    westeros-main.cpp
    )
set(WESTEROS_APP_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    ${LIBXKBCOMMON_INCLUDE_DIRS}
    )
set(WESTEROS_APP_LIBS
    ${WAYLAND_SERVER_LIBRARIES}
    westeros_compositor
    ${FREEGLUT_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${LIBX11_LIBRARIES}
    ${EGL_LIBRARIES}
    ${GLESV2_LIBRARIES}
    ${WESTEROS_EGL_LIBS}
    ${WESTEROS_OPENGL_LIBS}
    ${LIBXKBCOMMON_LIBRARIES}
    )
message(STATUS "WESTEROS_APP_COMPILE_DEFINITIONS: ${WESTEROS_APP_COMPILE_DEFINITIONS}")
message(STATUS "WESTEROS_APP_COMPILER_OPTIONS   : ${WESTEROS_APP_COMPILER_OPTIONS}")
message(STATUS "WESTEROS_APP_INCLUDE_DIRS       : ${WESTEROS_APP_INCLUDE_DIRS}")
message(STATUS "WESTEROS_APP_LIBS               : ${WESTEROS_APP_LIBS}")

add_executable(westeros ${WESTEROS_APP_SOURCES})
target_compile_definitions(westeros PRIVATE ${WESTEROS_APP_COMPILE_DEFINITIONS})
target_compile_options(westeros PRIVATE ${WESTEROS_APP_COMPILER_OPTIONS})
target_include_directories(westeros PRIVATE ${WESTEROS_APP_INCLUDE_DIRS})
target_link_libraries(westeros PRIVATE ${WESTEROS_APP_LIBS})
set_target_properties(westeros PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros PROPERTIES RUNTIME_OUTPUT_NAME westeros-${WESTEROS_VERSION})
set_target_properties(westeros PROPERTIES LINK_FLAGS "${LINK_RPATH}")

show_target_properties(westeros)

# westeros_player
set(WESTEROS_PLAYER_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_PLAYER_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_PLAYER_SOURCES
    westeros-player.cpp
    )
set(WESTEROS_PLAYER_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    ${GSTREAMER_INCLUDE_DIRS}
    )
set(WESTEROS_PLAYER_LIBS
    ${GSTREAMER_LIBRARIES}
    ${WAYLAND_CLIENT_LIBRARIES}
    ${WESTEROS_EGL_LIBS}
    ${EGL_LIBRARIES}
    )
message(STATUS "WESTEROS_PLAYER_COMPILE_DEFINITIONS : ${WESTEROS_PLAYER_COMPILE_DEFINITIONS}")
message(STATUS "WESTEROS_PLAYER_COMPILER_OPTIONS    : ${WESTEROS_PLAYER_COMPILER_OPTIONS}")
message(STATUS "WESTEROS_PLAYER_INCLUDE_DIRS        : ${WESTEROS_PLAYER_INCLUDE_DIRS}")
message(STATUS "WESTEROS_PLAYER_LIBS                : ${WESTEROS_PLAYER_LIBS}")

add_executable(westeros_player ${WESTEROS_PLAYER_SOURCES})
target_compile_definitions(westeros_player PRIVATE ${WESTEROS_PLAYER_COMPILE_DEFINITIONS})
target_compile_options(westeros_player PRIVATE ${WESTEROS_PLAYER_COMPILER_OPTIONS})
target_include_directories(westeros_player PRIVATE ${WESTEROS_PLAYER_INCLUDE_DIRS})
target_link_libraries(westeros_player PRIVATE ${WESTEROS_PLAYER_LIBS})
set_target_properties(westeros_player PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_player PROPERTIES RUNTIME_OUTPUT_NAME westeros_player-${WESTEROS_VERSION})
set_target_properties(westeros_player PROPERTIES LINK_FLAGS "${LINK_RPATH}")

show_target_properties(westeros_player)

# westeros_test
set(WESTEROS_TEST_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_TEST_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_TEST_SOURCES
    westeros-test.cpp
    )
set(WESTEROS_TEST_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    ${LIBXKBCOMMON_INCLUDE_DIRS}
    )
set(WESTEROS_TEST_LIBS
    ${WAYLAND_SERVER_LIBRARIES}
    ${WAYLAND_CLIENT_LIBRARIES}
    westeros_simpleshell_client
    ${WESTEROS_EGL_LIBS}
    ${EGL_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${LIBXKBCOMMON_LIBRARIES}
    )
message(STATUS "WESTEROS_TEST_INCLUDE_DIRS: ${WESTEROS_TEST_INCLUDE_DIRS}")
message(STATUS "WESTEROS_TEST_LIBS: ${WESTEROS_TEST_LIBS}")

add_executable(westeros_test ${WESTEROS_TEST_SOURCES})
target_compile_definitions(westeros_test PRIVATE ${WESTEROS_TEST_COMPILE_DEFINITIONS})
target_compile_options(westeros_test PRIVATE ${WESTEROS_TEST_COMPILER_OPTIONS})
target_include_directories(westeros_test PRIVATE ${WESTEROS_TEST_INCLUDE_DIRS})
target_link_libraries(westeros_test PRIVATE ${WESTEROS_TEST_LIBS})
set_target_properties(westeros_test PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(westeros_test PROPERTIES RUNTIME_OUTPUT_NAME westeros_test-${WESTEROS_VERSION})
set_target_properties(westeros_test PROPERTIES LINK_FLAGS "${LINK_RPATH}")

show_target_properties(westeros_test)

if (ENABLE_WESTEROS_APP)
    message(STATUS "ENABLE_WESTEROS_APP")
endif()
if (ENABLE_WESTEROS_TEST)
    message(STATUS "ENABLE_WESTEROS_TEST")
endif()
if (ENABLE_WESTEROS_PLAYER)
    message(STATUS "ENABLE_WESTEROS_PLAYER")
endif()

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

add_dependencies(uninstall-components uninstall_${PROJECT_NAME})

add_custom_target(${WESTEROS_BASE} DEPENDS
    westeros_simplebuffer_client
    westeros_simplebuffer_client-shared
    westeros_simplebuffer_server
    westeros_simplebuffer_server-shared
    westeros_simpleshell_client
    westeros_simpleshell_client-shared
    westeros_simpleshell_server
    westeros_simpleshell_server-shared
    westeros_compositor
    westeros_compositor-shared
    westeros_render_gl
    westeros_render_gl-shared
    westeros_render_embedded
    westeros_render_embedded-shared
    westeros_gl
    westeros
    westeros_player
    westeros_test
    simplebuffer/protocol/simplebuffer-protocol.c
    simplebuffer/protocol/simplebuffer-client-protocol.h
    simplebuffer/protocol/simplebuffer-server-protocol.h
    simpleshell/protocol/simpleshell-protocol.c
    simpleshell/protocol/simpleshell-client-protocol.h
    simpleshell/protocol/simpleshell-server-protocol.h
    protocol/version4/xdg-shell-protocol.c
    protocol/version4/xdg-shell-client-protocol.h
    protocol/version4/xdg-shell-server-protocol.h
    protocol/version5/xdg-shell-protocol.c
    protocol/version5/xdg-shell-client-protocol.h
    protocol/version5/xdg-shell-server-protocol.h
    ${CMAKE_CURRENT_SOURCE_DIR}/protocol/vpc-protocol.c
    ${CMAKE_CURRENT_SOURCE_DIR}/protocol/vpc-client-protocol.h
    ${CMAKE_CURRENT_SOURCE_DIR}/protocol/vpc-server-protocol.h
    )

add_dependencies(install_${PROJECT_NAME}
    ${WESTEROS_BASE})

set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix "\${prefix}")
set(datarootdir "\${prefix}/share")
set(datadir "\${datarootdir}")
set(libdir "\${exec_prefix}/lib")
set(PACKAGE "${PROJECT_NAME}")
set(PACKAGE_VERSION ${WESTEROS_VERSION})

configure_file(westeros-compositor.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/westeros-compositor.pc @ONLY)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/westeros-compositor.pc
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_simplebuffer_client
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_simplebuffer_client-shared
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_simplebuffer_server
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_simplebuffer_server-shared
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_simpleshell_client
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_simpleshell_client-shared
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_simpleshell_server
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_simpleshell_server-shared
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_compositor
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_compositor-shared
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_gl
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_render_embedded
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_render_embedded-shared
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_render_gl
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_render_gl-shared
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    COMPONENT ${PROJECT_NAME})

install(CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E create_symlink
              westeros-${WESTEROS_VERSION}
              ${CMAKE_INSTALL_PREFIX}/bin/westeros)"
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_player
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    COMPONENT ${PROJECT_NAME})

install(CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E create_symlink
              ${CMAKE_INSTALL_PREFIX}/bin/westeros_player-${WESTEROS_VERSION}
              ${CMAKE_INSTALL_PREFIX}/bin/westeros_player)"
    COMPONENT ${PROJECT_NAME})

install(TARGETS westeros_test
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    COMPONENT ${PROJECT_NAME})

install(CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" -E create_symlink
              westeros_test-${WESTEROS_VERSION}
              ${CMAKE_INSTALL_PREFIX}/bin/westeros_test)"
    COMPONENT ${PROJECT_NAME})

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/simplebuffer/westeros-simplebuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleshell/westeros-simpleshell.h
    ${CMAKE_CURRENT_SOURCE_DIR}/westeros-compositor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/westeros-render.h
    ${CMAKE_CURRENT_SOURCE_DIR}/protocol/vpc-client-protocol.h
    ${CMAKE_CURRENT_SOURCE_DIR}/simplebuffer/protocol/simplebuffer-client-protocol.h
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleshell/protocol/simpleshell-client-protocol.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    COMPONENT ${PROJECT_NAME})
