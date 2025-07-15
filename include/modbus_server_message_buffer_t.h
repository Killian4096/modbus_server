#ifndef __MODBUS_SERVER_MESSAGE_BUFFER_T__
#define __MODBUS_SERVER_MESSAGE_BUFFER_T__

struct modbus_server_message_buffer_t{
    uint8_t array[MODBUS_SERVER_DATA_BUFFER_SIZE];
    size_t length;
};

typedef struct modbus_server_message_buffer_t modbus_server_message_buffer_t;

#endif
