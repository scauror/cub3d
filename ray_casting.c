/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:15:50 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/30 09:15:52 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_cord_dist(t_cord *p1, t_cord *p2)
{
	return (sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2)));
}

void	ft_ray_dir(t_casting *cast)
{
	cast->ray_down = cast->ray_angle > 0 && cast->ray_angle < M_PI;
	cast->ray_up = !cast->ray_down * -1;
	cast->ray_right = cast->ray_angle < 0.5 * M_PI
		|| cast->ray_angle > 1.5 * M_PI;
	cast->ray_left = !cast->ray_right * -1;
}

void	ft_init_ray_dir(t_ray *ray, t_casting *cast)
{
	ray->ray_up = cast->ray_up;
	ray->ray_down = cast->ray_down;
	ray->ray_left = cast->ray_left;
	ray->ray_right = cast->ray_right;
}

void	ft_wall_hit(t_ray *ray, t_casting *cast)
{
	ft_h_inter(cast);
	ft_v_inter(cast);
	if (cast->h_found_wall)
		cast->h_dist = ft_cord_dist(cast->player, cast->h_insec);
	else
		cast->h_dist = INT_MAX;
	if (cast->v_found_wall)
		cast->v_dist = ft_cord_dist(cast->player, cast->v_insec);
	else
		cast->v_dist = INT_MAX;
	if (cast->h_dist <= cast->v_dist)
	{
		ft_init_cord(ray->wall_hit, cast->h_insec->x, cast->h_insec->y);
		ray->ray_distance = cast->h_dist;
		ray->ray_type = H_RAY;
	}
	else
	{
		ft_init_cord(ray->wall_hit, cast->v_insec->x, cast->v_insec->y);
		ray->ray_distance = cast->v_dist;
		ray->ray_type = V_RAY;
	}
	ft_init_ray_dir(ray, cast);
}

void	ft_cast_rays(t_mlx *mlx, t_ray *rays)
{
	t_player	*player_data;
	t_casting	cast[1];
	int			i;

	i = 0;
	player_data = mlx->player_data;
	cast->width = mlx->map_data->map_width;
	cast->height = mlx->map_data->map_height;
	cast->map = mlx->map_data->map;
	cast->player = player_data->player;
	cast->ray_angle = player_data->rot_angle - player_data->fov / 2;
	while (i < WIDTH)
	{
		rays[i].ray_angle = ft_norm_angle(&cast->ray_angle);
		ft_wall_hit((rays + i), cast);
		cast->ray_angle += player_data->fov / WIDTH;
		++i;
	}
}
