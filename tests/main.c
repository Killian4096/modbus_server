#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "modbus_slave.h"
#include "tests_header.h"

uint8_t TEST_PROTOCOL;

#include "test_utilities.c"
#include "unit_test_diagnostics.c"

void standard_tests(CU_pSuite *);

int main(void){
    CU_initialize_registry();
    TEST_PROTOCOL=MODBUS_SLAVE_PROTOCOL_RTU;
    CU_pSuite suite_RTU = CU_add_suite("ModbusSerialRTUTestSuite", 0, 0);
    standard_tests(&suite_RTU);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}

void standard_tests(CU_pSuite *suite){
    CU_add_test(*suite, "Diagnostics", unit_test_diagnostics);
}
