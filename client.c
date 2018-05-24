/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:30:04 by tadey             #+#    #+#             */
/*   Updated: 2018/05/23 14:01:51 by tadey            ###   ########.fr       */
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

void    open_read(int fd, char **store, t_client *client)
{
    int ret;
    char buff[2];
    char *new_line;
    char *file;
    char *old_line;
    int i;

    i = 0;
    ret = 0;
    new_line = ft_strnew(1);
    while (store[1][i] && store[1][i] != '\n')
                i++;
    file = ft_strnew(i);
    ft_strncpy(file, store[1], i);
    if ((fd = open(file, O_RDONLY)) < 0)
        error("Couldn't open file.\n");
    while ((ret = read(fd, buff, 1)) > 0)
    {
        buff[1] = '\0';
        old_line = new_line;
        new_line = ft_strjoin(new_line, buff);
        free(old_line);
    }
    send(client->client_socket, new_line, ft_strlen(new_line), 0);
}

void client_call(t_client *client)
{
    char *line;
    char buff[2048];
    int fd;
    char **store;

    fd = 0;
    line = ft_strnew(1);
    ft_putstr("-> ");
    line = read_user(line);
    if_quit(client, line);
    store = ft_strsplit(line, ' ');
    if (ft_strcmp(store[0], "put") == 0)
        open_read(fd, store, client);
    if (line) //&& ft_strncmp(store[0], "put", 3) != 0)
    {
        if (send(client->client_socket, line, ft_strlen(line), 0) <= 0)
            return;
    }
    recv_from_server(client, buff);
    buff[client->ret_from_server] = '\0';
    if (ft_strcmp("Cannot change from root directory.\n", buff) == 0)
        error("Cannot change from root directory.\n");
    printf("%s\n", buff);
    clear_buff(buff, 2048);
    ft_bzero(line, sizeof(line));
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
