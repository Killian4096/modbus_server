#ifndef __MODBUS_SLAVE_DATA_BUFFER_T__
#define __MODBUS_SLAVE_DATA_BUFFER_T__

struct modbus_slave_data_buffer_t{
    uint8_t array[MODBUS_SLAVE_DATA_BUFFER_SIZE];
    size_t length;
};

//data buffer factory
void modbus_slave_data_buffer_init(struct modbus_slave_data_buffer_t*);
void modbus_slave_data_buffer_add(struct modbus_slave_data_buffer_t*, uint8_t);
uint8_t modbus_slave_data_buffer_get(struct modbus_slave_data_buffer_t*, size_t);

uint8_t modbus_slave_data_buffer_CRC_check(const struct modbus_slave_data_buffer_t*);
void modbus_slave_data_buffer_CRC_gen(struct modbus_slave_data_buffer_t*);


typedef struct modbus_slave_data_buffer_t modbus_slave_data_buffer_t;

#endif
