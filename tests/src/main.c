#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "modbus_server.h"
#include "tests_header.h"

#include "tests_utilities.c"
#include "unit_tests_diagnostics.c"

int main(void){
    CU_initialize_registry();


    CU_pSuite suite = CU_add_suite("ModbusServerTestSuite", 0, 0);
    CU_add_test(suite, "RTU_Tests", modbus_server_rtu_tests);
    CU_add_test(suite, "ASCII_Tests", modbus_server_ascii_tests);
    CU_add_test(suite, "TCP_Tests", modbus_server_tcp_tests);


    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}

void modbus_server_rtu_tests(){
    unit_tests_standard(MODBUS_SERVER_PROTOCOL_RTU);
}

void modbus_server_ascii_tests(){
    unit_tests_standard(MODBUS_SERVER_PROTOCOL_ASCII);
}

void modbus_server_tcp_tests(){
    unit_tests_standard(MODBUS_SERVER_PROTOCOL_TCP);
}

void unit_tests_standard(int test_protocol){
    unit_tests_diagnostics(test_protocol);
}
