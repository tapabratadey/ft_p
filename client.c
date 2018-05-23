/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:30:04 by tadey             #+#    #+#             */
/*   Updated: 2018/05/16 15:30:05 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int error(char *str)
{
    ft_putstr(str);
    exit(0);
}

void error_cases(t_client *client, char *line)
{
    if (ft_strcmp(line, "quit\n") == 0)
    {
        close(client->client_socket);
        error("Disconnected.\n");
    }
    #if 0
    if ((ft_strcmp(line, "ls\n") != 0) && (ft_strcmp(line, "pwd\n") != 0) && (ft_strcmp(line, "cd\n") != 0)
    && (ft_strcmp(line, "cd ..\n") != 0) && (ft_strcmp(line, "cd libft\n") != 0) && (ft_strcmp(line, "cd /\n") != 0) &&
    (ft_strcmp(line, "cd cli\n") != 0) && (ft_strcmp(line, "cd srv\n") != 0))
    {
        close(client->client_socket);
        error("Wrong command.\n");
    }
    #endif
}

void clear_buff(char *buf, int size)
{
    int i;

    i = 0;
    while(i < size)
    {
        buf[i] = '\0';
        i++;
    }
}

void    recv_from_server(t_client *client, char *buff)
{
    if ((client->ret_from_server = recv(client->client_socket, buff, 2048, 0)) <= 0)
    {
        printf("%d", client->ret_from_server);
        error("Couldn't receive a response from server.\n");
        return;
    }
}

void client_call(t_client *client)
{
    char *line;
    char buff[2048];

    line = ft_strnew(1);
    // start
    ft_putstr("-> ");
    //read
    line = read_user(line);
    error_cases(client, line);
    //send to that line(command) to server
    if (line)
    {
        if (send(client->client_socket, line, ft_strlen(line), 0) <= 0)
            return;
    }
    //receive back what server parsed and sent to you
    recv_from_server(client, buff);
    buff[client->ret_from_server] = '\0';
    if (ft_strcmp("Cannot change from root directory.\n", buff) == 0)
        error("Cannot change from root directory.\n");
    //print it out
    printf("%s\n", buff);
    // reset buff and line
    clear_buff(buff, 2048);
    ft_bzero(line, sizeof(line));
    // close(client->client_socket);
}

void create_client_socket(t_client *client, char *hostname)
{
    // struct that deals with internet addresses
    struct sockaddr_in serv_addr;
    int optval;
    socklen_t optlen;
    int client_running;

    optlen = sizeof(optval);
    client_running = 1;

    // create a socket
    client->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->client_socket < 0)
        error("Couldn't create a socket.\n");
    printf("Client socket is created...\n");

    // set keep alive on
    optval = 1;
    optlen = sizeof(optval);

    // specify structure values
    serv_addr.sin_family = AF_INET; //refers to addresses from the internet
    serv_addr.sin_port = htons(client->port);

    // converts IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, hostname, &serv_addr.sin_addr) <= 0)
        error("Check your address.\n");

    // connect
    if ((client->client_connect = connect(client->client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
        error("Couldn't Connect\n");
    printf("Connected to Server.\n\n");
    while(client_running)
        client_call(client);
}

int main(int argc, char **argv)
{
    t_client *client;

    client = (t_client *)malloc(sizeof(t_client));
    client->port = ft_atoi(argv[2]);
    if (argc != 3)
        error("Usage: ./client <host machine> <port>\n");
    while (1)
    {
        create_client_socket(client, argv[1]);
        close(client->client_socket);
    }
    return (0);
}
