set(TEST_NAME modbus_server_tests)

add_executable(${TEST_NAME} src/main.c)

target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${TEST_NAME} PUBLIC modbus_server)


target_compile_definitions(modbus_server PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_RTU)
target_compile_definitions(modbus_server PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_ASCII)
target_compile_definitions(modbus_server PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_RTU_OVER_TCP)
target_compile_definitions(modbus_server PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_TCP)


target_link_libraries(${TEST_NAME} PUBLIC cunit)
