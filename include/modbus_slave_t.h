#ifndef __MODBUS_SLAVE_T__
#define __MODBUS_SLAVE_T__

#include "modbus_slave_data_buffer_t.h"
#include "modbus_slave_points_t.h"

struct modbus_slave_t{
    uint8_t address;
    uint8_t listen_only_mode;

    struct modbus_slave_data_buffer_t input_data_buffer;
    struct modbus_slave_data_buffer_t output_data_buffer;

    struct modbus_slave_points_t points;

    uint8_t exception_coils;
    uint8_t run_indicator_status;

};

typedef struct modbus_slave_t modbus_slave_t;

#endif
