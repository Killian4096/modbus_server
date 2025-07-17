cmake_minimum_required(VERSION 3.28)

project(modbus_server)

add_library(modbus_server src/modbus_server.c)
add_library(modbus_server_RTU src/modbus_server.c)
add_library(modbus_server_ASCII src/modbus_server.c)
add_library(modbus_server_TCP src/modbus_server.c)

target_include_directories(modbus_server       PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(modbus_server_RTU   PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(modbus_server_ASCII PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(modbus_server_TCP   PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(modbus_server       PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_RTU)
target_compile_definitions(modbus_server       PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_ASCII)
target_compile_definitions(modbus_server       PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_TCP)

target_compile_definitions(modbus_server_RTU   PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_RTU)
target_compile_definitions(modbus_server_ASCII PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_ASCII)
target_compile_definitions(modbus_server_TCP   PRIVATE MODBUS_SERVER_COMPILE_PROTOCOL_TCP)


if (BUILD_SAMPLES)
    add_subdirectory(samples)
endif ()

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
