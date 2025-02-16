/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:49:46 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/16 13:03:39 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_base(t_cub *cub, char **av)
{
	cub->map = ft_calloc(sizeof(t_map), 1);
	cub->map->map_lines_counter = map_1st_reading(av[1], cub);
	cub->map->file = ft_calloc(sizeof(char *), cub->map->map_lines_counter + 1);
	cub->map->last_line_info = 0;
	cub->map->map_lines = 0;
	cub->map->coords_counter = 0;
	cub->error.valid_map = true;
	cub->error.no_invalid = true;
	cub->error.so_invalid = true;
	cub->error.we_invalid = true;
	cub->error.ea_invalid = true;
	cub->error.char_invalid = true;
	cub->error.f_invalid = true;
	cub->error.c_invalid = true;
}

void	init_mlx(t_cub *cub)
{
	(void)cub;
	cub->game.texture = ft_calloc(sizeof(t_tex), 4);
	if (!cub->game.texture)
		exit(EXIT_FAILURE);
}

void	init_game(t_cub *cub)
{
	cub->game.mlx = mlx_init();
	cub->game.win = mlx_new_window(cub->game.mlx,
			WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	cub->game.img = mlx_new_image(cub->game.mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->game.addr = mlx_get_data_addr(cub->game.img,
			&cub->game.bpp, &cub->game.line_len, &cub->game.endian);
	player_moves_vertical(cub);
	player_moves_horizontal(cub);
	cub->game.floor_color = create_rgb(cub->map->f_rgb.r,
			cub->map->f_rgb.g, cub->map->f_rgb.b);
	cub->game.ceiling_color = create_rgb(cub->map->c_rgb.r,
			cub->map->c_rgb.g, cub->map->c_rgb.b);
}
