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

char *read_user(char *line)
{
    int read_ret;
    char buff[2];
    char *old_line;

    read_ret = 0;
    while ((read_ret = read(0, buff, 1)) > 0)
    {
        buff[1] = '\0';
        old_line = line;
        line = ft_strjoin(line, buff);
        free(old_line);
        if (buff[0] == '\n')
            break;
    }
    return (line);
}

void error_cases(t_client *client, char *line)
{
    if (ft_strcmp(line, "quit\n") == 0)
    {
        close(client->client_socket);
        error("Disconnected.\n");
    }
    if ((ft_strcmp(line, "ls\n") != 0) && (ft_strcmp(line, "pwd\n") != 0) && (ft_strcmp(line, "cd\n") != 0))
    {
        close(client->client_socket);
        error("Wrong command.\n");
    }
}

void client_loop(t_client *client)
{
    char *line;
    int gnl;
    char buff[1024];
    // int optval;
    // socklen_t optlen = sizeof(optval);

    line = ft_strnew(1);
    gnl = 0;
    while (1)
    {
        // start
        ft_putstr("-> ");

        //read
        line = read_user(line);
        error_cases(client, line);

        ft_putstr(line);
        //send to that line(command) to server
        if (line)
            send(client->client_socket, line, ft_strlen(line), 0);
        
        //receive back what server parsed and sent to you
        if ((client->ret_from_server = recv(client->client_socket, buff, 1023, 0)) <= 0)
        {
            printf("%d", client->ret_from_server);     
            error("Couldn't receive a response from server.\n");
        }
        printf("recv: %d", client->ret_from_server); 
        // printf("Received response from server.\n");
        buff[client->ret_from_server] = '\0';

        //print it out
        printf("%s\n", buff);

        // reset buff and line
        ft_bzero(buff, sizeof(buff));
        ft_bzero(line, sizeof(line));
    }
}

void create_client_socket(t_client *client, char *hostname)
{
    // struct that deals with internet addresses
    struct sockaddr_in serv_addr;
    int optval;
    socklen_t optlen = sizeof(optval);

    // create a socket
    client->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->client_socket < 0)
        error("Couldn't create a socket.\n");
    printf("Client socket is created...\n");

    #if 0
        // check the status for the keepalive option
        if (getsockopt(client->client_socket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0)
        {
            perror("getsockopt()");
            close(client->client_socket);
            exit(EXIT_FAILURE);
        }
        printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));
    #endif 
        // set keep alive on
        optval = 1;
        optlen = sizeof(optval);
        if (setsockopt(client->client_socket, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0)
        {
            perror("setsockopt()");
            close(client->client_socket);
            exit(EXIT_FAILURE);
        }
        printf("SO_KEEPALIVE is set to ON\n");
    #if 0
        // check the status again
        if (getsockopt(client->client_socket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0)
        {
            perror("getsockopt()");
            close(client->client_socket);
            exit(EXIT_FAILURE);
        }
        printf("SO_KEEPALIVE is %s\n\n", (optval ? "ON" : "OFF"));

    #endif
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
    client_loop(client);
}

int main(int argc, char **argv)
{
    t_client *client;

    client = (t_client *)malloc(sizeof(t_client));
    client->port = ft_atoi(argv[2]);
    if (argc != 3)
        error("Usage: ./client <host machine> <port>\n");
    create_client_socket(client, argv[1]);
    close(client->client_socket);
    return (0);
}
