void modbus_slave_test_input_message_buffer_generate_front(modbus_slave_t*);
void modbus_slave_test_input_message_buffer_generate_back(modbus_slave_t*);
uint8_t modbus_slave_test_output_message_buffer_data_get(modbus_slave_t*, index);
uint8_t modbus_slave_Test_output_message_buffer_check_back(modbus_slave_t*);

//Front
void modbus_slave_test_input_message_buffer_generate_front(modbus_slave_t* modbus_slave_tag){
    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    if((modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_RTU) || (modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP)){
        modbus_slave_input_message_buffer_add(1);
    }
    else if(modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_ASCII){
        modbus_slave_input_message_buffer_add(':');
        modbus_slave_input_message_buffer_add('0');
        modbus_slave_input_message_buffer_add('1');
    }
}


//Footer
void modbus_slave_test_input_message_buffer_generate_back(modbus_slave_t* modbus_slave_tag){
    if((modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_RTU) || (modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP)){
        modbus_slave_data_buffer_CRC_gen(&(modbus_slave_tag->input_message_buffer));
    }
    else if(modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_ASCII){
        modbus_slave_data_buffer_LRC_gen(&(modbus_slave_tag->input_message_buffer));
    }
}

//Data
uint8_t modbus_slave_test_output_message_buffer_data_get(modbus_slave_t* modbus_slave_tag, size_t index){
    if((modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_RTU) || (modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP)){
        return modbus_slave_output_message_buffer_get(modbus_slave_tag, index + 1);
    }
    else if(modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_ASCII){
        uint16_t ascii = (modbus_slave_output_message_buffer_get(modbus_slave_tag, 2*index + 3) << 8) | modbus_slave_output_message_buffer_get(modbus_slave_tag, 2*index + 4);
        return ASCII_convert_ascii_to_byte(ascii);
    }
}

uint8_t modbus_slave_Test_output_message_buffer_check_front(modbus_slave_t* modbus_slave_tag){
    if((modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_RTU) || (modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP)){
        modbus_slave_input_message_buffer_add(1);
    }
    else if(modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_ASCII){
        return modbus_slave_data_buffer_CRC_check(&(modbus_slave_tag->output_message_buffer));
    }
}


uint8_t modbus_slave_Test_output_message_buffer_check_back(modbus_slave_t* modbus_slave_tag){
    if((modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_RTU) || (modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP)){
        return modbus_slave_data_buffer_CRC_check(&(modbus_slave_tag->output_message_buffer));
    }
    else if(modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_ASCII){
        return modbus_slave_data_buffer_LRC_check(&(modbus_slave_tag->output_message_buffer));
    }
}
