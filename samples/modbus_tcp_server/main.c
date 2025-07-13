// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include "modbus_slave.h"

#define PORT 8080
int main(int argc, char const *argv[])
{
    //Definitions
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    //Modbus Configuration Stuff
    modbus_slave_t mst;
    modbus_slave_t* modbus_slave_tag = &mst;
    modbus_slave_init(modbus_slave_tag, 1, MODBUS_SLAVE_PROTOCOL_TCP);




    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    memset(address.sin_zero, '\0', sizeof address.sin_zero);


    //TCP Error Checking
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("Waiting for new client connection...\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        printf("Connected\n");

        while(1){
            //Initialize modbus input_message_buffer
            modbus_slave_input_message_buffer_init(modbus_slave_tag);
            valread = read(new_socket, modbus_slave_tag->input_message_buffer.array, MODBUS_SLAVE_DATA_BUFFER_SIZE);
            modbus_slave_tag->input_message_buffer.length = MODBUS_SLAVE_DATA_BUFFER_SIZE;
            modbus_slave(modbus_slave_tag);
            write(new_socket , modbus_slave_tag->output_message_buffer.array , modbus_slave_tag->output_message_buffer.length);
        }
        close(new_socket);
    }
    return 0;
}
