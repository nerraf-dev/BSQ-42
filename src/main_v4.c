// #include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "map.h"

void    ft_putstr(char *str);
void    process_map_file(char *filename);

int read_file_into_buffer(int fd, char *buf);
t_map *create_map(int num_lines);
int read_map_from_buffer(t_map *map, char *buf, int line_length);

int main(int argc, char **argv)
{
    int i;
    int fd;

    if (argc < 2)
    {
        ft_putstr("File name missing.");
        return 1;
    }
    //process map files
    i = 1;
    while (i < argc)
    {
        process_map_file(argv[i]);
        i++;
    }
    return 0;
}