/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:28 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/16 16:51:11 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	search_coords_player(t_cub *cub, int x)
{
	if (cub->map->file[x][0] == 'N'
				&& cub->map->file[x][1] == 'O'
				&& cub->map->file[x][2] == ' ')
	{
		copy_map_file(cub, x, 0);
	}
	else if (cub->map->file[x][0] == 'S'
			&& cub->map->file[x][1] == 'O'
			&& cub->map->file[x][2] == ' ')
	{
		copy_map_file(cub, x, 1);
	}
	else if (cub->map->file[x][0] == 'W'
			&& cub->map->file[x][1] == 'E'
			&& cub->map->file[x][2] == ' ')
	{
		copy_map_file(cub, x, 2);
	}
	else if (cub->map->file[x][0] == 'E'
			&& cub->map->file[x][1] == 'A'
			&& cub->map->file[x][2] == ' ')
	{
		copy_map_file(cub, x, 3);
	}
}

void	search_coords(t_cub *cub, int x)
{
	if (ft_strlen(cub->map->file[x]) > 5)
	{
		if (cub->map->file[x][0] == 'N' || cub->map->file[x][0] == 'S'
			|| cub->map->file[x][0] == 'E' || cub->map->file[x][0] == 'W')
			search_coords_player(cub, x);
		else if (cub->map->file[x][0] == 'C')
			copy_map_file(cub, x, 5);
		else if (cub->map->file[x][0] == 'F'
			&& cub->map->file[x][1] == ' ')
			copy_map_file(cub, x, 4);
	}
	search_coords_error(cub, x);
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

void	split_color_process(t_cub *cub)
{
	int	x;
	int	sign;

	sign = 0;
	x = 2;
	while (cub->map->f_info[x])
	{
		if (cub->map->f_info[x] == ',')
			sign++;
		x++;
	}
	if (sign == 2)
		split_color_f(cub);
	sign = 0;
	x = 2;
	while (cub->map->c_info[x])
	{
		if (cub->map->c_info[x] == ',')
			sign++;
		x++;
	}
	if (sign == 2)
		split_color_c(cub);
}

void	map_info_sniffer(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < cub->map->map_lines_counter)
	{
		search_coords(cub, x);
		x++;
	}
	search_coords_error_2(cub);
	split_color_process(cub);
	validate_color(cub);
	if (cub->error.valid_map == false)
		free_exit(cub, "Invalid info for Coords");
	validate_color(cub);
	if (cub->error.valid_map == false)
		free_exit(cub, "Invalid Color");
}
