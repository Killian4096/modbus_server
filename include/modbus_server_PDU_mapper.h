#ifndef __MODBUS_SERVER_PDU_MAPPER_H__
#define __MODBUS_SERVER_PDU_MAPPER_H__

static void modbus_server_output_PDU_mapper_init(struct modbus_server_t*);
static void modbus_server_output_PDU_mapper_add(struct modbus_server_t*, uint8_t);
static void modbus_server_output_PDU_mapper_add_RTU(struct modbus_server_t*, uint8_t);
static void modbus_server_output_PDU_mapper_add_ASCII(struct modbus_server_t*, uint8_t);

static uint8_t modbus_server_input_PDU_mapper_get(struct modbus_server_t*, uint8_t);
static uint8_t modbus_server_output_PDU_mapper_get(struct modbus_server_t*, uint8_t);

static uint8_t modbus_server_io_PDU_mapper_get_RTU(struct modbus_server_t*, uint8_t, uint8_t*);
static uint8_t modbus_server_io_PDU_mapper_get_ASCII(struct modbus_server_t*, uint8_t, uint8_t*);


static size_t modbus_server_input_PDU_mapper_length(struct modbus_server_t*);
static size_t modbus_server_output_PDU_mapper_length(struct modbus_server_t*);

#endif
