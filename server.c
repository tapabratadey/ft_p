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
#include <string.h>
#include <errno.h>

int error(char *str)
{
    ft_putstr(str);
    exit(0);
}

// void    if_get(t_server *server, char *buff)
// {
//     server = NULL;
//     if (ft_strcmp(buff, "get\n") == 0)
//         ft_putstr("hey");
// }

// void    if_cd(t_server *server, char *buff)
// {
//     server = NULL;
//     if (ft_strcmp(buff, "cd\n") == 0)
//         ft_putstr("hey");
// }

void if_pwd(int fd, t_server *server)
{
    server = NULL;
    close(0);
    close(1);
    close(2);
    dup2(fd, 1);
    dup2(fd, 2);

    execl("/bin/pwd", "pwd", 0);
#if 0
    char *path;
    (void)fd;
    path = (char *)malloc(sizeof(char *) * (MAXPATHLEN + 1));
    server->pwd = getcwd(path, MAXPATHLEN);
    if (server->pwd == NULL)
    {
        printf("getcwd error");
        exit(0);
    }
#endif
    // return (1);
}

void if_ls(int fd)
{
    close(0);
    close(1);
    close(2);
    dup2(fd, 1);
    dup2(fd, 2);

    execl("/bin/ls", "ls", 0);

    // return (0);
}

void get_from_client(t_server *server, int fd)
{
    char buff[1024];
    char *to_client;

    //server receives the msg
    while (1)
    {
        // receive what the client sent you
        server->ret_recv = recv(fd, buff, sizeof(buff) - 1, 0);
        printf("Bytes received: %d\n", server->ret_recv);
        buff[server->ret_recv] = '\0';
        printf("Client command: %s\n", buff);

        // parse it -TODO-
        if (ft_strcmp("pwd\n", buff) == 0)
            if_pwd(fd, server);
        #if 0
        {
            if (if_pwd(fd, server) == 1)
                to_client = ft_strdup(server->pwd);
        }
        #endif
        else if (ft_strcmp("ls\n", buff) == 0)
            if_ls(fd);
        #if 0
        {
            if (if_ls(fd) == 1)
                to_client = ft_strdup(server->read_buff);
        }
        #endif
        // if_cd(server, buff);
        // if_get(server, buff);
        // if_put(server, buff);

        //print it out to test

        //send back to client what you parsed
        // send(server->server_accept, to_client, ft_strlen(to_client), 0);

        //empty the buffer out
        ft_bzero(buff, sizeof(buff));
        ft_bzero(buff, sizeof(to_client));
        // free(to_client);
    }
}

void server_loop(t_server *server)
{
    int cli_fd;
    struct sockaddr_in cli_addr;
    socklen_t addr_len;

    listen(server->server_socket, 10);
    addr_len = sizeof(cli_addr);
    while (1)
    {
        if ((cli_fd = accept(server->server_socket, (struct sockaddr *)&cli_addr, &addr_len)) < 0)
            error("Couldn't accept connection.\n");
        printf("Connection accepted.\n\n");
        if (fork() == 0)
            get_from_client(server, cli_fd);
    }
}

void create_client_server(t_server *server)
{
    struct sockaddr_in serv_addr;
    if ((server->server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("Couldn't create a socket.\n");
    printf("Server socket is created...\n");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(server->port);
    if (bind(server->server_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        printf("%s", strerror(errno));
        error("Couldn't bind to port.\n");
    }
    printf("Connected to port...\n");
    server_loop(server);
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
