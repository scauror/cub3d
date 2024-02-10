/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 08:27:19 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/30 08:27:20 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_load_textures(t_mlx *mlx)
{
	mlx->no_txt = mlx_load_png(mlx->map_data->no_txt);
	if (!mlx->no_txt)
		ft_esc(mlx);
	mlx->so_txt = mlx_load_png(mlx->map_data->so_txt);
	if (!mlx->so_txt)
		ft_esc(mlx);
	mlx->we_txt = mlx_load_png(mlx->map_data->we_txt);
	if (!mlx->we_txt)
		ft_esc(mlx);
	mlx->ea_txt = mlx_load_png(mlx->map_data->ea_txt);
	if (!mlx->ea_txt)
		ft_esc(mlx);
}

uint32_t	ft_pix_clr(t_ray *ray, int y_offset, int x_offset)
{
	int	pos;

	pos = (y_offset * ray->texture->width + x_offset) * BPP;
	if (pos < 0
		|| pos > (int)(ray->texture->height * (ray->texture->width * BPP))
		- BPP)
		return (0);
	return (ft_rgb(ray->texture->pixels[pos], ray->texture->pixels[pos + 1],
			ray->texture->pixels[pos + 2], ray->texture->pixels[pos + 3]));
}

double	ft_txt_x_offset(t_ray *ray)
{
	double	x_offset;

	x_offset = 0;
	if (ray->ray_type == H_RAY)
	{
		x_offset = ray->texture->width - fmod(ray->wall_hit->x, TILE_SIZE)
			* ray->texture->width / TILE_SIZE;
		if (ray->ray_up)
			x_offset = fmod(ray->wall_hit->x, TILE_SIZE)
				* ray->texture->width / TILE_SIZE;
	}
	else if (ray->ray_type == V_RAY)
	{
		x_offset = fmod(ray->wall_hit->y, TILE_SIZE)
			* ray->texture->width / TILE_SIZE;
		if (ray->ray_left)
			x_offset = ray->texture->width - fmod(ray->wall_hit->y, TILE_SIZE)
				* ray->texture->width / TILE_SIZE;
	}
	return (x_offset);
}

void	ft_scale_cord_txt(t_mlx *mlx, t_ray *ray, int x)
{
	double	y_offset;
	double	x_offset;
	int		line_height;
	int		y;

	line_height = ray->wall_bottom_pixel - ray->wall_top_pixel;
	y = ray->wall_top_pixel;
	if (y < 0)
		y = 0;
	x_offset = ft_txt_x_offset(ray);
	while (y < ray->wall_bottom_pixel && y < HEIGHT)
	{
		y_offset = (1 - ((double)(ray->wall_bottom_pixel - y) / line_height))
			* ray->texture->height;
		mlx_put_pixel(mlx->img, x, y, ft_pix_clr(ray, y_offset, x_offset));
		y++;
	}
}

void	ft_render_walls(t_mlx *mlx, t_ray *rays)
{
	double	dist_proj;
	double	proj_wall_height;
	int		wall_strip_height;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ft_init_ray_texture(mlx, &rays[x]);
		rays[x].ray_distance
			*= cos(rays[x].ray_angle - mlx->player_data->rot_angle);
		dist_proj = (WIDTH / 2) / tan(mlx->player_data->fov / 2);
		proj_wall_height = (TILE_SIZE / rays[x].ray_distance) * dist_proj;
		wall_strip_height = (int)proj_wall_height;
		rays[x].wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
		rays[x].wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
		ft_scale_cord_txt(mlx, &rays[x], x);
		++x;
	}
}
