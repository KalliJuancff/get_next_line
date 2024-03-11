/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/11 18:03:32 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int	bytes_read;
	static char	*last_line;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE] = '\0';
	if (last_line != NULL)
		free(last_line);
	if (bytes_read == 0)
		return (NULL);
	last_line = ft_strdup(buffer);
	return (last_line);
}
