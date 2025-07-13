//HEADER
void modbus_server_test_input_message_buffer_generate_header(modbus_server_t* modbus_server_tag){
    modbus_server_input_message_buffer_init(modbus_server_tag);
    switch(modbus_server_tag->protocol){
        case MODBUS_SERVER_PROTOCOL_RTU:
            modbus_server_test_input_message_buffer_generate_header_RTU(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_RTU_OVER_TCP:
            modbus_server_test_input_message_buffer_generate_header_RTU(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_ASCII:
            modbus_server_test_input_message_buffer_generate_header_ASCII(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_TCP:
            modbus_server_test_input_message_buffer_generate_header_TCP(modbus_server_tag);
            break;
    }
}

void modbus_server_test_input_message_buffer_generate_header_RTU(modbus_server_t* modbus_server_tag){
    modbus_server_input_message_buffer_add(modbus_server_tag, modbus_server_tag->address);
}

void modbus_server_test_input_message_buffer_generate_header_ASCII(modbus_server_t* modbus_server_tag){
    modbus_server_input_message_buffer_add(modbus_server_tag, ':');
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, modbus_server_tag->address);
}

void modbus_server_test_input_message_buffer_generate_header_TCP(modbus_server_t* modbus_server_tag){
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 1);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);

    //To be filled later
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 0);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, 1);
}






//FOOTER
void modbus_server_test_input_message_buffer_generate_footer(modbus_server_t* modbus_server_tag){
    switch(modbus_server_tag->protocol){
        case MODBUS_SERVER_PROTOCOL_RTU:
            modbus_server_test_input_message_buffer_generate_footer_RTU(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_RTU_OVER_TCP:
            modbus_server_test_input_message_buffer_generate_footer_RTU(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_ASCII:
            modbus_server_test_input_message_buffer_generate_footer_ASCII(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_TCP:
            modbus_server_test_input_message_buffer_generate_footer_TCP(modbus_server_tag);
            break;
    }
}

void modbus_server_test_input_message_buffer_generate_footer_RTU(modbus_server_t* modbus_server_tag){
    modbus_server_data_buffer_CRC_gen(&(modbus_server_tag->input_message_buffer));
}

void modbus_server_test_input_message_buffer_generate_footer_ASCII(modbus_server_t* modbus_server_tag){
    modbus_server_data_buffer_LRC_gen(&(modbus_server_tag->input_message_buffer));
    modbus_server_input_message_buffer_add(modbus_server_tag, 0x0D);
    modbus_server_input_message_buffer_add(modbus_server_tag, 0x0A);

}

void modbus_server_test_input_message_buffer_generate_footer_TCP(modbus_server_t* modbus_server_tag){
    uint16_t length = modbus_server_input_message_buffer_length(modbus_server_tag);
    length = length - 6;
    modbus_server_tag->input_message_buffer.array[4] = length >> 8;
    modbus_server_tag->input_message_buffer.array[5] = length;
}




//ADD
void modbus_server_test_input_message_buffer_add_formatted(modbus_server_t* modbus_server_tag, uint8_t item){
    switch(modbus_server_tag->protocol){
        case MODBUS_SERVER_PROTOCOL_RTU:
            modbus_server_test_input_message_buffer_add_formatted_RTU(modbus_server_tag, item);
            break;
        case MODBUS_SERVER_PROTOCOL_RTU_OVER_TCP:
            modbus_server_test_input_message_buffer_add_formatted_RTU(modbus_server_tag, item);
            break;
        case MODBUS_SERVER_PROTOCOL_ASCII:
            modbus_server_test_input_message_buffer_add_formatted_ASCII(modbus_server_tag, item);
            break;
        case MODBUS_SERVER_PROTOCOL_TCP:
            modbus_server_test_input_message_buffer_add_formatted_RTU(modbus_server_tag, item);
            break;
    }
}

void modbus_server_test_input_message_buffer_add_formatted_RTU(modbus_server_t* modbus_server_tag, uint8_t item){
    modbus_server_input_message_buffer_add(modbus_server_tag, item);
}

void modbus_server_test_input_message_buffer_add_formatted_ASCII(modbus_server_t* modbus_server_tag, uint8_t item){
    uint16_t ascii = ASCII_byte_to_ascii(item);
    modbus_server_input_message_buffer_add(modbus_server_tag, ascii>>8);
    modbus_server_input_message_buffer_add(modbus_server_tag, ascii);
}

//GET
uint8_t modbus_server_test_output_message_buffer_get_formatted(modbus_server_t* modbus_server_tag, size_t index){
    switch(modbus_server_tag->protocol){
        case MODBUS_SERVER_PROTOCOL_RTU:
            return modbus_server_test_output_message_buffer_get_formatted_RTU(modbus_server_tag, index);
            break;
        case MODBUS_SERVER_PROTOCOL_RTU_OVER_TCP:
            return modbus_server_test_output_message_buffer_get_formatted_RTU(modbus_server_tag, index);
            break;
        case MODBUS_SERVER_PROTOCOL_ASCII:
            return modbus_server_test_output_message_buffer_get_formatted_ASCII(modbus_server_tag, index);
            break;
        case MODBUS_SERVER_PROTOCOL_TCP:
            return modbus_server_test_output_message_buffer_get_formatted_RTU(modbus_server_tag, index);
            break;
    }
    return 0;
}

uint8_t modbus_server_test_output_message_buffer_get_formatted_RTU(modbus_server_t* modbus_server_tag, size_t index){
    return modbus_server_output_message_buffer_get(modbus_server_tag, index);
}

uint8_t modbus_server_test_output_message_buffer_get_formatted_ASCII(modbus_server_t* modbus_server_tag, size_t index){
    uint16_t ascii = (modbus_server_output_message_buffer_get(modbus_server_tag, 2* index + 1) << 8) | modbus_server_output_message_buffer_get(modbus_server_tag, 2* index + 2);
    uint8_t byte = ASCII_ascii_to_byte(ascii);
    return byte;
}


//HEADER CHECK
//TODO
uint8_t modbus_server_test_output_message_buffer_check_header(modbus_server_t* modbus_server_tag){
    return 1;
}

//FOOTER CHECK
//TODO
uint8_t modbus_server_test_output_message_buffer_check_footer(modbus_server_t* modbus_server_tag){
    return 1;
}

uint8_t modbus_server_test_output_data_buffer_get_formatted(modbus_server_t* modbus_server_tag, size_t index){
    switch(modbus_server_tag->protocol){
        case MODBUS_SERVER_PROTOCOL_RTU:
            return modbus_server_test_output_data_buffer_get_formatted_RTU(modbus_server_tag, index);
            break;
        case MODBUS_SERVER_PROTOCOL_RTU_OVER_TCP:
            return modbus_server_test_output_data_buffer_get_formatted_RTU(modbus_server_tag, index);
            break;
        case MODBUS_SERVER_PROTOCOL_ASCII:
            return modbus_server_test_output_data_buffer_get_formatted_ASCII(modbus_server_tag, index);
            break;
        case MODBUS_SERVER_PROTOCOL_TCP:
            return modbus_server_test_output_data_buffer_get_formatted_TCP(modbus_server_tag, index);
            break;
    }
    return 0;
}
uint8_t modbus_server_test_output_data_buffer_get_formatted_RTU(modbus_server_t* modbus_server_tag, size_t index){
    return modbus_server_test_output_message_buffer_get_formatted(modbus_server_tag, index + 1);
}
uint8_t modbus_server_test_output_data_buffer_get_formatted_ASCII(modbus_server_t* modbus_server_tag, size_t index){
    return modbus_server_test_output_message_buffer_get_formatted(modbus_server_tag, index + 1);
}

uint8_t modbus_server_test_output_data_buffer_get_formatted_TCP(modbus_server_t* modbus_server_tag, size_t index){
    return modbus_server_test_output_message_buffer_get_formatted(modbus_server_tag, index + 7);
}







