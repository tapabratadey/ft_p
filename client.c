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
    char **store;

    line = ft_strnew(1);
    // start
    ft_putstr("-> ");
    //read
    line = read_user(line);
    store = ft_strsplit(line, ' ');
    error_cases(client, store);
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
