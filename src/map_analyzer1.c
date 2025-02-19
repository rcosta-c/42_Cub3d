/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analyzer1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:22 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/19 16:26:36 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	analize_char_map(t_cub *cub, int x)
{
	bool	flag;
	int		xx;

	flag = true;
	while (cub->map->map[x])
	{
		xx = 0;
		while (cub->map->map[x][xx])
		{
			if (cub->map->map[x][xx] == '\n' || cub->map->map[x][xx] == '0'
				|| cub->map->map[x][xx] == '1' || cub->map->map[x][xx] == 'N'
				|| cub->map->map[x][xx] == 'S' || cub->map->map[x][xx] == 'W'
				|| cub->map->map[x][xx] == 'E' || cub->map->map[x][xx] == ' ')
				xx++;
			else
			{
				flag = false;
				break ;
			}
		}
		x++;
	}
	if (flag == false)
		free_exit(cub, "Invalid Map(strange char)");
}

void	count_char_map(t_cub *cub)
{
	int	counter;
	int	x;
	int	xx;

	x = 0;
	counter = 0;
	while (cub->map->map[x])
	{
		xx = 0;
		while (cub->map->map[x][xx])
		{
			if (cub->map->map[x][xx] == 'N' || cub->map->map[x][xx] == 'S'
				|| cub->map->map[x][xx] == 'W' || cub->map->map[x][xx] == 'E')
			{
				cub->game.player = cub->map->map[x][xx];
				cub->game.player_x = (double)x + 0.5;
				cub->game.player_y = (double)xx + 0.5;
				counter++;
			}
			xx++;
		}
		x++;
	}
	if (counter > 4)
		free_exit(cub, "Invalid Map(wrong number of coords)");
}

void	analize_empty_lines(t_cub *cub)
{
	int	x;

	x = 0;
	while (cub->map->map[x] && x < cub->map->map_lines)
	{
		count_spaces(cub->map->map[x], cub);
		x++;
	}
}

void	analize_map(t_cub *cub)
{
	int		x;

	x = 0;
	analize_char_map(cub, x);
	analize_empty_lines(cub);
	if (cub->error.valid_map == false)
		free_exit(cub, "Invalid Map(empty lines)");
	count_char_map(cub);
	if (cub->error.valid_map == false)
		free_exit(cub, "Invalid Map(strange char)");
	check_map_walls(cub);
}

void	extract_map(t_cub *cub)
{
	int	x;
	int	min;
	int	map_lenght;

	x = 0;
	map_lenght = 0;
	update_last_line(cub);
	min = cub->map->last_line_info;
	cub->map->map_lines = cub->map->map_lines_counter \
		- cub->map->last_line_info;
	cub->map->map = malloc(sizeof(char *) * (cub->map->map_lines + 2));
	while (x < cub->map->map_lines)
	{
		if (map_lenght < (int)ft_strlen(cub->map->file[min]))
			map_lenght = (int)ft_strlen(cub->map->file[min]);
		cub->map->map[x] = ft_strdup(cub->map->file[min]);
		min++;
		x++;
	}
	cub->map->map_lenght = map_lenght;
	cub->map->map[x] = NULL;
}
