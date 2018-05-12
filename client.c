#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "libft/libft.h"

int main(int argc, char **argv)
{
    int client_socket;
    int ret;
    struct sockaddr_in server_addr;

    if (argc < 3)
    {
        printf("Usage: %s <server> <port>\n", argv[0]);
        exit(0);
    }
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        ft_putstr("Couldn't connect.\n");
        exit(0);
    }
    ft_putstr("Client socket is created.\n");

    // filling server struct with null values
    ft_memset((void**)&server_addr, '\0', sizeof(server_addr));

    // specify the struct values
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(ft_atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // connect which returns an integer
    // 1st param- is our socket
    // 2nd param- cast our server address struct sockadd and pass the address
    // 3rd param - size of the address use the sizeof();
    ret = connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0)
    {
        ft_putstr("Couldn't connect.\n");
        exit(0);
    }
    printf("Connected to the server.\n");

    // infinite while loop until the client wants to disconnect with the server
   /* while (1)
    {
        ft_putstr("Client: ");
        // sending the message to the server
        // 1st- sending the client socket
        // 2nd- the message
        // 3rd- size of the buffer
        send(client_socket, buff, ft_strlen(buff), 0);

        if (ft_strcmp(buff, "quit") == 0)
        {
            ft_putstr("Disconnected from the server.\n");
            exit(1);
        }
        if (recv(client_socket, buff, sizeof(buff), 0) < 0)
            ft_putstr("Couldn't receive data.\n");
        else
            printf("Server: %s\n", buff);
    }*/
    return (0);
}