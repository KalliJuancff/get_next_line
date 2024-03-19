/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/19 18:01:07 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// TODO: si se mantiene el comportamiento de machacar la cadena apuntada por "read_buf", renombrar la función para que sea evidente
char	*merge_pending_and_read_buffer(char **pend_buf, char *read_buf)
{
	char	*result;

	result = ft_strjoin(*pend_buf, read_buf);
	if (result == NULL)
		return (NULL);
	free(*pend_buf);
	*pend_buf = result;
	*read_buf = '\0';
	return (result);
}

char	*extract_next_line_from_pending_buffer(char **pend_buf, int len_line)
{
	char	*result;
	int	len_new_pend_buf;
	char	*new_pend_buf;

	result = malloc((len_line + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, *pend_buf, len_line + 1);
	len_new_pend_buf = ft_strlen(*pend_buf) - len_line;
	new_pend_buf = malloc((len_new_pend_buf + 1) * sizeof(char));
	if (new_pend_buf == NULL)
		return (free(result), NULL);
	ft_strlcpy(new_pend_buf, *pend_buf + len_line, len_new_pend_buf + 1);
	free(*pend_buf);
	*pend_buf = new_pend_buf;
	return (result);
}

/*
char	*remove_line_from_pending_buffer(char **buf, char *line)
{
	char	*result;
	int	len_buf;
	int	len_line;
	int	long_new_buf;

	len_buf = ft_strlen(buf);
	len_line = ft_strlen(line);
	long_new_buf = len_buf - len_line + 1;
	result = malloc(long_new_buf * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, buf + len_line, long_new_buf);
	free(*buf);
	*buf = result;
	return (result);
}
*/

char	*get_next_line_from_fd(char **pend_buf, int fd)
{
	char	*read_buf;
	int	bytes_read;
	char	*intro_pos;

	read_buf = NULL;
	bytes_read = BUFFER_SIZE;
	while (bytes_read == BUFFER_SIZE)
	{
		intro_pos = ft_strchr(*pend_buf, '\n');
		if (intro_pos != NULL)
			return (extract_next_line_from_pending_buffer(pend_buf, intro_pos - *pend_buf + 1));
		else
		{
			if (read_buf == NULL)
			{
				read_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
				if (read_buf == NULL)
					return (NULL);
			}
			bytes_read = read(fd, read_buf, BUFFER_SIZE);
			read_buf[bytes_read] = '\0';
			if (bytes_read == -1)
				return (free(read_buf), NULL);
			if (bytes_read > 0)
			{
				if(!merge_pending_and_read_buffer(pend_buf, read_buf))
					return (free(read_buf), NULL);
			}
			if (bytes_read < BUFFER_SIZE)
				free(read_buf);
		}
	}
	if (**pend_buf == '\0')
		return (NULL);
	read_buf = ft_strjoin(*pend_buf, "");
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
		// TODO: sustituir 'ft_calloc' por 'malloc' cuando pasen todos mis tests y los de Paco (¿y 'bzero' o pend_buf[0] = '\0'?). NOTA: Pensarlo primero; nada de 'ensayo-error'
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
