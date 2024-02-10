/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 05:57:04 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/30 05:57:05 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_all_elems(t_chk *map_chk)
{
	return (map_chk->no_elem && map_chk->so_elem && map_chk->we_elem
		&& map_chk->ea_elem && map_chk->c_elem && map_chk->f_elem);
}

void	ft_chk_elem(t_map *map_data)
{
	t_chk	*map_chk;
	char	**elem;

	map_chk = map_data->map_chk;
	elem = map_chk->elem;
	if (!ft_strncmp(*elem, "NO", 3) && !map_chk->no_elem)
		ft_dir_elem(map_data, &map_data->no_txt, &map_chk->no_elem);
	else if (!ft_strncmp(*elem, "SO", 3) && !map_chk->so_elem)
		ft_dir_elem(map_data, &map_data->so_txt, &map_chk->so_elem);
	else if (!ft_strncmp(*elem, "WE", 3) && !map_chk->we_elem)
		ft_dir_elem(map_data, &map_data->we_txt, &map_chk->we_elem);
	else if (!ft_strncmp(*elem, "EA", 3) && !map_chk->ea_elem)
		ft_dir_elem(map_data, &map_data->ea_txt, &map_chk->ea_elem);
	else if (!ft_strncmp(*elem, "C", 3) && !map_chk->c_elem)
		ft_rgb_elem(map_data, elem, 1);
	else if (!ft_strncmp(*elem, "F", 3) && !map_chk->f_elem)
		ft_rgb_elem(map_data, elem, 0);
	else
		ft_error("Error : Invalid map\n", map_data);
	map_chk->num_elem++;
}

void	ft_chk_map(t_map *map_data)
{
	int	i;

	i = 0;
	while (map_data->map[i])
	{
		if (map_data->map_chk->num_elem < 6)
		{
			map_data->map_chk->elem = ft_split(map_data->map[i], ' ');
			if (!map_data->map_chk->elem)
				ft_error(NULL, map_data);
			if (*map_data->map_chk->elem)
				ft_chk_elem(map_data);
			ft_clear((void **)map_data->map_chk->elem);
			map_data->map_chk->elem = NULL;
		}
		else
			if (map_data->map[i][0] != '\0')
				break ;
		++i;
	}
	if (!ft_all_elems(map_data->map_chk))
		ft_error("Error : Missing elements in map\n", map_data);
	ft_chk_content(map_data, i);
}
