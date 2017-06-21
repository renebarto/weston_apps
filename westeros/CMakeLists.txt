project(westeros)

set(WESTEROS_VERSION_MAJOR 2)
set(WESTEROS_VERSION_MINOR 0)
set(WESTEROS_VERSION_MICRO 0)
set(WESTEROS_VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
set(WESTEROS_REQUIRED_VERSION ${WESTEROS_VERSION})
set(WESTEROS_NAME ${PROJECT_NAME})
set(WESTEROS_BASE ${WESTEROS_NAME}-${WESTEROS_VERSION})

#set(LINK_WHOLE_LIB -Wl,--whole-archive)
#set(LINK_NO_WHOLE_LIB -Wl,--no-whole-archive)
#set(LINK_RPATH -Wl,-rpath,'\$ORIGIN/../lib/')

include(show_target_properties)

#find_package(Pixman REQUIRED)
#find_package(LibXKBCommon REQUIRED)
#find_package(LibInput REQUIRED)
#find_package(EGL REQUIRED)
#find_package(GLES REQUIRED)
#find_package(Eudev REQUIRED)
#find_package(LibDRM REQUIRED)
#find_package(LibGBM REQUIRED)
#find_package(Mtdev REQUIRED)
#find_package(LibFFI REQUIRED)
#find_package(LibEvdev REQUIRED)
find_package(GLEW QUIET)
find_package(WaylandEGL QUIET)
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

# Create protocol sources
# simplebuffer/protocol/simple-buffer.xml
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simplebuffer/protocol/simplebuffer-client-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> client-header < simplebuffer/protocol/simple-buffer.xml > simplebuffer/protocol/simplebuffer-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simplebuffer/protocol/simplebuffer-server-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> server-header < simplebuffer/protocol/simple-buffer.xml > simplebuffer/protocol/simplebuffer-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simplebuffer/protocol/simplebuffer-protocol.c
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> code < simplebuffer/protocol/simple-buffer.xml > simplebuffer/protocol/simplebuffer-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

# simpleshell/protocol/simple-buffer.xml
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simpleshell/protocol/simpleshell-client-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> client-header < simpleshell/protocol/simpleshell.xml > simpleshell/protocol/simpleshell-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simpleshell/protocol/simpleshell-server-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> server-header < simpleshell/protocol/simpleshell.xml > simpleshell/protocol/simpleshell-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/simpleshell/protocol/simpleshell-protocol.c
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> code < simpleshell/protocol/simpleshell.xml > simpleshell/protocol/simpleshell-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

# version4/xdg-shell.xml
#add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/version4/xdg-shell-client-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
#    COMMAND $<TARGET_FILE:wayland-scanner> client-header < version4/xdg-shell.xml > version4/xdg-shell-client-protocol.h
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/version4/xdg-shell-server-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> server-header < version4/xdg-shell.xml > version4/xdg-shell-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/version4/xdg-shell-protocol.c
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> code < version4/xdg-shell.xml > version4/xdg-shell-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

# version5/xdg-shell.xml
#add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/version5/xdg-shell-client-protocol.h
#    DEPENDS wayland-protocols-1.7 wayland-scanner
#    COMMAND $<TARGET_FILE:wayland-scanner> client-header < version5/xdg-shell.xml > version5/xdg-shell-client-protocol.h
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/version5/xdg-shell-server-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> server-header < version5/xdg-shell.xml > version5/xdg-shell-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/version5/xdg-shell-protocol.c
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> code < version5/xdg-shell.xml > version5/xdg-shell-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

# vpc.xml
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/vpc-client-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> client-header < vpc.xml > vpc-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/vpc-server-protocol.h
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> server-header < vpc.xml > vpc-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/vpc-protocol.c
    DEPENDS wayland-protocols-1.7 wayland-scanner
    COMMAND $<TARGET_FILE:wayland-scanner> code < vpc.xml > vpc-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

set(WESTEROS_COMPILE_DEFINITIONS
#    HAVE_CONFIG_H
#    DATADIR="${CMAKE_INSTALL_PREFIX}/share"
#    LIBWESTEROS_MODULEDIR="${CMAKE_INSTALL_PREFIX}/lib/libweston-${WESTEROS_VERSION_MAJOR}"
#    LIBEXECDIR="${CMAKE_INSTALL_PREFIX}/libexec"
#    BINDIR="${CMAKE_INSTALL_PREFIX}/bin"
#    _LARGEFILE_SOURCE
#    _LARGEFILE64_SOURCE
#    _FILE_OFFSET_BITS=64
    )
set(WESTEROS_COMPILER_OPTIONS -Wall -Wextra
#    -Wno-unused-parameter -Wno-shift-negative-value -Wno-missing-field-initializers
#    -fvisibility=hidden -Wstrict-prototypes -Wmissing-prototypes -Wsign-compare
    )
set(WESTEROS_INCLUDES
    .
    ./simplebuffer/protocol
    ./simpleshell/protocol
    ${SYSTEM_INCLUDES})

if (NOT GLEW_FOUND)
    list(APPEND WESTEROS_COMPILER_DEFINITIONS WESTEROS_PLATFORM_EMBEDDED)
endif()
if (WAYLAND_EGL_FOUND)
    set(WESTEROS_EGL_LIBS
        ${WAYLAND_EGL_LIBS} ${GLESV2_LIBRARIES})
else()
    set(WESTEROS_EGL_LIBS
        westeros_egl)
endif()

if(ENABLE_XDG_V4)
    list(APPEND WESTEROS_COMPILER_DEFINITIONS USE_XDG_VERSION4)
    list(APPEND WESTEROS_INCLUDES protocol/version4)
endif()

if(ENABLE_XDG_V5)
    list(APPEND WESTEROS_COMPILER_DEFINITIONS USE_XDG_VERSION5)
    list(APPEND WESTEROS_INCLUDES protocol/version5)
endif()


# westeros-simplebuffer-client
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
#    ${PIXMAN_INCLUDE_DIRS}
#    ${LIBXKBCOMMON_INCLUDE_DIRS}
    )
set(WESTEROS_SIMPLEBUFFER_CLIENT_LIBS
    wayland-client-shared
#    ${PIXMAN_LIBRARIES}
#    ${LIBXKBCOMMON_LIBRARIES}
#    m
#    ${LIBINPUT_LIBRARIES}
    )

message(STATUS "WESTEROS_SIMPLEBUFFER_CLIENT_INCLUDE_DIRS: ${WESTEROS_SIMPLEBUFFER_CLIENT_INCLUDE_DIRS}")
message(STATUS "WESTEROS_SIMPLEBUFFER_CLIENT_LIBS: ${WESTEROS_SIMPLEBUFFER_CLIENT_LIBS}")

add_library(westeros-simplebuffer-client SHARED ${WESTEROS_SIMPLEBUFFER_CLIENT_SOURCES})
target_compile_definitions(westeros-simplebuffer-client PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_COMPILE_DEFINITIONS})
target_compile_options(westeros-simplebuffer-client PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_COMPILER_OPTIONS})
target_include_directories(westeros-simplebuffer-client PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_INCLUDE_DIRS})
target_link_libraries(westeros-simplebuffer-client PRIVATE ${WESTEROS_SIMPLEBUFFER_CLIENT_LIBS})
set_target_properties(westeros-simplebuffer-client PROPERTIES POSITION_INDEPENDENT_CODE ON)

show_target_properties(westeros-simplebuffer-client)

# westeros-simplebuffer-server
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
    #    ${PIXMAN_INCLUDE_DIRS}
    #    ${LIBXKBCOMMON_INCLUDE_DIRS}
    )
set(WESTEROS_SIMPLEBUFFER_SERVER_LIBS
    wayland-server-shared
    #    ${PIXMAN_LIBRARIES}
    #    ${LIBXKBCOMMON_LIBRARIES}
    #    m
    #    ${LIBINPUT_LIBRARIES}
    )
message(STATUS "WESTEROS_SIMPLEBUFFER_SERVER_INCLUDE_DIRS: ${WESTEROS_SIMPLEBUFFER_SERVER_INCLUDE_DIRS}")
message(STATUS "WESTEROS_SIMPLEBUFFER_SERVER_LIBS: ${WESTEROS_SIMPLEBUFFER_SERVER_LIBS}")

add_library(westeros-simplebuffer-server SHARED ${WESTEROS_SIMPLEBUFFER_SERVER_SOURCES})
target_compile_definitions(westeros-simplebuffer-server PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_COMPILE_DEFINITIONS})
target_compile_options(westeros-simplebuffer-server PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_COMPILER_OPTIONS})
target_include_directories(westeros-simplebuffer-server PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_INCLUDE_DIRS})
target_link_libraries(westeros-simplebuffer-server PRIVATE ${WESTEROS_SIMPLEBUFFER_SERVER_LIBS})
set_target_properties(westeros-simplebuffer-server PROPERTIES POSITION_INDEPENDENT_CODE ON)

show_target_properties(westeros-simplebuffer-server)

# westeros-simpleshell-client
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
    #    ${PIXMAN_INCLUDE_DIRS}
    #    ${LIBXKBCOMMON_INCLUDE_DIRS}
    )
set(WESTEROS_SIMPLESHELL_CLIENT_LIBS
    wayland-client-shared
    #    ${PIXMAN_LIBRARIES}
    #    ${LIBXKBCOMMON_LIBRARIES}
    #    m
    #    ${LIBINPUT_LIBRARIES}
    )
message(STATUS "WESTEROS_SIMPLESHELL_CLIENT_INCLUDE_DIRS: ${WESTEROS_SIMPLESHELL_CLIENT_INCLUDE_DIRS}")
message(STATUS "WESTEROS_SIMPLESHELL_CLIENT_LIBS: ${WESTEROS_SIMPLESHELL_CLIENT_LIBS}")

add_library(westeros-simpleshell-client SHARED ${WESTEROS_SIMPLESHELL_CLIENT_SOURCES})
target_compile_definitions(westeros-simpleshell-client PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_COMPILE_DEFINITIONS})
target_compile_options(westeros-simpleshell-client PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_COMPILER_OPTIONS})
target_include_directories(westeros-simpleshell-client PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_INCLUDE_DIRS})
target_link_libraries(westeros-simpleshell-client PRIVATE ${WESTEROS_SIMPLESHELL_CLIENT_LIBS})
set_target_properties(westeros-simpleshell-client PROPERTIES POSITION_INDEPENDENT_CODE ON)

show_target_properties(westeros-simpleshell-client)

# westeros-simpleshell-server
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
    #    ${PIXMAN_INCLUDE_DIRS}
    #    ${LIBXKBCOMMON_INCLUDE_DIRS}
    )
set(WESTEROS_SIMPLESHELL_SERVER_LIBS
    wayland-server-shared
    #    ${PIXMAN_LIBRARIES}
    #    ${LIBXKBCOMMON_LIBRARIES}
    #    m
    #    ${LIBINPUT_LIBRARIES}
    )
message(STATUS "WESTEROS_SIMPLESHELL_SERVER_INCLUDE_DIRS: ${WESTEROS_SIMPLESHELL_SERVER_INCLUDE_DIRS}")
message(STATUS "WESTEROS_SIMPLESHELL_SERVER_LIBS: ${WESTEROS_SIMPLESHELL_SERVER_LIBS}")

add_library(westeros-simpleshell-server SHARED ${WESTEROS_SIMPLESHELL_SERVER_SOURCES})
target_compile_definitions(westeros-simpleshell-server PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_COMPILE_DEFINITIONS})
target_compile_options(westeros-simpleshell-server PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_COMPILER_OPTIONS})
target_include_directories(westeros-simpleshell-server PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_INCLUDE_DIRS})
target_link_libraries(westeros-simpleshell-server PRIVATE ${WESTEROS_SIMPLESHELL_SERVER_LIBS})
set_target_properties(westeros-simpleshell-server PROPERTIES POSITION_INDEPENDENT_CODE ON)

show_target_properties(westeros-simpleshell-server)

# westeros-core
set(WESTEROS_CORE_COMPILE_DEFINITIONS
    ${WESTEROS_COMPILE_DEFINITIONS}
    )
set(WESTEROS_CORE_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
set(WESTEROS_CORE_SOURCES
    simpleshell/protocol/simpleshell-server-protocol.h
    simpleshell/protocol/simpleshell-protocol.c
    simpleshell/westeros-simpleshell.cpp
    simpleshell/westeros-simpleshell.h
    )
set(WESTEROS_CORE_INCLUDE_DIRS
    ${WESTEROS_INCLUDES}
    #    ${PIXMAN_INCLUDE_DIRS}
    #    ${LIBXKBCOMMON_INCLUDE_DIRS}
    )
set(WESTEROS_CORE_LIBS
    wayland-server-shared
    #    ${PIXMAN_LIBRARIES}
    #    ${LIBXKBCOMMON_LIBRARIES}
    #    m
    #    ${LIBINPUT_LIBRARIES}
    )
message(STATUS "WESTEROS_CORE_INCLUDE_DIRS: ${WESTEROS_CORE_INCLUDE_DIRS}")
message(STATUS "WESTEROS_CORE_LIBS: ${WESTEROS_CORE_LIBS}")

add_library(westeros-core SHARED ${WESTEROS_CORE_SOURCES})
target_compile_definitions(westeros-core PRIVATE ${WESTEROS_CORE_COMPILE_DEFINITIONS})
target_compile_options(westeros-core PRIVATE ${WESTEROS_CORE_COMPILER_OPTIONS})
target_include_directories(westeros-core PRIVATE ${WESTEROS_CORE_INCLUDE_DIRS})
target_link_libraries(westeros-core PRIVATE ${WESTEROS_CORE_LIBS})
set_target_properties(westeros-core PROPERTIES POSITION_INDEPENDENT_CODE ON)

show_target_properties(westeros-core)


#set(WESTEROS_COMPILE_DEFINITIONS
#    HAVE_CONFIG_H
#    DATADIR="${CMAKE_INSTALL_PREFIX}/share"
#    LIBWESTEROS_MODULEDIR="${CMAKE_INSTALL_PREFIX}/lib/libweston-${WESTEROS_VERSION_MAJOR}"
#    LIBEXECDIR="${CMAKE_INSTALL_PREFIX}/libexec"
#    BINDIR="${CMAKE_INSTALL_PREFIX}/bin"
#    _LARGEFILE_SOURCE
#    _LARGEFILE64_SOURCE
#    _FILE_OFFSET_BITS=64)
#set(WESTEROS_COMPILER_OPTIONS -Wall -Wextra -Wno-unused-parameter -Wno-shift-negative-value -Wno-missing-field-initializers
#    -fvisibility=hidden -Wstrict-prototypes -Wmissing-prototypes -Wsign-compare)
#set(WESTEROS_INCLUDES . libweston clients tests shared protocol ${SYSTEM_INCLUDES})
#
## shared
#set(SHARED_COMPILE_DEFINITIONS ${WESTEROS_COMPILE_DEFINITIONS})
#set(SHARED_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS})
#set(SHARED_SOURCES
#    shared/config-parser.c
#    shared/config-parser.h
#    shared/option-parser.c
#    shared/file-util.c
#    shared/file-util.h
#    shared/os-compatibility.c
#    shared/os-compatibility.c
#    shared/xalloc.c
#    shared/xalloc.h)
#set(SHARED_INCLUDE_DIRS
#    ${WESTEROS_INCLUDES}
#    ${PIXMAN_INCLUDE_DIRS}
#    ${LIBXKBCOMMON_INCLUDE_DIRS})
#set(SHARED_LIBS
#    )
#message(STATUS "SHARED_INCLUDE_DIRS: ${SHARED_INCLUDE_DIRS}")
#message(STATUS "SHARED_LIBS: ${SHARED_LIBS}")
#
#add_library(shared-obj OBJECT ${SHARED_SOURCES})
#target_compile_definitions(shared-obj PRIVATE ${SHARED_COMPILE_DEFINITIONS})
#target_compile_options(shared-obj PRIVATE ${SHARED_COMPILER_OPTIONS})
#target_include_directories(shared-obj PRIVATE ${SHARED_INCLUDE_DIRS})
#set_target_properties(shared-obj PROPERTIES POSITION_INDEPENDENT_CODE ON)
#
#show_target_properties(shared-obj)
#
#add_library(shared STATIC $<TARGET_OBJECTS:shared-obj>)
#target_compile_definitions(shared PRIVATE ${SHARED_COMPILE_DEFINITIONS})
#target_compile_options(shared PRIVATE ${SHARED_COMPILER_OPTIONS})
#target_include_directories(shared PRIVATE ${SHARED_INCLUDE_DIRS})
#target_link_libraries(shared PRIVATE ${SHARED_LIBS})
#set_target_properties(shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
#
#show_target_properties(shared)
#
## weston-2
#set(LIBWESTEROS_2_COMPILE_DEFINITIONS ${WESTEROS_COMPILE_DEFINITIONS} IN_WESTEROS)
#set(LIBWESTEROS_2_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
#set(LIBWESTEROS_2_SOURCES
#    libweston/log.c
#    libweston/compositor.c
#    libweston/compositor.h
#    libweston/input.c
#    libweston/data-device.c
#    libweston/screenshooter.c
#    libweston/clipboard.c
#    libweston/zoom.c
#    libweston/bindings.c
#    libweston/animation.c
#    libweston/noop-renderer.c
#    libweston/pixman-renderer.c
#    libweston/pixman-renderer.h
#    libweston/plugin-registry.c
#    libweston/plugin-registry.h
#    libweston/timeline.c
#    libweston/timeline.h
#    libweston/linux-dmabuf.c
#    libweston/linux-dmabuf.h
#    shared/matrix.c
#    shared/matrix.h
#    protocol/weston-screenshooter-protocol.c
#    protocol/weston-screenshooter-server-protocol.h
#    protocol/text-cursor-position-protocol.c
#    protocol/text-cursor-position-server-protocol.h
#    protocol/text-input-unstable-v1-protocol.c
#    protocol/text-input-unstable-v1-server-protocol.h
#    protocol/input-method-unstable-v1-protocol.c
#    protocol/input-method-unstable-v1-server-protocol.h
#    protocol/presentation-time-protocol.c
#    protocol/presentation-time-server-protocol.h
#    protocol/viewporter-protocol.c
#    protocol/viewporter-server-protocol.h
#    protocol/linux-dmabuf-unstable-v1-protocol.c
#    protocol/linux-dmabuf-unstable-v1-server-protocol.h
#    protocol/relative-pointer-unstable-v1-protocol.c
#    protocol/relative-pointer-unstable-v1-server-protocol.h
#    protocol/pointer-constraints-unstable-v1-protocol.c
#    protocol/pointer-constraints-unstable-v1-server-protocol.h
#    )
#set(LIBWESTEROS_2_INCLUDE_DIRS
#    ${WESTEROS_INCLUDES}
#    ${PIXMAN_INCLUDE_DIRS}
#    ${LIBXKBCOMMON_INCLUDE_DIRS})
#set(LIBWESTEROS_2_LIBS
#    wayland-server-shared
#    ${PIXMAN_LIBRARIES}
#    ${LIBXKBCOMMON_LIBRARIES}
#    m
#    ${LIBINPUT_LIBRARIES}
#    )
#message(STATUS "LIBWESTEROS_2_INCLUDE_DIRS: ${LIBWESTEROS_2_INCLUDE_DIRS}")
#message(STATUS "LIBWESTEROS_2_LIBS: ${LIBWESTEROS_2_LIBS}")
#
#add_library(weston-2 STATIC ${LIBWESTEROS_2_SOURCES})
#target_compile_definitions(weston-2 PRIVATE ${LIBWESTEROS_2_COMPILE_DEFINITIONS})
#target_compile_options(weston-2 PRIVATE ${LIBWESTEROS_2_COMPILER_OPTIONS})
#target_include_directories(weston-2 PRIVATE ${LIBWESTEROS_2_INCLUDE_DIRS})
#target_link_libraries(weston-2 PRIVATE ${LIBWESTEROS_2_LIBS} shared)
#set_target_properties(weston-2 PROPERTIES POSITION_INDEPENDENT_CODE ON)
#set_target_properties(weston-2 PROPERTIES LINK_FLAGS "-rpath ../lib")
#
#show_target_properties(weston-2)
#
#add_library(weston-2-shared SHARED ${LIBWESTEROS_2_SOURCES})
#target_compile_definitions(weston-2-shared PRIVATE ${LIBWESTEROS_2_COMPILE_DEFINITIONS})
#target_compile_options(weston-2-shared PRIVATE ${LIBWESTEROS_2_COMPILER_OPTIONS})
#target_include_directories(weston-2-shared PRIVATE ${LIBWESTEROS_2_INCLUDE_DIRS})
#target_link_libraries(weston-2-shared PRIVATE ${LIBWESTEROS_2_LIBS})
#set_target_properties(weston-2-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
#set_target_properties(weston-2-shared PROPERTIES LINK_FLAGS "${LINK_WHOLE_LIB} ${CMAKE_CURRENT_BINARY_DIR}/libshared.a ${LINK_NO_WHOLE_LIB} ${LINK_RPATH}")
#set_property(TARGET weston-2-shared PROPERTY VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
#set_property(TARGET weston-2-shared PROPERTY SOVERSION ${WESTEROS_VERSION_MAJOR})
#set_property(TARGET weston-2-shared PROPERTY OUTPUT_NAME weston-2)
#
#show_target_properties(weston-2-shared)
#
## weston-desktop-2
#set(WESTEROS_DESKTOP_VERSION_MAJOR 0)
#set(WESTEROS_DESKTOP_VERSION_MINOR 0)
#set(WESTEROS_DESKTOP_VERSION_MICRO 0)
#set(WESTEROS_DESKTOP_2_COMPILE_DEFINITIONS ${WESTEROS_COMPILE_DEFINITIONS} IN_WESTEROS)
#set(WESTEROS_DESKTOP_2_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
#set(WESTEROS_DESKTOP_2_SOURCES
#    libweston-desktop/client.c
#    libweston-desktop/libweston-desktop.c
#    libweston-desktop/libweston-desktop.h
#    libweston-desktop/seat.c
#    libweston-desktop/surface.c
#    libweston-desktop/wl-shell.c
#    libweston-desktop/xdg-shell-v6.c
#    libweston-desktop/xdg-shell-v5.c
#    libweston-desktop/xwayland.c
#    protocol/xdg-shell-unstable-v5-protocol.c
#    protocol/xdg-shell-unstable-v5-server-protocol.h
#    protocol/xdg-shell-unstable-v6-protocol.c
#    protocol/xdg-shell-unstable-v6-server-protocol.h)
#set(WESTEROS_DESKTOP_2_INCLUDE_DIRS
#    ${WESTEROS_INCLUDES}
#    ${PIXMAN_INCLUDE_DIRS}
#    ${LIBXKBCOMMON_INCLUDE_DIRS})
#set(WESTEROS_DESKTOP_2_LIBS
#    wayland-server-shared
#    ${PIXMAN_LIBRARIES}
#    ${LIBXKBCOMMON_LIBRARIES})
#message(STATUS "WESTEROS_DESKTOP_2_INCLUDE_DIRS: ${WESTEROS_DESKTOP_2_INCLUDE_DIRS}")
#message(STATUS "WESTEROS_DESKTOP_2_LIBS: ${WESTEROS_DESKTOP_2_LIBS}")
#
#add_library(weston-desktop-2 STATIC ${WESTEROS_DESKTOP_2_SOURCES})
#target_compile_definitions(weston-desktop-2 PRIVATE ${WESTEROS_DESKTOP_2_COMPILE_DEFINITIONS})
#target_compile_options(weston-desktop-2 PRIVATE ${WESTEROS_DESKTOP_2_COMPILER_OPTIONS})
#target_include_directories(weston-desktop-2 PRIVATE ${WESTEROS_DESKTOP_2_INCLUDE_DIRS})
#target_link_libraries(weston-desktop-2 PRIVATE weston-2 ${WESTEROS_DESKTOP_2_LIBS})
#set_target_properties(weston-desktop-2 PROPERTIES POSITION_INDEPENDENT_CODE ON)
#
#show_target_properties(weston-desktop-2)
#
#add_library(weston-desktop-2-shared SHARED ${WESTEROS_DESKTOP_2_SOURCES})
#target_compile_definitions(weston-desktop-2-shared PRIVATE ${WESTEROS_DESKTOP_2_COMPILE_DEFINITIONS})
#target_compile_options(weston-desktop-2-shared PRIVATE ${WESTEROS_DESKTOP_2_COMPILER_OPTIONS})
#target_include_directories(weston-desktop-2-shared PRIVATE ${WESTEROS_DESKTOP_2_INCLUDE_DIRS})
#target_link_libraries(weston-desktop-2-shared PRIVATE weston-2-shared ${WESTEROS_DESKTOP_2_LIBS})
#set_target_properties(weston-desktop-2-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
#set_target_properties(weston-desktop-2-shared PROPERTIES LINK_FLAGS ${LINK_RPATH})
#set_property(TARGET weston-desktop-2-shared PROPERTY VERSION ${WESTEROS_DESKTOP_VERSION_MAJOR}.${WESTEROS_DESKTOP_VERSION_MINOR}.${WESTEROS_DESKTOP_VERSION_MICRO})
#set_property(TARGET weston-desktop-2-shared PROPERTY SOVERSION ${WESTEROS_DESKTOP_VERSION_MAJOR})
#set_property(TARGET weston-desktop-2-shared PROPERTY OUTPUT_NAME weston-desktop-2)
#
#show_target_properties(weston-desktop-2-shared)
#
## gl-renderer
#set(GL_RENDERER_COMPILE_DEFINITIONS ${WESTEROS_COMPILE_DEFINITIONS})
#set(GL_RENDERER_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
#set(GL_RENDERER_SOURCES
#    libweston/gl-renderer.c
#    libweston/gl-renderer.h
#    libweston/vertex-clipping.c
#    libweston/vertex-clipping.h)
#set(GL_RENDERER_INCLUDE_DIRS
#    ${WESTEROS_INCLUDES}
#    ${PIXMAN_INCLUDE_DIRS}
#    ${LIBXKBCOMMON_INCLUDE_DIRS}
#    ${EGL_INCLUDE_DIRS}
#    ${GLESV2_INCLUDE_DIRS}
#    ${LIBDRM_INCLUDE_DIRS})
#set(GL_RENDERER_LIBS
#    ${EGL_LIBRARIES}
#    ${GLESV2_LIBRARIES}
#    wayland-server-shared
#    ${PIXMAN_LIBRARIES}
#    ${LIBXKBCOMMON_LIBRARIES})
#
#message(STATUS "GL_RENDERER_INCLUDE_DIRS: ${GL_RENDERER_INCLUDE_DIRS}")
#message(STATUS "GL_RENDERER_LIBS: ${GL_RENDERER_LIBS}")
#
#add_library(gl-renderer STATIC ${GL_RENDERER_SOURCES})
#target_compile_definitions(gl-renderer PRIVATE ${GL_RENDERER_COMPILE_DEFINITIONS})
#target_compile_options(gl-renderer PRIVATE ${GL_RENDERER_COMPILER_OPTIONS})
#target_include_directories(gl-renderer PRIVATE ${GL_RENDERER_INCLUDE_DIRS})
#target_link_libraries(gl-renderer PRIVATE weston-2 ${GL_RENDERER_LIBS})
#set_target_properties(gl-renderer PROPERTIES POSITION_INDEPENDENT_CODE ON)
#
#show_target_properties(gl-renderer)
#
#add_library(gl-renderer-shared SHARED ${GL_RENDERER_SOURCES})
#target_compile_definitions(gl-renderer-shared PRIVATE ${GL_RENDERER_COMPILE_DEFINITIONS})
#target_compile_options(gl-renderer-shared PRIVATE ${GL_RENDERER_COMPILER_OPTIONS})
#target_include_directories(gl-renderer-shared PRIVATE ${GL_RENDERER_INCLUDE_DIRS})
#target_link_libraries(gl-renderer-shared PRIVATE weston-2-shared ${GL_RENDERER_LIBS})
#set_target_properties(gl-renderer-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
#set_target_properties(gl-renderer-shared PROPERTIES LINK_FLAGS ${LINK_RPATH})
#set_property(TARGET gl-renderer-shared PROPERTY OUTPUT_NAME gl-renderer)
#
#show_target_properties(gl-renderer-shared)
#
## shared-cairo
#set(SHARED_CAIRO_COMPILE_DEFINITIONS ${WESTEROS_COMPILE_DEFINITIONS})
#set(SHARED_CAIRO_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
#set(SHARED_CAIRO_SOURCES
#    shared/image-loader.c
#    shared/image-loader.h
#    shared/cairo-util.c
#    shared/cairo-util.h
#    shared/frame.c)
#set(SHARED_CAIRO_INCLUDE_DIRS
#    ${WESTEROS_INCLUDES}
#    ${PIXMAN_INCLUDE_DIRS}
#    ${CAIRO_INCLUDE_DIRS}
#    ${LIBGLIB2_INCLUDE_DIRS}
#    ${LIBDRM_INCLUDE_DIRS}
#    ${FREETYPE_INCLUDE_DIRS}
#    ${LIBPNG_INCLUDE_DIRS}
#    ${LIBJPEGTURBO_INCLUDE_DIRS}
#    )
#set(SHARED_CAIRO_LIBS
#    ${PIXMAN_LIBRARIES}
#    ${CAIRO_LIBRARIES}
#    ${LIBPNG_LIBRARIES}
#    ${LIBJPEGTURBO_LIBRARIES}
#    )
#
#message(STATUS "SHARED_CAIRO_INCLUDE_DIRS: ${SHARED_CAIRO_INCLUDE_DIRS}")
#message(STATUS "SHARED_CAIRO_LIBS: ${SHARED_CAIRO_LIBS}")
#
#add_library(shared-cairo STATIC $<TARGET_OBJECTS:shared-obj> ${SHARED_CAIRO_SOURCES})
#target_compile_definitions(shared-cairo PRIVATE ${SHARED_CAIRO_COMPILE_DEFINITIONS})
#target_compile_options(shared-cairo PRIVATE ${SHARED_CAIRO_COMPILER_OPTIONS})
#target_include_directories(shared-cairo PUBLIC ${SHARED_CAIRO_INCLUDE_DIRS})
#target_link_libraries(shared-cairo PUBLIC weston-2 ${SHARED_CAIRO_LIBS})
#set_target_properties(shared-cairo PROPERTIES POSITION_INDEPENDENT_CODE ON)
#
#show_target_properties(shared-cairo)
#
### x11-backend
##set(X11_BACKEND_COMPILE_DEFINITIONS ${WESTEROS_COMPILE_DEFINITIONS})
##set(X11_BACKEND_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
##set(X11_BACKEND_SOURCES
##    libweston/compositor-x11.c
##    libweston/compositor-x11.h
##    shared/image-loader.c
##    shared/image-loader.h
##    shared/cairo-util.c
##    shared/cairo-util.h
##    shared/frame.c
##    )
##set(X11_BACKEND_INCLUDE_DIRS
##    ${WESTEROS_INCLUDES}
##    ${CAIRO_INCLUDE_DIRS}
##    ${FONTCONFIG_INCLUDE_DIRS}
##    ${FREETYPE_INCLUDE_DIRS}
##    ${EGL_INCLUDE_DIRS}
##    ${LIBXCB_XFIXES_INCLUDE_DIRS}
##    ${LIBFFI_INCLUDE_DIR}
##    ${LIBXCB_RENDER_INCLUDE_DIR}
##
##    ${LIBXCB_INCLUDE_DIRS}
##    ${LIBGBM_INCLUDE_DIRS}
##    ${PIXMAN_INCLUDE_DIRS}
##    ${LIBPNG_INCLUDE_DIRS}
##    ${LIBJPEG_INCLUDE_DIRS}
##    ${FREETYPE2_INCLUDE_DIRS}
##    ${LIBDRM_INCLUDE_DIRS}
##    ${GLIB_INCLUDE_DIRS}
##    ${EXPAT_INCLUDE_DIR}
##    ${LIBGBM_INCLUDE_DIR}
##    )
##set(X11_BACKEND_LIBS
##    shared
##    ${CAIRO_LIBRARIES}
##    ${FONTCONFIG_LIBRARIES}
##    ${FREETYPE_LIBRARIES}
##    ${EGL_LIBRARIES}
##    ${LIBXCB_XFIXES_LIBRARIES}
##    ${LIBGBM_LIBRARIES}
##    wayland-client-shared
##    ${LIBFFI_LIBRARIES}
##    dl
##    ${LIBXCB_RENDER_LIBRARIES}
##    GL
##    ${EXPAT_LIBRARIES}
##    glapi
##    Xext
##    Xdamage
##    Xfixes
##    xcb-glx
##    xcb-dri2
##    ${LIBXCB_LIBRARIES}
##    Xau
##    Xdmcp
##    ${LIBDRM_LIBRARIES}
##    pthread
##    rt
##    atomic
##    m
##    ${LIBPNG_LIBRARIES}
##    z
##    jpeg
##    weston-2-shared
##    X11-xcb
##    X11
##    xcb
##    xcb-shm
##    xcb-xkb
##    wayland-server-shared
##    ${PIXMAN_LIBRARIES}
##    ${LIBXKBCOMMON_LIBRARIES}
##    )
##
##message(STATUS "X11_BACKEND_INCLUDE_DIRS: ${X11_BACKEND_INCLUDE_DIRS}")
##message(STATUS "X11_BACKEND_LIBS: ${X11_BACKEND_LIBS}")
##
##add_library(x11-backend STATIC ${X11_BACKEND_SOURCES})
##target_compile_definitions(x11-backend PRIVATE ${X11_BACKEND_COMPILE_DEFINITIONS})
##target_compile_options(x11-backend PRIVATE ${X11_BACKEND_COMPILER_OPTIONS})
##target_include_directories(x11-backend PRIVATE ${X11_BACKEND_INCLUDE_DIRS})
##target_link_libraries(x11-backend PRIVATE weston-2 ${X11_BACKEND_LIBS})
##set_target_properties(x11-backend PROPERTIES POSITION_INDEPENDENT_CODE ON)
##set_target_properties(x11-backend PROPERTIES LINK_FLAGS )
##
##add_library(x11-backend-shared SHARED ${X11_BACKEND_SOURCES})
##target_compile_definitions(x11-backend-shared PRIVATE ${X11_BACKEND_COMPILE_DEFINITIONS})
##target_compile_options(x11-backend-shared PRIVATE ${X11_BACKEND_COMPILER_OPTIONS})
##target_include_directories(x11-backend-shared PRIVATE ${X11_BACKEND_INCLUDE_DIRS})
##target_link_libraries(x11-backend-shared PRIVATE weston-2-shared ${X11_BACKEND_LIBS})
##set_target_properties(x11-backend-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
##set_target_properties(x11-backend-shared PROPERTIES LINK_FLAGS ${LINK_RPATH})
###set_property(TARGET x11-backend-shared PROPERTY VERSION ${WESTEROS_VERSION_MAJOR}.${WESTEROS_VERSION_MINOR}.${WESTEROS_VERSION_MICRO})
###set_property(TARGET x11-backend-shared PROPERTY SOVERSION ${WESTEROS_VERSION_MAJOR})
##set_property(TARGET x11-backend-shared PROPERTY OUTPUT_NAME x11-backend)
#
## session-helper
#set(SESSION_HELPER_COMPILE_DEFINITIONS ${WESTEROS_COMPILE_DEFINITIONS})
#set(SESSION_HELPER_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
#set(SESSION_HELPER_SOURCES
#    libweston/launcher-util.c
#    libweston/launcher-util.h
#    libweston/launcher-weston-launch.c
#    libweston/launcher-direct.c
#    )
#set(SESSION_HELPER_INCLUDE_DIRS
#    ${WESTEROS_INCLUDES}
#    ${PIXMAN_INCLUDE_DIRS}
#    ${LIBDRM_INCLUDE_DIRS}
#    )
#set(SESSION_HELPER_LIBS
#    weston-2
#    ${LIBDRM_LIBRARIES})
#
#message(STATUS "SESSION_HELPER_INCLUDE_DIRS: ${SESSION_HELPER_INCLUDE_DIRS}")
#message(STATUS "SESSION_HELPER_LIBS: ${SESSION_HELPER_LIBS}")
#
#add_library(session-helper STATIC ${SESSION_HELPER_SOURCES})
#target_compile_definitions(session-helper PRIVATE ${SESSION_HELPER_COMPILE_DEFINITIONS})
#target_compile_options(session-helper PRIVATE ${SESSION_HELPER_COMPILER_OPTIONS})
#target_include_directories(session-helper PRIVATE ${SESSION_HELPER_INCLUDE_DIRS})
#target_link_libraries(session-helper PRIVATE weston-2 ${SESSION_HELPER_LIBS})
#set_target_properties(session-helper PROPERTIES POSITION_INDEPENDENT_CODE ON)
#
#show_target_properties(session-helper)
#
## drm-backend
#set(DRM_BACKEND_COMPILE_DEFINITIONS ${WESTEROS_COMPILE_DEFINITIONS})
#set(DRM_BACKEND_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
#set(DRM_BACKEND_SOURCES
#    libweston/compositor-drm.c
#    libweston/compositor-drm.h
#    libweston/libinput-seat.c
#    libweston/libinput-seat.h
#    libweston/libinput-device.c
#    libweston/libinput-device.h
#    libweston/libbacklight.c
#    libweston/libbacklight.h
#    )
#set(DRM_BACKEND_INCLUDE_DIRS
#    ${WESTEROS_INCLUDES}
#    ${LIBFFI_INCLUDE_DIRS}
#    ${LIBEVDEV_INCLUDE_DIRS}
#    ${PIXMAN_INCLUDE_DIRS}
#    ${LIBXKBCOMMON_INCLUDE_DIRS}
#    ${EUDEV_INCLUDE_DIRS}
#    ${LIBDRM_INCLUDE_DIRS}
#    ${LIBGBM_INCLUDE_DIRS}
#    ${MTDEV_INCLUDE_DIRS}
#    ${LIBINPUT_INCLUDE_DIRS}
#    )
#set(DRM_BACKEND_LIBS
#    ${LIBFFI_LIBRARIES}
#    ${LIBEVDEV_LIBRARIES}
#    rt
#    m
#    wayland-server-shared
#    ${PIXMAN_LIBRARIES}
#    ${LIBXKBCOMMON_LIBRARIES}
#    ${EUDEV_LIBRARIES}
#    ${LIBDRM_LIBRARIES}
#    ${LIBGBM_LIBRARIES}
#    ${MTDEV_LIBRARIES}
#    ${LIBINPUT_LIBRARIES})
#
#message(STATUS "DRM_BACKEND_INCLUDE_DIRS: ${DRM_BACKEND_INCLUDE_DIRS}")
#message(STATUS "DRM_BACKEND_LIBS: ${DRM_BACKEND_LIBS}")
#
#add_library(drm-backend STATIC ${DRM_BACKEND_SOURCES})
#target_compile_definitions(drm-backend PRIVATE ${DRM_BACKEND_COMPILE_DEFINITIONS})
#target_compile_options(drm-backend PRIVATE ${DRM_BACKEND_COMPILER_OPTIONS})
#target_include_directories(drm-backend PRIVATE ${DRM_BACKEND_INCLUDE_DIRS})
#target_link_libraries(drm-backend PRIVATE session-helper weston-2 ${DRM_BACKEND_LIBS} shared)
#set_target_properties(drm-backend PROPERTIES POSITION_INDEPENDENT_CODE ON)
#set_target_properties(drm-backend PROPERTIES LINK_FLAGS "-rpath ${CMAKE_INSTALL_PREFIX}/lib/libweston-2")
#
#show_target_properties(drm-backend)
#
#add_library(drm-backend-shared SHARED ${DRM_BACKEND_SOURCES})
#target_compile_definitions(drm-backend-shared PRIVATE ${DRM_BACKEND_COMPILE_DEFINITIONS})
#target_compile_options(drm-backend-shared PRIVATE ${DRM_BACKEND_COMPILER_OPTIONS})
#target_include_directories(drm-backend-shared PRIVATE ${DRM_BACKEND_INCLUDE_DIRS})
#target_link_libraries(drm-backend-shared PRIVATE weston-2-shared ${DRM_BACKEND_LIBS})
#set_target_properties(drm-backend-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
#set_target_properties(drm-backend-shared PROPERTIES LINK_FLAGS "${LINK_WHOLE_LIB} ${CMAKE_CURRENT_BINARY_DIR}/libsession-helper.a ${CMAKE_CURRENT_BINARY_DIR}/libshared.a ${LINK_NO_WHOLE_LIB} ${LINK_RPATH}")
#set_property(TARGET drm-backend-shared PROPERTY OUTPUT_NAME drm-backend)
#
#show_target_properties(drm-backend-shared)
#
## wayland-backend
#set(WAYLAND_BACKEND_COMPILE_DEFINITIONS ${WESTEROS_COMPILE_DEFINITIONS})
#set(WAYLAND_BACKEND_COMPILER_OPTIONS ${WESTEROS_COMPILER_OPTIONS} -pthread)
#set(WAYLAND_BACKEND_SOURCES
#    libweston/compositor-wayland.c
#    libweston/compositor-wayland.h
#    protocol/fullscreen-shell-unstable-v1-protocol.c
#    protocol/fullscreen-shell-unstable-v1-server-protocol.h
#    protocol/xdg-shell-unstable-v6-protocol.c
#    protocol/xdg-shell-unstable-v6-server-protocol.h)
#set(WAYLAND_BACKEND_INCLUDE_DIRS
#    ${WESTEROS_INCLUDES}
#    ${PIXMAN_INCLUDE_DIRS}
#    ${LIBXKBCOMMON_INCLUDE_DIRS}
#    ${LIBDRM_INCLUDE_DIRS}
#    ${WAYLAND_EGL_INCLUDE_DIRS}
#    )
#set(WAYLAND_BACKEND_LIBS
#    wayland-server-shared
#    ${PIXMAN_LIBRARIES}
#    ${LIBXKBCOMMON_LIBRARIES}
#    ${WAYLAND_EGL_LIBRARIES}
#    wayland-client-shared
#    wayland-cursor-shared
#)
#
#message(STATUS "WAYLAND_BACKEND_INCLUDE_DIRS: ${WAYLAND_BACKEND_INCLUDE_DIRS}")
#message(STATUS "WAYLAND_BACKEND_LIBS: ${WAYLAND_BACKEND_LIBS}")
#
#add_library(wayland-backend STATIC ${WAYLAND_BACKEND_SOURCES})
#target_compile_definitions(wayland-backend PRIVATE ${WAYLAND_BACKEND_COMPILE_DEFINITIONS})
#target_compile_options(wayland-backend PRIVATE ${WAYLAND_BACKEND_COMPILER_OPTIONS})
#target_include_directories(wayland-backend PRIVATE ${WAYLAND_BACKEND_INCLUDE_DIRS})
#target_link_libraries(wayland-backend PRIVATE shared-cairo weston-2 ${WAYLAND_BACKEND_LIBS} shared)
#set_target_properties(wayland-backend PROPERTIES POSITION_INDEPENDENT_CODE ON)
#set_target_properties(wayland-backend PROPERTIES LINK_FLAGS "-rpath ${CMAKE_INSTALL_PREFIX}/lib/libweston-2")
#
#show_target_properties(wayland-backend)
#
#add_library(wayland-backend-shared SHARED ${WAYLAND_BACKEND_SOURCES})
#target_compile_definitions(wayland-backend-shared PRIVATE ${WAYLAND_BACKEND_COMPILE_DEFINITIONS})
#target_compile_options(wayland-backend-shared PRIVATE ${WAYLAND_BACKEND_COMPILER_OPTIONS})
#target_include_directories(wayland-backend-shared PRIVATE ${WAYLAND_BACKEND_INCLUDE_DIRS})
#target_link_libraries(wayland-backend-shared PRIVATE
#    ${CAIRO_LIBRARIES}
#    ${FONTCONFIG_LIBRARIES}
#    ${FREETYPE_LIBRARIES}
#    ${EGL_LIBRARIES}
#    ${LIBXCB_XFIXES_LIBRARIES}
#    ${LIBGBM_LIBRARIES}
#    ${LIBFFI_LIBRARIES}
#    ${LIBXCB_SHM_LIBRARIES}
#    ${LIBXCB_RENDER_LIBRARIES}
##    ${LIBGL_LIBRARIES}
#    ${EXPAT_LIBRARIES}
##    glapi
##    ${XEXT_LIBRARIES}
##    ${XDAMAGE_LIBRARIES}
##    ${XFIXES_LIBRARIES}
##    ${X11_XCB_LIBRARIES}
##    ${LIBX11_LIBRARIES}
#    ${LIBXCB_LIBRARIES}
#    ${LIBXCB_GLX_LIBRARIES}
#    ${LIBXCB_DRI2_LIBRARIES}
#    ${LIBXCB_LIBRARIES}
#    ${LIBXAU_LIBRARIES}
#    ${LIBXDMCP_LIBRARIES}
#    ${LIBDRM_LIBRARIES}
#    pthread
#    rt
#    atomic
#    m
#    ${LIBPNG_LIBRARIES}
#    ${LIBJPEGTURBO_LIBRARIES}
#    weston-2-shared
#    ${WAYLAND_BACKEND_LIBS})
#set_target_properties(wayland-backend-shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
#set_target_properties(wayland-backend-shared PROPERTIES LINK_FLAGS "${LINK_WHOLE_LIB} ${CMAKE_CURRENT_BINARY_DIR}/libsession-helper.a ${CMAKE_CURRENT_BINARY_DIR}/libshared.a ${LINK_NO_WHOLE_LIB} ${LINK_RPATH}")
#set_property(TARGET wayland-backend-shared PROPERTY OUTPUT_NAME wayland-backend)
#
#show_target_properties(wayland-backend-shared)

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

add_custom_target(${WESTEROS_BASE} DEPENDS
    wayland-scanner
    westeros-simplebuffer-client
    westeros-simplebuffer-server
    westeros-simpleshell-client
    westeros-simpleshell-server
#    shared
#    weston-2
#    weston-2-shared
#    weston-desktop-2
#    weston-desktop-2-shared
#    gl-renderer
#    gl-renderer-shared
#    shared-cairo
#    x11-backend
#    x11-backend-shared
#    session-helper
#    drm-backend
#    drm-backend-shared
    )

add_dependencies(install_${PROJECT_NAME}
    ${WESTEROS_BASE})

#configure_file(libweston/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/libweston/version.h @ONLY)

#set(prefix ${CMAKE_INSTALL_PREFIX})
#set(exec_prefix ${CMAKE_INSTALL_PREFIX})
#set(libdir "\${exec_prefix}/lib")
#set(includedir "\${prefix}/include")
#set(libexecdir "\${exec_prefix}/libexec")
#set(PACKAGE "${PROJECT_NAME}")
#set(LIBWESTEROS_MAJOR ${WESTEROS_VERSION_MAJOR})

#configure_file(compositor/weston.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/compositor/weston.pc @ONLY)
#configure_file(libweston/libweston.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/libweston/libweston-2.pc @ONLY)
#configure_file(libweston-desktop/libweston-desktop.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/libweston-desktop/libweston-desktop-2.pc @ONLY)

#install(FILES
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/background.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/border.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/fullscreen.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/home.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_editor.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_flower.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_ivi_clickdot.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_ivi_flower.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_ivi_simple-egl.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_ivi_simple-shm.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_ivi_smoke.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_terminal.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/icon_window.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/panel.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/pattern.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/random.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/sidebyside.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/sign_close.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/sign_maximize.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/sign_minimize.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/terminal.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/tiling.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/wayland.png
#    ${CMAKE_CURRENT_SOURCE_DIR}/data/wayland.svg
#    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/weston
#    COMPONENT ${PROJECT_NAME})
