#include "server.h"

int error(char *str)
{
    ft_putstr(str);
    exit(0);
}

// void    get_ls(t_server *server)
// {

// }

// void    if_ls(t_server *server, char *buff)
// {
//     if (ft_strcmp(buff, "ls") == 0)
//         get_ls(server);
// }

void    if_quit(char *buff)
{
    if (ft_strcmp(buff, "quit") == 0)
        error("Disconnected.\n");
}

void    get_from_client(t_server *server)
{
    char buff[1024];
    //server receives the msg
    while (1)
    {
        server->ret_recv = recv(server->server_accept, buff, 1023, 0);
        buff[server->ret_recv] = '\0';
        // if_ls(server, buff);
        if_quit(buff);
        printf("Clinet: %s\n", buff);
        send (server->server_accept, buff, ft_strlen(buff), 0);
        ft_bzero(buff, sizeof(buff));

    }
}

void    server_loop(t_server *server)
{
    struct sockaddr_in new_addr;
    socklen_t addr_size;
    // pid_t childpid;
    while (1)
    {
        listen(server->server_socket, 10);
        if ((server->server_accept = accept(server->server_socket, (struct sockaddr *)&new_addr, &addr_size)) < 0)
            error("Couldn't accept connection.\n");
        printf("Connection accepted.\n");//from %s:%d\n", inet_ntoa(new_addr.sin_addr), ntoa(new_addr.sin_port));
        ft_putstr("hello");
        // if ((childpid = fork()) == 0)
        //     close(server->server_socket);
        get_from_client(server);
    }
    close(server->server_socket);
}

void create_client_server(t_server *server)
{
    struct sockaddr_in serv_addr;
    if ((server->server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("Couldn't create a socket.\n");
    printf("Server socket is created.\n");
    // ft_memset((void**)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(server->port);
    if (bind(server->server_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
        error("Couldn't bind to port.\n");
    printf("Connected to port.\n");
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