#ifndef __MODBUS_SERVER_T__
#define __MODBUS_SERVER_T__

#include "modbus_server_settings.h"
#include "modbus_server_message_buffer_t.h"
#include "modbus_server_decode_buffer_t.h"
#include "modbus_server_points_t.h"

struct modbus_server_t{
    uint8_t address;
    uint8_t mode_listen_only;

    struct modbus_server_message_buffer_t input_message_buffer;
    struct modbus_server_message_buffer_t output_message_buffer;

    struct modbus_server_decode_buffer_t input_message_decode_buffer;

    uint8_t* output_PDU_mapper_array;
    size_t output_PDU_mapper_length;

    struct modbus_server_points_t points;

    uint8_t exception_coils;
    uint8_t run_indicator_status;
    uint16_t diagnostic_register;

    uint8_t check_parity;
    uint8_t check_crc;
    uint8_t check_lrc;
    uint8_t check_fcs;
    uint8_t check_ip_header;
    uint8_t check_tcp;

    uint8_t protocol;

};

typedef struct modbus_server_t modbus_server_t;

#endif
