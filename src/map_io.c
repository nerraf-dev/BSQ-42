/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:53:22 by sfarren           #+#    #+#             */
/*   Updated: 2024/02/13 13:27:37 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "map.h"

void	ft_putstr(char *str);
void	print_map(t_map *map);
int		calculate_line_length(char *buf);
void	find_largest_square(t_map *map);
int		str_to_int(char *str);
void	allocate_map_lines(t_map *map, int line_length);
// static const int	g_buff_size = 1024;

int	read_file_into_buffer(int fd, char *buf)
{
	int	read_bytes;

	read_bytes = (fd, buf, 1024 - 1);
	if (read_bytes > 0)
		buf[read_bytes] = '\0';
	// Ensure the buffer is null-terminated e/if read fails
	else
		buf[0] = '\0';
	return (read_bytes);
}

t_map	*create_map(int num_lines)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
	{
		ft_putstr("Failed to allocate memory for map");
		exit(1);
	}
	map->num_lines = num_lines;
	map->lines = (char **)malloc(num_lines * sizeof(char *));
	if (!map->lines)
	{
		ft_putstr("Failed to allocate memory for map lines");
		exit(1);
	}
	return (map);
}

int	read_map_from_buffer(t_map *map, char *buf, int line_length)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int prev_line_length = -1;
	// Skip the metadata line
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\n')
		i++; // Skip the newline character
	// Copy the map data
	while (buf[i] != '\0')
	{
		if (buf[i] != map->empty_char && buf[i] != map->obstacle_char && buf[i] != '\n')
			return (-1);
		if (buf[i] != '\n') 
		{
			map->lines[j][k] = buf[i];
			k++;
		} else 
		{
			if (prev_line_length != -1 && k != prev_line_length) 
				return (-2);
			prev_line_length = k;
			k = 0;
			j++;
		}
		i++;
	}
	if (buf[i-1] != '\n')
		return (-3);
	return 0; // No errors
}

void	process_map_file(char *filename)
{
	int		fd; // File descriptor
	char	buf[1024];
	int		num_lines;
	int		i;
	t_map	*map;

	fd = open(filename, 0);
	if (fd == -1)
	{
		write(2, "Failed to open file\n", 20);
		return;
	}
	if (read_file_into_buffer(fd, buf) <= 0)
	{
		write(2, "Failed to read file\n", 20);
		return;
	}
	num_lines = str_to_int(buf);
	map = create_map(num_lines);
	map->empty_char = buf[1];
	map->obstacle_char = buf[2];
	map->filled_char = buf[3];

	map->line_length = calculate_line_length(buf);
	allocate_map_lines(map, map->line_length);
	int error = read_map_from_buffer(map, buf, map->line_length);
	if (error != 0)
	{
		write(2, "map error\n", 10);
		return;
	}
	close(fd);
	find_largest_square(map);
	print_map(map);
	// Free the allocated memory
	i = 0;
	while (i < num_lines)
	{
		free(map->lines[i]);
		i++;
	}
	free(map->lines);
	free(map);
}
