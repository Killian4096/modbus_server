void unit_tests_exceptions(int test_protocol){
    unit_tests_exception_01(test_protocol);
}

void unit_tests_exception_01(int test_protocol){
    modbus_server_t mst;
    modbus_server_t* modbus_server_tag = &mst;
    modbus_server_init(modbus_server_tag, 1, test_protocol);

    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 100);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 0) == 100|(1<<7));
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));

}
