#ifndef __MODBUS_SLAVE_FUNCTIONS_H__
#define __MODBUS_SLAVE_FUNCTIONS_H__



//function codes
void modbus_slave_func_01_read_coil_status           (struct modbus_slave_t*);
void modbus_slave_func_02_read_input_status          (struct modbus_slave_t*);
void modbus_slave_func_03_read_holding_registers     (struct modbus_slave_t*);
void modbus_slave_func_04_read_input_registers       (struct modbus_slave_t*);
void modbus_slave_func_05_force_single_coil          (struct modbus_slave_t*);
void modbus_slave_func_06_present_single_register    (struct modbus_slave_t*);
void modbus_slave_func_07_read_exception_status      (struct modbus_slave_t*);
void modbus_slave_func_15_force_multiple_coils       (struct modbus_slave_t*);
void modbus_slave_func_16_present_multiple_registers (struct modbus_slave_t*);
void modbus_slave_func_08_diagnostics                (struct modbus_slave_t*);
void modbus_slave_func_17_report_slave_id            (struct modbus_slave_t*);

//Shared code
void modbus_slave_func_shared_read_coils (struct modbus_slave_t*, uint8_t[], size_t, uint8_t);
void modbus_slave_func_shared_read_registers (struct modbus_slave_t*, uint16_t[], size_t, uint8_t);

//diagnosic codes
void modbus_slave_diagnostic_00_return_query_data           (struct modbus_slave_t*);
void modbus_slave_diagnostic_01_restart_comm_option         (struct modbus_slave_t*);
void modbus_slave_diagnostic_02_return_diagnostic_register  (struct modbus_slave_t*);
void modbus_slave_diagnostic_04_force_listen_only_mode      (struct modbus_slave_t*);

#endif

