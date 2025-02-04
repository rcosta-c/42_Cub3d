#include "../includes/cub.h"

void    free_cub(t_cub *cub)
{
	int	x;

	x = 0;
	if(cub->map->file)
	{
		x = 0;
		while(cub->map->file[x])
		{
			free(cub->map->file[x]);
			x++;
		}
		free(cub->map->file);
	}

	if(cub->map->map)
	{
		x = 0;
		while(cub->map->map[x])
		{
			free(cub->map->map[x]);
			x++;
		}
		free(cub->map->map);
	}

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