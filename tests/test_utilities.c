void modbus_slave_test_input_message_buffer_crc_gen(modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_CRC_gen(&(modbus_slave_tag->input_message_buffer));
}

uint8_t modbus_slave_test_output_message_buffer_crc_check(modbus_slave_t* modbus_slave_tag){
    return modbus_slave_data_buffer_CRC_check(&(modbus_slave_tag->output_message_buffer));
}
