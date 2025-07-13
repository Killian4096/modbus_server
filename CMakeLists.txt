cmake_minimum_required(VERSION 3.28)

project(modbus_server)

set(LIBRARY_NAME modbus_server)

add_library(${LIBRARY_NAME} src/modbus_server.c)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TEST_NAME modbus_server_tests)

add_executable(${TEST_NAME} tests/main.c)

target_link_libraries(${TEST_NAME} PUBLIC ${LIBRARY_NAME})


target_compile_definitions(${LIBRARY_NAME} PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_RTU)
target_compile_definitions(${LIBRARY_NAME} PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_ASCII)
target_compile_definitions(${LIBRARY_NAME} PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_RTU_OVER_TCP)
target_compile_definitions(${LIBRARY_NAME} PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_TCP)


target_link_libraries(${TEST_NAME} PUBLIC cunit)

add_subdirectory(samples)
