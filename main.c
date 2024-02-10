/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:07:17 by scarpent          #+#    #+#             */
/*   Updated: 2024/01/29 09:07:19 by scarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_arg_chk(int ac, char *av)
{
	if (ac != 2)
		ft_error("Error : to execute type './cub3d maps/[map_name].cub'\n",
			NULL);
	if (ft_strlen(av) <= 4)
		ft_error("Error : map's name format incorrect\n", NULL);
	if (ft_strncmp(".cub", av + (ft_strlen(av) - 4), 4))
		ft_error("Error : the map must have '.cub' as its extension\n", NULL);
}

int	main(int ac, char **av)
{
	t_map	map_data[1];

	ft_bzero(map_data, sizeof(map_data));
	ft_arg_chk(ac, av[1]);
	ft_parse_map(map_data, av[1]);
	ft_chk_map(map_data);
	ft_render(map_data);
	exit(EXIT_SUCCESS);
}
