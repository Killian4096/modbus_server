void modbus_server_func_01_read_coil_status (struct modbus_server_t* modbus_server_tag){
    modbus_server_func_shared_read_coils(modbus_server_tag, modbus_server_tag->points.coils, MODBUS_SERVER_POINTS_COILS_SIZE, 1);
}

void modbus_server_func_02_read_input_status (struct modbus_server_t* modbus_server_tag){
    modbus_server_func_shared_read_coils(modbus_server_tag, modbus_server_tag->points.inputs, MODBUS_SERVER_POINTS_INPUTS_SIZE, 2);
}

void modbus_server_func_03_read_holding_registers (struct modbus_server_t* modbus_server_tag){
    modbus_server_func_shared_read_registers(modbus_server_tag, modbus_server_tag->points.holding_registers, MODBUS_SERVER_POINTS_HOLDING_REGISTERS_SIZE, 3);
}

void modbus_server_func_04_read_input_registers (struct modbus_server_t* modbus_server_tag){
    modbus_server_func_shared_read_registers(modbus_server_tag, modbus_server_tag->points.input_registers, MODBUS_SERVER_POINTS_INPUT_REGISTERS_SIZE, 4);
}


void modbus_server_func_05_force_single_coil (struct modbus_server_t* modbus_server_tag){

    uint16_t address;
    uint16_t value;

    if (modbus_server_input_data_buffer_length(modbus_server_tag) != 5){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }

    address = (modbus_server_input_data_buffer_get(modbus_server_tag, 1) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 2); //Address
    value = (modbus_server_input_data_buffer_get(modbus_server_tag, 3) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 4); //0xFF00 or 0x0000

    //If to big error
    if (address >= MODBUS_SERVER_POINTS_COILS_SIZE){
        modbus_server_exception_02_illegal_data_address(modbus_server_tag);
        return;
    }

    //If not valid error
    if (value != 0x0000 && value != 0xFF00){
        modbus_server_exception_03_illegal_data_value(modbus_server_tag);
        return;
    }

    modbus_server_tag->points.coils[address/8] &= ~(1<<(address%8)); //Turn off item
    modbus_server_tag->points.coils[address/8] |= (value > 0)<<(address%8); //Toggle based on value

    //Echo
    for(size_t i=0;i<modbus_server_input_data_buffer_length(modbus_server_tag);i++){
        modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, i));
    }
}

void modbus_server_func_06_present_single_register (struct modbus_server_t* modbus_server_tag){
    uint16_t address;
    uint16_t value;

    if (modbus_server_input_data_buffer_length(modbus_server_tag) != 5){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }

    address = (modbus_server_input_data_buffer_get(modbus_server_tag, 1) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 2); //Address
    value = (modbus_server_input_data_buffer_get(modbus_server_tag, 3) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 4); //0xFF00 or 0x0000

    //If to big error
    if (address >= MODBUS_SERVER_POINTS_COILS_SIZE){
        modbus_server_exception_02_illegal_data_address(modbus_server_tag);
        return;
    }

    modbus_server_tag->points.input_registers[address] = value; //Write value

    //Echo
    for(size_t i=0;i<modbus_server_input_data_buffer_length(modbus_server_tag);i++){
        modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, i));
    }
}

void modbus_server_func_07_read_exception_status (struct modbus_server_t* modbus_server_tag){
    if (modbus_server_input_data_buffer_length(modbus_server_tag) != 1){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }
    modbus_server_output_data_buffer_add(modbus_server_tag, 7);
    modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_tag->exception_coils);
}

void modbus_server_func_15_force_multiple_coils (struct modbus_server_t* modbus_server_tag){
    uint16_t starting_address;
    uint16_t count_address;

    uint8_t value;
    uint8_t byte_count;
    size_t byte_sent_count;

    if (modbus_server_input_data_buffer_length(modbus_server_tag) < 7){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }

    starting_address = (modbus_server_input_data_buffer_get(modbus_server_tag, 1) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 2); //Pull length from array
    count_address    = (modbus_server_input_data_buffer_get(modbus_server_tag, 3) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 4); //Pull address count

    byte_count = modbus_server_input_data_buffer_get(modbus_server_tag, 5);
    byte_sent_count = modbus_server_input_data_buffer_length(modbus_server_tag) - 6; //Determine how much sent by controller

    //If incorrect byte count
    if ((byte_count != byte_sent_count) || (byte_count != ((count_address-1)/8 + 1))){
        modbus_server_exception_03_illegal_data_value(modbus_server_tag);
        return;
    }

    if (starting_address+count_address > MODBUS_SERVER_POINTS_COILS_SIZE){
        modbus_server_exception_02_illegal_data_address(modbus_server_tag);
        return;
    }

    modbus_server_output_data_buffer_add(modbus_server_tag, 15);

    modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, 1)); //High address
    modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, 2)); //Low address
    modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, 3)); //High count
    modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, 4)); //Low count

    for(size_t i=0;i<count_address;i++){
        value = (( modbus_server_input_data_buffer_get(modbus_server_tag, (i/8)+7)) & (1<<(i%8))) > 0; //Determine 1 or 0
        modbus_server_tag->points.coils[(starting_address+i)/8] &= ~(1<<((starting_address+i)%8)); //Turn off item
        modbus_server_tag->points.coils[(starting_address+i)/8] |= value<<((starting_address+i)%8); //Toggle based on value
    }

    return;
}


void modbus_server_func_16_present_multiple_registers (struct modbus_server_t* modbus_server_tag){
    uint16_t starting_address;
    uint16_t count_address;

    uint8_t byte_count;
    size_t byte_sent_count;

    if (modbus_server_input_data_buffer_length(modbus_server_tag) < 7){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }

    starting_address = (modbus_server_input_data_buffer_get(modbus_server_tag, 1) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 2); //Pull length from array
    count_address    = (modbus_server_input_data_buffer_get(modbus_server_tag, 3) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 4); //Pull address count

    byte_count = modbus_server_input_data_buffer_get(modbus_server_tag, 5);
    byte_sent_count = modbus_server_input_data_buffer_length(modbus_server_tag) - 6; //Determine how much sent by controller

    //If incorrect byte count
    if (byte_count != byte_sent_count){
        modbus_server_exception_03_illegal_data_value(modbus_server_tag);
        return;
    }

    if (starting_address+count_address > MODBUS_SERVER_POINTS_HOLDING_REGISTERS_SIZE){
        modbus_server_exception_02_illegal_data_address(modbus_server_tag);
        return;
    }

    modbus_server_output_data_buffer_add(modbus_server_tag, 16);

    modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, 1)); //High address
    modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, 2)); //Low address
    modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, 3)); //High count
    modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, 4)); //Low countt

    //Load registers in
    for(size_t i=0;i<count_address;i++){
        modbus_server_tag->points.holding_registers[starting_address + i] = (modbus_server_input_data_buffer_get(modbus_server_tag,i*2+7)<<8) | (modbus_server_input_data_buffer_get(modbus_server_tag,i*2+8)); //Write register high and low
    }

    return;
}


void modbus_server_func_17_report_server_id (struct modbus_server_t* modbus_server_tag){
    //TODO: Develop specs for this
    if (modbus_server_input_data_buffer_length(modbus_server_tag) != 1){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }
    modbus_server_output_data_buffer_add(modbus_server_tag, 17);
    modbus_server_output_data_buffer_add(modbus_server_tag, 1); //Byte Count
    //If any value send 0xFF, 0xFF and 0x00 only valid
    if (modbus_server_tag->run_indicator_status) {
        modbus_server_output_data_buffer_add(modbus_server_tag, 0xFF);
    }
    else{
        modbus_server_output_data_buffer_add(modbus_server_tag, 0x00);
    }
}




//SHARED FUNCTIONS

void modbus_server_func_shared_read_coils (struct modbus_server_t* modbus_server_tag, uint8_t array[], size_t array_length, uint8_t function_code){
    uint16_t starting_address;
    uint16_t count_address;

    size_t i = 0;
    uint8_t register_buffer = 0;

    if (modbus_server_input_data_buffer_length(modbus_server_tag) != 5){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }

    starting_address = (modbus_server_input_data_buffer_get(modbus_server_tag, 1) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 2); //Pull length from array
    count_address    = (modbus_server_input_data_buffer_get(modbus_server_tag, 3) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 4); //Pull address count

    if (starting_address+count_address > array_length){
        modbus_server_exception_02_illegal_data_address(modbus_server_tag);
        return;
    }

    modbus_server_output_data_buffer_add(modbus_server_tag, function_code); //Function Code
    modbus_server_output_data_buffer_add(modbus_server_tag, (count_address-1)/8+1); //Byte count

    while(i<count_address){
        register_buffer |= ( ( array[(starting_address+i)/8] & (1 << (starting_address+i)%8) ) > 0 ) << i;
        i += 1;
        //If register buffer filled, add to array and reset
        if (i%8 == 0){
            modbus_server_output_data_buffer_add(modbus_server_tag, register_buffer);
            register_buffer = 0;
        }
    }
    if (i%8 != 0){
        modbus_server_output_data_buffer_add(modbus_server_tag, register_buffer);
        register_buffer = 0;
    }

    return;
}


void modbus_server_func_shared_read_registers (struct modbus_server_t* modbus_server_tag, uint16_t array[], size_t array_length, uint8_t function_code){
    uint16_t starting_address;
    uint16_t count_address;

    if (modbus_server_input_data_buffer_length(modbus_server_tag) != 5){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }

    starting_address = (modbus_server_input_data_buffer_get(modbus_server_tag, 1) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 2); //Pull length from array
    count_address    = (modbus_server_input_data_buffer_get(modbus_server_tag, 3) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 4); //Pull address count

    if (starting_address+count_address > array_length){
        modbus_server_exception_02_illegal_data_address(modbus_server_tag);
        return;
    }

    modbus_server_output_data_buffer_add(modbus_server_tag, function_code); //Function Code
    modbus_server_output_data_buffer_add(modbus_server_tag, count_address * 2); //Byte count

    for(size_t i=starting_address;i<starting_address+count_address;i++){
        modbus_server_output_data_buffer_add(modbus_server_tag, array[i]>>8); //High
        modbus_server_output_data_buffer_add(modbus_server_tag, array[i]);    //Low
    }

    return;
}
