/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/15 19:12:45 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	read_putting_null_char(int fildes, void *buf, size_t nbyte)
{
	char	*buf_char;
	ssize_t	result;

	buf_char = (char *) buf;
	result = read(fildes, buf, nbyte);
	if (result != -1)
	{
		buf_char[result] = '\0';
	}

	return (result);
}

char	*get_next_line(int fd)
{
	static char *buffer = NULL;
	ssize_t bytes_read;
	char *remainder;
	char *temp;

	if (buffer == NULL)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	// else
	//	ft_bzero(buffer, BUFFER_SIZE + 1);

	remainder = NULL;
	while ((bytes_read = read_putting_null_char(fd, buffer, BUFFER_SIZE)) == BUFFER_SIZE)
	{
		remainder = ft_strdup(buffer);
	}

	if (bytes_read <= 0)
		return (NULL);

	if (remainder != NULL)
	{
		temp = ft_strjoin(remainder, buffer);
		free(remainder);
		free(buffer);
		buffer = NULL;
		return(temp);
	}

	// Al ser buffer una variable estática, tenemos que "resetearla" o tendremos conflictos
	// entre llamadas (tests). Por eso no podemos devolver la variable 'buffer' directamente
	//     return (buffer);
	temp = ft_strdup(buffer);
	free(buffer);
	buffer = NULL;
	return (temp);
}
