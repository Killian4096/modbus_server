add_executable(modbus_tcp_server main.c)

target_link_libraries(modbus_tcp_server PUBLIC modbus_server)
