void modbus_slave_exception_shared(struct modbus_slave_t* modbus_slave_tag, uint8_t code) {
    modbus_slave_output_data_buffer_add(modbus_slave_tag, modbus_slave_input_data_buffer_get(modbus_slave_tag, 0) | 1<<7);
    modbus_slave_output_data_buffer_add(modbus_slave_tag, code);
}


void modbus_slave_exception_01_illegal_function(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_exception_shared(modbus_slave_tag, 1);
}

void modbus_slave_exception_02_illegal_data_address(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_exception_shared(modbus_slave_tag, 2);
}

void modbus_slave_exception_03_illegal_data_value(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_exception_shared(modbus_slave_tag, 3);
}

void modbus_slave_exception_04_slave_device_failure(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_exception_shared(modbus_slave_tag, 4);
}

void modbus_slave_exception_05_acknowledge(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_exception_shared(modbus_slave_tag, 5);
}

void modbus_slave_exception_06_slave_device_busy(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_exception_shared(modbus_slave_tag, 6);
}

void modbus_slave_exception_07_negative_acknowledge(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_exception_shared(modbus_slave_tag, 7);
}

void modbus_slave_exception_08_memory_parity_error(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_exception_shared(modbus_slave_tag, 8);
}

void modbus_slave_exception_XX_illegal_function_length(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_exception_01_illegal_function(modbus_slave_tag);
}
