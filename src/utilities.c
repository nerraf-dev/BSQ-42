/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:40:14 by sfarren           #+#    #+#             */
/*   Updated: 2024/02/13 13:36:17 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/**
 * Prints a string to the standard output followed by a newline character.
 *
 * @param str The string to be printed.
 */
void ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

/**
 * Calculates the length of a line in a buffer.
 *
 * @param buf The buffer containing the line.
 * @return The length of the line.
 */
int calculate_line_length(char *buf)
{
	int i;
	int length;

	i = 0;
	length = 0;
	// Skip the metadata line
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\n')
		i++; // Skip the newline character
	while (buf[i] != '\n' && buf[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}

/**
 * Converts a string to an integer.
 *
 * @param str The string to be converted.
 * @return The converted integer value.
 */
int str_to_int(char *str)
{
	int result;
	int i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return result;
}
