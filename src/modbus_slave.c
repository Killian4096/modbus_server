#include "modbus_slave.h"

#include "modbus_slave_functions.c"
#include "modbus_slave_exceptions.c"
#include "modbus_slave_decode.c"
#include "modbus_slave_data_buffer_t.c"
#include "modbus_slave_data_buffer.c"
#include "modbus_slave_message_buffer.c"
#include "modbus_slave_diagnostics.c"
#include "ASCII.c"
#include "CRC.c"
#include "LRC.c"

void modbus_slave_init(modbus_slave_t* modbus_slave_tag, uint8_t address, uint8_t protocol){
    modbus_slave_tag->address = address;
    modbus_slave_tag->mode_listen_only = 0;
    modbus_slave_tag->check_parity=0;
    modbus_slave_tag->protocol = protocol;
}

void modbus_slave(struct modbus_slave_t* modbus_slave_tag){

    //Init output
    modbus_slave_output_message_buffer_init(modbus_slave_tag);

    //Check for crc/parity/fcs/bad length/etc error, if no error tag will be extraxted
    if(!modbus_slave_input_message_buffer_decode(modbus_slave_tag)){
        //No response
        return;
    }
    //Gen header and set output data buffer to zero
    modbus_slave_output_message_buffer_header_gen(modbus_slave_tag);

    //Init output data buffer
    modbus_slave_output_data_buffer_init(modbus_slave_tag);

    if(modbus_slave_tag->mode_listen_only){
        if(modbus_slave_tag->decode_buffer.function_code == 8){
            modbus_slave_diagnostic_01_restart_comm_option(modbus_slave_tag);
        }
    }
    else{
        //Switch based on function code
        switch (modbus_slave_tag->decode_buffer.function_code) {
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
    }

    //TODO: Add better edge checking
    //If broadcast supress
    if(modbus_slave_tag->decode_buffer.address == 0 && modbus_slave_tag->protocol != MODBUS_SLAVE_PROTOCOL_TCP){
        modbus_slave_output_message_buffer_init(modbus_slave_tag);
        return;
    }

    //If no value
    if(modbus_slave_tag->output_data_buffer_length == 0){
        modbus_slave_output_message_buffer_init(modbus_slave_tag);
        return;
    }

    //Process message
    //Only CRC if actual message
    if (modbus_slave_output_message_buffer_length(modbus_slave_tag) != 0) {
        modbus_slave_output_message_buffer_footer_gen(modbus_slave_tag);
    }
}

