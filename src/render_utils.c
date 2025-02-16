/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:50:58 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/16 14:21:40 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static bool	dda_step(t_cub *cub, t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
	if (ray->map_x < 0 || ray->map_x >= cub->map->map_lines
		|| ray->map_y < 0 || ray->map_y >= cub->map->map_lenght)
		return (false);
	if (cub->map->map[ray->map_x][ray->map_y] == '1'
			|| cub->map->map[ray->map_x][ray->map_y] == 'D')
		return (true);
	return (false);
}

void	perform_dda(t_cub *cub, t_ray *ray)
{
	int	count;
	int	max_iter;
	int	hit;

	hit = 0;
	count = 0;
	max_iter = cub->map->map_lenght * cub->map->map_lines;
	while (!hit && count < max_iter)
	{
		count++;
		if (dda_step(cub, ray))
			hit = 1;
	}
}

void	compute_ray_direction(t_cub *cub, int x, t_ray *ray)
{
	ray->cam = 2 * x / (double)WIN_WIDTH - 1;
	ray->rd_x = cub->game.dir_x + cub->game.plane_x * ray->cam;
	ray->rd_y = cub->game.dir_y + cub->game.plane_y * ray->cam;
}

void	compute_ray_parameters(t_cub *cub, int x, t_ray *ray)
{
	compute_ray_direction(cub, x, ray);
	compute_initial_values(cub, ray);
	compute_steps_and_distances(cub, ray);
}

void	compute_wall(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp = (ray->map_x - cub->game.player_x
				+ (1 - ray->step_x) / 2.0) / ray->rd_x;
	else
		ray->perp = (ray->map_y - cub->game.player_y
				+ (1 - ray->step_y) / 2.0) / ray->rd_y;
	ray->lh = (int)(WIN_HEIGHT / ray->perp);
	ray->ds = -ray->lh / 2 + WIN_HEIGHT / 2;
	ray->de = ray->lh / 2 + WIN_HEIGHT / 2;
	if (ray->ds < 0)
		ray->ds = 0;
	if (ray->de >= WIN_HEIGHT)
		ray->de = WIN_HEIGHT - 1;
}
