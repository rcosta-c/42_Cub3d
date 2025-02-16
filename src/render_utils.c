/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:50:58 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/16 09:23:53 by rcosta-c         ###   ########.fr       */
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

/*void perform_dda(t_cub *cub) /*NOVA FUNCAO QUE NAO FUNCIONA AINDA*/
{
    int hit = 0;
    int max_iterations = cub->map->map_lenght * cub->map->map_lines; 
    int count = 0;

    while (!hit && count < max_iterations)
    {
        count++;

        if (cub->ray.side_dist_x < cub->ray.side_dist_y)
        { 
            cub->ray.side_dist_x += cub->ray.delta_dist_x; 
            cub->ray.mx += cub->ray.step_x; 
            cub->ray.side = 0; 
        }
        else
        { 
            cub->ray.side_dist_y += cub->ray.delta_dist_y; 
            cub->ray.my += cub->ray.step_y; 
            cub->ray.side = 1; 
        }

 		 if (cub->ray.map_x < 0 || cub->ray.map_x >= cub->map->map_lines || cub->ray.map_y < 0 || cub->ray.map_y >= cub->map->map_lenght)
            break;

        if (cub->map->map[cub->ray.map_x][cub->ray.map_y] == '1' || cub->map->map[cub->ray.map_x][cub->ray.map_y] == 'D')
            hit = 1;
    }
}*/

/* Calcula o parametro da câmera e a direção do raio para a coluna x */
void compute_ray_direction(t_cub *cub, int x)
{
    cub->ray.cam = 2 * x / (double)WIN_WIDTH - 1;
    cub->ray.rd_x = cub->game.dir_x + cub->game.plane_x * (cub->ray.cam);
    cub->ray.rd_y = cub->game.dir_y + cub->game.plane_y * (cub->ray.cam);
}

/* Define os valores iniciais do jogador */
void compute_initial_values(t_cub *cub, int *mx, int *my)
{
    *mx = (int)cub->game.player_x;
    *my = (int)cub->game.player_y;
}

/* Calcula os passos e as distancias laterais para o algoritmo DDA */

void compute_steps_and_distances(t_cub *cub, double rd_x, double rd_y, int mx, int my)
{
    if (rd_x < 0)
    {
        cub->ray.step_x = -1;
        cub->ray.sd_x = (cub->game.player_x - mx) * ((rd_x == 0) ? 1e30 : fabs(1 / rd_x));
    }
    else
    {
        cub->ray.step_x = 1;
        cub->ray.sd_x = (mx + 1.0 - cub->game.player_x) * ((rd_x == 0) ? 1e30 : fabs(1 / rd_x));
    }
    if (rd_y < 0)
    {
        cub->ray.step_y = -1;
        cub->ray.sd_y = (cub->game.player_y - my) * ((rd_y == 0) ? 1e30 : fabs(1 / rd_y));
    }
    else
    {
        cub->ray.step_y = 1;
        cub->ray.sd_y = (my + 1.0 - cub->game.player_y) * ((rd_y == 0) ? 1e30 : fabs(1 / rd_y));
    }
    cub->ray.ddx = (rd_x == 0) ? 1e30 : fabs(1 / rd_x);
    cub->ray.ddy = (rd_y == 0) ? 1e30 : fabs(1 / rd_y);
}

void compute_ray_parameters(t_cub *cub, int x)
{
    cub->ray.cam = 0;
    compute_ray_direction(cub, x);
    compute_initial_values(cub, &cub->ray.mx, &cub->ray.my);
    compute_steps_and_distances(cub, cub->ray.rd_x, cub->ray.rd_y, cub->ray.mx, cub->ray.my);
}
void compute_wall(t_cub *cub)
{
    cub->ray.perp = (cub->ray.side == 0) ? (cub->ray.mx - cub->game.player_x + (1 - cub->ray.step_x) / 2.0) / cub->ray.rd_x :
                                        (cub->ray.my - cub->game.player_y + (1 - cub->ray.step_y) / 2.0) / cub->ray.rd_y;
    cub->ray.lh = (int)(WIN_HEIGHT / cub->ray.perp);
    cub->ray.ds = -(cub->ray.lh) / 2 + WIN_HEIGHT / 2;
    cub->ray.de = (cub->ray.lh) / 2 + WIN_HEIGHT / 2;
    if (cub->ray.ds < 0)
        cub->ray.ds = 0;
    if (cub->ray.de >= WIN_HEIGHT)
        cub->ray.de = WIN_HEIGHT - 1;
}
