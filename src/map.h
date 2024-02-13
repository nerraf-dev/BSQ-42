// map.h

#ifndef MAP_H
#define MAP_H

static const int g_buff_size = 1024;

typedef struct s_map {
    int num_lines;
    char empty_char;
    char obstacle_char;
    char filled_char;
    char **lines;
    int line_length;
} t_map;

#endif