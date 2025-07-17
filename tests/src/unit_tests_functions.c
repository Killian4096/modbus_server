void unit_tests_functions(int test_protocol){
    unit_tests_function_01(test_protocol);
}


void unit_tests_function_01(int test_protocol){
    modbus_server_t mst;
    modbus_server_t* modbus_server_tag = &mst;
    modbus_server_init(modbus_server_tag, 1, test_protocol);
    modbus_server_tag->points.coils[0]=0xF0;
    modbus_server_tag->points.coils[1]=0x0F;

    //Read 0-8
    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 1);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 8);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 0) == 1);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 1) == 1);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 2) == 0xF0);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));


    //Read 0-4
    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 1);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 4);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 0) == 1);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 1) == 1);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 2) == 0x00);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));

    //Read 5-14
    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 1);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 5);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 9);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 0) == 1);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 1) == 2);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 2) == 0x7F);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 3) == 0x00);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));

}


void unit_tests_function_02(int test_protocol){
    modbus_server_t mst;
    modbus_server_t* modbus_server_tag = &mst;
    modbus_server_init(modbus_server_tag, 1, test_protocol);
    modbus_server_tag->points.inputs[0]=1;
    modbus_server_tag->points.inputs[1]=3;
    modbus_server_tag->points.inputs[2]=6;
    modbus_server_tag->points.inputs[3]=7;

    //Read 2-3
    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 2);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 2);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 1);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 0) == 1);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 1) == 2);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 2) == 6);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 3) == 7);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));


    //Read 0-3
    modbus_server_test_input_message_buffer_generate_header(modbus_server_tag);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 2);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 4);
    modbus_server_test_input_message_buffer_generate_footer(modbus_server_tag);

    modbus_server(modbus_server_tag);

    CU_ASSERT(modbus_server_test_output_message_buffer_check_header(modbus_server_tag));
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 0) == 1);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 1) == 2);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 2) == 1);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 3) == 3);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 4) == 6);
    CU_ASSERT(modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_tag, 5) == 7);
    CU_ASSERT(modbus_server_test_output_message_buffer_check_footer(modbus_server_tag));

}
