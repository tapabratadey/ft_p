#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "libft/libft.h"

typedef struct s_client
{
    int client_socket;
    int port;
    int client_connect;
    int ret_from_server;

}   t_client;

// client
void    create_client_socket(t_client *client, char *hostname);
int     error(char *str);
void    client_loop(t_client *client);
int		get_next_line(int const fd, char **line);
#endif