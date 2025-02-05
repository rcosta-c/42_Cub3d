#include "../includes/cub.h"

void    init_base(t_cub *cub)
{
	cub->map = ft_calloc(sizeof(t_map) , 1);
    cub->error.valid_map = true;
    cub->error.no_invalid = true;
    cub->error.so_invalid = true;
    cub->error.we_invalid = true;
    cub->error.ea_invalid = true;
    cub->error.char_invalid = true;
    cub->error.f_invalid = true;
    cub->error.c_invalid = true;

    cub->map->coords_counter = 0;
    cub->map->fd_no = -1;
    cub->map->fd_so = -1;
    cub->map->fd_we = -1;
    cub->map->fd_ea = -1;

}