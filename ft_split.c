/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 06:36:09 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/30 06:36:10 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_clr(char **ptr, size_t x)
{
	while (x--)
		free(ptr[x]);
	free(ptr);
	return (NULL);
}

size_t	word_count(char const *s, char c)
{
	size_t	wc;

	wc = 0;
	while (*s)
	{
		while (*s == c && *s)
			++s;
		if (*s)
			++wc;
		while (*s != c && *s)
			++s;
	}
	return (wc);
}

char	**ft_alloc(char **ptr, const char *s, char c, size_t wc)
{
	size_t	wl;
	size_t	x;

	x = 0;
	while (*s && x < wc)
	{
		wl = 0;
		while (*s == c && *s)
			++s;
		while (s[wl] != c && s[wl])
			++wl;
		ptr[x] = malloc(wl + 1);
		if (!ptr[x])
			return (ft_clr(ptr, x));
		ft_strlcpy(ptr[x], s, wl + 1);
		s += wl;
		++x;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	size_t	wc;
	char	**ptr;

	if (!s)
		return (NULL);
	wc = word_count(s, c);
	ptr = ft_calloc(wc + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	return (ft_alloc(ptr, s, c, wc));
}
