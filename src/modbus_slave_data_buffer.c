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



void modbus_slave_input_message_buffer_init(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_init(&(modbus_slave_tag->input_message_buffer));
}
void modbus_slave_input_message_buffer_add(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    modbus_slave_data_buffer_add(&(modbus_slave_tag->input_message_buffer), item);
}
void modbus_slave_output_message_buffer_init(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_init(&(modbus_slave_tag->output_message_buffer));
}
void modbus_slave_output_message_buffer_add(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    modbus_slave_data_buffer_add(&(modbus_slave_tag->output_message_buffer), item);
}




void modbus_slave_output_data_buffer_init(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_tag->output_data_buffer_array = &modbus_slave_tag->output_message_buffer.array[modbus_slave_tag->output_message_buffer.length];
    modbus_slave_tag->output_data_buffer_length = 0;
}

void modbus_slave_output_data_buffer_add(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    modbus_slave_output_message_buffer_add(modbus_slave_tag, item);
    modbus_slave_tag->output_data_buffer_length += 1;
}

uint8_t modbus_slave_input_message_buffer_get(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    return modbus_slave_tag->input_message_buffer.array[index];
}

uint8_t modbus_slave_output_message_buffer_get(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    return modbus_slave_tag->output_message_buffer.array[index];
}


uint8_t modbus_slave_input_data_buffer_get(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    return modbus_slave_tag->decode_buffer.input_data_buffer_array[index];
}

uint8_t modbus_slave_output_data_buffer_get(struct modbus_slave_t* modbus_slave_tag, uint8_t index){
    return modbus_slave_tag->output_data_buffer_array[index];
}

size_t modbus_slave_input_data_buffer_length(struct modbus_slave_t* modbus_slave_tag){
    return modbus_slave_tag->decode_buffer.input_data_buffer_length;
}

size_t modbus_slave_output_data_buffer_length(struct modbus_slave_t* modbus_slave_tag){
    return modbus_slave_tag->output_data_buffer_length;
}


size_t modbus_slave_input_message_buffer_length(struct modbus_slave_t* modbus_slave_tag){
    return modbus_slave_tag->input_message_buffer.length;
}

size_t modbus_slave_output_message_buffer_length(struct modbus_slave_t* modbus_slave_tag){
    return modbus_slave_tag->output_message_buffer.length;
}
