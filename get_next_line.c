/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/12 16:21:40 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	static char	*last_line = NULL;
	int		salir;

	if (last_line != NULL)
	{
		free(last_line);
		last_line = NULL;
	}
	salir = 0;
	while (salir != 1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
		{
			if (last_line == NULL)
				return (NULL);
			else
				return (last_line);
		}
		if (last_line == NULL)
			last_line = ft_strdup(buffer);
		else
		{
			char *temp = ft_strjoin(last_line, buffer);
			free(last_line);
			last_line = temp;
		}
		if (bytes_read < BUFFER_SIZE)
			salir = 1;
	}
	return (last_line);
}
