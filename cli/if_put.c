#include "../client.h"

void    open_read(int fd, char **store, t_client *client)
{

    int ret;
    char buff[2048];
    char *file;
    int i;
    

    i = 0;
    ret = 0;
    while (store[1][i] && store[1][i] != '\n')
                i++;
    file = ft_strnew(i);
    ft_strncpy(file, store[1], i);
    if ((fd = open(file, O_RDONLY)) <= 0)
        error("Couldn't open file.\n");
    while ((ret = read(fd, buff, 2048)) > 0)
        send(client->client_socket, buff, ret, 0);
    free(file);
}

void    store_file(char **store)
{
    int i;
    char *file;
    int fd;

    i = 0;
    fd = 0;
    while (store[1][i] && store[1][i] != '\n')
                i++;
    file = ft_strnew(i);
    ft_strncpy(file, store[1], i);
    if ((fd = open(file, O_RDONLY)) <= 0)
        error("Couldn't open file.\n");
    free(file);
}