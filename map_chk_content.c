/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chk_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 06:46:00 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/30 06:46:02 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_chk_character(t_map *map_data, int x, int y)
{
	if (ft_strchr("NSWE", map_data->map[y][x]))
	{
		if (map_data->charac_dir)
			ft_error("Error : Map has more than 1 player\n", map_data);
		map_data->charac_dir = map_data->map[y][x];
		map_data->charac->x = (x * TILE_SIZE) + (TILE_SIZE / 2);
		map_data->charac->y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	}
}

void	ft_chk_walls(t_map *map_data, char **map, size_t x, size_t y)
{
	if (map[y][x] == '0' || map[y][x] == map_data->charac_dir)
	{
		if (map[y][x + 1] == '\0' || map[y][x + 1] == ' ')
			ft_error("Error : Map is not closed by walls\n", map_data);
		if (x == 0 || map[y][x - 1] == ' ')
			ft_error("Error : Map is not closed by walls\n", map_data);
		if (x + 1 > ft_strlen(map[y + 1]) || map[y + 1][x] == ' ')
			ft_error("Error : Map is not closed by walls\n", map_data);
		if (y == 0 || x + 1 > ft_strlen(map[y - 1]) || map[y - 1][x] == ' ')
			ft_error("Error : Map is not closed by walls\n", map_data);
	}
}

void	ft_iso_content(t_map *map_data, int start)
{
	char	**map_content;
	int		i;

	i = 0;
	while (map_data->map[i])
		++i;
	map_content = ft_calloc((i + 1), sizeof(char *));
	if (!map_content)
		ft_error(NULL, map_data);
	i = 0;
	while (map_data->map[start + i])
	{
		map_content[i] = ft_strdup(map_data->map[start + i]);
		if (!map_content[i])
		{
			ft_clear((void **)map_content);
			ft_error(NULL, map_data);
		}
		++i;
	}
	ft_clear((void **)map_data->map);
	map_data->map = map_content;
}

void	ft_chk_content(t_map *map_data, int start)
{
	int	x;
	int	y;

	ft_iso_content(map_data, start);
	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		if (map_data->map[y][x] == '\0')
			ft_error("Error : Map has empty lines\n", map_data);
		while (map_data->map[y][x])
		{
			if (!ft_strchr("10 NSWE", map_data->map[y][x]))
				ft_error("Error : Invalid characters in the map\n", map_data);
			ft_chk_character(map_data, x, y);
			ft_chk_walls(map_data, map_data->map, x, y);
			++x;
		}
		if (map_data->map_width < x * TILE_SIZE)
			map_data->map_width = x * TILE_SIZE;
		++y;
	}
	map_data->map_height = y * TILE_SIZE;
	if (!map_data->charac_dir)
		ft_error("Error : Map doesn't have a player position\n", map_data);
}
