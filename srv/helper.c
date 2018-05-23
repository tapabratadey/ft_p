#include "../server.h"

int error(char *str)
{
    ft_putstr(str);
    exit(0);
}

void clear_buff(char *buf, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        buf[i] = '\0';
        i++;
    }
}