#include "modbus_slave.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

//#include "test_utilities.c"
//#include "unit_test_diagnostics.c"

int main(void){
    modbus_slave_t mst;
    modbus_slave_t* modbus_slave_tag = &mst;
    modbus_slave_init(modbus_slave_tag, 1, MODBUS_SLAVE_PROTOCOL_ASCII);
    modbus_slave_tag->diagnostic_register = 142;

    modbus_slave_input_message_buffer_init(modbus_slave_tag);
    modbus_slave_input_message_buffer_add(modbus_slave_tag, ':');
    modbus_slave_input_message_buffer_add(modbus_slave_tag, '0'); // Addr
    modbus_slave_input_message_buffer_add(modbus_slave_tag, '1');
    modbus_slave_input_message_buffer_add(modbus_slave_tag, '0'); // Func
    modbus_slave_input_message_buffer_add(modbus_slave_tag, '8');
    modbus_slave_input_message_buffer_add(modbus_slave_tag, '0'); // Data
    modbus_slave_input_message_buffer_add(modbus_slave_tag, '0');
    modbus_slave_input_message_buffer_add(modbus_slave_tag, '0'); // LRC
    modbus_slave_input_message_buffer_add(modbus_slave_tag, '0');
    modbus_slave_input_message_buffer_add(modbus_slave_tag, '0'); // End 2
    modbus_slave_input_message_buffer_add(modbus_slave_tag, '0');
    modbus_slave_data_buffer_LRC_gen(&(modbus_slave_tag->input_message_buffer));

    modbus_slave(modbus_slave_tag);

    printf("Addr:%i\n", modbus_slave_tag->decode_buffer.address);

    for(size_t i=0;i<modbus_slave_output_message_buffer_length(modbus_slave_tag);i++){
        printf("%c\n", modbus_slave_output_message_buffer_get(modbus_slave_tag, i));
    }





    /*CU_initialize_registry();
    #define TEST_PROTOCOL MODBUS_SLAVE_PROTOCOL_RTU
    CU_pSuite suite = CU_add_suite("ModbusSerialRTUTestSuite", 0, 0);
    CU_add_test(suite, "Diagnostics", unit_test_diagnostics);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;*/
}

