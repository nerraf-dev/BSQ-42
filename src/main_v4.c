#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "map.h"

void    ft_putstr(char *str);
void    find_largest_square(t_map *map);
void    allocate_map_lines(t_map *map, int line_length);
void    print_map(t_map *map);
int     calculate_line_length(char *buf);
int     str_to_int(char *str);
void    process_map_file(char *filename);

int read_file_into_buffer(int fd, char *buf);
t_map *create_map(int num_lines);
int read_map_from_buffer(t_map *map, char *buf, int line_length);


// void find_largest_square(t_map *map);

// void find_largest_square(t_map *map) {
//     int **solution;
//     int max_x;
//     int max_y;
//     int maxSquareSize;
//     int x;
//     int y;

//     max_x = 0;
//     max_y = 0;
//     maxSquareSize = 0;
//     x = 0;
//     y = 0;

//     // Allocate memory for the solution array
//     solution = (int **)malloc(map->num_lines * sizeof(int *));
//     while (x < map->num_lines) {
//         solution[x] = (int *)malloc(map->line_length * sizeof(int));
//         x++;
//     }
//     // Initialize the solution array and find the largest square
//     x = 0;
//     while (x < map->num_lines) {
//         y = 0;
//         while (y < map->line_length) {
//             if (x == 0 || y == 0 || map->lines[x][y] == map->obstacle_char)
//                 solution[x][y] = (map->lines[x][y] == map->obstacle_char) ? 0 : 1;
//             else {
//                 int min_val = solution[x-1][y-1];
//                 if (solution[x][y-1] < min_val)
//                     min_val = solution[x][y-1];
//                 if (solution[x-1][y] < min_val)
//                     min_val = solution[x-1][y];
//                 solution[x][y] = min_val + 1;
//             }
//             if (solution[x][y] > maxSquareSize) {
//                 maxSquareSize = solution[x][y];
//                 max_x = x;
//                 max_y = y;
//             }
//             y++;
//         }
//         x++;
//     }
//     // Draw the largest square on the map
//     x = max_x - maxSquareSize + 1;
//     while (x <= max_x) {
//         y = max_y - maxSquareSize + 1;
//         while (y <= max_y) {
//             map->lines[x][y] = map->filled_char;
//             y++;
//         }
//         x++;
//     }
//     // Free the solution array
//     x = 0;
//     while (x < map->num_lines) {
//         free(solution[x]);
//         x++;
//     }
//     free(solution);
// }

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