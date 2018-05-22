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

void get_cwd(t_server *server)
{
    char *path;

    path = (char *)malloc(sizeof(char *) * (MAXPATHLEN + 1));
    server->pwd = getcwd(path, MAXPATHLEN);
    if (server->pwd == NULL)
    {
        printf("getcwd error");
        exit (0);
    }
}


void    parse_cd(char *buff, int fd, t_server *server)
{
    // cd bring back to root
    // cd .. change dir
    // cd / go to root
    // cd <folder> go into a folder 
    char *to_client;

    to_client = "Cannot change from root directory.\n";
    if (ft_strcmp("cd ..\n", buff) == 0)
    {
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
    if ((ft_strcmp(buff, "cd\n") == 0) || (ft_strcmp(buff, "cd /\n") == 0))
    {
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
    if (ft_strcmp(buff, "cd libft\n") == 0)
    {
        if (chdir("/nfs/2017/t/tadey/ft_p/libft") == 0)
            send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
        else
            send(fd, "ERROR", ft_strlen("ERROR"), 0);
    }
    #if 0
    if (ft_strcmp(buff, "cd cli\n") == 0)
    {
        if (chdir("/nfs/2017/t/tadey/ft_p/cli") == 0)
            send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
        else
            send(fd, "ERROR", ft_strlen("ERROR"), 0);
    }
    #endif
    if (ft_strcmp(buff, "cd srv\n") == 0)
    {
        if (chdir("/nfs/2017/t/tadey/ft_p/libft/srv") == 0)
            send(fd, "SUCCESS", ft_strlen("SUCCESS"), 0);
        else
            send(fd, "ERROR", ft_strlen("ERROR"), 0);
    }
}

void get_from_client(t_server *server, int fd)
{
    char buff[1024];
    char *to_client;
    

    // second fork
    // the parent waits for the child to terminate
    // using waitpid
    if (fork() > 0)
    {
        int status;

        waitpid(-1, &status, 0);
        close(fd);
        printf("the child exited.\n");
        exit(EXIT_SUCCESS);
    }

    // SECOND CHILD

    //server receives the msg

    // receive what the client sent you
    server->ret_recv = recv(fd, buff, sizeof(buff) - 1, 0);
    printf("Bytes received: %d\n", server->ret_recv);
    buff[server->ret_recv] = '\0';
    printf("Client command: %s\n", buff);

    // parse it -TODO-
    get_cwd(server);
    parse_cd(buff, fd, server);
    if (ft_strcmp("pwd\n", buff) == 0)
        if_pwd(fd, server);
    else if (ft_strcmp("ls\n", buff) == 0)
        if_ls(fd);
    

    //send back to client what you parsed
    // send(server->server_accept, to_client, ft_strlen(to_client), 0);

    //empty the buffer out
    ft_bzero(buff, sizeof(buff));
    ft_bzero(buff, sizeof(to_client));
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
        // FORK RUNS IN A LOOP (parent) (child gets created)
        if (fork() == 0)
            get_from_client(server, cli_fd);
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
