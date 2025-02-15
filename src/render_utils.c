/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:50:58 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/15 18:20:06 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


void perform_dda(t_cub *cub, int *map_x, int *map_y, double *side_dist_x, 
                 double *side_dist_y, double delta_dist_x, double delta_dist_y, 
                 int step_x, int step_y, int *side)
{
    int hit = 0;
    int max_iterations = cub->map->map_lenght * cub->map->map_lines; 
    int count = 0;

    while (!hit && count < max_iterations)
    {
        count++;

        if (*side_dist_x < *side_dist_y)
        { 
            *side_dist_x += delta_dist_x; 
            *map_x += step_x; 
            *side = 0; 
        }
        else
        { 
            *side_dist_y += delta_dist_y; 
            *map_y += step_y; 
            *side = 1; 
        }

        // Verifica se está dentro dos limites antes de acessar a matriz
        if (*map_x < 0 || *map_x >= cub->map->map_lines || *map_y < 0 || *map_y >= cub->map->map_lenght)
            break;

        if (cub->map->map[*map_x][*map_y] == '1' || cub->map->map[*map_x][*map_y] == 'D')
            hit = 1;
    }
}

/* Calcula o parametro da câmera e a direção do raio para a coluna x */
void compute_ray_direction(t_cub *cub, int x, double *cam, double *rd_x, double *rd_y)
{
    *cam = 2 * x / (double)WIN_WIDTH - 1;
    *rd_x = cub->game.dir_x + cub->game.plane_x * (*cam);
    *rd_y = cub->game.dir_y + cub->game.plane_y * (*cam);
}

/* Define os valores iniciais do jogador */
void compute_initial_values(t_cub *cub, int *mx, int *my)
{
    *mx = (int)cub->game.player_x;
    *my = (int)cub->game.player_y;
}

/* Calcula os passos e as distancias laterais para o algoritmo DDA */
void compute_steps_and_distances(t_cub *cub, double rd_x, double rd_y, int mx, int my,
                                 int *step_x, int *step_y, double *sd_x, double *sd_y,
                                 double *ddx, double *ddy)
{
    if (rd_x < 0)
    {
        *step_x = -1;
        *sd_x = (cub->game.player_x - mx) * ((rd_x == 0) ? 1e30 : fabs(1 / rd_x));
    }
    else
    {
        *step_x = 1;
        *sd_x = (mx + 1.0 - cub->game.player_x) * ((rd_x == 0) ? 1e30 : fabs(1 / rd_x));
    }
    if (rd_y < 0)
    {
        *step_y = -1;
        *sd_y = (cub->game.player_y - my) * ((rd_y == 0) ? 1e30 : fabs(1 / rd_y));
    }
    else
    {
        *step_y = 1;
        *sd_y = (my + 1.0 - cub->game.player_y) * ((rd_y == 0) ? 1e30 : fabs(1 / rd_y));
    }
    *ddx = (rd_x == 0) ? 1e30 : fabs(1 / rd_x);
    *ddy = (rd_y == 0) ? 1e30 : fabs(1 / rd_y);
}

/* funcao principal que reune os calculos do raycasting */
void compute_ray_parameters(t_cub *cub, int x, int *mx, int *my, double *rd_x, double *rd_y,
                              int *step_x, int *step_y, double *sd_x, double *sd_y,
                              double *ddx, double *ddy)
{
    double cam;
    compute_ray_direction(ray.cub, x, &cam, rd_x, rd_y);
    compute_initial_values(ray.cub, mx, my);
    compute_steps_and_distances(ray.cub, *rd_x, *rd_y, *mx, *my, step_x, step_y, sd_x, sd_y, ddx, ddy);
}

void compute_wall(t_cub *cub, double rd_x, double rd_y, int step_x, int step_y,
                  int mx, int my, int side, double *perp, int *lh, int *ds, int *de)
{
    *perp = (side == 0) ? (mx - cub->game.player_x + (1 - step_x) / 2.0) / rd_x :
                          (my - cub->game.player_y + (1 - step_y) / 2.0) / rd_y;
    *lh = (int)(WIN_HEIGHT / *perp);
    *ds = -(*lh) / 2 + WIN_HEIGHT / 2;
    *de = (*lh) / 2 + WIN_HEIGHT / 2;
    if (*ds < 0)
        *ds = 0;
    if (*de >= WIN_HEIGHT)
        *de = WIN_HEIGHT - 1;
}