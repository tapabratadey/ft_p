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
    int sock_fd;
    int ret;
    int new_socket;

    struct sockaddr_in new_addr;
    struct sockaddr_in server_addr;

    char    *buff;
    pid_t   child;

    if (argc < 2)
    {
        printf("No port provided.\n");
        exit(0);
    }
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        ft_putstr("Couldn't connect.\n");
        exit(0);
    }
    ft_putstr("Server socket is created.\n");
    
    ft_memset((void**)&server_addr, '\0', sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(argv[1]);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sock_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if (ret < 0)
    {
        ft_putstr("Error in binding");
        exit(0);
    }
    printf("Binding to port %d\n", 4444);

    if (listen(sock_fd, 10) == 0)
        ft_putstr("Listening...\n");
    else
        ft_putstr("Error in binding.\n");

    while (1)
    {
        new_socket = accept(sock_fd, (struct sockaddr*)&new_addr, sizeof(new_addr));
        if (new_socket < 0)
            exit(0);
    }
    // print ip and port
    printf("Connection is accepted from %s:%d\n", inet_ntoa(new_addr.sin_addr), ntoa(new_addr.sin_port));
    
    if ((child = fork()) == 0)
        close (sock_fd);
    while (1)
    {
        recv(new_socket, buff, 1024, 0);
        if (ft_strcmp(buff, "quit") == 0)
        {
            printf("Connection is accepted from %s:%d\n", inet_ntoa(new_addr.sin_addr), ntoa(new_addr.sin_port));
            break ;
        }
        else
        {
            printf("Client: %s\n", buff);
            send(new_socket, buff, ft_strlen(buff, ))
        }

    }
    
    return (0);
}
