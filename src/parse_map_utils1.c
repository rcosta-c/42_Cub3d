#include "../includes/cub.h"

void	copy_map_file(t_cub *cub, int x, int coord)
{
	int 	xx;
	char	temp[1024];
	int		z;

	z = 0;
	xx = 2;
	while(cub->map->file[x][xx] == ' ')
	{
		xx++;
	}
	if(cub->map->file[x][xx] == '.')
	{
		xx++;
		if(cub->map->file[x][xx] == '/')
			xx++;
	}
	while(cub->map->file[x][xx] && cub->map->file[x][xx] != '\n')
	{
		temp[z] = cub->map->file[x][xx];
		xx++;
		z++;
	}
	temp[z] = '\0';
	if(coord == 0 && !cub->map->no_file) // 0 = NO
	{
		cub->map->no_file = ft_strdup(temp);
	}
	else if(coord == 1 && !cub->map->so_file) // 0 = SO
	{
		cub->map->so_file = ft_strdup(temp);
	}
	else if(coord == 2 && !cub->map->we_file) // 0 = WE
	{
		cub->map->we_file = ft_strdup(temp);
	}
	else if(coord == 3 && !cub->map->ea_file) // 0 = EA
	{
		cub->map->ea_file = ft_strdup(temp);
	}
	else if(coord == 4 && !cub->map->f_info) // 0 = F
	{
		cub->map->f_info = ft_strdup(temp);
	}
	else if(coord == 5 && !cub->map->c_info) // 0 = C
	{
		cub->map->c_info = ft_strdup(temp);
	}
    cub->map->coords_counter++;
}

void	search_coords(t_cub *cub, int x)
{
	if (ft_strlen(cub->map->file[x]) > 6)
	{
		if (cub->map->file[x][0] == 'N'
				&& cub->map->file[x][1] == 'O'
				&& cub->map->file[x][2] == ' ')
				{
					copy_map_file(cub, x, 0);
				}
		else if(cub->map->file[x][0] == 'S'
				&& cub->map->file[x][1] == 'O'
				&& cub->map->file[x][2] == ' ')
				{
					copy_map_file(cub, x, 1);
				}
		else if(cub->map->file[x][0] == 'W'
				&& cub->map->file[x][1] == 'E'
				&& cub->map->file[x][2] == ' ')
				{
					copy_map_file(cub, x, 2);
				}
		else if(cub->map->file[x][0] == 'E'
				&& cub->map->file[x][1] == 'A'
				&& cub->map->file[x][2] == ' ')
				{
					copy_map_file(cub, x, 3);
				}
		else if (cub->map->file[x][0] == 'C'
				&& cub->map->file[x][1] == ' ')
				{
					copy_map_file(cub, x, 5);
				}
		else if(cub->map->file[x][0] == 'F'
				&& cub->map->file[x][1] == ' ')
				{
					copy_map_file(cub, x, 4);
				}
	}
	else if (ft_strlen(cub->map->file[x]) < 6 && ft_strlen(cub->map->file[x]) > 0
		&& cub->map->file[x][0] != '\n')
	{
		cub->error.char_invalid = true;
		cub->error.valid_map = false;
	}

}

void	validate_info(t_cub *cub)
{
	if (cub->map->coords_counter != 6)
		cub->error.valid_map = false;
	else if (!cub->map->f_info || ft_strlen(cub->map->f_info) < 7)
		cub->error.valid_map = false;
	else if (!cub->map->c_info || ft_strlen(cub->map->c_info) < 7)
		cub->error.valid_map = false;
	else if (!cub->map->no_file || ft_strlen(cub->map->no_file) < 8)
		cub->error.valid_map = false;
	else if (!cub->map->so_file || ft_strlen(cub->map->so_file) < 8)
		cub->error.valid_map = false;
	else if (!cub->map->ea_file || ft_strlen(cub->map->ea_file) < 8)
		cub->error.valid_map = false;
	else if (!cub->map->we_file || ft_strlen(cub->map->we_file) < 8)
		cub->error.valid_map = false;
	else if(cub->map->c_rgb.r < 0 || cub->map->c_rgb.r > 255)
		cub->error.valid_map = false;
	else if(cub->map->c_rgb.g < 0 || cub->map->c_rgb.g > 255)
		cub->error.valid_map = false;
	else if(cub->map->c_rgb.b < 0 || cub->map->c_rgb.b > 255)
		cub->error.valid_map = false;
	else if(cub->map->f_rgb.r < 0 || cub->map->f_rgb.r > 255)
		cub->error.valid_map = false;
	else if(cub->map->f_rgb.g < 0 || cub->map->f_rgb.g > 255)
		cub->error.valid_map = false;
	else if(cub->map->f_rgb.b < 0 || cub->map->f_rgb.b > 255)
		cub->error.valid_map = false;
}


void	split_color_f(t_cub *cub)
{
	char	**res;
	int		x;

	x = 0;
	res = ft_split(cub->map->f_info, ',');
	cub->map->f_rgb.r = ft_atoi(res[0]);
	cub->map->f_rgb.g = ft_atoi(res[1]);
	cub->map->f_rgb.b = ft_atoi(res[2]);

	while(res[x])
	{
		free(res[x]);
		x++;
	}
	free(res);
}

void	split_color_c(t_cub *cub)
{
	char	**res;
	int		x;

	x = 0;
	res = ft_split(cub->map->c_info, ',');
	cub->map->c_rgb.r = ft_atoi(res[0]);
	cub->map->c_rgb.g = ft_atoi(res[1]);
	cub->map->c_rgb.b = ft_atoi(res[2]);

	while(res[x])
	{	free(res[x]);
		x++;
	}
	free(res);
}


void	split_color_process(t_cub *cub)
{
	int	x;
	int	sign;

	sign = 0;
	x = 2;
	while(cub->map->f_info[x])
	{
		if(cub->map->f_info[x] == ',')
			sign++;
		x++;
	}
	if(sign == 2)
		split_color_f(cub);
	sign = 0;
	x = 2;
	while(cub->map->c_info[x])
	{
		if(cub->map->c_info[x] == ',')
			sign++;
		x++;
	}
	if(sign == 2)
		split_color_c(cub);
}

void    map_info_sniffer(t_cub *cub)
{
	int x;

	x = 0;
	while(x < cub->map->map_lines_counter)
	{
		search_coords(cub, x);
		x++;
	}
	split_color_process(cub);
	validate_info(cub);
}
