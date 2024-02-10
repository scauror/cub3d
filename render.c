/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 07:20:48 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/30 07:20:50 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_mlx(t_mlx *mlx)
{
	mlx->win = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!mlx->win)
		ft_error("Error : MLX42 failed to initialize\n", mlx->map_data);
	mlx->img = mlx_new_image(mlx->win, WIDTH, HEIGHT);
	if (!mlx->img)
	{
		mlx_terminate(mlx->win);
		ft_error("Error : Failed to create image\n", mlx->map_data);
	}
	if (mlx_image_to_window(mlx->win, mlx->img, 0, 0) < 0)
	{
		mlx_terminate(mlx->win);
		ft_error("Error : Image to Window failed\n", mlx->map_data);
	}
	ft_load_textures(mlx);
	mlx->player_data->player = mlx->map_data->charac;
	mlx->player_data->rot_angle = ft_player_angle(mlx->map_data);
	mlx->player_data->rot_speed = ROT_SPEED * (M_PI / 180);
	mlx->player_data->fov = FOV_ANGLE * (M_PI / 180);
}

void	ft_paint_c_f(t_mlx *mlx)
{
	ft_paint_pix(mlx->img->pixels, mlx->map_data->f_color,
		mlx->img->width * mlx->img->height);
	ft_paint_pix(mlx->img->pixels, mlx->map_data->c_color,
		mlx->img->width * (mlx->img->height / 2));
}

void	ft_render_map(t_mlx *mlx)
{
	t_ray	rays[WIDTH];

	ft_paint_c_f(mlx);
	ft_cast_rays(mlx, rays);
	ft_render_walls(mlx, rays);
}

void	ft_render(t_map *map_data)
{
	t_mlx	mlx[1];

	ft_bzero(mlx, sizeof(mlx));
	mlx->map_data = map_data;
	ft_init_mlx(mlx);
	ft_render_map(mlx);
	mlx_loop_hook(mlx->win, &ft_player_moves, mlx);
	mlx_close_hook(mlx->win, &ft_esc, mlx);
	mlx_loop(mlx->win);
	ft_esc(mlx);
}
