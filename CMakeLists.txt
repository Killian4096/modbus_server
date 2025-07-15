cmake_minimum_required(VERSION 3.28)

project(modbus_server)

set(LIBRARY_NAME modbus_server)

add_library(${LIBRARY_NAME} src/modbus_server.c)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(samples)
add_subdirectory(tests)
