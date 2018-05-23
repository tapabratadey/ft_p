#include "../client.h"

int error(char *str)
{
    ft_putstr(str);
    exit(0);
}

void error_cases(t_client *client, char **store)
{
    if (ft_strcmp(store[0], "quit\n") == 0)
    {
        close(client->client_socket);
        error("Disconnected.\n");
    }
    else if ((ft_strcmp(store[0], "ls\n") != 0) &&
    (ft_strcmp(store[0], "pwd\n") != 0) && (ft_strncmp(store[0], "cd", 2) != 0)
    && (ft_strncmp(store[0], "get", 3) != 0) && (ft_strncmp(store[0], "put", 3) != 0))
    {
        close(client->client_socket);
        error("Wrong command.\n");
    }
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
