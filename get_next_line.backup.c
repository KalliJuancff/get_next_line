/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/18 18:33:41 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concat_buffers(char **buf, char *buf2, int bytes)
{
	char	*result;

	buf2[bytes] = '\0';
	result = ft_strjoin(*buf, buf2);
	if (result == NULL)
		return (NULL);
	free(*buf);
	*buf = result;
	return (result);
}

char	*remove_from_buffer(char **buf, int count)
{
	char	*result;
	int		len;

	len = ft_strlen(*buf);
	result = ft_calloc(len - count + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, *buf + count, len - count + 1);
	free(*buf);
	*buf = result;
	return (result);
}

char	*get_next_line_from_buffer(char **buf, char *intro_pos)
{
	char	*next_line;
	int		len;

	if (intro_pos == NULL)
		len = ft_strlen(*buf);
	else
		len = intro_pos - *buf + 1;
	next_line = ft_calloc(len + 1, sizeof(char));
	if (next_line == NULL)
		return (NULL);
	ft_strlcpy(next_line, *buf, len + 1);
	if ((*buf)[len] == '\0')
	{
		free(*buf);
		*buf = NULL;
	}
	else
	{
		if (!remove_from_buffer(buf, len))
		{
			free(next_line);
			return (NULL);
		}
	}
	return (next_line);
}

char	*get_next_line_from_fd(char **buf, int fd)
{
	char	*read_buf;
	char	*next_line;
	int		bytes;

	next_line = ft_strchr(*buf, '\n');
	if (next_line == NULL)
	{
		read_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (read_buf == NULL)
			return (NULL);
		bytes = 1;
		while (bytes > 0 && next_line == NULL)
		{
			bytes = read(fd, read_buf, BUFFER_SIZE);
			if (bytes < 0 || (bytes && !concat_buffers(buf, read_buf, bytes)))
				return (free(read_buf), NULL);
			next_line = ft_strchr(*buf, '\n');
		}
		free(read_buf);
		if (bytes == 0 && **buf == '\0')
			return (NULL);
		return (get_next_line_from_buffer(buf, next_line));
	}
	else
		return (get_next_line_from_buffer(buf, next_line));
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer == NULL)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (buffer == NULL)
			return (NULL);
	}
	next_line = get_next_line_from_fd(&buffer, fd);
	if (next_line == NULL)
	{
		free(buffer);
		buffer = NULL;
	}
	return (next_line);
}
