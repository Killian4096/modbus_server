void unit_test_diagnostics(void){
    unit_test_diagnostic_00();
    unit_test_diagnostic_01();
    unit_test_diagnostic_04();
}

void unit_test_diagnostic_00(void){
    modbus_slave_t mst;
    modbus_slave_t* modbus_slave_tag = &mst;
    modbus_slave_init(modbus_slave_tag, 1, TEST_PROTOCOL);


    modbus_slave_test_input_message_buffer_generate_header(modbus_slave_tag);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 8);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_generate_footer(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_test_output_message_buffer_check_header(modbus_slave_tag));
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 0) == 8);
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 1) == 0);
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 2) == 0);
    CU_ASSERT(modbus_slave_test_output_message_buffer_check_footer(modbus_slave_tag));
}


void unit_test_diagnostic_01(void){
    modbus_slave_t mst;
    modbus_slave_t* modbus_slave_tag = &mst;
    modbus_slave_init(modbus_slave_tag, 1, TEST_PROTOCOL);
    //Valid 0x00FF

    modbus_slave_test_input_message_buffer_generate_header(modbus_slave_tag);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 8);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 1);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0xFF);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_generate_footer(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_test_output_message_buffer_check_header(modbus_slave_tag));
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 0) == 8);
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 1) == 0);
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 2) == 1);
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 3) == 0xFF);
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 4) == 0);
    CU_ASSERT(modbus_slave_test_output_message_buffer_check_footer(modbus_slave_tag));


    //Invalid data
    modbus_slave_test_input_message_buffer_generate_header(modbus_slave_tag);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 8);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 1);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0xFF);
    modbus_slave_test_input_message_buffer_generate_footer(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_test_output_message_buffer_check_header(modbus_slave_tag));
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 0) == 8|(1<<7));
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 1) == 1);
    CU_ASSERT(modbus_slave_test_output_message_buffer_check_footer(modbus_slave_tag));
}






void unit_test_diagnostic_04(void){
    modbus_slave_t mst;
    modbus_slave_t* modbus_slave_tag = &mst;
    modbus_slave_init(modbus_slave_tag, 1, TEST_PROTOCOL);

    //Invalid data
    modbus_slave_test_input_message_buffer_generate_header(modbus_slave_tag);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 8);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 4);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0xFF);
    modbus_slave_test_input_message_buffer_generate_footer(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_test_output_message_buffer_check_header(modbus_slave_tag));
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 0) == 8|(1<<7));
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 1) == 1);
    CU_ASSERT(modbus_slave_test_output_message_buffer_check_footer(modbus_slave_tag));

    //Invalid data 0xFFFF
    modbus_slave_test_input_message_buffer_generate_header(modbus_slave_tag);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 8);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 4);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0xFF);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0xFF);
    modbus_slave_test_input_message_buffer_generate_footer(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_test_output_message_buffer_check_header(modbus_slave_tag));
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 0) == 8|(1<<7));
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 1) == 3);
    CU_ASSERT(modbus_slave_test_output_message_buffer_check_footer(modbus_slave_tag));

    //Valid turn off

    modbus_slave_test_input_message_buffer_generate_header(modbus_slave_tag);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 8);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 4);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_generate_footer(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_output_message_buffer_length(modbus_slave_tag) == 0);

    //Check cant talk
    modbus_slave_test_input_message_buffer_generate_header(modbus_slave_tag);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 8);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_generate_footer(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_output_message_buffer_length(modbus_slave_tag) == 0);

    //Valid turn on

    modbus_slave_test_input_message_buffer_generate_header(modbus_slave_tag);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 8);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 1);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0xFF);
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_generate_footer(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 0) == 8);
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 1) == 0);
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 2) == 1);
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 3) == 0xFF);
    CU_ASSERT(modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_tag, 4) == 0);
    CU_ASSERT(modbus_slave_test_output_message_buffer_check_footer(modbus_slave_tag));

    //Check can talk

}


























