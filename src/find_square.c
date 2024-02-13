#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "map.h"

void find_largest_square(t_map *map) {
    int **solution;
    int max_x;
    int max_y;
    int maxSquareSize;
    int x;
    int y;

    max_x = 0;
    max_y = 0;
    maxSquareSize = 0;
    x = 0;
    y = 0;

    // Allocate memory for the auxiliary array
    solution = (int **)malloc(map->num_lines * sizeof(int *));
    while (x < map->num_lines) {
        solution[x] = (int *)malloc(map->line_length * sizeof(int));
        x++;
    }

    // Initialize the auxiliary array and find the largest square
    x = 0;
    while (x < map->num_lines) {
        y = 0;
        while (y < map->line_length) {
            if (x == 0 || y == 0 || map->lines[x][y] == map->obstacle_char)
                solution[x][y] = (map->lines[x][y] == map->obstacle_char) ? 0 : 1;
            else {
                int min_val = solution[x-1][y-1];
                if (solution[x][y-1] < min_val)
                    min_val = solution[x][y-1];
                if (solution[x-1][y] < min_val)
                    min_val = solution[x-1][y];
                solution[x][y] = min_val + 1;
            }

            if (solution[x][y] > maxSquareSize) {
                maxSquareSize = solution[x][y];
                max_x = x;
                max_y = y;
            }
            y++;
        }
        x++;
    }

    // Draw the largest square on the map
    x = max_x - maxSquareSize + 1;
    while (x <= max_x) {
        y = max_y - maxSquareSize + 1;
        while (y <= max_y) {
            map->lines[x][y] = map->filled_char;
            y++;
        }
        x++;
    }

    // Free the auxiliary array
    x = 0;
    while (x < map->num_lines) {
        free(solution[x]);
        x++;
    }
    free(solution);
}
