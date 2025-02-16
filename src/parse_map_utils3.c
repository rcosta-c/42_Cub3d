/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:28 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/16 16:53:54 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	search_coords_error(t_cub *cub, int x)
{
	if (ft_strlen(cub->map->file[x]) < 6
		&& ft_strlen(cub->map->file[x]) > 0
		&& cub->map->file[x][0] != '\n')
	{
		cub->error.char_invalid = true;
		cub->error.valid_map = false;
		free_exit(cub, "Invalid Coords");
	}
}

void	search_coords_error_2(t_cub *cub)
{
	if (cub->map->coords_counter != 6)
	{
		cub->error.char_invalid = true;
		cub->error.valid_map = false;
		free_exit(cub, "Invalid Coords");
	}
}

void	validate_color(t_cub *cub)
{
	if (cub->map->c_rgb.r < 0 || cub->map->c_rgb.r > 255)
		cub->error.valid_map = false;
	else if (cub->map->c_rgb.g < 0 || cub->map->c_rgb.g > 255)
		cub->error.valid_map = false;
	else if (cub->map->c_rgb.b < 0 || cub->map->c_rgb.b > 255)
		cub->error.valid_map = false;
	else if (cub->map->f_rgb.r < 0 || cub->map->f_rgb.r > 255)
		cub->error.valid_map = false;
	else if (cub->map->f_rgb.g < 0 || cub->map->f_rgb.g > 255)
		cub->error.valid_map = false;
	else if (cub->map->f_rgb.b < 0 || cub->map->f_rgb.b > 255)
		cub->error.valid_map = false;
}

void	validate_info(t_cub *cub)
{
	if (cub->map->coords_counter != 6)
		cub->error.valid_map = false;
	else if (!cub->map->f_info || ft_strlen(cub->map->f_info) < 7)
		cub->error.valid_map = false;
	else if (!cub->map->c_info || ft_strlen(cub->map->c_info) < 7)
		cub->error.valid_map = false;
	else if (!cub->map->no_file || ft_strlen(cub->map->no_file) < 8)
		cub->error.valid_map = false;
	else if (!cub->map->so_file || ft_strlen(cub->map->so_file) < 8)
		cub->error.valid_map = false;
	else if (!cub->map->ea_file || ft_strlen(cub->map->ea_file) < 8)
		cub->error.valid_map = false;
	else if (!cub->map->we_file || ft_strlen(cub->map->we_file) < 8)
		cub->error.valid_map = false;
}
