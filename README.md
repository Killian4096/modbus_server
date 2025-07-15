# Modbus Server

A simple, protable library designed to emulate a modbus server. Written in C to ensure maximum compatibility.

## Usage

Usage is fairly simple. See below.

```
#include "modbus_server.h"
#include <stdio.h>


//Declare Modbus Server Struct
modbus_server_t modbus_server_tag;

//Initialize Struct Values
modbus_server_init(modbus_server_tag);

//Do your own stuff
modbus_server_tag.address = 2;                      //Set server address to 2
modbus_server_tag.points.coils[0] = 0xFF;           //Set first 00001-00008 coils to 1
modbus_server_tag.points.holding_registers[2] = 25; //Set holding reg 400003 to 25
//etc

while(1){
    some_function(some_value); //Your looping code

    //Code to process from peripheral (RS-232, TCP, Other Serial, etc) to buffer
    //In this example buffer sends a read coil command function code 0
    modbus_server_input_PDU_mapper_init(modbus_server_tag);    //Init message
    modbus_server_input_PDU_mapper_add(modbus_server_tag, 2);  //Server Address 2
    modbus_server_input_PDU_mapper_add(modbus_server_tag, 1);  //Function Code 1
    modbus_server_input_PDU_mapper_add(modbus_server_tag, 0);  //High Byte Start Address
    modbus_server_input_PDU_mapper_add(modbus_server_tag, 13); //Start Address 13
    modbus_server_input_PDU_mapper_add(modbus_server_tag, 00); //High Byte Register Count
    modbus_server_input_PDU_mapper_add(modbus_server_tag, 25); //Read 25 Registers
    modbus_server_input_PDU_mapper_add(modbus_server_tag, 27); //CRC
    modbus_server_input_PDU_mapper_add(modbus_server_tag, 0C); //CRC

    modbus_server(modbus_server_tag) //Process request

    //Send request, in this case print
    for(size_t i=0;i<modbus_server_tag.output_PDU_mapper.length;i++){
        printf("%i", modbus_server_tag.output_PDU_mapper.array[i])
    }
}
```

See full Modbus Documentation at [Modbus Reference Guide](https://www.modbus.org/docs/PI_MBUS_300.pdf).

## Documentation

Coming Soon...
