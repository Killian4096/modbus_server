void modbus_server_exception_shared(struct modbus_server_t* modbus_server_tag, uint8_t code) {
    modbus_server_output_PDU_mapper_add(modbus_server_tag, modbus_server_input_PDU_mapper_get(modbus_server_tag, 0) | 1<<7);
    modbus_server_output_PDU_mapper_add(modbus_server_tag, code);
}


void modbus_server_exception_01_illegal_function(struct modbus_server_t* modbus_server_tag){
    modbus_server_exception_shared(modbus_server_tag, 1);
}

void modbus_server_exception_02_illegal_data_address(struct modbus_server_t* modbus_server_tag){
    modbus_server_exception_shared(modbus_server_tag, 2);
}

void modbus_server_exception_03_illegal_data_value(struct modbus_server_t* modbus_server_tag){
    modbus_server_exception_shared(modbus_server_tag, 3);
}

void modbus_server_exception_04_server_device_failure(struct modbus_server_t* modbus_server_tag){
    modbus_server_exception_shared(modbus_server_tag, 4);
}

void modbus_server_exception_05_acknowledge(struct modbus_server_t* modbus_server_tag){
    modbus_server_exception_shared(modbus_server_tag, 5);
}

void modbus_server_exception_06_server_device_busy(struct modbus_server_t* modbus_server_tag){
    modbus_server_exception_shared(modbus_server_tag, 6);
}

void modbus_server_exception_07_negative_acknowledge(struct modbus_server_t* modbus_server_tag){
    modbus_server_exception_shared(modbus_server_tag, 7);
}

void modbus_server_exception_08_memory_parity_error(struct modbus_server_t* modbus_server_tag){
    modbus_server_exception_shared(modbus_server_tag, 8);
}

void modbus_server_exception_XX_illegal_function_length(struct modbus_server_t* modbus_server_tag){
    modbus_server_exception_01_illegal_function(modbus_server_tag);
}
