#include <stdlib.h>
#include "map.h"

void    ft_putstr(char *str);

void allocate_map_lines(t_map *map, int line_length)
{
    int i = 0;
    while (i < map->num_lines) {
        map->lines[i] = (char *)malloc((line_length + 1) * sizeof(char));
        if (!map->lines[i]) {
            ft_putstr("Failed to allocate memory for map line");
            exit(1);
        }
        i++;
    }
}

void print_map(t_map *map)
{
    int i = 0;
    while (i < map->num_lines) {
        ft_putstr(map->lines[i]);
        i++;
    }
}
