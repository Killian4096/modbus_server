void modbus_slave_data_buffer_init(struct modbus_slave_data_buffer_t* data_buffer){
    data_buffer->length = 0;
}

void modbus_slave_data_buffer_add(struct modbus_slave_data_buffer_t* data_buffer, uint8_t item){
    data_buffer->array[data_buffer->length] = item;
    data_buffer->length += 1;
}

uint8_t modbus_slave_data_buffer_get(struct modbus_slave_data_buffer_t* data_buffer, size_t index){
    return data_buffer->array[index];
}

void modbus_slave_data_buffer_CRC_gen(struct modbus_slave_data_buffer_t* data_buffer){
    uint16_t crc = CRC16(data_buffer->array, data_buffer->length);
    uint8_t crc_high = crc >> 8;
    uint8_t crc_low = crc;
    modbus_slave_data_buffer_add(data_buffer, crc_high);
    modbus_slave_data_buffer_add(data_buffer, crc_low);
}

uint8_t modbus_slave_data_buffer_CRC_check(const struct modbus_slave_data_buffer_t* data_buffer){
    uint16_t CRC_correct = CRC16(data_buffer->array, data_buffer->length-3);
    uint16_t CRC_current = (data_buffer->array[data_buffer->length-2]<<8) | data_buffer->array[data_buffer->length-1];
    return CRC_correct == CRC_current;
}

void modbus_slave_data_buffer_LRC_gen(struct modbus_slave_data_buffer_t* data_buffer){
    //Exclude leading :
    uint8_t lrc = LRC(&(data_buffer->array[1]), data_buffer->length-1);
    uint16_t ascii = ASCII_convert_byte_to_ascii(lrc);
    modbus_slave_data_buffer_add(data_buffer, ascii>>8);
    modbus_slave_data_buffer_add(data_buffer, ascii);
}

uint8_t modbus_slave_data_buffer_LRC_check(const struct modbus_slave_data_buffer_t* data_buffer){
    uint8_t LRC_correct = LRC(data_buffer->array, data_buffer->length-2);
    uint8_t LRC_current = data_buffer->array[data_buffer->length-1];
    return LRC_correct == LRC_current;
}
