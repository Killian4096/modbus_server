#ifndef __MODBUS_SLAVE_MESSAGE_BUFFER_H__
#define __MODBUS_SLAVE_MESSAGE_BUFFER_H__

static uint8_t modbus_slave_input_message_buffer_decode(struct modbus_slave_t*);
static uint8_t modbus_slave_input_message_buffer_decode_RTU(struct modbus_slave_t*);
static uint8_t modbus_slave_input_message_buffer_decode_ASCII(struct modbus_slave_t*);
static uint8_t modbus_slave_input_message_buffer_decode_TCP(struct modbus_slave_t*);


//Public
void modbus_slave_input_message_buffer_init(struct modbus_slave_t*);
void modbus_slave_input_message_buffer_add(struct modbus_slave_t*, uint8_t);
void modbus_slave_output_message_buffer_init(struct modbus_slave_t*);
void modbus_slave_output_message_buffer_add(struct modbus_slave_t*, uint8_t);

uint8_t modbus_slave_input_message_buffer_get(struct modbus_slave_t*, uint8_t);
uint8_t modbus_slave_output_message_buffer_get(struct modbus_slave_t*, uint8_t);

size_t modbus_slave_input_message_buffer_length(struct modbus_slave_t*);
size_t modbus_slave_output_message_buffer_length(struct modbus_slave_t*);

//ASCII
static uint8_t modbus_slave_input_message_buffer_get_from_ASCII(struct modbus_slave_t*, uint8_t);
static void modbus_slave_output_message_buffer_add_to_ASCII(struct modbus_slave_t*, uint8_t);

static void modbus_slave_output_data_buffer_init(struct modbus_slave_t*);
static void modbus_slave_output_data_buffer_add(struct modbus_slave_t*, uint8_t);
static void modbus_slave_output_data_buffer_add_RTU(struct modbus_slave_t*, uint8_t);
static void modbus_slave_output_data_buffer_add_ASCII(struct modbus_slave_t*, uint8_t);

static uint8_t modbus_slave_input_data_buffer_get(struct modbus_slave_t*, uint8_t);
static uint8_t modbus_slave_output_data_buffer_get(struct modbus_slave_t*, uint8_t);

static uint8_t modbus_slave_io_data_buffer_get_RTU(struct modbus_slave_t*, uint8_t, uint8_t*);
static uint8_t modbus_slave_io_data_buffer_get_ASCII(struct modbus_slave_t*, uint8_t, uint8_t*);


static size_t modbus_slave_input_data_buffer_length(struct modbus_slave_t*);
static size_t modbus_slave_output_data_buffer_length(struct modbus_slave_t*);

//Header
static void modbus_slave_output_message_buffer_header_gen(struct modbus_slave_t*);
static void modbus_slave_output_message_buffer_header_gen_RTU(struct modbus_slave_t*);
static void modbus_slave_output_message_buffer_header_gen_ASCII(struct modbus_slave_t*);
static void modbus_slave_output_message_buffer_header_gen_TCP(struct modbus_slave_t*);


//Footer
static void modbus_slave_output_message_buffer_footer_gen(struct modbus_slave_t*);
static void modbus_slave_output_message_buffer_footer_gen_RTU(struct modbus_slave_t*);
static void modbus_slave_output_message_buffer_footer_gen_ASCII(struct modbus_slave_t*);
static void modbus_slave_output_message_buffer_footer_gen_TCP(struct modbus_slave_t*);

#endif
