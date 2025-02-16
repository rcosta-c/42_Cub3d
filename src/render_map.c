/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:50:54 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/16 13:57:02 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_column_parts(t_cub *cub, int x, t_ray *ray)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;

	y = 0;
	while (y++ < ray->ds)
	{
		my_mlx_pixel_put(&(cub->game), x, y, cub->game.ceiling_color);
	}
	y = ray->ds;
	while (y < ray->de)
	{
		d = y * 256 - WIN_HEIGHT * 128 + ray->lh * 128;
		tex_y = ((d * ray->tex->height) / ray->lh) / 256;
		color = ((int *)ray->tex->addr)[tex_y * ray->tex->width + ray->tex_x];
		my_mlx_pixel_put(&(cub->game), x, y, color);
		y++;
	}
	y = ray->de;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&(cub->game), x, y, cub->game.floor_color);
		y++;
	}
}

static void	setup_ray(t_cub *cub, int x, t_ray *ray)
{
	compute_ray_parameters(cub, x, ray);
	perform_dda(cub, ray);
	compute_wall(cub, ray);
	if (ray->side == 0)
	{
		if (ray->rd_x > 0)
			ray->tex = &cub->game.texture[3];
		else
			ray->tex = &cub->game.texture[2];
	}
	else
	{
		if (ray->rd_y > 0)
			ray->tex = &cub->game.texture[1];
		else
			ray->tex = &cub->game.texture[0];
	}
	if (ray->side == 0)
		ray->wall_x = cub->game.player_y + ray->perp * ray->rd_y;
	else
		ray->wall_x = cub->game.player_x + ray->perp * ray->rd_x;
	ray->wall_x = ray->wall_x - floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)ray->tex->width);
	if ((ray->side == 0 && ray->rd_x > 0) || (ray->side == 1 && ray->rd_y < 0))
		ray->tex_x = ray->tex->width - ray->tex_x - 1;
}

void	render_column(t_cub *cub, int x)
{
	t_ray	ray;

	setup_ray(cub, x, &ray);
	draw_column_parts(cub, x, &ray);
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
	mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.img, 0, 0);
}
