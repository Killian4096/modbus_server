//ACCESSORS
//INIT
void modbus_server_input_message_buffer_init(struct modbus_server_t* modbus_server_tag){
    modbus_server_message_buffer_init(&(modbus_server_tag->input_message_buffer));
}
void modbus_server_output_message_buffer_init(struct modbus_server_t* modbus_server_tag){
    modbus_server_message_buffer_init(&(modbus_server_tag->output_message_buffer));
}

//ADD
void modbus_server_input_message_buffer_add(struct modbus_server_t* modbus_server_tag, uint8_t item){
    modbus_server_message_buffer_add(&(modbus_server_tag->input_message_buffer), item);
}
void modbus_server_output_message_buffer_add(struct modbus_server_t* modbus_server_tag, uint8_t item){
    modbus_server_message_buffer_add(&(modbus_server_tag->output_message_buffer), item);
}

//GET
uint8_t modbus_server_input_message_buffer_get(struct modbus_server_t* modbus_server_tag, size_t index){
    return modbus_server_tag->input_message_buffer.array[index];
}

uint8_t modbus_server_output_message_buffer_get(struct modbus_server_t* modbus_server_tag, size_t index){
    return modbus_server_tag->output_message_buffer.array[index];
}

//LENGTH
size_t modbus_server_input_message_buffer_length(struct modbus_server_t* modbus_server_tag){
    return modbus_server_tag->input_message_buffer.length;
}

size_t modbus_server_output_message_buffer_length(struct modbus_server_t* modbus_server_tag){
    return modbus_server_tag->output_message_buffer.length;
}

//ASCII
static uint8_t modbus_server_input_message_buffer_get_from_ASCII(struct modbus_server_t* modbus_server_tag, uint8_t index){
    uint16_t ascii = (modbus_server_input_message_buffer_get(modbus_server_tag, index) << 8) | modbus_server_input_message_buffer_get(modbus_server_tag, index+1);
    uint8_t byte = ASCII_ascii_to_byte(ascii);
    return byte;
}

static void modbus_server_output_message_buffer_add_to_ASCII(struct modbus_server_t* modbus_server_tag, uint8_t item){
    uint16_t ascii_address = ASCII_byte_to_ascii(item);
    modbus_server_output_message_buffer_add(modbus_server_tag, ascii_address>>8);
    modbus_server_output_message_buffer_add(modbus_server_tag, ascii_address);
}






//HEADER GEN
static void modbus_server_output_message_buffer_header_gen(struct modbus_server_t* modbus_server_tag){
    switch(modbus_server_tag->protocol){
        #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_RTU
        case MODBUS_SERVER_PROTOCOL_RTU:
            modbus_server_output_message_buffer_header_gen_RTU(modbus_server_tag);
            break;
            #endif
        #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_ASCII
        case MODBUS_SERVER_PROTOCOL_ASCII:
            modbus_server_output_message_buffer_header_gen_ASCII(modbus_server_tag);
            break;
            #endif
        #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_RTU_OVER_TCP
        case MODBUS_SERVER_PROTOCOL_RTU_OVER_TCP:
            modbus_server_output_message_buffer_header_gen_RTU(modbus_server_tag);
            break;
            #endif
        #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_TCP
        case MODBUS_SERVER_PROTOCOL_TCP:
            modbus_server_output_message_buffer_header_gen_TCP(modbus_server_tag);
            break;
            #endif
    }

}

static void modbus_server_output_message_buffer_header_gen_RTU(struct modbus_server_t* modbus_server_tag){
    modbus_server_output_message_buffer_add(modbus_server_tag, modbus_server_tag->input_message_decode_buffer.address);
}

static void modbus_server_output_message_buffer_header_gen_ASCII(struct modbus_server_t* modbus_server_tag){
    modbus_server_output_message_buffer_add(modbus_server_tag, ':');
    modbus_server_output_message_buffer_add_to_ASCII(modbus_server_tag, modbus_server_tag->input_message_decode_buffer.address);
}

static void modbus_server_output_message_buffer_header_gen_TCP(struct modbus_server_t* modbus_server_tag){
    modbus_server_output_message_buffer_add(modbus_server_tag, modbus_server_tag->input_message_decode_buffer.transaction_identifier >> 8);
    modbus_server_output_message_buffer_add(modbus_server_tag, modbus_server_tag->input_message_decode_buffer.transaction_identifier);
    modbus_server_output_message_buffer_add(modbus_server_tag, modbus_server_tag->input_message_decode_buffer.protocol_identifier >> 8);
    modbus_server_output_message_buffer_add(modbus_server_tag, modbus_server_tag->input_message_decode_buffer.protocol_identifier);

    //Populate at later time in loop footer section
    modbus_server_output_message_buffer_add(modbus_server_tag, 0);
    modbus_server_output_message_buffer_add(modbus_server_tag, 0);

    modbus_server_output_message_buffer_add(modbus_server_tag, modbus_server_tag->input_message_decode_buffer.unit_identifier);
}


//FOOTER GEN
static void modbus_server_output_message_buffer_footer_gen(struct modbus_server_t* modbus_server_tag){
    switch(modbus_server_tag->protocol){
        #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_RTU
        case MODBUS_SERVER_PROTOCOL_RTU:
            modbus_server_output_message_buffer_footer_gen_RTU(modbus_server_tag);
            break;
            #endif
        #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_ASCII
        case MODBUS_SERVER_PROTOCOL_ASCII:
            modbus_server_output_message_buffer_footer_gen_ASCII(modbus_server_tag);
            break;
            #endif
        #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_RTU_OVER_TCP
        case MODBUS_SERVER_PROTOCOL_RTU_OVER_TCP:
            modbus_server_output_message_buffer_footer_gen_RTU(modbus_server_tag);
            break;
            #endif
        #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_TCP
        case MODBUS_SERVER_PROTOCOL_TCP:
            modbus_server_output_message_buffer_footer_gen_TCP(modbus_server_tag);
            break;
            #endif
    }
}

static void modbus_server_output_message_buffer_footer_gen_RTU(struct modbus_server_t* modbus_server_tag){
    //Add CRC to footer
    uint16_t crc = CRC16(modbus_server_tag->output_message_buffer.array, modbus_server_tag->output_message_buffer.length);
    uint8_t crc_high = crc >> 8;
    uint8_t crc_low = crc;
    modbus_server_output_message_buffer_add(modbus_server_tag, crc_high);
    modbus_server_output_message_buffer_add(modbus_server_tag, crc_low);
}

static void modbus_server_output_message_buffer_footer_gen_ASCII(struct modbus_server_t* modbus_server_tag){
    //Add LRC to footer
    //Exclude leading ':'
    uint8_t lrc = LRC(&(modbus_server_tag->output_message_buffer.array[1]), modbus_server_tag->output_message_buffer.length-1);
    modbus_server_output_message_buffer_add_to_ASCII(modbus_server_tag, lrc);

    //Characters to mark end ASCII code
    modbus_server_output_message_buffer_add(modbus_server_tag, 0x0D);
    modbus_server_output_message_buffer_add(modbus_server_tag, 0x0A);
}

static void modbus_server_output_message_buffer_footer_gen_TCP(struct modbus_server_t* modbus_server_tag){
    //TODO: Create proper set function
    //Direct access to add length in header
    //Take data buffer length and add 1 for unit idenifier
    uint16_t output_length = modbus_server_tag->output_PDU_mapper_length + 1;
    modbus_server_tag->output_message_buffer.array[4] = output_length >> 8;
    modbus_server_tag->output_message_buffer.array[5] = output_length;
}



//Basic items
static void modbus_server_message_buffer_init(struct modbus_server_message_buffer_t* data_buffer){
    data_buffer->length = 0;
}

static void modbus_server_message_buffer_add(struct modbus_server_message_buffer_t* data_buffer, uint8_t item){
    data_buffer->array[data_buffer->length] = item;
    data_buffer->length += 1;
}




static uint8_t modbus_server_message_buffer_CRC_check(const struct modbus_server_message_buffer_t* message_buffer){
    uint16_t CRC_correct = CRC16(message_buffer->array, message_buffer->length-2);
    uint16_t CRC_current = (message_buffer->array[message_buffer->length-2]<<8) | message_buffer->array[message_buffer->length-1];
    return CRC_correct == CRC_current;
}

static uint8_t modbus_server_message_buffer_LRC_check(const struct modbus_server_message_buffer_t* message_buffer){
    uint8_t LRC_correct = LRC(&(message_buffer->array[1]), message_buffer->length-5);
    uint16_t ascii = message_buffer->array[message_buffer->length-4]<<8 | message_buffer->array[message_buffer->length-3];
    uint8_t LRC_current = ASCII_ascii_to_byte(ascii);
    return LRC_correct == LRC_current;
}



