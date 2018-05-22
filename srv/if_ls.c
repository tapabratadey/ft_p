#include "../server.h"

void if_ls(int fd)
{
    close(0);
    close(1);
    close(2);
    dup2(fd, 1);
    dup2(fd, 2);

    execl("/bin/ls", "ls", 0);
}