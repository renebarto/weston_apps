project(kylin-simple-app)

include(show_target_properties)

# kylin-simple-app
set(KYLIN_SIMPLE_APP_COMPILE_DEFINITIONS
    )
set(KYLIN_SIMPLE_APP_COMPILER_OPTIONS
    -g -O0 -Wall -Wextra -pthread)
set(KYLIN_SIMPLE_APP_SOURCES
    main.cpp
    )
set(KYLIN_SIMPLE_APP_INCLUDE_DIRS
    )
set(KYLIN_SIMPLE_APP_LIBS
    HdmiWrapper
    pthread
    udev
    )
message(STATUS "KYLIN_SIMPLE_APP_COMPILE_DEFINITIONS : ${KYLIN_SIMPLE_APP_COMPILE_DEFINITIONS}")
message(STATUS "KYLIN_SIMPLE_APP_COMPILER_OPTIONS    : ${KYLIN_SIMPLE_APP_COMPILER_OPTIONS}")
message(STATUS "KYLIN_SIMPLE_APP_INCLUDE_DIRS        : ${KYLIN_SIMPLE_APP_INCLUDE_DIRS}")
message(STATUS "KYLIN_SIMPLE_APP_LIBS                : ${KYLIN_SIMPLE_APP_LIBS}")

add_executable(kylin-simple-app ${KYLIN_SIMPLE_APP_SOURCES})
target_compile_definitions(kylin-simple-app PRIVATE ${KYLIN_SIMPLE_APP_COMPILE_DEFINITIONS})
target_compile_options(kylin-simple-app PRIVATE ${KYLIN_SIMPLE_APP_COMPILER_OPTIONS})
target_include_directories(kylin-simple-app PRIVATE ${KYLIN_SIMPLE_APP_INCLUDE_DIRS})
target_link_libraries(kylin-simple-app PRIVATE ${KYLIN_SIMPLE_APP_LIBS})
set_target_properties(kylin-simple-app PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(kylin-simple-app PROPERTIES RUNTIME_OUTPUT_NAME kylin-simple-app)
set_target_properties(kylin-simple-app PROPERTIES LINK_FLAGS "${LINK_RPATH}")

show_target_properties(kylin-simple-app)

add_custom_target(uninstall_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${PROJECT_NAME} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake
    COMMENT "Uninstalling ${PROJECT_NAME}")

add_custom_target(install_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${PROJECT_NAME} -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMENT "Installing ${PROJECT_NAME}")

add_dependencies(install-components install_${PROJECT_NAME})

add_dependencies(uninstall-components uninstall_${PROJECT_NAME})

install(TARGETS kylin-simple-app
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    COMPONENT ${PROJECT_NAME})
