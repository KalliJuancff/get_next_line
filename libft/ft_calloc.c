/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:25 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/21 16:34:04 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*result;
	size_t			num_bytes;

	num_bytes = count * size;
	result = malloc(num_bytes);
	if (result == NULL)
		return (NULL);
	while (num_bytes > 0)
	{
		result[num_bytes - 1] = '\0';
		num_bytes--;
	}
	return (result);
}
