/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chk_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 06:01:11 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/30 06:01:11 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_dir_elem(t_map *map_data, char **dir_txt, int *dir_elem)
{
	int	i;

	i = 0;
	while (map_data->map_chk->elem[i])
		++i;
	if (i != 2)
		ft_error("Error : Invalid path structure\n", map_data);
	*dir_txt = ft_strdup(map_data->map_chk->elem[1]);
	if (!*dir_txt)
		ft_error(NULL, map_data);
	*dir_elem = 1;
}

void	ft_rgb_init(t_map *map_data, char *elem, uint32_t *clr, int *i)
{
	uint32_t	rgb;

	rgb = 0;
	while (ft_isdigit(elem[*i]))
	{
		rgb = (rgb * 10) + (elem[*i] - 48);
		++(*i);
	}
	if (rgb > 255)
		ft_error("Error : RGB color invalid (superior to 255)\n", map_data);
	*clr |= (rgb << (8 * (3 - map_data->map_chk->digit_count)));
	map_data->map_chk->digit_count++;
	if (map_data->map_chk->digit_count == 3)
		*clr |= 0xFF;
	if (map_data->map_chk->digit_count >= 4)
		ft_error("Error : RGB can't have more than 3 values", map_data);
	(*i)--;
}

void	ft_rgb_chk(t_map *map_data, char *elem, uint32_t *clr)
{
	int	i;

	i = 0;
	while (elem[i])
	{
		if (ft_isdigit(elem[i]))
		{
			ft_rgb_init(map_data, elem, clr, &i);
			map_data->map_chk->digit = 1;
		}
		else if (elem[i] == ',' && map_data->map_chk->digit == 1)
		{
			map_data->map_chk->comma_count++;
			map_data->map_chk->digit = 0;
		}
		else
			ft_error("Error : Invalid char in RGB values\n", map_data);
		++i;
	}
}

void	ft_rgb_elem(t_map *map_data, char **elem, int opt)
{
	int	i;

	i = 1;
	while (elem[i])
	{
		if (opt)
			ft_rgb_chk(map_data, elem[i], &map_data->c_color);
		else
			ft_rgb_chk(map_data, elem[i], &map_data->f_color);
		++i;
	}
	if (map_data->map_chk->digit_count != 3)
		ft_error("Error : RGB values must be 3 numbers\n", map_data);
	if (map_data->map_chk->comma_count != 2)
		ft_error("Error : Invalid RGB value structure\n", map_data);
	map_data->map_chk->digit = 0;
	map_data->map_chk->digit_count = 0;
	map_data->map_chk->comma_count = 0;
	if (opt)
		map_data->map_chk->c_elem = 1;
	else
		map_data->map_chk->f_elem = 1;
}
