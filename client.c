#include "client.h"

int error(char *str)
{
    ft_putstr(str);
    exit(0);
}

char *read_user(char *line)
{
    int read_ret;
    char buff[2];
    char *old_line;

    read_ret = 0;
    while ((read_ret = read(0, buff, 1)) > 0)
    {
        buff[1] = '\0';
        old_line = line;
        line = ft_strjoin(line, buff);
        free(old_line);
        if (buff[0] == '\n')
            break;
    }
    return (line);
}

void client_loop(t_client *client)
{
    char *line;
    int gnl;
    char buff[1024];

    line = NULL;
    gnl = 0;

    while (1)
    {
        // send(client->client_socket, "quit", ft_strlen("quit"), 0);
        // send(client->client_socket, "ayyy", ft_strlen("ayyy"), 0);
        // ft_putstr(line);
        // if (ft_strcmp(line, "quit"))
        //     error("Disconnected.\n");

        // start
        ft_putstr("-> ");
        // gnl = get_next_line(0, &line);
        // if (gnl <= 0)
        //     error("Couldn't read\n");
        //read
        line = read_user(line);
        ft_putstr(line);
        //send to that line(command) to server
        if (line)
            send(client->client_socket, line, ft_strlen(line), 0);
        //receive back what server parsed and sent to you
        if ((client->ret_from_server = recv(client->client_socket, buff, 1023, 0)) <= 0)
            error("Couldn't receive a response from server.\n");
        printf("Received response from server.\n");
        buff[client->ret_from_server] = '\0';
        //print it out
        // printf("%s\n", buff);
        memset(buff, '\0', ft_strlen(buff));
        free(line);
    }
}

void create_client_socket(t_client *client, char *hostname)
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
    if ((client->client_connect = connect(client->client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
        error("Couldn't Connect\n");
    printf("Connected to Server.\n");
    client_loop(client);
}

int main(int argc, char **argv)
{
    t_client *client;

    client = (t_client *)malloc(sizeof(t_client));
    client->port = ft_atoi(argv[2]);
    if (argc != 3)
        error("Usage: ./client <host machine> <port>\n");
    create_client_socket(client, argv[1]);
    close(client->client_socket);
    return (0);
}