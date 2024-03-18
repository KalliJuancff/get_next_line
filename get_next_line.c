/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/18 10:35:22 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_buffer_to_remainder(char **rem, char *buf)
{
	char	*temp;

	if (ft_strlen(buf) == 0)
		return ;
	if (*rem == NULL)
		*rem = ft_strdup(buf);
	else
	{
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
	result = malloc((len_prefix + count + 1) * sizeof(char));
	ft_strlcpy(result, prefix, len_prefix + 1);
	ft_strlcpy(result + len_prefix, str, count + 1);
	return (result);
}

char	*create_line_with_remainder_and_buffer(char **buf, char **rem)
{
	char	*line;
	char	*temp;

	line = create_substr(*buf, get_intro_pos(*buf) + 1, *rem);
	free(*rem);
	temp = *buf;
	if (temp[get_intro_pos(*buf) + 1] == '\0')
		free_and_reset_buffer(buf);
	else
	{
		*rem = ft_strdup(*buf + get_intro_pos(*buf) + 1);
		free_and_reset_buffer(buf);
		*buf = *rem;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*remainder;
	int			end_of_file;
	ssize_t		bytes_read;

	remainder = NULL;
	if (buffer != NULL)
	{
		remainder = ft_strdup(buffer);
		free_and_reset_buffer(&buffer);
	}
	buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	end_of_file = 0;
	while (end_of_file == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		if (bytes_read < BUFFER_SIZE)
			end_of_file = 1;
		if (get_intro_pos(buffer) >= 0)
			return (create_line_with_remainder_and_buffer(&buffer, &remainder));
		else
			add_buffer_to_remainder(&remainder, buffer);
	}
	if (*buffer == '\0' && remainder == NULL)
	{
		free_and_reset_buffer(&buffer);
		return (NULL);
	}
	free_and_reset_buffer(&buffer);
	return (remainder);
}
