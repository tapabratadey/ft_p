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

// void    if_get(fd)
// {
// }

#if 0
client sends file-server recvs file (put)
client asks for file-server sends file (get)
#endif

#if 0
void    if_put(int fd, char **store)
{
    int fd;
    int ret;
    char buff[2];

    fd = 0;
    ret = 0;
    file = store[1];
    fd = open(file, O_RDONLY);
    while ((ret = read(fd, buff, 1) > 0)
    {
        buff[1] = '\0';
        old_line = line;
        line = ft_strjoin(line, buff);
        free(old_line);
    }
    send(fd, )
    
}
#endif




void get_from_client(t_server *server, int fd)
{
    char buff[2048];
    char **store;
    char *file;

    // receive what the client sent you
    while ((server->ret_recv = recv(fd, buff, sizeof(buff) - 1, 0)) <= 0)
        ;
    printf("Bytes received: %d\n", server->ret_recv);
    buff[server->ret_recv] = '\0';
    store = ft_strsplit(buff, ' ');
    file = ft_strdup(store[1]);
    // write (fd, &file, ft_strlen(file));
    printf("Client command: %s\n", buff);
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
    // else if (ft_strcmp(store[0], "put") == 0)
    //     if_put(fd, store);
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
