/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analyzer4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:22 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/19 17:03:01 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	count_spaces(char *line, t_cub *cub)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(line);
	while (line[x] && (line[x] == ' ' || line[x] == '\n'))
	{
		x++;
	}
	if (x == len)
		free_exit(cub, "Invalid Map(Empty space/line in map)");
}

bool	check_end_wall(char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	while (line[len])
	{
		if (len > 0)
		{
			if (line[len] == '0' && line[len + 1] != '1')
				return (false);
			else if (line[len] == '0' && line[len + 1] == '1')
				return (true);
		}
		len++;
	}
	return (true);
}

bool	check_begin_wall(char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (x > 0)
		{
			if (line[x] == '0' && line[x - 1] != '1')
				return (false);
			else if (line[x] == '0' && line[x - 1] == '1')
				return (true);
		}
		x++;
	}
	return (true);
}

void	check_wall_integrity(t_cub *cub)
{
	int	x;

	x = 0;
	while (cub->map->map[x])
	{
		if (check_begin_wall(cub->map->map[x]) == false
			|| check_end_wall(cub->map->map[x]) == false)
		{
			free_exit(cub, "Invalid Map(walls with holes)");
		}
		x++;
	}
}
