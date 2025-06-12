#ifndef __MODBUS_SLAVE_T__
#define __MODBUS_SLAVE_T__

#include "modbus_slave_settings.h"
#include "modbus_slave_data_buffer_t.h"
#include "modbus_slave_decode_buffer_t.h"
#include "modbus_slave_points_t.h"

struct modbus_slave_t{
    uint8_t address;
    uint8_t mode_listen_only;

    struct modbus_slave_data_buffer_t input_message_buffer;
    struct modbus_slave_data_buffer_t output_message_buffer;

    struct modbus_slave_decode_buffer_t decode_buffer;

    uint8_t* output_data_buffer_array;
    size_t output_data_buffer_length;

    struct modbus_slave_points_t points;

    uint8_t exception_coils;
    uint8_t run_indicator_status;
    uint16_t diagnostic_register;

    uint8_t check_parity;
    uint8_t check_crc;
    uint8_t check_lrc;
    uint8_t check_fcs;
    uint8_t check_ip_header;
    uint8_t check_tcp;

};

typedef struct modbus_slave_t modbus_slave_t;

#endif
