/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfidalgo <jfidalgo@student.42bar(...).com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:10:25 by jfidalgo          #+#    #+#             */
/*   Updated: 2024/03/13 20:35:01 by jfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char) c;
	while (*s != ch)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *) s);
}

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *) s;
	while (n > 0)
	{
		*p = 0;
		p++;
		n--;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*result;
	size_t			num_bytes;

	num_bytes = count * size;
	result = malloc(num_bytes);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, num_bytes);
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// Cuando la longitud del buffer es igual al tamaño especificado como parámetro,
// el buffer de destino está lleno por lo que no podemos agregar más carácteres.
// En ese caso, aunque no hemos hecho ninguna copia "real", tenemos que devolver
// la longitud total si no hubiese restricciones de espacio
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlong;

	dstlong = 0;
	while (dst[dstlong] != '\0' && dstlong < dstsize)
		dstlong++;
	if (dstlong == dstsize)
		return (dstlong + ft_strlen(src));
	return (dstlong + ft_strlcpy(dst + dstlong, src, dstsize - dstlong));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcat(result, s2, s1_len + s2_len + 1);
	return (result);
}
