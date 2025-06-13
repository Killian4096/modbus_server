void modbus_slave_output_data_buffer_init(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_tag->output_data_buffer_array = &modbus_slave_tag->output_message_buffer.array[modbus_slave_tag->output_message_buffer.length];
    modbus_slave_tag->output_data_buffer_length = 0;
}



void modbus_slave_output_data_buffer_add(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    if(modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_ASCII){
        modbus_slave_output_data_buffer_add_ASCII(modbus_slave_tag, item);
    }
    else{
        modbus_slave_output_data_buffer_add_RTU(modbus_slave_tag, item);
    }
}

void modbus_slave_output_data_buffer_add_RTU(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    modbus_slave_output_message_buffer_add(modbus_slave_tag, item);
    modbus_slave_tag->output_data_buffer_length += 1;
}

void modbus_slave_output_data_buffer_add_ASCII(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    uint16_t ascii = ASCII_convert_byte_to_ascii(item);
    modbus_slave_output_message_buffer_add(modbus_slave_tag, ascii>>8);
    modbus_slave_output_message_buffer_add(modbus_slave_tag, ascii);
    modbus_slave_tag->output_data_buffer_length += 1;
}



uint8_t modbus_slave_input_data_buffer_get(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    if(modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_ASCII){
        return modbus_slave_io_data_buffer_get_ASCII(modbus_slave_tag, index, modbus_slave_tag->decode_buffer.input_data_buffer_array);
    }
    else{
        return modbus_slave_io_data_buffer_get_RTU(modbus_slave_tag, index, modbus_slave_tag->decode_buffer.input_data_buffer_array);
    }
}

uint8_t modbus_slave_output_data_buffer_get(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    if(modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_ASCII){
        return modbus_slave_io_data_buffer_get_ASCII(modbus_slave_tag, index, modbus_slave_tag->output_data_buffer_array);
    }
    else{
        return modbus_slave_io_data_buffer_get_RTU(modbus_slave_tag, index, modbus_slave_tag->output_data_buffer_array);
    }
}

uint8_t modbus_slave_io_data_buffer_get_RTU(struct modbus_slave_t* modbus_slave_tag, uint8_t index, uint8_t* data_buffer_array){
    return data_buffer_array[index];
}

uint8_t modbus_slave_io_data_buffer_get_ASCII(struct modbus_slave_t* modbus_slave_tag, uint8_t index, uint8_t* data_buffer_array){
    uint16_t ascii = (data_buffer_array[index*2]<<8) | data_buffer_array[index*2+1];
    uint8_t byte = ASCII_convert_ascii_to_byte(ascii);
    return byte;
}



size_t modbus_slave_input_data_buffer_length(struct modbus_slave_t* modbus_slave_tag){
    return modbus_slave_tag->decode_buffer.input_data_buffer_length;
}

size_t modbus_slave_output_data_buffer_length(struct modbus_slave_t* modbus_slave_tag){
    return modbus_slave_tag->output_data_buffer_length;
}



