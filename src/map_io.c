/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:53:22 by sfarren           #+#    #+#             */
/*   Updated: 2024/02/13 14:20:34 by sfarren          ###   ########.fr       */
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

/**
 * Reads data from a file descriptor into a buffer.
 *
 * @param fd The file descriptor to read from.
 * @param buf The buffer to store the read data.
 * @return The number of bytes read, or -1 if an error occurred.
 */
int read_file_into_buffer(int fd, char *buf)
{
	int read_bytes;

	read_bytes = read(fd, buf, 1024 - 1);
	if (read_bytes > 0)
		buf[read_bytes] = '\0';
	// Ensure the buffer is null-terminated e/if read fails
	else
		buf[0] = '\0';
	return (read_bytes);
}

/**
 * Creates a new map with the specified number of lines.
 *
 * @param num_lines The number of lines in the map.
 * @return A pointer to the newly created map.
 */
t_map *create_map(int num_lines)
{
	t_map *map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
	{
		ft_putstr("Failed to allocate memory for map");
		exit(1);
	}
	map->num_lines = num_lines;
	map->lines = (char **)malloc(num_lines * 8);	//was usign sizeof(char *)...but unsure if i can!
	if (!map->lines)
	{
		ft_putstr("Failed to allocate memory for map lines");
		exit(1);
	}
	return (map);
}

/**
 * Reads the map data from a buffer and stores it in the given map structure.
 * 
 * @param map           The map structure to store the map data.
 * @param buf           The buffer containing the map data.
 * @param line_length   The length of each line in the map data.
 * @return              0 if no errors occurred, -1 if invalid characters are found,
 *                      -2 if the line lengths are inconsistent, -3 if the map data
 *                      does not end with a newline character.
 */
int	read_map_from_buffer(t_map *map, char *buf, int line_length)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int prev_line_length = -1;
	// Skip the settings line
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\n')
		i++; // Skip the newline character
	
	// Copy the map data
	/**
	 * iterates through the input buffer and performs the following tasks:
	 * - Checks if each character in the buffer is a valid empty character, obstacle character, or newline character.
	 * - Populates the lines of the map structure with the valid characters.
	 * - Checks if the length of each line is consistent with the previous line.
	 *
	 * @param buf The input buffer containing the map data.
	 * @param map The map structure to be populated.
	 * @return Returns -1 if an invalid character is found, -2 if the line lengths are inconsistent, or 0 if successful.
	 */
	while (buf[i] != '\0')
	{
		if (buf[i] != map->empty_char && buf[i] != map->obstacle_char && buf[i] != '\n')
			return (-1);
		// If the character is not a newline character, copy it to the map structure
		if (buf[i] != '\n') 
		{
			map->lines[j][k] = buf[i];
			k++;
		}
		else 
		{
			// If the length of the current line is inconsistent with the previous line, return an error
			if (prev_line_length != -1 && k != prev_line_length) 
				return (-2);
			prev_line_length = k;
			k = 0;
			j++;
		}
		i++;
	}
	// if (buf[i-1] != '\n')
	// 	return (-3);
	// Check if the last line was processed
    if (k != 0)
	{
        if (prev_line_length != -1 && k != prev_line_length)
            return -2;
    }
	return 0; // No errors
}

/**
 * @brief Processes a map file.
 * 
 * This function reads a map file, extracts the necessary information, and performs
 * operations on the map data to find the largest square. It also prints the map
 * and frees the allocated memory.
 * 
 * @param filename The path of the map file to be processed.
 */
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

	// allocate values to the relevant map structure variables
	num_lines = str_to_int(buf);
	map = create_map(num_lines);
	map->empty_char = buf[1];
	map->obstacle_char = buf[2];
	map->filled_char = buf[3];

	// Calculate the length of each line and allocate memory for the map lines
	map->line_length = calculate_line_length(buf);

	// Allocate memory for the map lines
	allocate_map_lines(map, map->line_length);

	// Read the map data from the buffer
	int error = read_map_from_buffer(map, buf, map->line_length);
	if (error != 0)
	{
		write(2, "map error\n", 10);
		return;
	}
	close(fd);

	// Find the largest square and print the map
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
