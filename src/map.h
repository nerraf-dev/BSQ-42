/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:46:14 by sfarren           #+#    #+#             */
/*   Updated: 2024/02/13 10:51:19 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_map
{
	int		num_lines;
	char	empty_char;
	char	obstacle_char;
	char	filled_char;
	char	**lines;
	int		line_length;
}	t_map;
