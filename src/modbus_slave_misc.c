void modbus_slave_data_buffer_CRC_gen(struct modbus_slave_data_buffer_t* data_buffer){
    uint16_t crc = CRC16(data_buffer->array, data_buffer->length);
    uint8_t crc_high = crc >> 8;
    uint8_t crc_low = crc;
    modbus_slave_data_buffer_add(data_buffer, crc_high);
    modbus_slave_data_buffer_add(data_buffer, crc_low);
}

uint8_t modbus_slave_data_buffer_CRC_check(const struct modbus_slave_data_buffer_t* data_buffer){
    uint16_t CRC_correct = CRC16(data_buffer->array, data_buffer->length-2);
    uint16_t CRC_current = (data_buffer->array[data_buffer->length-2]<<8) | data_buffer->array[data_buffer->length-1];
    return CRC_correct == CRC_current;
}


uint8_t modbus_slave_input_message_buffer_decode(struct modbus_slave_t* modbus_slave_tag){
    //If invalid length return False
    if(modbus_slave_input_message_buffer_length(modbus_slave_tag) <  4){
        return 0;
    }
    modbus_slave_tag->decode_buffer.address = modbus_slave_input_message_buffer_get(modbus_slave_tag, 0);
    modbus_slave_tag->decode_buffer.function_code = modbus_slave_input_message_buffer_get(modbus_slave_tag, 1);
    uint8_t CRC_HIGH = modbus_slave_input_message_buffer_get(modbus_slave_tag, modbus_slave_input_message_buffer_length(modbus_slave_tag)-2);
    uint8_t CRC_LOW  = modbus_slave_input_message_buffer_get(modbus_slave_tag, modbus_slave_input_message_buffer_length(modbus_slave_tag)-1);
    modbus_slave_tag->decode_buffer.CRC = (CRC_HIGH<<8) | (CRC_LOW);
    modbus_slave_tag->decode_buffer.input_data_buffer_array = &(modbus_slave_tag->input_message_buffer.array[1]);
    modbus_slave_tag->decode_buffer.input_data_buffer_length = modbus_slave_input_message_buffer_length(modbus_slave_tag) - 3;
    return 1;
}

void modbus_slave_output_message_buffer_header_gen(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_output_message_buffer_add(modbus_slave_tag, modbus_slave_tag->decode_buffer.address);
}

void modbus_slave_output_message_buffer_CRC_gen(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_CRC_gen(&(modbus_slave_tag->output_message_buffer));
}
