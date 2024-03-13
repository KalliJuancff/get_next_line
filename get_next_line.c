/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/13 17:23:27 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	int			bytes_read;
	char		*pending;
	char		*temp;

	pending = NULL;
	if (buffer == NULL)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (buffer == NULL)
			return (NULL);
	}
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		if (bytes_read == -1)
		{
			if (pending != NULL)
				free(pending);
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
		{
			if (pending == NULL)
				return (NULL);
			else
			{
				return (pending);
			}
		}
		if (bytes_read < BUFFER_SIZE)
			if (pending == NULL)
				return (ft_strdup(buffer));
			else
			{
				temp = ft_strjoin(pending, buffer);
				free(pending);
				pending = temp;
			}
		else
			if (pending == NULL)
				pending = ft_strdup(buffer);
			else
			{
				temp = ft_strjoin(pending, buffer);
				free(pending);
				pending = temp;
			}
	}
}
