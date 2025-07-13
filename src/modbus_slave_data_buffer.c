void modbus_slave_output_data_buffer_init(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_tag->output_data_buffer_array = &modbus_slave_tag->output_message_buffer.array[modbus_slave_tag->output_message_buffer.length];
    modbus_slave_tag->output_data_buffer_length = 0;
}



void modbus_slave_output_data_buffer_add(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    switch(modbus_slave_tag->protocol){
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_RTU
        case MODBUS_SLAVE_PROTOCOL_RTU:
            modbus_slave_output_data_buffer_add_RTU(modbus_slave_tag, item);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_ASCII
        case MODBUS_SLAVE_PROTOCOL_ASCII:
            modbus_slave_output_data_buffer_add_ASCII(modbus_slave_tag, item);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_RTU_OVER_TCP
        case MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP:
            modbus_slave_output_data_buffer_add_RTU(modbus_slave_tag, item);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_TCP
        case MODBUS_SLAVE_PROTOCOL_TCP:
            //RTU and TCP use same width
            modbus_slave_output_data_buffer_add_RTU(modbus_slave_tag, item);
            break;
        #endif
        default:
            return;
    }
}

void modbus_slave_output_data_buffer_add_RTU(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    modbus_slave_output_message_buffer_add(modbus_slave_tag, item);
    modbus_slave_tag->output_data_buffer_length += 1;
}

void modbus_slave_output_data_buffer_add_ASCII(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    uint16_t ascii = ASCII_byte_to_ascii(item);
    modbus_slave_output_message_buffer_add(modbus_slave_tag, ascii>>8);
    modbus_slave_output_message_buffer_add(modbus_slave_tag, ascii);
    modbus_slave_tag->output_data_buffer_length += 1;
}


uint8_t modbus_slave_input_data_buffer_get(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    switch(modbus_slave_tag->protocol){
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_RTU
        case MODBUS_SLAVE_PROTOCOL_RTU:
            return modbus_slave_io_data_buffer_get_RTU(modbus_slave_tag, index, modbus_slave_tag->decode_buffer.input_data_buffer_array);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_ASCII
        case MODBUS_SLAVE_PROTOCOL_ASCII:
            return modbus_slave_io_data_buffer_get_ASCII(modbus_slave_tag, index, modbus_slave_tag->decode_buffer.input_data_buffer_array);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_RTU_OVER_TCP
        case MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP:
            return modbus_slave_io_data_buffer_get_RTU(modbus_slave_tag, index, modbus_slave_tag->decode_buffer.input_data_buffer_array);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_TCP
        case MODBUS_SLAVE_PROTOCOL_TCP:
            //RTU and TCP use same width
            return modbus_slave_io_data_buffer_get_RTU(modbus_slave_tag, index, modbus_slave_tag->decode_buffer.input_data_buffer_array);
            break;
        #endif
        default:
            return 0;
    }
}

uint8_t modbus_slave_output_data_buffer_get(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    switch(modbus_slave_tag->protocol){
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_RTU
        case MODBUS_SLAVE_PROTOCOL_RTU:
            return modbus_slave_io_data_buffer_get_RTU(modbus_slave_tag, index, modbus_slave_tag->output_data_buffer_array);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_ASCII
        case MODBUS_SLAVE_PROTOCOL_ASCII:
            return modbus_slave_io_data_buffer_get_ASCII(modbus_slave_tag, index, modbus_slave_tag->output_data_buffer_array);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_RTU_OVER_TCP
        case MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP:
            return modbus_slave_io_data_buffer_get_RTU(modbus_slave_tag, index, modbus_slave_tag->output_data_buffer_array);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_TCP
        case MODBUS_SLAVE_PROTOCOL_TCP:
            //RTU and TCP use same width
            return modbus_slave_io_data_buffer_get_RTU(modbus_slave_tag, index, modbus_slave_tag->output_data_buffer_array);
            break;
        #endif
        default:
            return 0;
    }
}

uint8_t modbus_slave_io_data_buffer_get_RTU(struct modbus_slave_t* modbus_slave_tag, uint8_t index, uint8_t* data_buffer_array){
    return data_buffer_array[index];
}

uint8_t modbus_slave_io_data_buffer_get_ASCII(struct modbus_slave_t* modbus_slave_tag, uint8_t index, uint8_t* data_buffer_array){
    uint16_t ascii = (data_buffer_array[index*2]<<8) | data_buffer_array[index*2+1];
    uint8_t byte = ASCII_ascii_to_byte(ascii);
    return byte;
}



size_t modbus_slave_input_data_buffer_length(struct modbus_slave_t* modbus_slave_tag){
    return modbus_slave_tag->decode_buffer.input_data_buffer_length;
}

size_t modbus_slave_output_data_buffer_length(struct modbus_slave_t* modbus_slave_tag){
    return modbus_slave_tag->output_data_buffer_length;
}



