/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:46:14 by sfarren           #+#    #+#             */
/*   Updated: 2024/02/13 14:10:16 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @struct t_map
 * @brief Represents a map with its properties and contents.
 * 
 * The t_map struct contains information about the map, such as the number of lines,
 * the characters used to represent empty spaces, obstacles, and filled spaces,
 * and a 2D array of characters representing the map's contents.
 * It also includes the length of each line in the map.
 */
typedef struct s_map
{
	int		num_lines;
	char	empty_char;
	char	obstacle_char;
	char	filled_char;
	char	**lines;		// 2D array of characters
	int		line_length;
}	t_map;
