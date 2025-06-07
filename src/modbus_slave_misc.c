#include "modbus_slave.h"

/*uint8_t modbus_slave_error_check(struct modbus_slave_control_t* control, const struct modbus_slave_data_buffer_t* data_buffer){
    return 0;
}*/

void modbus_slave_data_buffer_crc_gen(struct modbus_slave_data_buffer_t* data_buffer){
    uint16_t crc = CRC16(data_buffer->array, data_buffer->length);
    uint8_t crc_high = crc >> 8;
    uint8_t crc_low = crc;
    modbus_slave_data_buffer_add(data_buffer, crc_high);
    modbus_slave_data_buffer_add(data_buffer, crc_low);
    //modbus_slave_data_buffer_add(data_buffer, 123);
    //modbus_slave_data_buffer_add(data_buffer, 123);
}

void modbus_slave_data_buffer_init(struct modbus_slave_data_buffer_t* data_buffer){
    data_buffer->length = 0;
}

void modbus_slave_data_buffer_add(struct modbus_slave_data_buffer_t* data_buffer, uint8_t item){
    data_buffer->array[data_buffer->length] = item;
    data_buffer->length += 1;
}

uint8_t modbus_slave_data_buffer_get(struct modbus_slave_data_buffer_t* data_buffer, size_t index){
    return data_buffer->array[index];
}


void modbus_slave_input_data_buffer_init(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_init(&(modbus_slave_tag->input_data_buffer));
}

void modbus_slave_input_data_buffer_add(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    modbus_slave_data_buffer_add(&(modbus_slave_tag->input_data_buffer), item);
}

void modbus_slave_output_data_buffer_init(struct modbus_slave_t* modbus_slave_tag){
    modbus_slave_data_buffer_init(&(modbus_slave_tag->output_data_buffer));
}

void modbus_slave_output_data_buffer_add(struct modbus_slave_t* modbus_slave_tag, uint8_t item){
    modbus_slave_data_buffer_add(&(modbus_slave_tag->output_data_buffer), item);
}
