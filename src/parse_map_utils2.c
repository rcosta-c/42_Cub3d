/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:28 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/19 17:00:22 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	copy_map_file_helper_2(t_cub *cub, int x, int coord, char *temp)
{
	if (coord == 3 && !cub->map->ea_file)
	{
		cub->map->coords_counter++;
		cub->map->ea_file = ft_strdup(temp);
	}
	if (coord == 4 && !cub->map->f_info)
	{
		cub->map->coords_counter++;
		cub->map->f_info = ft_strdup(temp);
	}
	if (coord == 5 && !cub->map->c_info)
	{
		cub->map->coords_counter++;
		cub->map->c_info = ft_strdup(temp);
	}
	if (x > cub->map->last_line_info)
		cub->map->last_line_info = x;
}

void	copy_map_file_helper(t_cub *cub, int x, int coord, char *temp)
{
	if (coord == 0 && !cub->map->no_file)
	{
		cub->map->coords_counter++;
		cub->map->no_file = ft_strdup(temp);
	}
	if (coord == 1 && !cub->map->so_file)
	{
		cub->map->coords_counter++;
		cub->map->so_file = ft_strdup(temp);
	}
	if (coord == 2 && !cub->map->we_file)
	{
		cub->map->coords_counter++;
		cub->map->we_file = ft_strdup(temp);
	}
	copy_map_file_helper_2(cub, x, coord, temp);
}

void	copy_map_file(t_cub *cub, int x, int coord)
{
	int		xx;
	char	temp[5120];
	int		z;

	z = 0;
	xx = 2;
	while (cub->map->file[x][xx] == ' ')
		xx++;
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

void	split_color_c(t_cub *cub)
{
	char	**res;
	int		x;

	x = 0;
	res = ft_split(cub->map->c_info, ',');
	cub->map->c_rgb.r = ft_atoi(res[0]);
	cub->map->c_rgb.g = ft_atoi(res[1]);
	cub->map->c_rgb.b = ft_atoi(res[2]);
	while (res[x])
	{
		free(res[x]);
		x++;
	}
	free(res);
}
