include(${CMAKE_SOURCE_DIR}/cmake/nativeCompile.cmake)

add_executable(adcs-sensors adcs-sensors.c)
add_executable(adcs-sensors-util adcs-sensors-util.c)

#
# Libraries that adcs-sensors depends on
#
target_link_libraries(adcs-sensors proc polydrivers m pthread dl rt pthread )
target_link_libraries(adcs-sensors-util proc pthread polydrivers m dl rt )

IF (PROJECT_COMPILE)
# Include directories to search in
target_include_directories(adcs-sensors PUBLIC /opt/toolchain/toolchain-arm-linux/include)
target_include_directories(adcs-sensors-util PUBLIC /opt/toolchain/toolchain-arm-linux/include)
ENDIF (PROJECT_COMPILE)

INSTALL(TARGETS adcs-sensors DESTINATION bin COMPONENT binaries)
INSTALL(TARGETS adcs-sensors-util DESTINATION bin COMPONENT binaries)
INSTALL(FILES adcs-sensors.cmd.cfg DESTINATION /etc/ COMPONENT config)
INSTALL(FILES adcs-sensors-telemetry.cfg DESTINATION /usr/local/etc/dl_config COMPONENT config)
#
# Create symlinks for adcs-sensors-* utilities and install them
#
INSTALL(CODE "EXECUTE_PROCESS(COMMAND ln -sf adcs-sensors-util adcs-sensors-status WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})")
INSTALL(CODE "EXECUTE_PROCESS(COMMAND ln -sf adcs-sensors-util adcs-sensors-telemetry WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})")
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/adcs-sensors-status DESTINATION bin COMPONENT binaries)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/adcs-sensors-telemetry DESTINATION bin COMPONENT binaries)
