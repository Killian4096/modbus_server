#ifndef __MODBUS_SLAVE_DECODE_BUFFER_T__
#define __MODBUS_SLAVE_DECODE_BUFFER_T__


//TODO: Pragma for compilation optionsd


struct modbus_slave_decode_buffer_t{
    uint8_t address;
    uint8_t function_code;
    uint8_t* input_data_buffer_array;
    size_t input_data_buffer_length;
    uint16_t CRC;
};


typedef struct modbus_slave_decode_buffer_t modbus_slave_decode_buffer_t;

#endif
