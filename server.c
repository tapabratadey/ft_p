/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadey <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:30:27 by tadey             #+#    #+#             */
/*   Updated: 2018/05/16 15:30:32 by tadey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void    if_put(int fd, char **store)
{
    int ret;
    char buff[2048];
    char *file;
    int fd_open;
    int i;

    i = 0;
    fd_open = 0;
    ret = 0;
    while (store[1][i] && store[1][i] != '\n')
                i++;
    file = ft_strnew(i);
    ft_strncpy(file, store[1], i);
    fd_open = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
    while ((ret = recv(fd, buff, sizeof(buff), 0)) > 0)
    {
        write (fd_open, buff, ret);
            break;
    }
    send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
}

void    if_get(int fd, char **store)
{
    int ret;
    char buff[2048];
    char *file;
    int i;
    int fd_open;

    fd_open = 0;
    i = 0;
    ret = 0;
    while (store[1][i] && store[1][i] != '\n')
                i++;
    file = ft_strnew(i);
    ft_strncpy(file, store[1], i);
    if ((fd_open = open(file, O_RDONLY)) <= 0)
        send(fd, "Couldn't open file.\n", ft_strlen("Couldn't open file.\n"), 0);
    while ((ret = read(fd_open, buff, 2048)) > 0)
        send(fd, buff, ret, 0);
}

void get_from_client(t_server *server, int fd)
{
    char buff[2048];
    char **store;
    int i;

    i = 0;
    // ft_putstr("COMMMMM");
    // receive what the client sent you
    while ((server->ret_recv = recv(fd, buff, sizeof(buff) - 1, 0)) <= 0)
        ;
    // ft_putstr("ONNNN");
    printf("Bytes received: %d\n", server->ret_recv);
    buff[server->ret_recv] = '\0';
    store = ft_strsplit(buff, ' ');
    while (store[i])
    {
        if (i >= 2)
            send(fd, "Max 2 params.", ft_strlen("Max 2 params."), 0);
        i++;
    }
    printf("Client command: %s\n", buff);
    if ((ft_strcmp(store[0], "put") == 0) && store[1] != NULL)
        if_put(fd, store);
    else if ((ft_strcmp(store[0], "get") == 0) && store[1] != NULL)
        if_get(fd, store);
    else
        error_cases(store, fd);
    // parse it -TODO-
    getcwd(server->pwd, MAXPATHLEN);
    
    if ((ft_strcmp(store[0], "cd") == 0) || (ft_strcmp(store[0], "cd\n") == 0))
        parse_cd(fd, server, store);
    else if (ft_strcmp("pwd\n", buff) == 0)
        if_pwd(fd);
    else if (ft_strcmp("ls\n", buff) == 0)
        if_ls(fd);
    // else if (ft_strcmp(store[0], "get") == 0)
    //     if_get(fd);
    ft_putstr("Done with child.\n");

    //empty the buffer out
    clear_buff(buff, 2048);
}

void server_loop(t_server *server)
{
    int cli_fd;
    struct sockaddr_in cli_addr;
    socklen_t addr_len;
    int in_client;

    listen(server->server_socket, 10);
    in_client = 1;
    addr_len = sizeof(cli_addr);
    while (1)
    {
        if ((cli_fd = accept(server->server_socket, (struct sockaddr *)&cli_addr, &addr_len)) < 0)
            error("Couldn't accept connection.\n");
        printf("Connection accepted.\n\n");

        // FORK
        // run in a loop to recv from client
        if (fork() == 0)
        {
            ft_putendl("Forking for client");
            while (in_client)
                get_from_client(server, cli_fd);
        }
    }
}

int main(int argc, char **argv)
{
    t_server *server;

    server = (t_server *)malloc(sizeof(t_server));
    if (argc != 2)
        error("Usage: ./server <port>\n");
    server->port = ft_atoi(argv[1]);
    create_client_server(server);
    close(server->server_socket);
    return (0);
}
