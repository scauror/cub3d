/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 07:36:48 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/30 07:36:49 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_cord(t_cord *cord, double x, double y)
{
	cord->x = x;
	cord->y = y;
}

void	ft_paint_pix(uint8_t *pix, uint32_t clr, size_t size)
{
	size_t	i;
	int		shift;

	shift = 3;
	i = 0;
	while (i < size * BPP)
	{
		if (shift == -1)
			shift = 3;
		pix[i] = (clr >> (8 * shift)) & 0xFF;
		--shift;
		++i;
	}
}

double	ft_norm_angle(double *angle)
{
	*angle = remainder(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += (2 * M_PI);
	return (*angle);
}

double	ft_player_angle(t_map *map_data)
{
	if (map_data->charac_dir == 'N')
		return (3 * M_PI / 2);
	else if (map_data->charac_dir == 'S')
		return (M_PI_2);
	else if (map_data->charac_dir == 'W')
		return (M_PI);
	else if (map_data->charac_dir == 'E')
		return (0);
	return (0);
}

uint32_t	ft_rgb(uint32_t r, uint32_t g, uint32_t b, uint32_t o)
{
	return (r << 24 | g << 16 | b << 8 | o);
}
