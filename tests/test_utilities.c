//HEADER
void modbus_slave_test_input_message_buffer_generate_header(modbus_slave_t* modbus_slave_tag){
    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    switch(modbus_slave_tag->protocol){
        case MODBUS_SLAVE_PROTOCOL_RTU:
            modbus_slave_test_input_message_buffer_generate_header_RTU(modbus_slave_tag);
            break;
        case MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP:
            modbus_slave_test_input_message_buffer_generate_header_RTU(modbus_slave_tag);
            break;
        case MODBUS_SLAVE_PROTOCOL_ASCII:
            modbus_slave_test_input_message_buffer_generate_header_ASCII(modbus_slave_tag);
            break;
    }
}

void modbus_slave_test_input_message_buffer_generate_header_RTU(modbus_slave_t* modbus_slave_tag){
    modbus_slave_input_message_buffer_add(modbus_slave_tag, modbus_slave_tag->address);
}

void modbus_slave_test_input_message_buffer_generate_header_ASCII(modbus_slave_t* modbus_slave_tag){
    modbus_slave_input_message_buffer_add(modbus_slave_tag, ':');
    modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_tag, modbus_slave_tag->address);
}






//FOOTER
void modbus_slave_test_input_message_buffer_generate_footer(modbus_slave_t* modbus_slave_tag){
    switch(modbus_slave_tag->protocol){
        case MODBUS_SLAVE_PROTOCOL_RTU:
            modbus_slave_test_input_message_buffer_generate_footer_RTU(modbus_slave_tag);
            break;
        case MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP:
            modbus_slave_test_input_message_buffer_generate_footer_RTU(modbus_slave_tag);
            break;
        case MODBUS_SLAVE_PROTOCOL_ASCII:
            modbus_slave_test_input_message_buffer_generate_footer_ASCII(modbus_slave_tag);
            break;
    }
}

void modbus_slave_test_input_message_buffer_generate_footer_RTU(modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_CRC_gen(&(modbus_slave_tag->input_message_buffer));
}

void modbus_slave_test_input_message_buffer_generate_footer_ASCII(modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_LRC_gen(&(modbus_slave_tag->input_message_buffer));
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0x0D);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, 0x0A);

}




//ADD
void modbus_slave_test_input_message_buffer_add_formatted(modbus_slave_t* modbus_slave_tag, uint8_t item){
    switch(modbus_slave_tag->protocol){
        case MODBUS_SLAVE_PROTOCOL_RTU:
            modbus_slave_test_input_message_buffer_add_formatted_RTU(modbus_slave_tag, item);
            break;
        case MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP:
            modbus_slave_test_input_message_buffer_add_formatted_RTU(modbus_slave_tag, item);
            break;
        case MODBUS_SLAVE_PROTOCOL_ASCII:
            modbus_slave_test_input_message_buffer_add_formatted_ASCII(modbus_slave_tag, item);
            break;
    }
}

void modbus_slave_test_input_message_buffer_add_formatted_RTU(modbus_slave_t* modbus_slave_tag, uint8_t item){
    modbus_slave_input_message_buffer_add(modbus_slave_tag, item);
}

void modbus_slave_test_input_message_buffer_add_formatted_ASCII(modbus_slave_t* modbus_slave_tag, uint8_t item){
    uint16_t ascii = ASCII_byte_to_ascii(item);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, ascii>>8);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, ascii);
}

//GET
uint8_t modbus_slave_test_output_message_buffer_get_formatted(modbus_slave_t* modbus_slave_tag, size_t index){
    switch(modbus_slave_tag->protocol){
        case MODBUS_SLAVE_PROTOCOL_RTU:
            return modbus_slave_test_output_message_buffer_get_formatted_RTU(modbus_slave_tag, index);
            break;
        case MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP:
            return modbus_slave_test_output_message_buffer_get_formatted_RTU(modbus_slave_tag, index);
            break;
        case MODBUS_SLAVE_PROTOCOL_ASCII:
            return modbus_slave_test_output_message_buffer_get_formatted_ASCII(modbus_slave_tag, index);
            break;
    }
    return 0;
}

uint8_t modbus_slave_test_output_message_buffer_get_formatted_RTU(modbus_slave_t* modbus_slave_tag, size_t index){
    return modbus_slave_output_message_buffer_get(modbus_slave_tag, index);
}

uint8_t modbus_slave_test_output_message_buffer_get_formatted_ASCII(modbus_slave_t* modbus_slave_tag, size_t index){
    uint16_t ascii = (modbus_slave_output_message_buffer_get(modbus_slave_tag, 2* index + 1) << 8) | modbus_slave_output_message_buffer_get(modbus_slave_tag, 2* index + 2);
    uint8_t byte = ASCII_ascii_to_byte(ascii);
    return byte;
}


//HEADER CHECK
uint8_t modbus_slave_test_output_message_buffer_check_header(modbus_slave_t* modbus_slave_tag){
    return 1;
}

//FOOTER CHECK
uint8_t modbus_slave_test_output_message_buffer_check_footer(modbus_slave_t* modbus_slave_tag){
    return 1;
}

uint8_t modbus_slave_test_output_data_buffer_get_formatted(modbus_slave_t* modbus_slave_tag, size_t index){
    switch(modbus_slave_tag->protocol){
        case MODBUS_SLAVE_PROTOCOL_RTU:
            return modbus_slave_test_output_data_buffer_get_formatted_RTU(modbus_slave_tag, index);
            break;
        case MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP:
            return modbus_slave_test_output_data_buffer_get_formatted_RTU(modbus_slave_tag, index);
            break;
        case MODBUS_SLAVE_PROTOCOL_ASCII:
            return modbus_slave_test_output_data_buffer_get_formatted_ASCII(modbus_slave_tag, index);
            break;
    }
    return 0;
}
uint8_t modbus_slave_test_output_data_buffer_get_formatted_RTU(modbus_slave_t* modbus_slave_tag, size_t index){
    return modbus_slave_test_output_message_buffer_get_formatted(modbus_slave_tag, index + 1);
}
uint8_t modbus_slave_test_output_data_buffer_get_formatted_ASCII(modbus_slave_t* modbus_slave_tag, size_t index){
    return modbus_slave_test_output_message_buffer_get_formatted(modbus_slave_tag, index + 1);
}









