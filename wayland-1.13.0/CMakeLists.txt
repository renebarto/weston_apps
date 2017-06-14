project(wayland)

include(show_target_properties)

set(WAYLAND_VERSION_MAJOR 1)
set(WAYLAND_VERSION_MINOR 13)
set(WAYLAND_VERSION_MICRO 0)
set(WAYLAND_VERSION ${WAYLAND_VERSION_MAJOR}.${WAYLAND_VERSION_MINOR}.${WAYLAND_VERSION_MICRO})
set(WAYLAND_REQUIRED_VERSION ${WAYLAND_VERSION})
set(WAYLAND_NAME ${PROJECT_NAME})
set(WAYLAND_BASE ${WAYLAND_NAME}-${WAYLAND_VERSION})

find_package(LibFFI REQUIRED)
find_package(EXPAT REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(Wayland QUIET)

set(WAYLAND_COMPILE_DEFINITIONS HAVE_CONFIG_H
#    WAYLAND_DEBUG
    )
set(WAYLAND_COMPILER_OPTIONS -Wall -Wextra -Wno-unused-parameter -Wstrict-prototypes -Wmissing-prototypes -fvisibility=hidden)
set(WAYLAND_INCLUDE_DIRS . src protocol ${SYSTEM_INCLUDES})

# wayland-util
set(WAYLAND_UTIL_COMPILE_DEFINITIONS ${WAYLAND_COMPILE_DEFINITIONS})
set(WAYLAND_UTIL_COMPILER_OPTIONS ${WAYLAND_COMPILER_OPTIONS})
set(WAYLAND_UTIL_SOURCES
    src/wayland-util.c
    src/wayland-util.h)
set(WAYLAND_UTIL_INCLUDE_DIRS ${WAYLAND_INCLUDE_DIRS})
set(WAYLAND_UTIL_LINK_OPTIONS )
set(WAYLAND_UTIL_LIBS)

add_library(wayland-util STATIC ${WAYLAND_UTIL_SOURCES})
target_compile_definitions(wayland-util PRIVATE ${WAYLAND_UTIL_COMPILE_DEFINITIONS})
target_compile_options(wayland-util PRIVATE ${WAYLAND_UTIL_COMPILER_OPTIONS})
target_include_directories(wayland-util PRIVATE ${WAYLAND_UTIL_INCLUDE_DIRS})
target_link_libraries(wayland-util PRIVATE ${WAYLAND_UTIL_LIBS})
set_target_properties(wayland-util PROPERTIES POSITION_INDEPENDENT_CODE ON)
if(NOT "${WAYLAND_UTIL_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(wayland-util PROPERTIES LINK_FLAGS ${WAYLAND_UTIL_LINK_OPTIONS})
endif()

# wayland-scanner
set(WAYLAND_SCANNER_COMPILE_DEFINITIONS)
set(WAYLAND_SCANNER_COMPILER_OPTIONS ${WAYLAND_COMPILER_OPTIONS})
set(WAYLAND_SCANNER_SOURCES
    src/scanner.c
    src/dtddata.S)
set(WAYLAND_SCANNER_SOURCES_NODIST)
set(WAYLAND_SCANNER_INCLUDE_DIRS
    ${WAYLAND_INCLUDE_DIRS}
    ${EXPAT_INCLUDE_DIR}
    ${LIBXML2_INCLUDE_DIR})
set(WAYLAND_SCANNER_LINK_OPTIONS
    -L${CMAKE_INSTALL_PREFIX}/lib)
set(WAYLAND_SCANNER_LIBS
    wayland-util
    ${EXPAT_LIBRARIES}
    ${LIBXML2_LIBRARIES})

add_custom_target(wayland-scanner-dtd
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/protocol/wayland.dtd ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland.dtd.embed)
add_library(wayland-scanner-scanner OBJECT src/scanner.c)
target_compile_definitions(wayland-scanner-scanner PRIVATE ${WAYLAND_SCANNER_COMPILE_DEFINITIONS})
target_compile_options(wayland-scanner-scanner PRIVATE ${WAYLAND_SCANNER_COMPILER_OPTIONS})
target_include_directories(wayland-scanner-scanner PRIVATE ${WAYLAND_SCANNER_INCLUDE_DIRS})
set_target_properties(wayland-scanner-scanner PROPERTIES POSITION_INDEPENDENT_CODE ON)

enable_language(ASM)
set_property(SOURCE src/dtddata.S PROPERTY LANGUAGE ASM)
add_library(wayland-scanner-dtddata OBJECT src/dtddata.S)
target_compile_definitions(wayland-scanner-dtddata PRIVATE ${WAYLAND_SCANNER_COMPILE_DEFINITIONS})
target_compile_options(wayland-scanner-dtddata PRIVATE -O2)
target_include_directories(wayland-scanner-dtddata PRIVATE ${WAYLAND_SCANNER_INCLUDE_DIRS})
add_dependencies(wayland-scanner-dtddata wayland-scanner-dtd)

add_executable(wayland-scanner
    $<TARGET_OBJECTS:wayland-scanner-scanner>
    $<TARGET_OBJECTS:wayland-scanner-dtddata>)
target_link_libraries(wayland-scanner PRIVATE ${WAYLAND_SCANNER_LIBS})
if(NOT "${WAYLAND_SCANNER_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(wayland-scanner PROPERTIES LINK_FLAGS ${WAYLAND_SCANNER_LINK_OPTIONS})
endif()

# Create protocol sources
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/wayland-server-protocol.h
    DEPENDS wayland-scanner
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/wayland-scanner server-header < protocol/wayland.xml > protocol/wayland-server-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/wayland-protocol.c
    DEPENDS wayland-scanner
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/wayland-scanner code < protocol/wayland.xml > protocol/wayland-protocol.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/protocol/wayland-client-protocol.h
    DEPENDS wayland-scanner
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/wayland-scanner client-header < protocol/wayland.xml > protocol/wayland-client-protocol.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)

# wayland-private
set(WAYLAND_PRIVATE_COMPILE_DEFINITIONS ${WAYLAND_COMPILE_DEFINITIONS})
set(WAYLAND_PRIVATE_COMPILER_OPTIONS ${WAYLAND_COMPILER_OPTIONS})
set(WAYLAND_PRIVATE_SOURCES
    src/connection.c
    src/wayland-os.c
    src/wayland-os.h
    src/wayland-private.h)
set(WAYLAND_PRIVATE_INCLUDE_DIRS ${WAYLAND_INCLUDE_DIRS})
set(WAYLAND_PRIVATE_LINK_OPTIONS)
set(WAYLAND_PRIVATE_LIBS)
add_library(wayland-private STATIC ${WAYLAND_PRIVATE_SOURCES})
target_compile_definitions(wayland-private PRIVATE ${WAYLAND_PRIVATE_COMPILE_DEFINITIONS})
target_compile_options(wayland-private PRIVATE ${WAYLAND_PRIVATE_COMPILER_OPTIONS})
target_include_directories(wayland-private PRIVATE ${WAYLAND_PRIVATE_INCLUDE_DIRS})
target_link_libraries(wayland-private PRIVATE ${WAYLAND_PRIVATE_LIBS})
set_target_properties(wayland-private PROPERTIES POSITION_INDEPENDENT_CODE ON)
if(NOT "${WAYLAND_PRIVATE_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(wayland-private PROPERTIES LINK_FLAGS ${WAYLAND_PRIVATE_LINK_OPTIONS})
endif()

set(WAYLAND_CLIENT_COMPILE_DEFINITIONS ${WAYLAND_COMPILE_DEFINITIONS})
set(WAYLAND_CLIENT_COMPILER_OPTIONS ${WAYLAND_COMPILER_OPTIONS} -pthread)
set(WAYLAND_CLIENT_SOURCES
    src/wayland-client.c)
set(WAYLAND_CLIENT_SOURCES_NODIST
    protocol/wayland-server-protocol.h
    protocol/wayland-protocol.c)
set(WAYLAND_CLIENT_INCLUDE_DIRS
    ${WAYLAND_INCLUDE_DIRS}
    ${LIBFFI_INCLUDE_DIR})
set(WAYLAND_CLIENT_LINK_OPTIONS
    "-Wl,-rpath,'\$ORIGIN/../lib/'")
set(WAYLAND_CLIENT_LIBS
    wayland-private
    wayland-util
    ${LIBFFI_LIBRARIES}
    rt
    m
    pthread)
set(WAYLAND_CLIENT_VERSION_MAJOR 0)
set(WAYLAND_CLIENT_VERSION_MINOR 3)
set(WAYLAND_CLIENT_VERSION_MICRO 0)
add_library(wayland-client-obj OBJECT ${WAYLAND_CLIENT_SOURCES} ${WAYLAND_CLIENT_SOURCES_NODIST})
target_compile_definitions(wayland-client-obj PRIVATE ${WAYLAND_CLIENT_COMPILE_DEFINITIONS})
target_compile_options(wayland-client-obj PRIVATE ${WAYLAND_CLIENT_COMPILER_OPTIONS})
target_include_directories(wayland-client-obj PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIRS})
set_target_properties(wayland-client-obj PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(wayland-client STATIC $<TARGET_OBJECTS:wayland-client-obj>)
target_link_libraries(wayland-client PRIVATE ${WAYLAND_CLIENT_LIBS})
if(NOT "${WAYLAND_CLIENT_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(wayland-client PROPERTIES LINK_FLAGS ${WAYLAND_CLIENT_LINK_OPTIONS})
endif()

add_library(wayland-client-shared SHARED $<TARGET_OBJECTS:wayland-client-obj>)
target_link_libraries(wayland-client-shared PRIVATE ${WAYLAND_CLIENT_LIBS})
if(NOT "${WAYLAND_CLIENT_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(wayland-client-shared PROPERTIES LINK_FLAGS ${WAYLAND_CLIENT_LINK_OPTIONS})
endif()
set_property(TARGET wayland-client-shared PROPERTY VERSION ${WAYLAND_CLIENT_VERSION_MAJOR}.${WAYLAND_CLIENT_VERSION_MINOR}.${WAYLAND_CLIENT_VERSION_MICRO})
set_property(TARGET wayland-client-shared PROPERTY SOVERSION ${WAYLAND_CLIENT_VERSION_MAJOR})
set_property(TARGET wayland-client-shared PROPERTY OUTPUT_NAME wayland-client)

set(WAYLAND_SERVER_COMPILE_DEFINITIONS ${WAYLAND_COMPILE_DEFINITIONS})
set(WAYLAND_SERVER_COMPILER_OPTIONS ${WAYLAND_COMPILER_OPTIONS} -pthread)
set(WAYLAND_SERVER_SOURCES
    src/wayland-server.c
    src/wayland-shm.c
    src/event-loop.c)
set(WAYLAND_SERVER_SOURCES_NODIST
    protocol/wayland-server-protocol.h
    protocol/wayland-protocol.c)
set(WAYLAND_SERVER_INCLUDE_DIRS
    ${WAYLAND_INCLUDE_DIRS}
    ${LIBFFI_INCLUDE_DIR})
set(WAYLAND_SERVER_LINK_OPTIONS
    "-Wl,-rpath,'\$ORIGIN/../lib/'")
set(WAYLAND_SERVER_LIBS
    wayland-private
    wayland-util
    ${LIBFFI_LIBRARIES}
    rt
    m
    pthread)
set(WAYLAND_SERVER_VERSION_MAJOR 0)
set(WAYLAND_SERVER_VERSION_MINOR 1)
set(WAYLAND_SERVER_VERSION_MICRO 0)

add_library(wayland-server-obj OBJECT ${WAYLAND_SERVER_SOURCES} ${WAYLAND_SERVER_SOURCES_NODIST})
target_compile_definitions(wayland-server-obj PRIVATE ${WAYLAND_SERVER_COMPILE_DEFINITIONS})
target_compile_options(wayland-server-obj PRIVATE ${WAYLAND_SERVER_COMPILER_OPTIONS})
target_include_directories(wayland-server-obj PRIVATE ${WAYLAND_SERVER_INCLUDE_DIRS})
set_target_properties(wayland-server-obj PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(wayland-server STATIC $<TARGET_OBJECTS:wayland-server-obj>)
target_link_libraries(wayland-server PRIVATE ${WAYLAND_SERVER_LIBS})
if(NOT "${WAYLAND_SERVER_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(wayland-server PROPERTIES LINK_FLAGS ${WAYLAND_SERVER_LINK_OPTIONS})
endif()

add_library(wayland-server-shared SHARED $<TARGET_OBJECTS:wayland-server-obj>)
target_link_libraries(wayland-server-shared PRIVATE ${WAYLAND_SERVER_LIBS})
if(NOT "${WAYLAND_SERVER_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(wayland-server-shared PROPERTIES LINK_FLAGS ${WAYLAND_SERVER_LINK_OPTIONS})
endif()
set_property(TARGET wayland-server-shared PROPERTY VERSION ${WAYLAND_SERVER_VERSION_MAJOR}.${WAYLAND_SERVER_VERSION_MINOR}.${WAYLAND_SERVER_VERSION_MICRO})
set_property(TARGET wayland-server-shared PROPERTY SOVERSION ${WAYLAND_SERVER_VERSION_MAJOR})
set_property(TARGET wayland-server-shared PROPERTY OUTPUT_NAME wayland-server)

set(ICONDIR ${CMAKE_INSTALL_PREFIX}/share/icons)
set(WAYLAND_CURSOR_COMPILE_DEFINITIONS
    ${WAYLAND_COMPILE_DEFINITIONS}
    ICONDIR=\"${ICONDIR}\")
set(WAYLAND_CURSOR_COMPILER_OPTIONS ${WAYLAND_COMPILER_OPTIONS})
set(WAYLAND_CURSOR_SOURCES
    cursor/wayland-cursor.c
    cursor/os-compatibility.c
    cursor/os-compatibility.h
    cursor/cursor-data.h
    cursor/xcursor.c
    cursor/xcursor.h)
set(WAYLAND_CURSOR_SOURCES_NODIST
    )
set(WAYLAND_CURSOR_INCLUDE_DIRS
    ${WAYLAND_INCLUDE_DIRS}
    ${EXPAT_INCLUDE_DIR}
    ${LIBXML2_INCLUDE_DIR})
set(WAYLAND_CURSOR_LINK_OPTIONS
    )
set(WAYLAND_CURSOR_LIBS
    wayland-client
    ${EXPAT_LIBRARIES}
    ${LIBXML2_LIBRARIES})
set(WAYLAND_CURSOR_VERSION_MAJOR 0)
set(WAYLAND_CURSOR_VERSION_MINOR 0)
set(WAYLAND_CURSOR_VERSION_MICRO 0)
add_library(wayland-cursor-obj OBJECT ${WAYLAND_CURSOR_SOURCES} ${WAYLAND_CURSOR_SOURCES_NODIST})
target_compile_definitions(wayland-cursor-obj PRIVATE ${WAYLAND_CURSOR_COMPILE_DEFINITIONS})
target_compile_options(wayland-cursor-obj PRIVATE ${WAYLAND_CURSOR_COMPILER_OPTIONS})
target_include_directories(wayland-cursor-obj PRIVATE ${WAYLAND_CURSOR_INCLUDE_DIRS})
set_target_properties(wayland-cursor-obj PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(wayland-cursor STATIC $<TARGET_OBJECTS:wayland-cursor-obj>)
target_link_libraries(wayland-cursor PRIVATE ${WAYLAND_CURSOR_LIBS})
if(NOT "${WAYLAND_CURSOR_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(wayland-cursor PROPERTIES LINK_FLAGS ${WAYLAND_CURSOR_LINK_OPTIONS})
endif()

add_library(wayland-cursor-shared SHARED $<TARGET_OBJECTS:wayland-cursor-obj>)
target_link_libraries(wayland-cursor-shared PRIVATE ${WAYLAND_CURSOR_LIBS})
if(NOT "${WAYLAND_CURSOR_LINK_OPTIONS}" STREQUAL "")
    set_target_properties(wayland-cursor-shared PROPERTIES LINK_FLAGS ${WAYLAND_CURSOR_LINK_OPTIONS})
endif()
set_property(TARGET wayland-cursor-shared PROPERTY VERSION ${WAYLAND_CURSOR_VERSION_MAJOR}.${WAYLAND_CURSOR_VERSION_MINOR}.${WAYLAND_CURSOR_VERSION_MICRO})
set_property(TARGET wayland-cursor-shared PROPERTY SOVERSION ${WAYLAND_CURSOR_VERSION_MAJOR})
set_property(TARGET wayland-cursor-shared PROPERTY OUTPUT_NAME wayland-cursor)

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

add_custom_target(${WAYLAND_BASE}
    DEPENDS wayland-client wayland-client-shared wayland-server wayland-server-shared wayland-cursor wayland-cursor-shared wayland-scanner)

add_dependencies(install_${PROJECT_NAME}
    ${WAYLAND_BASE})

set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix "\${prefix}")
set(bindir "\${exec_prefix}/bin")
set(libdir "\${exec_prefix}/lib")
set(includedir "\${prefix}/include")
set(datarootdir "\${prefix}/share")
set(datadir "\${datarootdir}")
set(PACKAGE "${PROJECT_NAME}")
set(PACKAGE_VERSION "${WAYLAND_VERSION}")

configure_file(src/wayland-client.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-client.pc @ONLY)
configure_file(src/wayland-server.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-server.pc @ONLY)
configure_file(cursor/wayland-cursor.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/cursor/wayland-cursor.pc @ONLY)
configure_file(src/wayland-scanner.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-scanner.pc @ONLY)

set(abs_top_builddir "${CMAKE_CURRENT_SOURCE_DIR}")
set(abs_top_srcdir "${CMAKE_CURRENT_SOURCE_DIR}")
set(abs_builddir "${CMAKE_CURRENT_BINARY_DIR}/cursor")
set(abs_srcdir "${CMAKE_CURRENT_BINARY_DIR}/cursor")

configure_file(cursor/wayland-cursor-uninstalled.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/cursor/wayland-cursor-uninstalled.pc @ONLY)

set(abs_builddir "${CMAKE_CURRENT_BINARY_DIR}/src")
set(abs_srcdir "${CMAKE_CURRENT_BINARY_DIR}/src")

configure_file(src/wayland-client-uninstalled.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-client-uninstalled.pc @ONLY)
configure_file(src/wayland-server-uninstalled.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-server-uninstalled.pc @ONLY)
configure_file(src/wayland-scanner-uninstalled.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-scanner-uninstalled.pc @ONLY)
configure_file(src/wayland-version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-version.h @ONLY)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-client.pc
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
    COMPONENT ${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-server.pc
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
    COMPONENT ${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cursor/wayland-cursor.pc
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
    COMPONENT ${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-scanner.pc
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
    COMPONENT ${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/protocol/wayland.dtd
    DESTINATION ${CMAKE_INSTALL_PREFIX}/shared/wayland
    COMPONENT ${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/protocol/wayland.xml
    DESTINATION ${CMAKE_INSTALL_PREFIX}/shared/wayland
    COMPONENT ${PROJECT_NAME})
install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-util.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-server.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-server-core.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-client.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-client-core.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-egl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-egl-core.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wayland-version.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cursor/wayland-cursor.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    COMPONENT ${PROJECT_NAME})
install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/protocol/wayland-server-protocol.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    COMPONENT ${PROJECT_NAME})
install(TARGETS wayland-scanner
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    COMPONENT ${PROJECT_NAME})
install(TARGETS wayland-client
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})
install(TARGETS wayland-client-shared
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})
install(TARGETS wayland-server
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})
install(TARGETS wayland-server-shared
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})
install(TARGETS wayland-cursor
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})
install(TARGETS wayland-cursor-shared
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT ${PROJECT_NAME})
