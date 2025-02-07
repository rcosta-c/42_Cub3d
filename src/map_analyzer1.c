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
		free_exit(cub, "Invalid Map(strange char)");
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
		free_exit(cub, "Invalid Map(wrong number of coords)");
}


void	analize_empty_lines(t_cub *cub)
{
	int x;
	int xx;
	int counter;
	
	x = 0;
	while(cub->map->map[x] && x < cub->map->map_lines)
	{
		xx = 0;
		counter = 0;
		while(cub->map->map[x][xx])
		{
			if(ft_strlen(cub->map->map[x]) > 0
				&& (cub->map->map[x][xx] != ' ' || cub->map->map[x][xx] != '\n'))
			{
				counter++;
			}
			xx++;
		}
		if(counter == 0)
		{
			cub->error.valid_map = false;
			return;
		}
		x++;
	}
}

void	analize_map(t_cub *cub)
{
	int		x;

    x = 0;
    analize_char_map(cub, x);
	analize_empty_lines(cub);
	if(cub->error.valid_map == false)
		free_exit(cub, "Invalid Map(empty lines)");
	count_char_map(cub);
	if(cub->error.valid_map == false)
		free_exit(cub, "Invalid Map(strange char)");
	check_map_walls(cub);
}

void	update_last_line(t_cub *cub)
{
	int last;

	last = cub->map->last_line_info;
	last++;
	if(ft_strlen(cub->map->file[last]) >= 1 && cub->map->file[last][0] == '\n')
		last++;
	if(ft_strlen(cub->map->file[last]) > 1)
		cub->map->last_line_info = last;
}

void	extract_map(t_cub *cub)
{
	int x;
	int min;

	x = 0;
	update_last_line(cub);
	min = cub->map->last_line_info;
	cub->map->map_lines = cub->map->map_lines_counter - cub->map->last_line_info;
	cub->map->map = malloc(sizeof(char *) * (cub->map->map_lines + 2));
	while(x < cub->map->map_lines)
	{
		cub->map->map[x] = ft_strdup(cub->map->file[min]);
		min++;
		x++;
	}
	cub->map->map[x] = NULL;
}