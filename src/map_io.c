
#include <unistd.h>
#include <stdlib.h>
#include "map.h"
void    ft_putstr(char *str);

int read_file_into_buffer(int fd, char *buf)
{
    int read_bytes = read(fd, buf, g_buff_size - 1);
    if (read_bytes > 0)
        buf[read_bytes] = '\0';
    else
        buf[0] = '\0'; // Ensure the buffer is null-terminated even if read fails
    return read_bytes;
}

t_map *create_map(int num_lines)
{
    t_map *map = (t_map *)malloc(sizeof(t_map));
    if (!map) {
        ft_putstr("Failed to allocate memory for map");
        exit(1);
    }
    map->num_lines = num_lines;
    map->lines = (char **)malloc(num_lines * sizeof(char *));
    if (!map->lines) {
        ft_putstr("Failed to allocate memory for map lines");
        exit(1);
    }
    return map;
}

int read_map_from_buffer(t_map *map, char *buf, int line_length)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int prev_line_length = -1;

    // Skip the metadata line
    while (buf[i] != '\n' && buf[i] != '\0') {
        i++;
    }
    if (buf[i] == '\n') {
        i++; // Skip the newline character
    }

    // Copy the map data
    while (buf[i] != '\0') {
        if (buf[i] != map->empty_char && buf[i] != map->obstacle_char && buf[i] != '\n')
            return -1;
        if (buf[i] != '\n') 
        {
            map->lines[j][k] = buf[i];
            k++;
        } else 
        {
            if (prev_line_length != -1 && k != prev_line_length) 
                return -2;
            prev_line_length = k;
            k = 0;
            j++;
        }
        i++;
    }
    if (buf[i-1] != '\n')
        return -3;

    return 0; // No errors
}
