#include "../includes/cub.h"



bool    validate_avmap(char *arg)
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

int main(int ac, char **av)
{
	t_cub   *cub;

	cub = malloc(sizeof(t_cub) * 1);
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
		cub->map->file = malloc(sizeof(char *) * cub->map->map_lines_counter + 1);
		map_copy(cub, av[1]);

		map_info_sniffer(cub);
		extract_map(cub);
		analize_map(cub);


		if(cub->error.valid_map == false)
		{
			printf("AAAA-Error!\n");
			return(1);
		}











		printf("numero de linhas = %d\n ficheiro = %s", cub->map->map_lines_counter, av[1]);

		printf("\n\nNO = %s\n", cub->map->no_file);
		printf("SO = %s\n", cub->map->so_file);
		printf("WE = %s\n", cub->map->we_file);
		printf("EA = %s\n", cub->map->ea_file);

		printf("C = %s\n", cub->map->c_info);
		printf("F = %s\n", cub->map->f_info);
		printf("valores em f_rgb - r=%d  g=%d  b=%d\n\n", cub->map->f_rgb.r, cub->map->f_rgb.g, cub->map->f_rgb.b);
		printf("valores em c_rgb - r=%d  g=%d  b=%d\n\n", cub->map->c_rgb.r, cub->map->c_rgb.g, cub->map->c_rgb.b);

		int xx = 0;
		while(cub->map->map[xx])
		{
			printf("line%d=%s", xx, cub->map->map[xx]);
			xx++;
		}


	}

	free_cub(cub);

	return (0);
}