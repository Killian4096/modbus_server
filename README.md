# Modbus Slave

A simple, protable library designed to emulate a modbus slave. Written in C to ensure maximum compatibility.

## Usage

Usage is fairly simple. See below.

```
#include "modbus_slave.h"
#include <stdio.h>


//Declare Modbus Slave Struct
modbus_slave_t modbus_slave_tag;

//Initialize Struct Values
modbus_slave_init(modbus_slave_tag);

//Do your own stuff
modbus_slave_tag.address = 2;                      //Set slave address to 2
modbus_slave_tag.points.coils[0] = 0xFF;           //Set first 00001-00008 coils to 1
modbus_slave_tag.points.holding_registers[2] = 25; //Set holding reg 400003 to 25
//etc

while(1){
    some_function(some_value); //Your looping code

    //Code to process from peripheral (RS-232, TCP, Other Serial, etc) to buffer
    //In this example buffer sends a read coil command function code 0
    modbus_slave_input_data_buffer_init(modbus_slave_tag);    //Init message
    modbus_slave_input_data_buffer_add(modbus_slave_tag, 2);  //Slave Address 2
    modbus_slave_input_data_buffer_add(modbus_slave_tag, 1);  //Function Code 1
    modbus_slave_input_data_buffer_add(modbus_slave_tag, 0);  //High Byte Start Address
    modbus_slave_input_data_buffer_add(modbus_slave_tag, 13); //Start Address 13
    modbus_slave_input_data_buffer_add(modbus_slave_tag, 00); //High Byte Register Count
    modbus_slave_input_data_buffer_add(modbus_slave_tag, 25); //Read 25 Registers
    modbus_slave_input_data_buffer_add(modbus_slave_tag, 27); //CRC
    modbus_slave_input_data_buffer_add(modbus_slave_tag, 0C); //CRC

    modbus_slave(modbus_slave_tag) //Process request

    //Send request, in this case print
    for(size_t i=0;i<modbus_slave_tag.output_data_buffer.length;i++){
        printf("%i", modbus_slave_tag.output_data_buffer.array[i])
    }
}
```

See full Modbus Documentation at [Modbus Reference Guide](https://www.modbus.org/docs/PI_MBUS_300.pdf).

## Documentation

Coming Soon...
