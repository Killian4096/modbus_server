set(LIBRARY_NAME modbus_slave)

add_library(${LIBRARY_NAME} src/modbus_slave.c)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TEST_NAME modbus_slave_tests)

add_executable(${TEST_NAME} tests/main.c)

target_link_libraries(${TEST_NAME} PUBLIC ${LIBRARY_NAME})

target_link_libraries(${TEST_NAME} PUBLIC cunit)
