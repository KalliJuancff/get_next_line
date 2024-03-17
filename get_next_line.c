/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/17 14:05:42 by jfidalgo         ###   ########.fr       */
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

int	get_intro_pos(char *buf)
{
	char	*result;

	result = ft_strchr(buf, '\n');
	if (result == NULL)
		return (-1);
	return (result - buf);
}

char	*create_substr(char *str, int count, char *prefix)
{
	char	*result;
	size_t	len_prefix;

	if (prefix == NULL)
		prefix = "";
	len_prefix = ft_strlen(prefix);
	result = ft_calloc(len_prefix + count + 1, sizeof(char));
	ft_strlcpy(result, prefix, len_prefix + 1);
	ft_strlcpy(result + len_prefix, str, count + 1);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*remainder;
	char		*line;
	int			end_of_file;
	ssize_t		bytes_read;

	remainder = NULL;
	if (buffer != NULL)
	{
		remainder = ft_strdup(buffer);
		free_and_reset_buffer(&buffer);
	}
	buffer = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	end_of_file = 0;
	while (end_of_file == 0)
	{
		if (end_of_file == 0)
		{
			bytes_read = read (fd, buffer, BUFFER_SIZE);
			buffer[bytes_read] = '\0';
		}
		if (get_intro_pos(buffer) >= 0)
		{
			line = create_substr(buffer, get_intro_pos(buffer) + 1, remainder);
			free (remainder);
			buffer += get_intro_pos(buffer) + 1;
			return (line);
		}
		else
			add_buffer_to_remainder(&remainder, buffer);
		if (bytes_read < BUFFER_SIZE)
			end_of_file = 1;
	}
	if (*buffer == '\0' && remainder == NULL)
	{
		free_and_reset_buffer(&buffer);
		return (NULL);
	}
	free_and_reset_buffer(&buffer);
	return (remainder);
}
