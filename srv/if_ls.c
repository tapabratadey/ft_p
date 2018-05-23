#include "../server.h"

void if_ls(int fd)
{
    if (fork() == 0)
    {
        ft_putendl("In child");
        close(0);
        close(1);
        close(2);
        dup2(fd, 1);
        dup2(fd, 2);
    execl("/bin/ls", "ls", 0);
    exit(0);
    }

    wait(NULL);
}