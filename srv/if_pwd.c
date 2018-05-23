#include "../server.h"

void if_pwd(int fd)
{
    char *current_cwd;

    current_cwd = NULL;
    current_cwd = getcwd(current_cwd, MAXPATHLEN);
    send(fd, current_cwd, ft_strlen(current_cwd), 0);
}