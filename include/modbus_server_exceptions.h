#ifndef __MODBUS_SERVER_EXCEPTIONS_H__
#define __MODBUS_SERVER_EXCEPTIONS_H__


//exception codes
static void modbus_server_exception_01_illegal_function      (struct modbus_server_t*);
static void modbus_server_exception_02_illegal_data_address  (struct modbus_server_t*);
static void modbus_server_exception_03_illegal_data_value    (struct modbus_server_t*);
static void modbus_server_exception_04_server_device_failure  (struct modbus_server_t*);
static void modbus_server_exception_05_acknowledge           (struct modbus_server_t*);
static void modbus_server_exception_06_server_device_busy     (struct modbus_server_t*);
static void modbus_server_exception_07_negative_acknowledge  (struct modbus_server_t*);
static void modbus_server_exception_08_memory_parity_error   (struct modbus_server_t*);

static void modbus_server_exception_XX_illegal_function_length   (struct modbus_server_t*);

static void modbus_server_exception_shared (struct modbus_server_t*, uint8_t);

#endif
