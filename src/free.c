#include "../includes/cub.h"

void	free_game(t_cub *cub)
{
	int x;

	(void)cub;
	x = 0;
	while(x < 4)
	{
	//	if (cub->game.texture[x].path)
	//		free(cub->game.texture[x].path);
		x++;
	}
	/*free(cub->game.texture);
	if (cub->game.addr)
		free(cub->game.addr);*/
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
