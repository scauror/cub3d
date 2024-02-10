/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:16:02 by scarpent          #+#    #+#             */
/*   Updated: 2023/05/05 17:41:53 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dtlen;
	size_t	sclen;

	if (!dst && !size)
		return (0);
	dtlen = ft_strlen(dst);
	sclen = ft_strlen(src);
	if (size <= dtlen)
		return (size + sclen);
	dst = (dst + dtlen);
	ft_strlcpy(dst, src, (size - dtlen));
	return (dtlen + sclen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	slen;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	slen = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(slen);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, slen);
	return (str);
}

char	*ft_check_nl(char **reserve)
{
	char	*line;
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	while (*(*reserve + i) != '\n')
		++i;
	line = malloc(i + 2);
	if (!line)
		return (free(*reserve), *reserve = NULL, NULL);
	ft_strlcpy_gnl(line, *reserve, (i + 2));
	len = ft_strlen_gnl(*reserve + i + 1);
	if (!len)
		return (free(*reserve), *reserve = NULL, line);
	else
	{
		tmp = malloc(len + 1);
		ft_strlcpy_gnl(tmp, (*reserve + i + 1), (len + 1));
		free(*reserve);
		*reserve = ft_strdup_gnl(&tmp);
		return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*buffer;
	int			nbyte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(reserve), reserve = NULL, NULL);
	while (1)
	{
		nbyte = read(fd, buffer, BUFFER_SIZE);
		if (nbyte < 0)
			return (free(buffer), free(reserve), reserve = NULL, NULL);
		if (!nbyte && !ft_strchr_gnl(reserve, '\n'))
			return (free(buffer), ft_strdup_gnl(&reserve));
		buffer[nbyte] = '\0';
		if (nbyte)
			reserve = ft_strjoin_gnl(reserve, buffer);
		if (ft_strchr_gnl(reserve, '\n'))
			return (free(buffer), ft_check_nl(&reserve));
	}
}
