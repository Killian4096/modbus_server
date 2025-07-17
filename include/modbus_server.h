#ifndef __MODBUS_SERVER_H__
#define __MODBUS_SERVER_H__


#include <stdint.h>
#include <stddef.h>

//Headers to be exposed
#include "modbus_server_t.h"
#include "modbus_server_defines.h"
#include "modbus_server_settings.h"


//Main
void modbus_server (struct modbus_server_t*);

//Init
void modbus_server_init(struct modbus_server_t*, uint8_t, uint8_t);


//Public Message Accessors
void modbus_server_input_message_buffer_init(struct modbus_server_t*);
void modbus_server_input_message_buffer_add(struct modbus_server_t*, uint8_t);
void modbus_server_output_message_buffer_init(struct modbus_server_t*);
void modbus_server_output_message_buffer_add(struct modbus_server_t*, uint8_t);

uint8_t modbus_server_input_message_buffer_get(struct modbus_server_t*, size_t);
uint8_t modbus_server_output_message_buffer_get(struct modbus_server_t*, size_t);

size_t modbus_server_input_message_buffer_length(struct modbus_server_t*);
size_t modbus_server_output_message_buffer_length(struct modbus_server_t*);








#endif
