#include "../includes/cub.h"


int	map_copy(t_cub *cub, char *file)
{
	char	*line;
	int		x;
	int     fd;

	x = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		printf("Error opening the file(map)");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		else
		{
			cub->map->file[x] = ft_strdup(line);
		}
		free(line);
		x++;
	}
	cub->map->file[x] = '\0';
	close(fd);
	return(x);
}

int	map_1st_reading(char *file)
{
	char	*line;
	int		x;
	int     fd;

	x = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return(x);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		free(line);
		x++;
	}
	close(fd);
	return(x);
}


