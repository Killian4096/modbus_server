//ACCESSORS
//INIT
void modbus_slave_input_message_buffer_init(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_init(&(modbus_slave_tag->input_message_buffer));
}
void modbus_slave_output_message_buffer_init(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_init(&(modbus_slave_tag->output_message_buffer));
}

//ADD
void modbus_slave_input_message_buffer_add(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    modbus_slave_data_buffer_add(&(modbus_slave_tag->input_message_buffer), item);
}
void modbus_slave_output_message_buffer_add(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    modbus_slave_data_buffer_add(&(modbus_slave_tag->output_message_buffer), item);
}

//GET
uint8_t modbus_slave_input_message_buffer_get(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    return modbus_slave_tag->input_message_buffer.array[index];
}

uint8_t modbus_slave_output_message_buffer_get(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    return modbus_slave_tag->output_message_buffer.array[index];
}

//LENGTH
size_t modbus_slave_input_message_buffer_length(struct modbus_slave_t* modbus_slave_tag){
    return modbus_slave_tag->input_message_buffer.length;
}

size_t modbus_slave_output_message_buffer_length(struct modbus_slave_t* modbus_slave_tag){
    return modbus_slave_tag->output_message_buffer.length;
}

//ASCII
uint8_t modbus_slave_input_message_buffer_get_from_ASCII(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    uint16_t ascii = (modbus_slave_input_message_buffer_get(modbus_slave_tag, index) << 8) | modbus_slave_input_message_buffer_get(modbus_slave_tag, index+1);
    uint8_t byte = ASCII_ascii_to_byte(ascii);
    return byte;
}

void modbus_slave_output_message_buffer_add_to_ASCII(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    uint16_t ascii_address = ASCII_byte_to_ascii(item);
    modbus_slave_output_message_buffer_add(modbus_slave_tag, ascii_address>>8);
    modbus_slave_output_message_buffer_add(modbus_slave_tag, ascii_address);
}






//HEADER GEN
void modbus_slave_output_message_buffer_header_gen(struct modbus_slave_t* modbus_slave_tag){
    if(modbus_slave_tag->protocol == MODBUS_SLAVE_PROTOCOL_ASCII){
        return modbus_slave_output_message_buffer_header_gen_ASCII(modbus_slave_tag);
    }
    else{
        return modbus_slave_output_message_buffer_header_gen_RTU(modbus_slave_tag);
    }
}

void modbus_slave_output_message_buffer_header_gen_RTU(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_output_message_buffer_add(modbus_slave_tag, modbus_slave_tag->decode_buffer.address);
}

void modbus_slave_output_message_buffer_header_gen_ASCII(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_output_message_buffer_add(modbus_slave_tag, ':');
    modbus_slave_output_message_buffer_add_to_ASCII(modbus_slave_tag, modbus_slave_tag->decode_buffer.address);
}



//FOOTER GEN
void modbus_slave_output_message_buffer_footer_gen(struct modbus_slave_t* modbus_slave_tag){
    switch(modbus_slave_tag->protocol){
        #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_RTU
        case MODBUS_SLAVE_PROTOCOL_RTU:
            modbus_slave_output_message_buffer_footer_gen_RTU(modbus_slave_tag);
            break;
            #endif
            #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_ASCII
        case MODBUS_SLAVE_PROTOCOL_ASCII:
            modbus_slave_output_message_buffer_footer_gen_ASCII(modbus_slave_tag);
            break;
            #endif
            #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_RTU_OVER_TCP
        case MODBUS_SLAVE_PROTOCOL_RTU_OVER_TCP:
            modbus_slave_output_message_buffer_footer_gen_RTU(modbus_slave_tag);
            break;
            #endif
            #ifdef MODBUS_SLAVE_COMPILE_PROTOCOL_TCP
        case MODBUS_SLAVE_PROTOCOL_TCP:
            break;
            #endif
    }
}

void modbus_slave_output_message_buffer_footer_gen_RTU(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_CRC_gen(&(modbus_slave_tag->output_message_buffer));
}

void modbus_slave_output_message_buffer_footer_gen_ASCII(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_LRC_gen(&(modbus_slave_tag->output_message_buffer));
    modbus_slave_output_message_buffer_add(modbus_slave_tag, 0x0D);
    modbus_slave_output_message_buffer_add(modbus_slave_tag, 0x0A);
}
