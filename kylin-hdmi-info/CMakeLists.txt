project(kylin-simple-app)

include(show_target_properties)

# hdmi-test
set(HDMI_TEST_COMPILE_DEFINITIONS
    )
set(HDMI_TEST_COMPILER_OPTIONS
    -g -O0 -Wall -Wextra -pthread)
set(HDMI_TEST_SOURCES
    main.cpp
    )
set(HDMI_TEST_INCLUDE_DIRS
    )
set(HDMI_TEST_LIBS
    HdmiWrapper
    pthread
    udev
    )
message(STATUS "HDMI_TEST_COMPILE_DEFINITIONS : ${HDMI_TEST_COMPILE_DEFINITIONS}")
message(STATUS "HDMI_TEST_COMPILER_OPTIONS    : ${HDMI_TEST_COMPILER_OPTIONS}")
message(STATUS "HDMI_TEST_INCLUDE_DIRS        : ${HDMI_TEST_INCLUDE_DIRS}")
message(STATUS "HDMI_TEST_LIBS                : ${HDMI_TEST_LIBS}")

add_executable(hdmi-test ${HDMI_TEST_SOURCES})
target_compile_definitions(hdmi-test PRIVATE ${HDMI_TEST_COMPILE_DEFINITIONS})
target_compile_options(hdmi-test PRIVATE ${HDMI_TEST_COMPILER_OPTIONS})
target_include_directories(hdmi-test PRIVATE ${HDMI_TEST_INCLUDE_DIRS})
target_link_libraries(hdmi-test PRIVATE ${HDMI_TEST_LIBS})
set_target_properties(hdmi-test PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(hdmi-test PROPERTIES RUNTIME_OUTPUT_NAME hdmi-test)
set_target_properties(hdmi-test PROPERTIES LINK_FLAGS "${LINK_RPATH}")

show_target_properties(hdmi-test)

add_custom_target(uninstall_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${PROJECT_NAME} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake
    COMMENT "Uninstalling ${PROJECT_NAME}")

add_custom_target(install_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${PROJECT_NAME} -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMENT "Installing ${PROJECT_NAME}")

add_dependencies(install-components install_${PROJECT_NAME})

add_dependencies(uninstall-components uninstall_${PROJECT_NAME})

install(TARGETS hdmi-test
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    COMPONENT ${PROJECT_NAME})
