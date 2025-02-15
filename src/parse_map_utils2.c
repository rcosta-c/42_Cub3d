/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:28 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/15 18:10:17 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	copy_map_file_helper(t_cub *cub, int x, int coord, char *temp)
{
	if (coord == 0 && !cub->map->no_file)
	{
		cub->map->no_file = ft_strdup(temp);
	}
	else if (coord == 1 && !cub->map->so_file)
	{
		cub->map->so_file = ft_strdup(temp);
	}
	else if (coord == 2 && !cub->map->we_file)
	{
		cub->map->we_file = ft_strdup(temp);
	}
	else if (coord == 3 && !cub->map->ea_file)
	{
		cub->map->ea_file = ft_strdup(temp);
	}
	else if (coord == 4 && !cub->map->f_info)
		cub->map->f_info = ft_strdup(temp);
	else if (coord == 5 && !cub->map->c_info)
		cub->map->c_info = ft_strdup(temp);
	cub->map->coords_counter++;
	if (x > cub->map->last_line_info)
		cub->map->last_line_info = x;
}

void	copy_map_file(t_cub *cub, int x, int coord)
{
	int		xx;
	char	temp[1024];
	int		z;

	z = 0;
	xx = 2;
	while (cub->map->file[x][xx] == ' ')
	{
		xx++;
	}
	if (cub->map->file[x][xx] == '.')
	{
		xx++;
		if (cub->map->file[x][xx] == '/')
			xx++;
	}
	while (cub->map->file[x][xx] && cub->map->file[x][xx] != '\n')
	{
		temp[z] = cub->map->file[x][xx];
		xx++;
		z++;
	}
	temp[z] = '\0';
	copy_map_file_helper(cub, x, coord, temp);
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

void	split_color_f(t_cub *cub)
{
	char	**res;
	int		x;

	x = 0;
	res = ft_split(cub->map->f_info, ',');
	cub->map->f_rgb.r = ft_atoi(res[0]);
	cub->map->f_rgb.g = ft_atoi(res[1]);
	cub->map->f_rgb.b = ft_atoi(res[2]);
	while (res[x])
	{
		free(res[x]);
		x++;
	}
	free(res);
}
