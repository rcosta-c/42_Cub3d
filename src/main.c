#include "../includes/cub.h"

static bool    validate_avmap(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if(len < 7)
		return(false);
	if(arg[len - 1] == 'b' && arg[len - 2] == 'u' 
		&& arg[len - 3] == 'c' && arg[len - 4] == '.')
	{
		return(true);
	}
	return(false);
}

int game_loop(t_cub *cub)
{
	int x;

	x = 0;
    render_scene(cub); // Renderiza a cena atual
	while(x < 4)
	{
		mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.texture[x].img, cub->game.player_x, cub->game.player_y);
		x++;
	}
    return (0);
}

void start_game(t_cub *cub)
{
    mlx_hook(cub->game.win, 2, 1L << 0, handle_key, cub); // Captura pressionar de teclas
   // mlx_hook(cub->game.win, 3, 1L << 1, handle_key_release, cub); // Captura soltar de teclas
    mlx_hook(cub->game.win, 17, 0L, clean_exit, cub); // Captura fechar a janela
    mlx_loop_hook(cub->game.mlx, game_loop, cub); // Loop contínuo do jogo
    mlx_loop(cub->game.mlx); // Inicia o loop da MiniLibX
}

void	print_tests(t_cub *cub, char **av)
{
		printf("numero de linhas = %d\n ficheiro = %s", cub->map->map_lines_counter, av[1]);

		printf("\n\nNO = %s\n", cub->map->no_file);
		printf("SO = %s\n", cub->map->so_file);
		printf("WE = %s\n", cub->map->we_file);
		printf("EA = %s\n", cub->map->ea_file);

		printf("C = %s\n", cub->map->c_info);
		printf("F = %s\n", cub->map->f_info);
		printf("valores em f_rgb - r=%d  g=%d  b=%d\n\n", cub->map->f_rgb.r, cub->map->f_rgb.g, cub->map->f_rgb.b);
		printf("valores em c_rgb - r=%d  g=%d  b=%d\n\n", cub->map->c_rgb.r, cub->map->c_rgb.g, cub->map->c_rgb.b);
		printf("maplinecounter=%d\n", cub->map->map_lines_counter);
		printf("maplines=%d\n", cub->map->map_lines);

		int xx = 0;
		while(cub->map->map[xx])
		{
			printf("line%d=%s\n", xx, cub->map->map[xx]);
			xx++;
		}	


}


int main(int ac, char **av)
{
	t_cub   *cub;

	cub = ft_calloc(sizeof(t_cub) , 1);
	if (ac != 2)
		return(printf("Error!\n"));
	else
	{
		if(validate_avmap(av[1]) == false)
		{
			printf("Error!\n");
			return (1);
		}
		init_base(cub);
		
		cub->map->map_lines_counter = map_1st_reading(av[1]);
		if (cub->map->map_lines_counter == 0)
		{
			printf("Error!\n");
			return(1);
		}
		cub->map->file = ft_calloc(sizeof(char *) , cub->map->map_lines_counter + 1);
		map_copy(cub, av[1]);

		map_info_sniffer(cub);
		extract_map(cub);
		analize_map(cub);

		init_mlx(cub);

//print_tests(cub, av);

		init_game(cub);
		mlx_hook(cub->game.win, 2, 1L << 0, handle_key, &cub->game);
		
		//render_scene(cub);
    	//mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.texture->img, 0, 0);

		start_game(cub);

		
	//	mlx_loop(cub->game.mlx);

		if(cub->error.valid_map == false)
		{
			printf("A-Error!\n");
			return(1);
		}











	


	}

	free_cub(cub);

	return (0);
}