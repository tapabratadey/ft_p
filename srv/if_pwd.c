#include "../server.h"

void if_pwd(int fd, t_server *server)
{
    server = NULL;
    close(0);
    close(1);
    close(2);
    dup2(fd, 1);
    dup2(fd, 2);

    execl("/bin/pwd", "pwd", 0);
}