/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:02:02 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/16 17:07:48 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static bool	validate_avmap(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len < 7)
		return (false);
	if (arg[len - 1] == 'b' && arg[len - 2] == 'u'
		&& arg[len - 3] == 'c' && arg[len - 4] == '.')
	{
		return (true);
	}
	return (false);
}

int	game_loop(t_cub *cub)
{
	render_map(cub);
	mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.img, 0, 0);
	return (0);
}

int	free_all(t_cub *cub)
{
	free_game(cub);
	exit(0);
}

void	start_game(t_cub *cub)
{
	init_game(cub);
	load_textures(cub);
	mlx_hook(cub->game.win, 2, 1L << 0, handle_input, cub);
	mlx_hook(cub->game.win, 17, 0, clean_exit, cub);
	mlx_loop_hook(cub->game.mlx, game_loop, cub);
	mlx_loop(cub->game.mlx);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
	{
		printf("Error!\nOnly 1 map as argument\n");
		return (1);
	}
	if (validate_avmap(av[1]) == false)
	{
		printf("Error!\nNot a Cub file\n");
		return (1);
	}
	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		return (1);
	init_base(cub, av);
	if (cub->map->map_lines_counter == 0)
		free_exit(cub, "Empty Map");
	map_copy(cub, av[1]);
	map_info_sniffer(cub);
	extract_map(cub);
	analize_map(cub);
	init_mlx(cub);
	start_game(cub);
	return (0);
}
