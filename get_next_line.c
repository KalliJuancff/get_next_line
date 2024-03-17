/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/17 12:26:55 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_buffer_to_remainder(char **rem, char *buf)
{
	char	*temp;

	if (*rem == NULL && ft_strlen(buf) > 0)
		*rem = ft_strdup(buf);
	else
	{
		if (ft_strlen(buf) == 0)
			return ;
		temp = ft_strjoin(*rem, buf);
		free (*rem);
		*rem = temp;
	}
}

void	free_and_reset_buffer(char **buf)
{
	free(*buf);
	*buf = NULL;
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*remainder;
	int			end_of_file;
	ssize_t		bytes_read;

	remainder = NULL;
	buffer = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	end_of_file = 0;
	while (end_of_file == 0)
	{
		if (end_of_file == 0)
		{
			bytes_read = read (fd, buffer, BUFFER_SIZE);
			buffer[bytes_read] = '\0';
		}
		add_buffer_to_remainder(&remainder, buffer);
		if (bytes_read < BUFFER_SIZE)
			end_of_file = 1;
	}
	if (*buffer == 0 && remainder == NULL)
	{
		free_and_reset_buffer(&buffer);
		return (NULL);
	}
	free_and_reset_buffer(&buffer);
	return (remainder);
}
