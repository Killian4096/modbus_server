void modbus_slave_func_08_diagnostics (struct modbus_slave_t* modbus_slave_tag){

    //Broadcast not supported

    uint16_t diagnosic_subfunction = 0;

    if (modbus_slave_input_data_buffer_length(modbus_slave_tag) < 3){
        modbus_slave_exception_XX_illegal_function_length(modbus_slave_tag);
        return;
    }

    diagnosic_subfunction = (modbus_slave_input_data_buffer_get(modbus_slave_tag, 1) << 8) | modbus_slave_input_data_buffer_get(modbus_slave_tag, 2); //Grab subfunction

    switch (diagnosic_subfunction) {
        case 0:
            modbus_slave_diagnostic_00_return_query_data(modbus_slave_tag);
            break;
        case 1:
            modbus_slave_diagnostic_01_restart_comm_option(modbus_slave_tag);
            break;
        case 2:
            modbus_slave_diagnostic_02_return_diagnostic_register(modbus_slave_tag);
            break;
        case 4:
            modbus_slave_diagnostic_04_force_listen_only_mode(modbus_slave_tag);
            break;
        default:
            modbus_slave_exception_01_illegal_function(modbus_slave_tag);
    }
}


void modbus_slave_diagnostic_00_return_query_data (struct modbus_slave_t* modbus_slave_tag){
    for(size_t i=0;i<modbus_slave_input_data_buffer_length(modbus_slave_tag);i++){
        modbus_slave_output_data_buffer_add(modbus_slave_tag, modbus_slave_input_data_buffer_get(modbus_slave_tag, i));
    }
}

void modbus_slave_diagnostic_01_restart_comm_option (struct modbus_slave_t* modbus_slave_tag){
    //Func is called directly so double check subfunction
    uint16_t diagnosic_subfunction = (modbus_slave_input_data_buffer_get(modbus_slave_tag, 1) << 8) | modbus_slave_input_data_buffer_get(modbus_slave_tag, 2);
    //Bypass if not subfunc aka called from main and not restart
    if(diagnosic_subfunction != 01){
        return;
    }

    uint16_t clear_event_log;
    if (modbus_slave_input_data_buffer_length(modbus_slave_tag) != 5){
        modbus_slave_exception_XX_illegal_function_length(modbus_slave_tag);
        return;
    }

    clear_event_log = (modbus_slave_input_data_buffer_get(modbus_slave_tag, 3) << 8) | modbus_slave_input_data_buffer_get(modbus_slave_tag, 4);

    if(clear_event_log==0xFF00){
        //TODO:Do something
    }
    else if(clear_event_log==0x0000){
        //TODO:Do something
    }
    else{
        //0x00FF and 0x0000 ony valid, error if not those
        modbus_slave_exception_03_illegal_data_value(modbus_slave_tag);
        return;
    }

    modbus_slave_tag->mode_listen_only=0;

    //Return query if all good
    modbus_slave_diagnostic_00_return_query_data(modbus_slave_tag);
}



void modbus_slave_diagnostic_02_return_diagnostic_register (struct modbus_slave_t* modbus_slave_tag){
    if (modbus_slave_input_data_buffer_length(modbus_slave_tag) != 5){
        modbus_slave_exception_XX_illegal_function_length(modbus_slave_tag);
        return;
    }

    modbus_slave_output_data_buffer_add(modbus_slave_tag, 8);
    modbus_slave_output_data_buffer_add(modbus_slave_tag, 0);
    modbus_slave_output_data_buffer_add(modbus_slave_tag, 2);
    modbus_slave_output_data_buffer_add(modbus_slave_tag, (modbus_slave_tag->diagnostic_register)>>8);
    modbus_slave_output_data_buffer_add(modbus_slave_tag, modbus_slave_tag->diagnostic_register);
    return;
}



void modbus_slave_diagnostic_04_force_listen_only_mode (struct modbus_slave_t* modbus_slave_tag){
    //Check length
    if (modbus_slave_input_data_buffer_length(modbus_slave_tag) != 5){
        modbus_slave_exception_XX_illegal_function_length(modbus_slave_tag);
        return;
    }

    //Check data field for 00 00
    if (modbus_slave_input_data_buffer_get(modbus_slave_tag, 3) || modbus_slave_input_data_buffer_get(modbus_slave_tag, 4)){
        modbus_slave_exception_03_illegal_data_value(modbus_slave_tag);
        return;
    }
    modbus_slave_tag->mode_listen_only = 1;
    return;
}

