void modbus_server_func_08_diagnostics (struct modbus_server_t* modbus_server_tag){

    //Broadcast not supported

    uint16_t diagnosic_subfunction = 0;

    if (modbus_server_input_data_buffer_length(modbus_server_tag) < 3){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }

    diagnosic_subfunction = (modbus_server_input_data_buffer_get(modbus_server_tag, 1) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 2); //Grab subfunction

    switch (diagnosic_subfunction) {
        case 0:
            modbus_server_diagnostic_00_return_query_data(modbus_server_tag);
            break;
        case 1:
            modbus_server_diagnostic_01_restart_comm_option(modbus_server_tag);
            break;
        case 2:
            modbus_server_diagnostic_02_return_diagnostic_register(modbus_server_tag);
            break;
        case 4:
            modbus_server_diagnostic_04_force_listen_only_mode(modbus_server_tag);
            break;
        default:
            modbus_server_exception_01_illegal_function(modbus_server_tag);
    }
}


void modbus_server_diagnostic_00_return_query_data (struct modbus_server_t* modbus_server_tag){
    for(size_t i=0;i<modbus_server_input_data_buffer_length(modbus_server_tag);i++){
        modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_input_data_buffer_get(modbus_server_tag, i));
    }
}

void modbus_server_diagnostic_01_restart_comm_option (struct modbus_server_t* modbus_server_tag){
    //Func is called directly so double check subfunction
    uint16_t diagnosic_subfunction = (modbus_server_input_data_buffer_get(modbus_server_tag, 1) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 2);
    //Bypass if not subfunc aka called from main and not restart
    if(diagnosic_subfunction != 01){
        return;
    }

    uint16_t clear_event_log;
    if (modbus_server_input_data_buffer_length(modbus_server_tag) != 5){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }

    clear_event_log = (modbus_server_input_data_buffer_get(modbus_server_tag, 3) << 8) | modbus_server_input_data_buffer_get(modbus_server_tag, 4);

    if(clear_event_log==0xFF00){
        //TODO:Do something
    }
    else if(clear_event_log==0x0000){
        //TODO:Do something
    }
    else{
        //0x00FF and 0x0000 ony valid, error if not those
        modbus_server_exception_03_illegal_data_value(modbus_server_tag);
        return;
    }

    modbus_server_tag->mode_listen_only=0;

    //Return query if all good
    modbus_server_diagnostic_00_return_query_data(modbus_server_tag);
}



void modbus_server_diagnostic_02_return_diagnostic_register (struct modbus_server_t* modbus_server_tag){
    if (modbus_server_input_data_buffer_length(modbus_server_tag) != 5){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }

    modbus_server_output_data_buffer_add(modbus_server_tag, 8);
    modbus_server_output_data_buffer_add(modbus_server_tag, 0);
    modbus_server_output_data_buffer_add(modbus_server_tag, 2);
    modbus_server_output_data_buffer_add(modbus_server_tag, (modbus_server_tag->diagnostic_register)>>8);
    modbus_server_output_data_buffer_add(modbus_server_tag, modbus_server_tag->diagnostic_register);
    return;
}



void modbus_server_diagnostic_04_force_listen_only_mode (struct modbus_server_t* modbus_server_tag){
    //Check length
    if (modbus_server_input_data_buffer_length(modbus_server_tag) != 5){
        modbus_server_exception_XX_illegal_function_length(modbus_server_tag);
        return;
    }

    //Check data field for 00 00
    if (modbus_server_input_data_buffer_get(modbus_server_tag, 3) || modbus_server_input_data_buffer_get(modbus_server_tag, 4)){
        modbus_server_exception_03_illegal_data_value(modbus_server_tag);
        return;
    }
    modbus_server_tag->mode_listen_only = 1;
    return;
}

