/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:13:48 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/16 14:21:51 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	compute_initial_values(t_cub *cub, t_ray *ray)
{
	ray->map_x = (int)cub->game.player_x;
	ray->map_y = (int)cub->game.player_y;
}

static void	compute_steps_x(t_cub *cub, t_ray *ray)
{
	double	factor;

	if (ray->rd_x < 0)
	{
		ray->step_x = -1;
		if (ray->rd_x == 0)
			factor = 1e30;
		else
			factor = fabs(1 / ray->rd_x);
		ray->side_dist_x = (cub->game.player_x - ray->map_x) * factor;
	}
	else
	{
		ray->step_x = 1;
		if (ray->rd_x == 0)
			factor = 1e30;
		else
			factor = fabs(1 / ray->rd_x);
		ray->side_dist_x = ((ray->map_x + 1.0) - cub->game.player_x) * factor;
	}
}

static void	compute_steps_y(t_cub *cub, t_ray *ray)
{
	double	factor;

	if (ray->rd_y < 0)
	{
		ray->step_y = -1;
		if (ray->rd_y == 0)
			factor = 1e30;
		else
			factor = fabs(1 / ray->rd_y);
		ray->side_dist_y = (cub->game.player_y - ray->map_y) * factor;
	}
	else
	{
		ray->step_y = 1;
		if (ray->rd_y == 0)
			factor = 1e30;
		else
			factor = fabs(1 / ray->rd_y);
		ray->side_dist_y = ((ray->map_y + 1.0) - cub->game.player_y) * factor;
	}
}

static void	compute_delta_distances(t_ray *ray)
{
	if (ray->rd_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->rd_x);
	if (ray->rd_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->rd_y);
}

void	compute_steps_and_distances(t_cub *cub, t_ray *ray)
{
	compute_steps_x(cub, ray);
	compute_steps_y(cub, ray);
	compute_delta_distances(ray);
}
