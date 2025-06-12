#ifndef __MODBUS_SLAVE_EXCEPTIONS_H__
#define __MODBUS_SLAVE_EXCEPTIONS_H__


//exception codes
void modbus_slave_exception_01_illegal_function      (struct modbus_slave_t*);
void modbus_slave_exception_02_illegal_data_address  (struct modbus_slave_t*);
void modbus_slave_exception_03_illegal_data_value    (struct modbus_slave_t*);
void modbus_slave_exception_04_slave_device_failure  (struct modbus_slave_t*);
void modbus_slave_exception_05_acknowledge           (struct modbus_slave_t*);
void modbus_slave_exception_06_slave_device_busy     (struct modbus_slave_t*);
void modbus_slave_exception_07_negative_acknowledge  (struct modbus_slave_t*);
void modbus_slave_exception_08_memory_parity_error   (struct modbus_slave_t*);

void modbus_slave_exception_XX_illegal_function_length   (struct modbus_slave_t*);

void modbus_slave_exception_shared (struct modbus_slave_t*, uint8_t);

#endif
