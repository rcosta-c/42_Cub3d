#include "../includes/cub.h"

static int get_max_width(char **map, int rows)
{
    int max_width;
    int i;
    int len;

    i = 0;
    (void)rows;
    max_width = 0;
    while (map[i])
    {
        len = ft_strlen(map[i]);
        if (len > max_width)
            max_width = len;
        i++;
    }
    return max_width;
}

void check_map_walls(t_cub *cub)
{
    int i = 0;
    int j = 0;
    int cols;
    char **fixed_map;
    int temp;

    cols = get_max_width(cub->map->map, cub->map->map_lines);
    fixed_map = ft_calloc(sizeof(char *), cub->map->map_lines + 2);
    while(cub->map->map[i])
    {
        fixed_map[i] = ft_calloc(sizeof(char), cols + 1);
        j = 0;
        while(j <= cols)
        {
            fixed_map[i][j] = '1';
            j++;
        }
        fixed_map[i][cols] = '\0';
        i++;
    }
    i = 0;
    while (cub->map->map[i])
    {
        j = 0;
        while (cub->map->map[i][j])
        {
            if (j >= (int)ft_strlen(cub->map->map[i]) || ft_isspace(cub->map->map[i][j])) 
                fixed_map[i][j] = '1';
            else
                fixed_map[i][j] = cub->map->map[i][j];
            j++;
        }
        i++;
    }
    i = 0;
    while (i < cols - 1)
    {
        if (fixed_map[0][i] != '1')
        {
            cub->error.valid_map = false;
            break ;
        }
        i++;
    }
    i = 0;
    while (fixed_map[cub->map->map_lines - 2][i])
    {
        if (fixed_map[cub->map->map_lines - 2][i] != '1')
        {
            cub->error.valid_map = false;
            break ;
        }
        i++;
    }
    i = 0;
    while (fixed_map[i])
    {
        temp = ft_strlen(fixed_map[i]);
        if (fixed_map[i][0] != '1' || fixed_map[i][temp - 1] != '1')
        {
            cub->error.valid_map = false;
            break ;
        }
        i++;
    }
    i = 1;
    while (i < cub->map->map_lines - 1)
    {
        j = 1;
        while (j < cols - 1) {
            if (fixed_map[i][j] == '0' || fixed_map[i][j] == 'N' || fixed_map[i][j] == 'S' || fixed_map[i][j] == 'E' || fixed_map[i][j] == 'W') {
                if (fixed_map[i - 1][j] == ' ' || fixed_map[i + 1][j] == ' ' ||
                    fixed_map[i][j - 1] == ' ' || fixed_map[i][j + 1] == ' ') {
                    {
                        cub->error.valid_map = false;
                        break ;
                    }
                }
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < cub->map->map_lines)
    {
        free(cub->map->map[i]);
        i++;
    }
    free(cub->map->map);
    cub->map->map = fixed_map;
    return;
}

