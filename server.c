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

int error(char *str)
{
    ft_putstr(str);
    exit(0);
}

void    cd_dot_dot(int fd, t_server *server)
{
    // cd .. change dir
    char *to_client;

    to_client = "Cannot change from root directory.\n";
    if (ft_strcmp(server->pwd, "/nfs/2017/t/tadey/ft_p") == 0)
        send(fd, to_client, ft_strlen(to_client), 0);
    else
    {
        if (chdir("/nfs/2017/t/tadey/ft_p") == 0)
            send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
        else
            send(fd, "ERROR", ft_strlen("ERROR"), 0);
    }
}

void    cd_cd_slash(int fd, t_server *server)
{
    // cd bring back to root
    // cd / go to root
    if (ft_strcmp(server->pwd, "/nfs/2017/t/tadey/ft_p") == 0)
        send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
    else
    {
        if (chdir("/nfs/2017/t/tadey/ft_p") == 0)
            send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
        else
            send(fd, "ERROR", ft_strlen("ERROR"), 0);
    }
}
#if 0
void    cd_folder(int fd, t_server *server, char **store)
{
    // cd <folder> go into a folder 
    if (ft_strcmp(buff, "cd libft\n") == 0)
    {
        if (chdir("/nfs/2017/t/tadey/ft_p/libft") == 0)
        {
            getcwd(server->pwd, MAXPATHLEN);
            ft_putstr("Server CWD: ");
            ft_putendl(server->pwd);
            send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
        }
        else
            send(fd, "ERROR", ft_strlen("ERROR"), 0);
    }
}
#endif

void    parse_cd(int fd, t_server *server, char **store)
{
    if ((ft_strcmp(store[0], "cd\n") == 0) || (ft_strcmp(store[1], "/\n") == 0))
        cd_cd_slash(fd, server);
    else if (ft_strcmp(store[1], "..\n") == 0)
        cd_dot_dot(fd, server);
    // else if cd_folder(buff, fd, server, store);
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

void get_from_client(t_server *server, int fd)
{
    char buff[2048];
    char **store;

    // receive what the client sent you
    while((server->ret_recv = recv(fd, buff, sizeof(buff) - 1, 0)) <= 0);
    printf("Bytes received: %d\n", server->ret_recv);
    buff[server->ret_recv] = '\0';
    store = ft_strsplit(buff, ' ');
    // ft_putstr(store[0]);
    // ft_putchar('\n');
    // ft_putstr(store[1]);
    printf("Client command: %s\n", buff);

    // parse it -TODO-
    getcwd(server->pwd, MAXPATHLEN);
    if ((ft_strcmp(store[0], "cd") == 0) || (ft_strcmp(store[0], "cd\n") == 0))
        parse_cd(fd, server, store);
    else if (ft_strcmp("pwd\n", buff) == 0)
        if_pwd(fd);
    else if (ft_strcmp("ls\n", buff) == 0)
        if_ls(fd);
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
            while(in_client)
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
