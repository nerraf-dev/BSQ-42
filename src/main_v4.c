/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_v4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:35:14 by sfarren           #+#    #+#             */
/*   Updated: 2024/02/13 13:35:29 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "map.h"

void	ft_putstr(char *str);
void	process_map_file(char *filename);
int		read_file_into_buffer(int fd, char *buf);
t_map	*create_map(int num_lines);
int		read_map_from_buffer(t_map *map, char *buf, int line_length);

/**
 * @brief The main function of the program.
 * 
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char **argv)
{
	int i;
	int fd;

	if (argc < 2)
	{
		ft_putstr("File name missing.");
		return (1);
	}

	// Process map files
	i = 1;
	while (i < argc)
	{
		process_map_file(argv[i]);
		i++;
	}

	return 0;
}
