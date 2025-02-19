/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:28 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/19 17:01:59 by rcosta-c         ###   ########.fr       */
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

void	split_color_process_p2(t_cub *cub)
{
	int	x;
	int	sign;

	sign = 0;
	x = 2;
	while (cub->map->c_info[x])
	{
		if (cub->map->c_info[x] == ',' && cub->map->c_info[x + 1] == ',')
			free_exit(cub, "Invalid Map(Color range)");
		if (cub->map->c_info[x] == ',')
			sign++;
		x++;
	}
	if (sign != 2)
		free_exit(cub, "Invalid Map(Color error)");
	if (sign == 2)
		split_color_c(cub);
}

void	split_color_process_p1(t_cub *cub)
{
	int	x;
	int	sign;

	sign = 0;
	x = 2;
	while (cub->map->f_info[x])
	{
		if (cub->map->f_info[x] == ',' && cub->map->f_info[x + 1] == ',')
			free_exit(cub, "Invalid Map(Color range)");
		if (cub->map->f_info[x] == ',')
			sign++;
		x++;
	}
	if (sign != 2)
		free_exit(cub, "Invalid Map(Color error)");
	if (sign == 2)
		split_color_f(cub);
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
	split_color_process_p1(cub);
	split_color_process_p2(cub);
	validate_color(cub);
	if (cub->error.valid_map == false)
		free_exit(cub, "Invalid info for Coords");
	validate_color(cub);
	is_readable_texture(cub->map->no_file, cub);
	is_readable_texture(cub->map->so_file, cub);
	is_readable_texture(cub->map->we_file, cub);
	is_readable_texture(cub->map->ea_file, cub);
	if (cub->error.valid_map == false)
		free_exit(cub, "Invalid Color");
}
