/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:10 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/15 17:03:27 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_game(t_cub *cub)
{
	free(cub->game.texture);
}

void	free_double_pointer(char **ptr, int max)
{
	int x;

	x = 0;
	while(x < max)
	{
		free(ptr[x]);
		x++;
	}
	free(ptr);
}

void    free_cub(t_cub *cub)
{
	if(cub->map->file)
		free_double_pointer(cub->map->file, cub->map->map_lines_counter);
	if(cub->map->map)
		free_double_pointer(cub->map->map, cub->map->map_lines);
	if(cub->map->no_file)
		free(cub->map->no_file);
	if(cub->map->so_file)
		free(cub->map->so_file);
	if(cub->map->we_file)
		free(cub->map->we_file);
	if(cub->map->ea_file)
		free(cub->map->ea_file);
	if(cub->map->c_info)
		free(cub->map->c_info);
	if(cub->map->f_info)
		free(cub->map->f_info);
	free(cub->map);
	free_game(cub);
	free(cub);
}

void	free_exit(t_cub *cub, char *msg)
{
	printf("Error!\n");
	printf("%s\n", msg);
	free_game(cub);
	free_cub(cub);
	exit(1);
}
