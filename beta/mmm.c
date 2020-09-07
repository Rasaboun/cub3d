#include "test.h"


int main()
{
    int fd;

    char *line;
    fd = open("/home/user42/Bureau/cub3d/acacia_log.xpm",O_RDONLY);
    while(get_next_line(fd,&line))
    {
        free(line);
    }
    free(line);
    close(fd);
}