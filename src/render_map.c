/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:50:54 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/14 22:51:59 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_ceiling(t_cub *cub, int x, int ds)
{
    int y = 0;
    while (y < ds)
    {
        my_mlx_pixel_put(&(cub->game), x, y, cub->game.ceiling_color);
        y++;
    }
}

void draw_wall(t_cub *cub, int x, int ds, int de, t_tex *tex, int lh, int texX)
{
    int y, d, texY, color;
    y = ds;
    while (y < de)
    {
        d = y * 256 - WIN_HEIGHT * 128 + lh * 128;
        texY = ((d * tex->height) / lh) / 256;
        color = ((int *)tex->addr)[texY * tex->width + texX];
        my_mlx_pixel_put(&(cub->game), x, y, color);
        y++;
    }
}

void draw_floor(t_cub *cub, int x, int de)
{
    int y = de;
    while (y < WIN_HEIGHT)
    {
        my_mlx_pixel_put(&(cub->game), x, y, cub->game.floor_color);
        y++;
    }
}

void render_column(t_cub *cub, int x)
{
    int mx, my, step_x, step_y, side;
    double rd_x, rd_y, sd_x, sd_y, ddx, ddy, perp, wallX;
    int lh, ds, de, texture_index, texX;
    t_tex *tex;

    compute_ray_parameters(cub, x, &mx, &my, &rd_x, &rd_y, &step_x, &step_y,
                           &sd_x, &sd_y, &ddx, &ddy);
    perform_dda(cub, &mx, &my, &sd_x, &sd_y, ddx, ddy, step_x, step_y, &side);
    compute_wall(cub, rd_x, rd_y, step_x, step_y, mx, my, side, &perp, &lh, &ds, &de);
    texture_index = (side == 0) ? ((rd_x > 0) ? 3 : 2) : ((rd_y > 0) ? 1 : 0);
    tex = &cub->game.texture[texture_index];
    wallX = (side == 0) ? cub->game.player_y + perp * rd_y :
                          cub->game.player_x + perp * rd_x;
    wallX = wallX - floor(wallX);
    texX = (int)(wallX * (double)tex->width);
    if ((side == 0 && rd_x > 0) || (side == 1 && rd_y < 0))
        texX = tex->width - texX - 1;
    draw_ceiling(cub, x, ds);
    draw_wall(cub, x, ds, de, tex, lh, texX);
    draw_floor(cub, x, de);
}

void render_map(t_cub *cub)
{
    int x = 0;
    while (x < WIN_WIDTH)
    {
        render_column(cub, x);
        x++;
    }
    mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.img, 0, 0);
}
