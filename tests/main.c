#include "modbus_slave.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "test_utilities.c"
#include "unit_test_diagnostics.c"

int main(void){
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("ModbusSerialTestSuite", 0, 0);
    CU_add_test(suite, "Diagnostics Tests", unit_test_diagnostics);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}

