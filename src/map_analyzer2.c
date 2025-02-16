/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analyzer2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:26 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/16 16:50:13 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	get_max_width(char **map, int rows)
{
	int	max_width;
	int	i;
	int	len;

	i = 0;
	(void)rows;
	max_width = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

void	check_map_walls(t_cub *cub)
{
	int		i;
	int		cols;
	char	**fixed_map;

	i = 0;
	cols = get_max_width(cub->map->map, cub->map->map_lines);
	fixed_map = ft_calloc(sizeof(char *), cub->map->map_lines + 2);
	check_walls_p1(cub, cols, fixed_map);
	check_walls_p2(cub, cols, fixed_map);
	check_walls_p3(cub, fixed_map);
	check_walls_p4(cub, cols, fixed_map);
	i = 0;
	while (i < cub->map->map_lines)
	{
		free(cub->map->map[i]);
		i++;
	}
	free(cub->map->map);
	cub->map->map = fixed_map;
	if (cub->error.valid_map == false)
		free_exit(cub, "Invalid Map(walls)");
	return ;
}

void	update_last_line(t_cub *cub)
{
	int	last;

	last = cub->map->last_line_info;
	last++;
	if (!cub->map->file[last])
		free_exit(cub, "Invalid Map");
	if (ft_strlen(cub->map->file[last]) >= 1 && cub->map->file[last][0] == '\n')
		last++;
	if (ft_strlen(cub->map->file[last]) > 1)
		cub->map->last_line_info = last;
}
