/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:50:54 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/16 09:23:25 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_ceiling(t_cub *cub, int x, int ds)
{
	int	y;

	y = 0;
	while (y < ds)
	{
		my_mlx_pixel_put(&(cub->game), x, y, cub->game.ceiling_color);
		y++;
	}
}

void draw_wall(t_cub *cub, int x, t_tex *tex)
{
    int y = cub->ray.ds;
    int d, texY, color;

    while (y < cub->ray.de)
    {
        d = y * 256 - WIN_HEIGHT * 128 + cub->ray.lh * 128;
        texY = ((d * tex->height) / cub->ray.lh) / 256;
        color = ((int *)tex->addr)[texY * tex->width + cub->ray.texX];
        my_mlx_pixel_put(&(cub->game), x, y, color);
        y++;
    }
}

void	draw_floor(t_cub *cub, int x, int de)
{
	int	y;

	y = de;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&(cub->game), x, y, cub->game.floor_color);
		y++;
	}
}

void	render_column(t_cub *cub, int x)
{
	t_tex *tex;
	
	compute_ray_parameters(cub, x);
	perform_dda(cub, &cub->ray.mx, &cub->ray.my, &cub->ray.sd_x, &cub->ray.sd_y,
		cub->ray.ddx, cub->ray.ddy, cub->ray.step_x, cub->ray.step_y, &cub->ray.side);
	compute_wall(cub);
	cub->ray.texture_index = (cub->ray.side == 0) ? ((cub->ray.rd_x > 0) ? 3 : 2) : ((cub->ray.rd_y > 0) ? 1 : 0);
	tex = &cub->game.texture[cub->ray.texture_index];
	cub->ray.wallX = (cub->ray.side == 0) ? cub->game.player_y + cub->ray.perp * cub->ray.rd_y :
		cub->game.player_x + cub->ray.perp * cub->ray.rd_x;
	cub->ray.wallX -= floor(cub->ray.wallX);
	cub->ray.texX = (int)(cub->ray.wallX * (double)tex->width);
	if ((cub->ray.side == 0 && cub->ray.rd_x > 0) || (cub->ray.side == 1 && cub->ray.rd_y < 0))
		cub->ray.texX = tex->width - cub->ray.texX - 1;
	draw_ceiling(cub, x, cub->ray.ds);
	draw_wall(cub, x, tex);
	draw_floor(cub, x, cub->ray.de);
}

void	render_map(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		render_column(cub, x);
		x++;
	}
	mlx_put_image_to_window(cub->game.mlx, cub->game.win,
			cub->game.img, 0, 0);
}
