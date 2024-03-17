/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:06 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/17 11:16:11 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*remainder;

	remainder = NULL;
	if (buffer == NULL)
		buffer = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	while ((read (fd, buffer, BUFFER_SIZE)) == BUFFER_SIZE)
	{
	}
	if (*buffer == '\0')
		return (NULL);
	remainder = ft_strdup(buffer);
	free (buffer);
	buffer = NULL;
	return (remainder);
}
