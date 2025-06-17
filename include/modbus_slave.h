#ifndef __MODBUS_SLAVE_H__
#define __MODBUS_SLAVE_H__


#include <stdint.h>
#include <stddef.h>

#include "modbus_slave_settings.h"
#include "modbus_slave_defines.h"
#include "modbus_slave_t.h"
#include "modbus_slave_exceptions.h"
#include "modbus_slave_functions.h"
#include "modbus_slave_message_buffer.h"
#include "ASCII.h"
#include "CRC.h"
#include "LRC.h"


void modbus_slave (struct modbus_slave_t*);

//Init
void modbus_slave_init(struct modbus_slave_t*, uint8_t, uint8_t);








#endif
