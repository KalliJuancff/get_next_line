/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/15 17:12:31 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	ssize_t			bytes_read;

	if (buffer == NULL)
		buffer = ft_calloc(BUFFER_SIZE, sizeof(char));

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) == BUFFER_SIZE)
	{
	}

	if (bytes_read <= 0)
	{
		free (buffer);
		return (NULL);
	}

	return (buffer);
}
