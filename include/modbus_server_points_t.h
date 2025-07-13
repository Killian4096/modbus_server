#ifndef __MODBUS_SERVER_POINTS_T__
#define __MODBUS_SERVER_POINTS_T__

struct modbus_server_points_t{
    uint8_t coils[(MODBUS_SERVER_POINTS_COILS_SIZE-1)/8 + 1];
    uint8_t inputs[(MODBUS_SERVER_POINTS_INPUTS_SIZE-1)/8 + 1];
    uint16_t holding_registers[MODBUS_SERVER_POINTS_HOLDING_REGISTERS_SIZE];
    uint16_t input_registers[MODBUS_SERVER_POINTS_INPUT_REGISTERS_SIZE];
};

typedef struct modbus_server_points_t modbus_server_points_t;

#endif
