#include "modbus_slave.h"

#include "modbus_slave_functions.c"
#include "modbus_slave_exceptions.c"
#include "modbus_slave_misc.c"
#include "modbus_slave_diagnostics.c"

void modbus_slave(struct modbus_slave_t* modbus_slave_tag){
    uint8_t address = 0;
    uint8_t function_code = 0;
    //Init output
    modbus_slave_output_data_buffer_init(modbus_slave_tag);

    //Check proper message address + function + 2xCRC
    if(modbus_slave_tag->input_data_buffer.length < 4){
        //No response
        return;
    }


    //Check for crc/parity error
    /*if(modbus_slave_error_check(control, input_data_buffer)){
        //No response
        return;
    }*/

    //Check address
    address = modbus_slave_tag->input_data_buffer.array[0];
    if (address != modbus_slave_tag->address) {
        return; //Not for me
    }

    //Get func code
    function_code = modbus_slave_tag->input_data_buffer.array[1];

    switch (function_code) {
        case 1:
            modbus_slave_func_01_read_coil_status(modbus_slave_tag);
            break;
        case 2:
            modbus_slave_func_02_read_input_status(modbus_slave_tag);
            break;
        case 3:
            modbus_slave_func_03_read_holding_registers(modbus_slave_tag);
            break;
        case 4:
            modbus_slave_func_04_read_input_registers(modbus_slave_tag);
            break;
        case 5:
            modbus_slave_func_05_force_single_coil(modbus_slave_tag);
            break;
        case 6:
            modbus_slave_func_06_present_single_register(modbus_slave_tag);
            break;
        case 7:
            modbus_slave_func_07_read_exception_status(modbus_slave_tag);
            break;
        case 8:
            modbus_slave_func_08_diagnostics(modbus_slave_tag);
            break;
        case 15:
            modbus_slave_func_15_force_multiple_coils(modbus_slave_tag);
            break;
        case 16:
            modbus_slave_func_16_present_multiple_registers(modbus_slave_tag);
            break;
        case 17:
            modbus_slave_func_17_report_slave_id(modbus_slave_tag);
            break;
        default:
            modbus_slave_exception_01_illegal_function(modbus_slave_tag);
    }

    //Only CRC if actual message
    if (modbus_slave_tag->output_data_buffer.length != 0) {
        modbus_slave_data_buffer_crc_gen(&(modbus_slave_tag->output_data_buffer));
    }
}

