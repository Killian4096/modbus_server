#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "modbus_server.h"
#include "tests_header.h"

#include "tests_utilities.c"
#include "CRC.c"
#include "LRC.c"
#include "unit_tests_diagnostics.c"
#include "unit_tests_functions.c"
#include "unit_tests_exceptions.c"

int main(void){
    CU_initialize_registry();


    CU_pSuite suite = CU_add_suite("ModbusServerTestSuite", 0, 0);
    #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_RTU
    CU_add_test(suite, "RTU_Tests", modbus_server_rtu_tests);
    #endif
    #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_ASCII
    CU_add_test(suite, "ASCII_Tests", modbus_server_ascii_tests);
    #endif
    #ifdef MODBUS_SERVER_COMPILE_PROTOCOL_TCP
    CU_add_test(suite, "TCP_Tests", modbus_server_tcp_tests);
    #endif

    CU_basic_run_tests();
    int failed_tests = CU_get_number_of_tests_failed();
    CU_cleanup_registry();

    //return CU_get_error();
    return failed_tests;
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
    unit_tests_functions(test_protocol);
    unit_tests_exceptions(test_protocol);
}
