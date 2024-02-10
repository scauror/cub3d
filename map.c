/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 04:17:02 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/30 04:17:04 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_nb_line(t_map *map_data, char *name)
{
	char	*line;
	int		fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		ft_error("Error opening map\n", NULL);
	line = "gnl";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
			++map_data->map_chk->line_count;
		free(line);
	}
	close(fd);
	if (map_data->map_chk->line_count == 0)
		ft_error("Error : Map is empty\n", NULL);
}

void	ft_open_map(t_map *map_data, char *name)
{
	int	nb_line;
	int	i;
	int	fd;

	i = 0;
	ft_nb_line(map_data, name);
	nb_line = map_data->map_chk->line_count;
	map_data->map = ft_calloc((nb_line + 1), sizeof(char *));
	if (!map_data->map)
		ft_error("Error allocating the map\n", NULL);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		ft_error("Error opening map\n", map_data);
	while (i < nb_line)
		map_data->map[i++] = get_next_line(fd);
	close(fd);
}

void	ft_parse_map(t_map *map_data, char *name)
{
	int	i;
	int	j;

	i = 0;
	ft_open_map(map_data, name);
	while (map_data->map[i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (map_data->map[i][j] == '\t')
				ft_error("Error : Map has tabulation\n", map_data);
			if (map_data->map[i][j] == '\n' && !map_data->map[i + 1])
				ft_error("Error : map has empty lines\n", map_data);
			if (map_data->map[i][j] == '\n')
				map_data->map[i][j] = '\0';
			++j;
		}
		++i;
	}
}
