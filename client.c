#include "client.h"

int error(char *str)
{
    ft_putstr(str);
    exit(0);
}

void    client_loop(t_client *client)
{
    int gnl;
    char *line;
    char buff[1024];

    gnl = 0;

    while (1)
    {
        ft_putstr("-> ");
        gnl = get_next_line(0, &line);
        if (gnl <= 0)
            error("Couldn't read\n");
        send(client->client_socket, line, ft_strlen(line), 0);
        if ((client->ret_from_server = recv(client->client_socket, buff, 1023, 0)) <= 0)
            error("Couldn't receive a response from server.\n");
        printf("Received response from server.\n");
        buff[client->client_socket] = '\0';
        printf("%s\n", buff);
        ft_memset((void**)buff, '\0', ft_strlen(buff));
        //     get_put(client, line);
        free(line);
    }
}

void    create_client_socket(t_client *client, char *hostname)
{
    // struct that deals with internet addresses
    struct sockaddr_in serv_addr;

    // create a socket
    client->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->client_socket < 0)
        error("Couldn't create a socket\n");
    printf("Client socket is created.\n");
    // fill the structure with null values
    // ft_memset((void**)&serv_addr, '\0', sizeof(serv_addr));
    // specify structure values
    serv_addr.sin_family = AF_INET; //refers to addresses from the internet
    serv_addr.sin_port = htons(client->port);
    // converts IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, hostname, &serv_addr.sin_addr) <= 0)
        error("Check your address.\n");
    // connect
    if ((client->client_connect = connect(client->client_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
        error("Couldn't Connect\n");
    printf("Connected to Server.\n");
    client_loop(client);
}

int main(int argc, char **argv)
{
    t_client *client;

    client = (t_client*)malloc(sizeof(t_client));
    client->port = ft_atoi(argv[2]);
    if (argc != 3)
        error("Usage: ./client <host machine> <port>\n");
    create_client_socket(client, argv[1]);
    close(client->client_socket);
    return (0);
}