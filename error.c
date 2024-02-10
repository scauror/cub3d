/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:14:29 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/29 09:14:30 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *err, t_map *map_data)
{
	if (err)
		ft_putendl(err);
	else if (errno)
		perror("Error");
	ft_destroy_map_data(map_data);
	exit(EXIT_FAILURE);
}

void	ft_clear(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
			free(ptr[i++]);
		free(ptr);
	}
}

void	ft_destroy_map_data(t_map *map_data)
{
	if (map_data)
	{
		ft_clear((void **)map_data->map_chk->elem);
		ft_clear((void **)map_data->map);
		free(map_data->no_txt);
		free(map_data->so_txt);
		free(map_data->we_txt);
		free(map_data->ea_txt);
	}
}

void	ft_esc(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	ft_destroy_map_data(mlx->map_data);
	if (mlx->no_txt)
		mlx_delete_texture(mlx->no_txt);
	if (mlx->so_txt)
		mlx_delete_texture(mlx->so_txt);
	if (mlx->we_txt)
		mlx_delete_texture(mlx->we_txt);
	if (mlx->ea_txt)
		mlx_delete_texture(mlx->ea_txt);
	mlx_terminate(mlx->win);
	exit(EXIT_SUCCESS);
}
