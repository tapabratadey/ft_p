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

// void    get_ls(t_server *server)
// {

// }

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

int    if_ls(t_server *server, char *buff)
{
    // parent
    if (fork() != 0)
        close(server->server_accept);
    else
    {
        close(server->server_socket);
        // Map stdin, stdout and stderr to the data connection
            // dup2(server->server_accept, 0);
            // dup2(server->server_accept, 1);
            // dup2(server->server_accept, 2);

            //Call external program
            execl("/bin/ls", "/bin/ls", 0);
    }
    return (1);
}

int if_pwd(t_server *server, char *buff)
{
    char *path;

    path = (char *)malloc(sizeof(char *) * (MAXPATHLEN + 1));
    server->pwd = getcwd(path, MAXPATHLEN);
    if (server->pwd == NULL)
    {
        printf("getcwd error");
        exit (0);
    }
    return (1);
}

void    get_from_client(t_server *server)
{
    char buff[1024];
    char *to_client;

    // pwd = ft_strnew(MAXPATHLEN);
    //server receives the msg
    while (1)
    {
        // receive what the client sent you
        server->ret_recv = recv(server->server_accept, buff, 1023, 0);
        printf("Bytes received: %d\n", server->ret_recv);
        buff[server->ret_recv] = '\0';
        printf("Client command: %s\n", buff);
        
        // parse it -TODO-
        if (ft_strcmp("pwd\n", buff) == 0)
        {
            if (if_pwd(server, buff) == 1)
                to_client = ft_strdup(server->pwd);
        }
        else
            if (if_ls(server, buff) == 1)
                to_client = ft_strdup(server->if_ls);
            
        // if_cd(server, buff);
        // if_get(server, buff);
        // if_put(server, buff);

        //print it out to test
        printf("to_client: %s\n", to_client);
        
        //send back to client what you parsed 
        send (server->server_accept, to_client, ft_strlen(to_client), 0);
        
        //empty the buffer out
        ft_bzero(buff, sizeof(buff));
        // ft_bzero(buff, sizeof(to_client));
        free(to_client);
    }
}

void    server_loop(t_server *server)
{
    struct sockaddr_in new_addr;
    socklen_t addr_size;
    while (1)
    {
        listen(server->server_socket, 10);
        if ((server->server_accept = accept(server->server_socket, (struct sockaddr *)&new_addr, &addr_size)) < 0)
            error("Couldn't accept connection.\n");
        printf("Connection accepted.\n\n");
        get_from_client(server);
    }
    close(server->server_socket);
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
