#include <stdlib.h>
#include "map.h"

void    ft_putstr(char *str);

/**
 * @brief Allocates memory for each line in the map.
 * 
 * This function dynamically allocates memory for each line in the map structure.
 * It takes the map structure and the length of each line as parameters.
 * The memory allocation is done using the malloc function.
 * If the memory allocation fails, an error message is displayed and the program exits.
 * 
 * @param map The map structure.
 * @param line_length The length of each line in the map.
 */
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

/**
 * Prints the contents of a map.
 *
 * @param map The map to be printed.
 */
void print_map(t_map *map)
{
    int i = 0;
    while (i < map->num_lines) {
        ft_putstr(map->lines[i]);
        i++;
    }
}
