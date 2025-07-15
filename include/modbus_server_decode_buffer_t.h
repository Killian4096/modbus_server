#ifndef __MODBUS_SERVER_DECODE_BUFFER_T__
#define __MODBUS_SERVER_DECODE_BUFFER_T__


//TODO: Pragma for compilation options


struct modbus_server_decode_buffer_t{
    uint8_t address;
    uint8_t function_code;
    uint8_t* input_PDU_mapper_array;
    size_t input_PDU_mapper_length;
    uint16_t CRC;
    uint8_t LRC;
    uint16_t transaction_identifier;
    uint16_t protocol_identifier;
    uint8_t unit_identifier;
};


typedef struct modbus_server_decode_buffer_t modbus_server_decode_buffer_t;

#endif
