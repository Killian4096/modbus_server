#include "CRC.h"
#include "LRC.h"

//Includes from lib
uint16_t modbus_server_test_ASCII_byte_to_ascii(uint8_t);
uint8_t modbus_server_test_ASCII_ascii_to_byte(uint16_t);
uint8_t modbus_server_test_ASCII_ascii_to_byte_lookup_table(uint8_t);

//Utility
void modbus_server_test_input_message_buffer_generate_header(modbus_server_t*);

void modbus_server_test_input_message_buffer_generate_header_RTU(modbus_server_t*);
void modbus_server_test_input_message_buffer_generate_header_ASCII(modbus_server_t*);
void modbus_server_test_input_message_buffer_generate_header_TCP(modbus_server_t*);

void modbus_server_test_input_message_buffer_generate_footer(modbus_server_t*);
void modbus_server_test_input_message_buffer_generate_footer_RTU(modbus_server_t*);
void modbus_server_test_input_message_buffer_generate_footer_ASCII(modbus_server_t*);
void modbus_server_test_input_message_buffer_generate_footer_TCP(modbus_server_t*);


//ACCESSORS
void modbus_server_test_input_message_buffer_add_formatted(modbus_server_t*, uint8_t);
void modbus_server_test_input_message_buffer_add_formatted_RTU(modbus_server_t*, uint8_t);
void modbus_server_test_input_message_buffer_add_formatted_ASCII(modbus_server_t*, uint8_t);

uint8_t modbus_server_test_output_message_buffer_get_formatted(modbus_server_t*, size_t);
uint8_t modbus_server_test_output_message_buffer_get_formatted_RTU(modbus_server_t*, size_t);
uint8_t modbus_server_test_output_message_buffer_get_formatted_ASCII(modbus_server_t*, size_t);



uint8_t modbus_server_test_output_message_buffer_check_header(modbus_server_t*);
uint8_t modbus_server_test_output_message_buffer_check_header_RTU(modbus_server_t*);
uint8_t modbus_server_test_output_message_buffer_check_header_ASCII(modbus_server_t*);
uint8_t modbus_server_test_output_message_buffer_check_header_TCP(modbus_server_t*);

uint8_t modbus_server_test_output_message_buffer_check_footer(modbus_server_t*);
uint8_t modbus_server_test_output_message_buffer_check_footer_RTU(modbus_server_t*);
uint8_t modbus_server_test_output_message_buffer_check_footer_ASCII(modbus_server_t*);
uint8_t modbus_server_test_output_message_buffer_check_footer_TCP(modbus_server_t*);

//Data Buffer
uint8_t modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_t*, size_t);
uint8_t modbus_server_test_output_PDU_mapper_get_formatted_RTU(modbus_server_t*, size_t);
uint8_t modbus_server_test_output_PDU_mapper_get_formatted_ASCII(modbus_server_t*, size_t);
uint8_t modbus_server_test_output_PDU_mapper_get_formatted_TCP(modbus_server_t*, size_t);


//UNIT TESTS
void modbus_server_rtu_tests();
void modbus_server_ascii_tests();
void modbus_server_tcp_tests();
void unit_tests_standard(int);


//FUNCTIONS
void unit_tests_function(int);
void unit_tests_function_01(int);
void unit_tests_function_02(int);
void unit_tests_function_03(int);
void unit_tests_function_04(int);


//EXCEPTIONS


//DIAGNOSICS
void unit_tests_diagnostics(int);
void unit_tests_diagnostic_00(int);
void unit_tests_diagnostic_01(int);
void unit_tests_diagnostic_04(int);
