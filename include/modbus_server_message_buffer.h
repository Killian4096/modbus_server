#ifndef __MODBUS_SERVER_MESSAGE_BUFFER_H__
#define __MODBUS_SERVER_MESSAGE_BUFFER_H__

static uint8_t modbus_server_input_message_buffer_decode(struct modbus_server_t*);
static uint8_t modbus_server_input_message_buffer_decode_RTU(struct modbus_server_t*);
static uint8_t modbus_server_input_message_buffer_decode_ASCII(struct modbus_server_t*);
static uint8_t modbus_server_input_message_buffer_decode_TCP(struct modbus_server_t*);


//Public
void modbus_server_input_message_buffer_init(struct modbus_server_t*);
void modbus_server_input_message_buffer_add(struct modbus_server_t*, uint8_t);
void modbus_server_output_message_buffer_init(struct modbus_server_t*);
void modbus_server_output_message_buffer_add(struct modbus_server_t*, uint8_t);

uint8_t modbus_server_input_message_buffer_get(struct modbus_server_t*, uint8_t);
uint8_t modbus_server_output_message_buffer_get(struct modbus_server_t*, uint8_t);

size_t modbus_server_input_message_buffer_length(struct modbus_server_t*);
size_t modbus_server_output_message_buffer_length(struct modbus_server_t*);

//ASCII
static uint8_t modbus_server_input_message_buffer_get_from_ASCII(struct modbus_server_t*, uint8_t);
static void modbus_server_output_message_buffer_add_to_ASCII(struct modbus_server_t*, uint8_t);

//Header
static void modbus_server_output_message_buffer_header_gen(struct modbus_server_t*);
static void modbus_server_output_message_buffer_header_gen_RTU(struct modbus_server_t*);
static void modbus_server_output_message_buffer_header_gen_ASCII(struct modbus_server_t*);
static void modbus_server_output_message_buffer_header_gen_TCP(struct modbus_server_t*);


//Footer
static void modbus_server_output_message_buffer_footer_gen(struct modbus_server_t*);
static void modbus_server_output_message_buffer_footer_gen_RTU(struct modbus_server_t*);
static void modbus_server_output_message_buffer_footer_gen_ASCII(struct modbus_server_t*);
static void modbus_server_output_message_buffer_footer_gen_TCP(struct modbus_server_t*);

//Basic
static void modbus_server_message_buffer_init(struct modbus_server_message_buffer_t*);
static void modbus_server_message_buffer_add(struct modbus_server_message_buffer_t*, uint8_t);

//CRC and LRC
void modbus_server_message_buffer_CRC_gen(struct modbus_server_message_buffer_t*);
void modbus_server_message_buffer_LRC_gen(struct modbus_server_message_buffer_t*);
uint8_t modbus_server_message_buffer_CRC_check(const struct modbus_server_message_buffer_t*);
uint8_t modbus_server_message_buffer_LRC_check(const struct modbus_server_message_buffer_t*);

#endif
