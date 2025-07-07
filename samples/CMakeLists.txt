add_executable(modbus_tcp_server samples/modbus_tcp_server)

target_link_libraries(${TEST_NAME} PUBLIC ${LIBRARY_NAME})
