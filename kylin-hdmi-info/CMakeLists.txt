project(kylin-hmdi-info)

include(show_target_properties)

# kylin-hmdi-info
set(KYLIN_HDMI_INFO_COMPILE_DEFINITIONS
    )
set(KYLIN_HDMI_INFO_COMPILER_OPTIONS
    -g -O0 -Wall -Wextra -pthread)
set(KYLIN_HDMI_INFO_SOURCES
    main.cpp
    )
set(KYLIN_HDMI_INFO_INCLUDE_DIRS
    ${STAGING_DIR}/usr/include/realtek/
    ${STAGING_DIR}/usr/include/realtek/system/core/include/
    ${STAGING_DIR}/usr/include/realtek/hardware/realtek/hdmitx/
    ${STAGING_DIR}/usr/include/realtek/device/realtek/proprietary/libs/rtk_libs/common/IPC/generate/include/system/
    ${STAGING_DIR}/usr/include/realtek/device/realtek/proprietary/libs/rtk_libs/common/IPC/include/)
set(KYLIN_HDMI_INFO_LIBS
    HdmiWrapper
    hardware        # Defines hardware API from hardware/libhardware/include/hardware/hardware.h
    utils           # Defines android::String16 and others from system/core/include/utils/String16.h
    cutils          # For android_atomic_inc and android_atomic_dec
    pthread
    udev
    dl
    )
set(KYLIN_HDMI_INFO_LINK_FLAGS
    -L${STAGING_DIR}/usr/lib/realtek/ # For a.o. libutils.a
    )

message(STATUS "KYLIN_HDMI_INFO_COMPILE_DEFINITIONS : ${KYLIN_HDMI_INFO_COMPILE_DEFINITIONS}")
message(STATUS "KYLIN_HDMI_INFO_COMPILER_OPTIONS    : ${KYLIN_HDMI_INFO_COMPILER_OPTIONS}")
message(STATUS "KYLIN_HDMI_INFO_INCLUDE_DIRS        : ${KYLIN_HDMI_INFO_INCLUDE_DIRS}")
message(STATUS "KYLIN_HDMI_INFO_LIBS                : ${KYLIN_HDMI_INFO_LIBS}")

add_executable(kylin-hmdi-info ${KYLIN_HDMI_INFO_SOURCES})
target_compile_definitions(kylin-hmdi-info PRIVATE ${KYLIN_HDMI_INFO_COMPILE_DEFINITIONS})
target_compile_options(kylin-hmdi-info PRIVATE ${KYLIN_HDMI_INFO_COMPILER_OPTIONS})
target_include_directories(kylin-hmdi-info PRIVATE ${KYLIN_HDMI_INFO_INCLUDE_DIRS})
target_link_libraries(kylin-hmdi-info PRIVATE ${KYLIN_HDMI_INFO_LIBS})
set_target_properties(kylin-hmdi-info PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(kylin-hmdi-info PROPERTIES RUNTIME_OUTPUT_NAME kylin-hmdi-info)
set_target_properties(kylin-hmdi-info PROPERTIES LINK_FLAGS "${KYLIN_HDMI_INFO_LINK_FLAGS} ${LINK_RPATH}")

show_target_properties(kylin-hmdi-info)

add_custom_target(uninstall_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${PROJECT_NAME} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake
    COMMENT "Uninstalling ${PROJECT_NAME}")

add_custom_target(install_${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -DCOMPONENT=${PROJECT_NAME} -P ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMENT "Installing ${PROJECT_NAME}")

add_dependencies(install-components install_${PROJECT_NAME})

add_dependencies(uninstall-components uninstall_${PROJECT_NAME})

install(TARGETS kylin-hmdi-info
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    COMPONENT ${PROJECT_NAME})
