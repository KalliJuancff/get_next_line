/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/20 13:33:04 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*merge_pending_and_read_buffer(char **pend_buf, char *read_buf)
{
	char	*result;

	result = ft_strjoin(*pend_buf, read_buf);
	if (result == NULL)
		return (NULL);
	free(*pend_buf);
	*pend_buf = result;
	return (result);
}

char	*extract_line(char **pend_buf, int len_line)
{
	char	*result;
	int		len_new_pend_buf;
	char	*new_pend_buf;

	result = ft_calloc(len_line + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, *pend_buf, len_line + 1);
	len_new_pend_buf = ft_strlen(*pend_buf) - len_line;
	new_pend_buf = ft_calloc(len_new_pend_buf + 1, sizeof(char));
	if (new_pend_buf == NULL)
		return (free(result), NULL);
	ft_strlcpy(new_pend_buf, *pend_buf + len_line, len_new_pend_buf + 1);
	free(*pend_buf);
	*pend_buf = new_pend_buf;
	return (result);
}

char	*fill_read_buffer_from_fd(int fd, char **read_buf, int *bytes_read)
{
	if (*read_buf == NULL)
	{
		*read_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (*read_buf == NULL)
			return (NULL);
	}
	*bytes_read = read(fd, *read_buf, BUFFER_SIZE);
	if (*bytes_read == -1)
		return (NULL);
	(*read_buf)[*bytes_read] = '\0';
	return (*read_buf);
}

char	*get_next_line_from_fd(char **pend_buf, int fd)
{
	char	*read_buf;
	int		bytes_rd;
	int		finish;
	char	*p;

	read_buf = NULL;
	finish = 0;
	while (finish == 0)
	{
		p = ft_strchr(*pend_buf, '\n');
		if (p != NULL)
			return (free(read_buf), extract_line(pend_buf, p - *pend_buf + 1));
		else
		{
			if (!fill_read_buffer_from_fd(fd, &read_buf, &bytes_rd))
				return (free(read_buf), NULL);
			if (bytes_rd > 0)
			{
				if (!merge_pending_and_read_buffer(pend_buf, read_buf))
					return (free(read_buf), NULL);
			}
		}
		finish = (bytes_rd < BUFFER_SIZE && ft_strchr(*pend_buf, '\n') == NULL);
	}
	free(read_buf);
	if (**pend_buf == '\0')
		return (NULL);
	read_buf = extract_line(pend_buf, ft_strlen(*pend_buf));
	free(*pend_buf);
	*pend_buf = NULL;
	return (read_buf);
}

char	*get_next_line(int fd)
{
	static char	*pend_buf = NULL;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (pend_buf == NULL)
	{
		pend_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (pend_buf == NULL)
			return (NULL);
	}
	next_line = get_next_line_from_fd(&pend_buf, fd);
	if (next_line == NULL)
	{
		free(pend_buf);
		pend_buf = NULL;
	}
	return (next_line);
}
