void unit_tests_diagnostics(int test_protocol){
    unit_tests_diagnostic_00(test_protocol);
    unit_tests_diagnostic_01(test_protocol);
    unit_tests_diagnostic_04(test_protocol);
}

void unit_tests_diagnostic_00(int test_protocol){
    modbus_server_t mst;
    modbus_server_t* modbus_server_tag = &mst;
    modbus_server_init(modbus_server_tag, 1, test_protocol);


    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 8);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 0) == 8);
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 1) == 0);
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 2) == 0);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));
}


void unit_tests_diagnostic_01(int test_protocol){
    modbus_server_t mst;
    modbus_server_t* modbus_server_tag = &mst;
    modbus_server_init(modbus_server_tag, 1, test_protocol);
    //Valid 0x00FF

    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 8);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 1);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0xFF);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 0) == 8);
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 1) == 0);
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 2) == 1);
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 3) == 0xFF);
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 4) == 0);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));


    //Invalid data
    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 8);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 1);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0xFF);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 0) == 8|(1<<7));
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 1) == 1);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));
}






void unit_tests_diagnostic_04(int test_protocol){
    modbus_server_t mst;
    modbus_server_t* modbus_server_tag = &mst;
    modbus_server_init(modbus_server_tag, 1, test_protocol);

    //Invalid data
    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 8);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 4);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0xFF);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 0) == 8|(1<<7));
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 1) == 1);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));

    //Invalid data 0xFFFF
    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 8);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 4);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0xFF);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0xFF);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 0) == 8|(1<<7));
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 1) == 3);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));

    //Valid turn off

    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 8);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 4);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_output_message_buffer_length(modbus_server_tag) == 0);

    //Check cant talk
    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 8);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_output_message_buffer_length(modbus_server_tag) == 0);

    //Valid turn on

    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 8);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 1);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0xFF);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 0) == 8);
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 1) == 0);
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 2) == 1);
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 3) == 0xFF);
    CU_ASSERT(modbus_server_test_output_data_buffer_get_formatted(modbus_server_tag, 4) == 0);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));

    //Check can talk

}


























