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
    //Add CRC to footer
    uint16_t crc = CRC16(modbus_server_tag->input_message_buffer.array, modbus_server_tag->input_message_buffer.length);
    uint8_t crc_high = crc >> 8;
    uint8_t crc_low = crc;
    modbus_server_input_message_buffer_add(modbus_server_tag, crc_high);
    modbus_server_input_message_buffer_add(modbus_server_tag, crc_low);
}

void modbus_server_test_input_message_buffer_generate_footer_ASCII(modbus_server_t* modbus_server_tag){
    //Add LRC to footer
    //Exclude leading ':'
    uint8_t lrc = LRC(&(modbus_server_tag->input_message_buffer.array[1]), modbus_server_tag->input_message_buffer.length-1);
    modbus_server_test_input_message_buffer_add_formatted(modbus_server_tag, lrc);

    //Characters to mark end ASCII code
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
    uint16_t ascii = modbus_server_test_ASCII_byte_to_ascii(item);
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
    uint8_t byte = modbus_server_test_ASCII_ascii_to_byte(ascii);
    return byte;
}


//HEADER CHECK
uint8_t modbus_server_test_output_message_buffer_check_header(modbus_server_t* modbus_server_tag){
    switch(modbus_server_tag->protocol){
        case MODBUS_SERVER_PROTOCOL_RTU:
            return modbus_server_test_output_message_buffer_check_header_RTU(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_RTU_OVER_TCP:
            return modbus_server_test_output_message_buffer_check_header_RTU(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_ASCII:
            return modbus_server_test_output_message_buffer_check_header_ASCII(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_TCP:
            return modbus_server_test_output_message_buffer_check_header_TCP(modbus_server_tag);
            break;
        default:
            return 0;
    }
}

uint8_t modbus_server_test_output_message_buffer_check_header_RTU(modbus_server_t* modbus_server_tag){
    uint8_t address =  modbus_server_tag->output_message_buffer.array[0];
    return address == modbus_server_tag->address;
}

uint8_t modbus_server_test_output_message_buffer_check_header_ASCII(modbus_server_t* modbus_server_tag){
    uint8_t header_fails = 0;
    uint16_t address =  modbus_server_test_output_message_buffer_get_formatted_ASCII(modbus_server_tag, 0);
    header_fails += (modbus_server_tag->output_message_buffer.array[0] != ':');
    header_fails += (address != modbus_server_tag->address);
    return header_fails == 0;
}

uint8_t modbus_server_test_output_message_buffer_check_header_TCP(modbus_server_t* modbus_server_tag){
    uint8_t header_fails = 0;
    uint16_t protocol_identifier =  modbus_server_tag->output_message_buffer.array[2]<<8 | modbus_server_tag->output_message_buffer.array[3];
    uint16_t length = modbus_server_tag->output_message_buffer.array[4]<<8 | modbus_server_tag->output_message_buffer.array[5];
    header_fails += (protocol_identifier != 0);
    header_fails += (length != (modbus_server_tag->output_message_buffer.length - 6));
    return header_fails == 0;
}




//FOOTER CHECK
uint8_t modbus_server_test_output_message_buffer_check_footer(modbus_server_t* modbus_server_tag){
    switch(modbus_server_tag->protocol){
        case MODBUS_SERVER_PROTOCOL_RTU:
            return modbus_server_test_output_message_buffer_check_footer_RTU(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_RTU_OVER_TCP:
            return modbus_server_test_output_message_buffer_check_footer_RTU(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_ASCII:
            return modbus_server_test_output_message_buffer_check_footer_ASCII(modbus_server_tag);
            break;
        case MODBUS_SERVER_PROTOCOL_TCP:
            return modbus_server_test_output_message_buffer_check_footer_TCP(modbus_server_tag);
            break;
        default:
            return 0;
    }
}

uint8_t modbus_server_test_output_message_buffer_check_footer_RTU(modbus_server_t* modbus_server_tag){
    //Length check
    if(modbus_server_output_message_buffer_length(modbus_server_tag) < 4){
        return 0;
    }

    //CRC
    uint16_t CRC_correct = CRC16(modbus_server_tag->output_message_buffer.array, modbus_server_tag->output_message_buffer.length-2);
    uint16_t CRC_current = modbus_server_output_message_buffer_get(modbus_server_tag, modbus_server_output_message_buffer_length(modbus_server_tag)-2)<<8 |
    modbus_server_output_message_buffer_get(modbus_server_tag, modbus_server_output_message_buffer_length(modbus_server_tag)-1);
    if(CRC_correct != CRC_current){
        return 0;
    }

    return 1;
}

uint8_t modbus_server_test_output_message_buffer_check_footer_ASCII(modbus_server_t* modbus_server_tag){
    //Length check
    if(modbus_server_output_message_buffer_length(modbus_server_tag) < 5){
        return 0;
    }

    uint8_t footer_fails = 0;

    uint8_t LRC_correct = LRC(&(modbus_server_tag->output_message_buffer.array[1]), modbus_server_tag->output_message_buffer.length-5);
    uint16_t ascii = modbus_server_output_message_buffer_get(modbus_server_tag, modbus_server_output_message_buffer_length(modbus_server_tag)-4)<<8 |
    modbus_server_output_message_buffer_get(modbus_server_tag, modbus_server_output_message_buffer_length(modbus_server_tag)-3);
    uint8_t LRC_current = modbus_server_test_ASCII_ascii_to_byte(ascii);

    footer_fails += LRC_correct != LRC_current;
    footer_fails += modbus_server_output_message_buffer_get(modbus_server_tag, modbus_server_output_message_buffer_length(modbus_server_tag)-2) != 0x0D;
    footer_fails += modbus_server_output_message_buffer_get(modbus_server_tag, modbus_server_output_message_buffer_length(modbus_server_tag)-1) != 0x0A;
    return footer_fails == 0;
}

uint8_t modbus_server_test_output_message_buffer_check_footer_TCP(modbus_server_t* modbus_server_tag){
    return 1; //No checks for tcp, length checked in header
}

uint8_t modbus_server_test_output_PDU_mapper_get_formatted(modbus_server_t* modbus_server_tag, size_t index){
    switch(modbus_server_tag->protocol){
        case MODBUS_SERVER_PROTOCOL_RTU:
            return modbus_server_test_output_PDU_mapper_get_formatted_RTU(modbus_server_tag, index);
            break;
        case MODBUS_SERVER_PROTOCOL_RTU_OVER_TCP:
            return modbus_server_test_output_PDU_mapper_get_formatted_RTU(modbus_server_tag, index);
            break;
        case MODBUS_SERVER_PROTOCOL_ASCII:
            return modbus_server_test_output_PDU_mapper_get_formatted_ASCII(modbus_server_tag, index);
            break;
        case MODBUS_SERVER_PROTOCOL_TCP:
            return modbus_server_test_output_PDU_mapper_get_formatted_TCP(modbus_server_tag, index);
            break;
    }
    return 0;
}
uint8_t modbus_server_test_output_PDU_mapper_get_formatted_RTU(modbus_server_t* modbus_server_tag, size_t index){
    return modbus_server_test_output_message_buffer_get_formatted(modbus_server_tag, index + 1);
}
uint8_t modbus_server_test_output_PDU_mapper_get_formatted_ASCII(modbus_server_t* modbus_server_tag, size_t index){
    return modbus_server_test_output_message_buffer_get_formatted(modbus_server_tag, index + 1);
}

uint8_t modbus_server_test_output_PDU_mapper_get_formatted_TCP(modbus_server_t* modbus_server_tag, size_t index){
    return modbus_server_test_output_message_buffer_get_formatted(modbus_server_tag, index + 7);
}

//Inluded from file
uint16_t modbus_server_test_ASCII_byte_to_ascii(uint8_t byte){
    char lookup_table[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    uint8_t upper_half_word = byte/16;
    uint8_t lower_half_word = byte%16;
    return (lookup_table[upper_half_word] << 8) | lookup_table[lower_half_word];
}

uint8_t modbus_server_test_ASCII_ascii_to_byte(uint16_t ascii){
    return (modbus_server_test_ASCII_ascii_to_byte_lookup_table(ascii>>8) * 16) | modbus_server_test_ASCII_ascii_to_byte_lookup_table(ascii);
}

uint8_t modbus_server_test_ASCII_ascii_to_byte_lookup_table(uint8_t ascii){
    if(ascii >= '0' && ascii <= '9'){
        return ascii - '0';
    }
    else if(ascii >= 'A' && ascii <= 'F'){
        return ascii - 'A' + 10;
    }
    else{
        return 0;
    }
}


