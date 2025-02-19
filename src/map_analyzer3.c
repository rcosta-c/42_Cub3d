/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analyzer3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:22 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/19 17:01:08 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_walls_p1_p1(t_cub *cub, char **fixed_map)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map->map[i])
	{
		j = 0;
		while (cub->map->map[i][j])
		{
			if (j >= (int)ft_strlen(cub->map->map[i])
				|| ft_isspace(cub->map->map[i][j]))
				fixed_map[i][j] = '1';
			else
				fixed_map[i][j] = cub->map->map[i][j];
			j++;
		}
		i++;
	}
}

void	check_walls_p1(t_cub *cub, int cols, char **fixed_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub->map->map[i])
	{
		fixed_map[i] = ft_calloc(sizeof(char), cols + 1);
		j = 0;
		while (j <= cols)
		{
			fixed_map[i][j] = '1';
			j++;
		}
		fixed_map[i][cols] = '\0';
		i++;
	}
	check_walls_p1_p1(cub, fixed_map);
}

void	check_walls_p2(t_cub *cub, int cols, char **fixed_map)
{
	int	i;

	i = 0;
	while (i < cols - 1)
	{
		if (fixed_map[0][i] != '1')
		{
			cub->error.valid_map = false;
			break ;
		}
		i++;
	}
	i = 0;
	while (fixed_map[cub->map->map_lines - 1][i])
	{
		if (fixed_map[cub->map->map_lines - 1][i] != '1')
		{
			cub->error.valid_map = false;
			break ;
		}
		i++;
	}
}

void	check_walls_p3(t_cub *cub, char **fixed_map)
{
	int	i;
	int	temp;

	i = 0;
	while (fixed_map[i])
	{
		temp = ft_strlen(fixed_map[i]);
		if (fixed_map[i][0] != '1' || fixed_map[i][temp - 1] != '1')
		{
			cub->error.valid_map = false;
			break ;
		}
		i++;
	}
}

void	check_walls_p4(t_cub *cub, int cols, char **fixed_map)
{
	int	i;
	int	j;

	i = 1;
	while (i < cub->map->map_lines - 1)
	{
		j = 1;
		while (j < cols - 1)
		{
			if (fixed_map[i][j] == '0' || fixed_map[i][j] == 'N'
				|| fixed_map[i][j] == 'S' || fixed_map[i][j] == 'E'
				|| fixed_map[i][j] == 'W')
			{
				if (fixed_map[i - 1][j] == ' ' || fixed_map[i + 1][j] == ' ' ||
					fixed_map[i][j - 1] == ' ' || fixed_map[i][j + 1] == ' ')
				{
					cub->error.valid_map = false;
					break ;
				}
			}
			j++;
		}
		i++;
	}
}
