uint8_t modbus_slave_input_message_buffer_decode(struct modbus_slave_t* modbus_slave_tag){
    switch(modbus_slave_tag->protocol){
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_RTU
        case MODBUS_SLAVE_PROTOCOL_RTU:
            return modbus_slave_input_message_buffer_decode_RTU(modbus_slave_tag);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_RTU_OVER_TCP
        case MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP:
            return modbus_slave_input_message_buffer_decode_RTU(modbus_slave_tag);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_ASCII
        case MODBUS_SLAVE_PROTOCOL_ASCII:
            return modbus_slave_input_message_buffer_decode_ASCII(modbus_slave_tag);
            break;
        #endif
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_TCP
        case MODBUS_SLAVE_PROTOCOL_TCP:
            return modbus_slave_input_message_buffer_decode_TCP(modbus_slave_tag);
            break;
        #endif
        default:
            return 0;
    }
}

uint8_t modbus_slave_input_message_buffer_decode_RTU(struct modbus_slave_t* modbus_slave_tag){
    //If invalid length return False
    if(modbus_slave_input_message_buffer_length(modbus_slave_tag) <  4){
        return 0;
    }
    modbus_slave_tag->input_message_decode_buffer.address = modbus_slave_input_message_buffer_get(modbus_slave_tag, 0);
    modbus_slave_tag->input_message_decode_buffer.function_code = modbus_slave_input_message_buffer_get(modbus_slave_tag, 1);
    uint8_t CRC_HIGH = modbus_slave_input_message_buffer_get(modbus_slave_tag, modbus_slave_input_message_buffer_length(modbus_slave_tag)-2);
    uint8_t CRC_LOW  = modbus_slave_input_message_buffer_get(modbus_slave_tag, modbus_slave_input_message_buffer_length(modbus_slave_tag)-1);
    modbus_slave_tag->input_message_decode_buffer.CRC = (CRC_HIGH<<8) | (CRC_LOW);
    modbus_slave_tag->input_message_decode_buffer.input_data_buffer_array = &(modbus_slave_tag->input_message_buffer.array[1]);
    modbus_slave_tag->input_message_decode_buffer.input_data_buffer_length = modbus_slave_input_message_buffer_length(modbus_slave_tag) - 3;
    if (modbus_slave_tag->input_message_decode_buffer.address != modbus_slave_tag->address && modbus_slave_tag->input_message_decode_buffer.address != 0) {
        return 0; //Not for me
    }
    return 1;
}


uint8_t modbus_slave_input_message_buffer_decode_TCP(struct modbus_slave_t* modbus_slave_tag){
    //If invalid length return False
    /*if(modbus_slave_input_message_buffer_length(modbus_slave_tag) <  8){
        return 0;
    }*/
    uint8_t transaction_identifier_high = modbus_slave_input_message_buffer_get(modbus_slave_tag, 0);
    uint8_t transaction_identifier_low = modbus_slave_input_message_buffer_get(modbus_slave_tag, 1);
    modbus_slave_tag->input_message_decode_buffer.transaction_identifier = (transaction_identifier_high << 8) | transaction_identifier_low;

    uint8_t protocol_identifier_high = modbus_slave_input_message_buffer_get(modbus_slave_tag, 2);
    uint8_t protocol_identifier_low = modbus_slave_input_message_buffer_get(modbus_slave_tag, 3);
    modbus_slave_tag->input_message_decode_buffer.protocol_identifier = (protocol_identifier_high << 8) | protocol_identifier_low;

    uint8_t tcp_length_high = modbus_slave_input_message_buffer_get(modbus_slave_tag, 4);
    uint8_t tcp_length_low = modbus_slave_input_message_buffer_get(modbus_slave_tag, 5);
    uint16_t tcp_length = (tcp_length_high << 8) | tcp_length_low;
    if (tcp_length < 2){
        return 0;
    }
    tcp_length = tcp_length - 1;
    modbus_slave_tag->input_message_decode_buffer.input_data_buffer_length = tcp_length;

    modbus_slave_tag->input_message_decode_buffer.function_code = modbus_slave_input_message_buffer_get(modbus_slave_tag, 7);
    modbus_slave_tag->input_message_decode_buffer.unit_identifier = modbus_slave_input_message_buffer_get(modbus_slave_tag, 6);
    modbus_slave_tag->input_message_decode_buffer.input_data_buffer_array = &(modbus_slave_tag->input_message_buffer.array[7]);


    return 1;
}


uint8_t modbus_slave_input_message_buffer_decode_ASCII(struct modbus_slave_t* modbus_slave_tag){
    //If no heeader get out
    if(modbus_slave_input_message_buffer_get(modbus_slave_tag, 0) != ':'){
        return 0;
    }
    //Always odd due to : at beginning
    if(modbus_slave_input_message_buffer_length(modbus_slave_tag) % 2 != 1){
        return 0;
    }
    //If invalid length return False
    if(modbus_slave_input_message_buffer_length(modbus_slave_tag) <  9){
        return 0;
    }
    modbus_slave_tag->input_message_decode_buffer.address = modbus_slave_input_message_buffer_get_from_ASCII(modbus_slave_tag, 1);
    modbus_slave_tag->input_message_decode_buffer.function_code = modbus_slave_input_message_buffer_get_from_ASCII(modbus_slave_tag, 3);
    modbus_slave_tag->input_message_decode_buffer.LRC = modbus_slave_input_message_buffer_get_from_ASCII(modbus_slave_tag, modbus_slave_input_message_buffer_length(modbus_slave_tag) - 4);
    modbus_slave_tag->input_message_decode_buffer.input_data_buffer_array = &(modbus_slave_tag->input_message_buffer.array[3]);
    modbus_slave_tag->input_message_decode_buffer.input_data_buffer_length = (modbus_slave_input_message_buffer_length(modbus_slave_tag) - 7)/2;
    if (modbus_slave_tag->input_message_decode_buffer.address != modbus_slave_tag->address && modbus_slave_tag->input_message_decode_buffer.address != 0) {
        return 0; //Not for me
    }
    return 1;
}
