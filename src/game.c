/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:15:54 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/16 12:57:33 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	clean_exit(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->game.texture[i].img)
		{
			mlx_destroy_image(cub->game.mlx, cub->game.texture[i].img);
		}
		i++;
	}
	mlx_destroy_image(cub->game.mlx, cub->game.img);
	mlx_destroy_window(cub->game.mlx, cub->game.win);
	mlx_destroy_display(cub->game.mlx);
	free(cub->game.mlx);
	free_cub(cub);
	exit(0);
}

void	put_pixel_to_img(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = cub->game.addr
			+ (y * cub->game.line_len + x * (cub->game.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	player_moves_vertical(t_cub *cub)
{
	if (cub->game.player == 'N')
	{
		cub->game.dir_y = -1.0;
		cub->game.dir_x = 0;
		cub->game.plane_x = 0.8;
		cub->game.plane_y = 0.0;
	}
	else if (cub->game.player == 'S')
	{
		cub->game.dir_y = 1.0;
		cub->game.dir_x = 0;
		cub->game.plane_x = -0.8;
		cub->game.plane_y = 0.0;
	}
}

void	player_moves_horizontal(t_cub *cub)
{
	if (cub->game.player == 'W')
	{
		cub->game.dir_y = 0;
		cub->game.dir_x = -1.0;
		cub->game.plane_x = 0.1;
		cub->game.plane_y = -0.8;
	}
	else if (cub->game.player == 'E')
	{
		cub->game.dir_y = 0;
		cub->game.dir_x = 1.0;
		cub->game.plane_x = 0.1;
		cub->game.plane_y = 0.8;
	}
}
