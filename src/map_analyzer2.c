#include "../includes/cub.h"

static int get_max_width(char **map, int rows)
{
    int max_width = 0;
    int i = 0;

    while (i < rows) {
        int len = ft_strlen(map[i]);
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

    cols = get_max_width(cub->map->map, cub->map->map_lines);
    fixed_map = malloc(cub->map->map_lines + 1 * sizeof(char *));
    while (i < cub->map->map_lines)
    {
        fixed_map[i] = malloc(cols + 1);
        j = 0;
        while (j < cols) {
            if (j >= (int)ft_strlen(cub->map->map[i]) || isspace(cub->map->map[i][j])) 
                fixed_map[i][j] = '1';
            else
                fixed_map[i][j] = cub->map->map[i][j];
            j++;
        }
        fixed_map[i][cols] = '\0';
        i++;
    }
    i = 0;
    while (i < cols) {
        if (fixed_map[0][i] != '1' || fixed_map[cub->map->map_lines - 1][i] != '1')
            exit(cub->error.valid_map = false);
        i++;
    }
    i = 0;
    while (i < cub->map->map_lines) {
        if (fixed_map[i][0] != '1' || fixed_map[i][cols - 1] != '1')
            exit(cub->error.valid_map = false);
        i++;
    }
    i = 1;
    while (i < cub->map->map_lines - 1) {
        j = 1;
        while (j < cols - 1) {
            if (fixed_map[i][j] == '0' || fixed_map[i][j] == 'N' || fixed_map[i][j] == 'S' || fixed_map[i][j] == 'E' || fixed_map[i][j] == 'W') {
                if (fixed_map[i - 1][j] == ' ' || fixed_map[i + 1][j] == ' ' ||
                    fixed_map[i][j - 1] == ' ' || fixed_map[i][j + 1] == ' ') {
                    exit(cub->error.valid_map = false);
                }
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < cub->map->map_lines)
    {
        free(fixed_map[i]);
        i++;
    }
    free(fixed_map);
    return;
}

