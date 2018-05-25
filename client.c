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
#if 0
void    open_read(int fd, char **store, t_client *client)
{

    int ret;
    char buff[2048];
    char *file;
    int i;
    

    i = 0;
    ret = 0;
    while (store[1][i] && store[1][i] != '\n')
                i++;
    file = ft_strnew(i);
    ft_strncpy(file, store[1], i);
    if ((fd = open(file, O_RDONLY)) <= 0)
        error("Couldn't open file.\n");
    while ((ret = read(fd, buff, 2048)) > 0)
        send(client->client_socket, buff, ret, 0);
    free(file);
}

void    store_file(char **store)
{
    int i;
    char *file;
    int fd;

    i = 0;
    fd = 0;
    while (store[1][i] && store[1][i] != '\n')
                i++;
    file = ft_strnew(i);
    ft_strncpy(file, store[1], i);
    if ((fd = open(file, O_RDONLY)) <= 0)
        error("Couldn't open file.\n");
    free(file);
}
#endif
void    make_file(char **store, int ret, char *buff)
{
    char *file;
    int fd;
    int i;
 
    i = 0;    
    fd = 0;
    while (store[1][i] && store[1][i] != '\n')
                i++;
    file = ft_strnew(i);
    ft_strncpy(file, store[1], i);
    fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
    write (fd, buff, ret);
    ft_putstr("SUCCESS\n");
    free(file);
}

void    save_file(int fd, char **store, t_client *client)
{
    fd = 0;
    int ret;
    char buff[2048];

    ret = 0;
    if ((ret = recv(client->client_socket, buff, sizeof(buff), 0)) <= 0)
    {
        printf("%d", client->ret_from_server);
        error("Couldn't receive a response from server.\n");
        return;
    }
    if (ft_strcmp(buff, "Couldn't open file.\n") != 0)
        make_file(store, ret, buff);
    else
        ft_putstr(buff);
    clear_buff(buff, 2048);
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
        store_file(store);
    if (line)
    {
        if (send(client->client_socket, line, ft_strlen(line), 0) <= 0)
            return;
    }
    if (ft_strcmp(store[0], "get") == 0)
        save_file(fd, store, client);
    if (ft_strcmp(store[0], "put") == 0)
        open_read(fd, store, client);
    if (ft_strcmp(store[0], "get") != 0)
        recv_from_server(client, buff);
    if (ft_strcmp(store[0], "get") != 0)
        buff[client->ret_from_server] = '\0';
    if (ft_strcmp("Cannot change from root directory.\n", buff) == 0)
        error("Cannot change from root directory.\n");
    if (ft_strcmp(store[0], "get") != 0)
        printf("%s\n", buff);
    clear_buff(buff, 2048);
    free(line);
    // ft_bzero(line, sizeof(line));
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
