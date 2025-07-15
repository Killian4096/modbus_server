#ifndef __MODBUS_SERVER_H__
#define __MODBUS_SERVER_H__


#include <stdint.h>
#include <stddef.h>

#include "modbus_server_settings.h"
#include "modbus_server_defines.h"
#include "modbus_server_t.h"
#include "modbus_server_exceptions.h"
#include "modbus_server_functions.h"
#include "modbus_server_message_buffer.h"
#include "modbus_server_PDU_mapper.h"
#include "ASCII.h"
#include "CRC.h"
#include "LRC.h"


void modbus_server (struct modbus_server_t*);

//Init
void modbus_server_init(struct modbus_server_t*, uint8_t, uint8_t);








#endif
