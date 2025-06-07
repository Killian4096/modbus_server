set(LIBRARY_NAME modbus_slave)

add_library(${LIBRARY_NAME} src/modbus_slave.c)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
