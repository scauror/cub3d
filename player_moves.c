/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:30:43 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/30 10:30:44 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mv_straight(t_mlx *mlx, int pix)
{
	double	x;
	double	y;

	x = mlx->player_data->player->x + cos(mlx->player_data->rot_angle)
		* (pix * MOVE_SPEED);
	y = mlx->player_data->player->y;
	if (mlx->map_data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
		ft_init_cord(mlx->player_data->player, x, y);
	x = mlx->player_data->player->x;
	y = mlx->player_data->player->y + sin(mlx->player_data->rot_angle)
		* (pix * MOVE_SPEED);
	if (mlx->map_data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
		ft_init_cord(mlx->player_data->player, x, y);
}

void	ft_mv_sides(t_mlx *mlx, int pix)
{
	double	x;
	double	y;

	x = mlx->player_data->player->x;
	if (pix == 1)
		y = mlx->player_data->player->y + sin(mlx->player_data->rot_angle
				+ M_PI / 2) * MOVE_SPEED;
	else
		y = mlx->player_data->player->y + sin(mlx->player_data->rot_angle
				- M_PI / 2) * MOVE_SPEED;
	if (mlx->map_data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
		ft_init_cord(mlx->player_data->player, x, y);
	y = mlx->player_data->player->y;
	if (pix == 1)
		x = mlx->player_data->player->x + cos(mlx->player_data->rot_angle
				+ M_PI / 2) * MOVE_SPEED;
	else
		x = mlx->player_data->player->x + cos(mlx->player_data->rot_angle
				- M_PI / 2) * MOVE_SPEED;
	if (mlx->map_data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '1')
		ft_init_cord(mlx->player_data->player, x, y);
}

void	ft_rotate(t_mlx *mlx, int pix)
{
	t_player	*player_data;

	player_data = mlx->player_data;
	player_data->rot_angle += (pix * player_data->rot_speed);
	ft_norm_angle(&player_data->rot_angle);
}

void	ft_player_moves(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		ft_mv_straight(mlx, 1);
	else if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		ft_mv_straight(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		ft_mv_sides(mlx, 1);
	else if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		ft_mv_sides(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		ft_rotate(mlx, 1);
	else if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
		ft_rotate(mlx, -1);
	if (mlx_is_key_down(mlx->win, MLX_KEY_ESCAPE))
		ft_esc(mlx);
	ft_render_map(mlx);
}
