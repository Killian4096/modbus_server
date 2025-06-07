#include "modbus_slave.h"

void modbus_slave_func_08_diagnostics (struct modbus_slave_t* modbus_slave_tag){

    uint16_t diagnosic_subfunction = 0;

    if (modbus_slave_tag->input_data_buffer.length < 6){
        modbus_slave_exception_XX_illegal_function_length(modbus_slave_tag);
        return;
    }

    diagnosic_subfunction = (modbus_slave_tag->input_data_buffer.array[3] << 8) | modbus_slave_tag->input_data_buffer.array[2]; //Grab subfunction

    switch (diagnosic_subfunction) {
        case 0:
            modbus_slave_diagnostic_00_return_query_data(modbus_slave_tag);
            break;
        case 1:
            modbus_slave_diagnostic_01_restart_comm_option(modbus_slave_tag);
            break;
        default:
            modbus_slave_exception_01_illegal_function(modbus_slave_tag);
    }
}


void modbus_slave_diagnostic_00_return_query_data (struct modbus_slave_t* modbus_slave_tag){
    for(size_t i=0;i<modbus_slave_tag->input_data_buffer.length;i++){
        modbus_slave_output_data_buffer_add(modbus_slave_tag, modbus_slave_tag->input_data_buffer.array[i]);
    }
}

void modbus_slave_diagnostic_01_restart_comm_option (struct modbus_slave_t* modbus_slave_tag){
    //TODO: Add functionality
    uint16_t clear_event_log;
    if (modbus_slave_tag->input_data_buffer.length != 8){
        modbus_slave_exception_XX_illegal_function_length(modbus_slave_tag);
        return;
    }

    clear_event_log = (modbus_slave_tag->input_data_buffer.array[4] << 8) | modbus_slave_tag->input_data_buffer.array[5];

    if(clear_event_log==0xFF00){
        //Do something
    }
    else if(clear_event_log==0x0000){
        //Do something
    }
    else{
        //0x00FF and 0x0000 ony valid, error if not those
        modbus_slave_exception_03_illegal_data_value(modbus_slave_tag);
        return;
    }

    //Return query if all good
    modbus_slave_diagnostic_00_return_query_data(modbus_slave_tag);
}

void modbus_slave_diagnostic_02_return_diagnostic_register (struct modbus_slave_t* modbus_slave_tag){
    //TODO: Add Functionality
    return;
}

void modbus_slave_diagnostic_04_force_listen_only_mode (struct modbus_slave_t* modbus_slave_tag){
    //TODO: Add functionaity
    return;
}

