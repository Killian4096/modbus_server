#ifndef __MODBUS_SLAVE_MESSAGE_BUFFER_H__
#define __MODBUS_SLAVE_MESSAGE_BUFFER_H__

uint8_t modbus_slave_input_message_buffer_decode(struct modbus_slave_t*);

void modbus_slave_input_message_buffer_init(struct modbus_slave_t*);
void modbus_slave_input_message_buffer_add(struct modbus_slave_t*, uint8_t);
void modbus_slave_output_message_buffer_init(struct modbus_slave_t*);
void modbus_slave_output_message_buffer_add(struct modbus_slave_t*, uint8_t);
uint8_t modbus_slave_input_message_buffer_get(struct modbus_slave_t*, uint8_t);
uint8_t modbus_slave_output_message_buffer_get(struct modbus_slave_t*, uint8_t);
size_t modbus_slave_input_message_buffer_length(struct modbus_slave_t*);
size_t modbus_slave_output_message_buffer_length(struct modbus_slave_t*);

void modbus_slave_output_data_buffer_init(struct modbus_slave_t*);
void modbus_slave_output_data_buffer_add(struct modbus_slave_t*, uint8_t);
uint8_t modbus_slave_input_data_buffer_get(struct modbus_slave_t*, uint8_t);
uint8_t modbus_slave_output_data_buffer_get(struct modbus_slave_t*, uint8_t);
size_t modbus_slave_input_data_buffer_length(struct modbus_slave_t*);
size_t modbus_slave_output_data_buffer_length(struct modbus_slave_t*);

void modbus_slave_output_message_buffer_header_gen(struct modbus_slave_t*);

#endif
