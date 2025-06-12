void unit_test_diagnostic_00(void);
void unit_test_diagnostic_01(void);
void unit_test_diagnostic_04(void);

void unit_test_diagnostics(void){
    unit_test_diagnostic_00();
    unit_test_diagnostic_01();
    unit_test_diagnostic_04();
}

void unit_test_diagnostic_00(void){
    modbus_slave_t mst;

    modbus_slave_t* modbus_slave_tag = &mst;
    modbus_slave_init(modbus_slave_tag, 2);
    modbus_slave_tag->diagnostic_register = 142;

    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 2);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 8);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_crc_gen(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 0) == 2);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 1) == 8);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 2) == 0);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 3) == 0);
    CU_ASSERT(modbus_slave_test_output_message_buffer_crc_check(modbus_slave_tag));
}

void unit_test_diagnostic_01(void){
    //Valid 0x00FF
    modbus_slave_t mst;

    modbus_slave_t* modbus_slave_tag = &mst;
    modbus_slave_init(modbus_slave_tag, 2);
    modbus_slave_tag->diagnostic_register = 142;

    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 2);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 8);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 1);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0xFF);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_crc_gen(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 0) == 2);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 1) == 8);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 2) == 0);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 3) == 1);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 4) == 0xFF);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 5) == 0);
    CU_ASSERT(modbus_slave_test_output_message_buffer_crc_check(modbus_slave_tag));


    //Invalid data
    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 2);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 8);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 1);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0xFF);
    modbus_slave_test_input_message_buffer_crc_gen(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 0) == 2);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 1) == 8|(1<<7));
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 2) == 1);
    CU_ASSERT(modbus_slave_test_output_message_buffer_crc_check(modbus_slave_tag));
}






void unit_test_diagnostic_04(void){
    modbus_slave_t mst;

    modbus_slave_t* modbus_slave_tag = &mst;
    modbus_slave_init(modbus_slave_tag, 2);
    modbus_slave_tag->diagnostic_register = 142;

    //Invalid data
    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 2);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 8);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 4);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0xFF);
    modbus_slave_test_input_message_buffer_crc_gen(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 0) == 2);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 1) == 8|(1<<7));
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 2) == 1);
    CU_ASSERT(modbus_slave_test_output_message_buffer_crc_check(modbus_slave_tag));

    //Invalid data 0xFFFF
    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 2);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 8);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 4);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0xFF);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0xFF);
    modbus_slave_test_input_message_buffer_crc_gen(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 0) == 2);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 1) == 8|(1<<7));
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 2) == 3);
    CU_ASSERT(modbus_slave_test_output_message_buffer_crc_check(modbus_slave_tag));

    //Valid turn off

    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 2);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 8);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 4);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_crc_gen(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_output_message_buffer_length(modbus_slave_tag) == 0);

    //Check cant talk
    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 2);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 8);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_crc_gen(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_output_message_buffer_length(modbus_slave_tag) == 0);

    //Valid turn on

    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 2);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 8);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 1);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0xFF);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0);
    modbus_slave_test_input_message_buffer_crc_gen(modbus_slave_tag);

    modbus_slave(modbus_slave_tag);

    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 0) == 2);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 1) == 8);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 2) == 0);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 3) == 1);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 4) == 0xFF);
    CU_ASSERT(modbus_slave_output_message_buffer_get(modbus_slave_tag, 5) == 0);
    CU_ASSERT(modbus_slave_test_output_message_buffer_crc_check(modbus_slave_tag));

    //Check can talk

}


























