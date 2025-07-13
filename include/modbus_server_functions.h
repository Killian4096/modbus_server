#ifndef __MODBUS_SERVER_FUNCTIONS_H__
#define __MODBUS_SERVER_FUNCTIONS_H__



//function codes
static void modbus_server_func_01_read_coil_status           (struct modbus_server_t*);
static void modbus_server_func_02_read_input_status          (struct modbus_server_t*);
static void modbus_server_func_03_read_holding_registers     (struct modbus_server_t*);
static void modbus_server_func_04_read_input_registers       (struct modbus_server_t*);
static void modbus_server_func_05_force_single_coil          (struct modbus_server_t*);
static void modbus_server_func_06_present_single_register    (struct modbus_server_t*);
static void modbus_server_func_07_read_exception_status      (struct modbus_server_t*);
static void modbus_server_func_15_force_multiple_coils       (struct modbus_server_t*);
static void modbus_server_func_16_present_multiple_registers (struct modbus_server_t*);
static void modbus_server_func_08_diagnostics                (struct modbus_server_t*);
static void modbus_server_func_17_report_server_id            (struct modbus_server_t*);

//Shared code
static void modbus_server_func_shared_read_coils (struct modbus_server_t*, uint8_t[], size_t, uint8_t);
static void modbus_server_func_shared_read_registers (struct modbus_server_t*, uint16_t[], size_t, uint8_t);

//diagnosic codes
static void modbus_server_diagnostic_00_return_query_data           (struct modbus_server_t*);
static void modbus_server_diagnostic_01_restart_comm_option         (struct modbus_server_t*);
static void modbus_server_diagnostic_02_return_diagnostic_register  (struct modbus_server_t*);
static void modbus_server_diagnostic_04_force_listen_only_mode      (struct modbus_server_t*);

#endif

