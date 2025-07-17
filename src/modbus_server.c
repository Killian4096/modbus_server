#include "modbus_server.h"
#include "modbus_server_exceptions.h"
#include "modbus_server_functions.h"
#include "modbus_server_message_buffer.h"
#include "modbus_server_PDU_mapper.h"
#include "ASCII.h"
#include "CRC.h"
#include "LRC.h"

#include "modbus_server_functions.c"
#include "modbus_server_exceptions.c"
#include "modbus_server_decode.c"
#include "modbus_server_PDU_mapper.c"
#include "modbus_server_message_buffer.c"
#include "modbus_server_diagnostics.c"
#include "ASCII.c"
#include "CRC.c"
#include "LRC.c"

void modbus_server_init(modbus_server_t* modbus_server_tag, uint8_t address, uint8_t protocol){
    modbus_server_tag->address = address;
    modbus_server_tag->mode_listen_only = 0;
    modbus_server_tag->check_parity=0;
    modbus_server_tag->protocol = protocol;
}

void modbus_server(struct modbus_server_t* modbus_server_tag){

    //Init output
    modbus_server_output_message_buffer_init(modbus_server_tag);

    //Check for crc/parity/fcs/bad length/etc error, if no error tag will be extraxted
    if(!modbus_server_input_message_buffer_decode(modbus_server_tag)){
        //No response
        return;
    }
    //Gen header and set output data buffer to zero
    modbus_server_output_message_buffer_header_gen(modbus_server_tag);

    //Init output data buffer
    modbus_server_output_PDU_mapper_init(modbus_server_tag);

    if(modbus_server_tag->mode_listen_only){
        if(modbus_server_tag->input_message_decode_buffer.function_code == 8){
            modbus_server_diagnostic_01_restart_comm_option(modbus_server_tag);
        }
    }
    else{
        //Switch based on function code
        switch (modbus_server_tag->input_message_decode_buffer.function_code) {
            case 1:
                modbus_server_func_01_read_coil_status(modbus_server_tag);
                break;
            case 2:
                modbus_server_func_02_read_input_status(modbus_server_tag);
                break;
            case 3:
                modbus_server_func_03_read_holding_registers(modbus_server_tag);
                break;
            case 4:
                modbus_server_func_04_read_input_registers(modbus_server_tag);
                break;
            case 5:
                modbus_server_func_05_force_single_coil(modbus_server_tag);
                break;
            case 6:
                modbus_server_func_06_present_single_register(modbus_server_tag);
                break;
            case 7:
                modbus_server_func_07_read_exception_status(modbus_server_tag);
                break;
            case 8:
                modbus_server_func_08_diagnostics(modbus_server_tag);
                break;
            case 15:
                modbus_server_func_15_force_multiple_coils(modbus_server_tag);
                break;
            case 16:
                modbus_server_func_16_present_multiple_registers(modbus_server_tag);
                break;
            case 17:
                modbus_server_func_17_report_server_id(modbus_server_tag);
                break;
            default:
                modbus_server_exception_01_illegal_function(modbus_server_tag);
        }
    }

    //TODO: Add better edge checking
    //If broadcast supress
    if(modbus_server_tag->input_message_decode_buffer.address == 0 && modbus_server_tag->protocol != MODBUS_SERVER_PROTOCOL_TCP){
        modbus_server_output_message_buffer_init(modbus_server_tag);
        return;
    }

    //If no value
    if(modbus_server_tag->output_PDU_mapper_length == 0){
        modbus_server_output_message_buffer_init(modbus_server_tag);
        return;
    }

    //Process message
    //Only CRC if actual message
    if (modbus_server_output_message_buffer_length(modbus_server_tag) != 0) {
        modbus_server_output_message_buffer_footer_gen(modbus_server_tag);
    }
}

