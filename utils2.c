/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:41:25 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/29 09:41:25 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	sclen;

	sclen = ft_strlen(src);
	if (size)
	{
		while (--size && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (sclen);
}

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = malloc(ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	if (!((char)c))
		return ((char *)s);
	return (NULL);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}
