#include "../includes/cub.h"

void    analize_char_map(t_cub *cub, int x)
{
   	bool	flag;
    int     xx;

    flag = true;
    while(cub->map->map[x])
	{
		xx = 0;
		while(cub->map->map[x][xx])
		{
			if(cub->map->map[x][xx] == '\n' || cub->map->map[x][xx] == '0'
				|| cub->map->map[x][xx] == '1' ||cub->map->map[x][xx] == 'N'
				|| cub->map->map[x][xx] == 'S' || cub->map->map[x][xx] == 'W'
				|| cub->map->map[x][xx] == 'E' || cub->map->map[x][xx] == ' ')
				xx++;
			else
			{
				flag = false;
				break;
			}
		}
		x++;
	}
	if (flag == false)
		cub->error.valid_map = false;
}

void    count_char_map(t_cub *cub)
{
    int counter;
    int x;
    int xx;

    x = 0;
    counter = 0;
	if(cub->error.valid_map == false)
		return;
	while(cub->map->map[x])
	{
		xx = 0;
		while(cub->map->map[x][xx])
		{
			if(cub->map->map[x][xx] == 'N' || cub->map->map[x][xx] == 'S' || cub->map->map[x][xx] == 'W' || cub->map->map[x][xx] == 'E')
			{
				cub->game.player = cub->map->map[x][xx];
				cub->game.player_x = x;
				cub->game.player_y = xx;
				counter++;
			}
			xx++;
		}
		x++;
	}
	if (counter > 4)
		cub->error.valid_map = false;
}

void	analize_map(t_cub *cub)
{
	int		x;

    x = 0;
    analize_char_map(cub, x);
	count_char_map(cub);
	if(cub->error.valid_map == false)
		return;
	check_map_walls(cub);
}

void	extract_map(t_cub *cub)
{
	int	min;
	int	x;

	x = 0;
	min = cub->map->map_lines_counter - 1;
	while(cub->map->file[min])
	{
		if(ft_strlen(cub->map->file[min]) == 1 && cub->map->file[min][0] == '\n')
			break;
		min--;
	}
	cub->map->map = malloc(sizeof(char *) * (cub->map->map_lines_counter - min + 1));
	cub->map->map_lines = cub->map->map_lines_counter - min;
	min++;
	while(min < cub->map->map_lines_counter)
	{
		cub->map->map[x] = ft_strdup(cub->map->file[min]);
		min++;
		x++;
	}
	cub->map->map[x] = NULL;
}