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
    render_map(cub);
    mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.img, 0, 0);
    return (0);
}

void start_game(t_cub *cub)
{

    init_game(cub);
    load_textures(&cub->game, cub->map);
    mlx_hook(cub->game.win, 2, 1L << 0, handle_input, cub);
    mlx_loop_hook(cub->game.mlx, game_loop, cub);
    mlx_loop(cub->game.mlx);
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
    t_cub *cub;

    if (ac != 2)
    {
        printf("Error! Only 1 map as argument\n");
        return (1);
    }
    cub = ft_calloc(1, sizeof(t_cub));
    if (!cub)
        return (1);
    if (validate_avmap(av[1]) == false)
        free_exit(cub, "Not a Cub file");
    init_base(cub, av);
    if (cub->map->map_lines_counter == 0)
        free_exit(cub, "Empty Map");
    map_copy(cub, av[1]);
    map_info_sniffer(cub);
    extract_map(cub);
    analize_map(cub);
    init_mlx(cub);
    start_game(cub);
    free_cub(cub);
    return (0);
}
