#include "../includes/cub.h"

static int create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

int clean_exit(t_cub *cub)
{
    int i = 0;
    while (i < 4)
    {
        if(cub->game.texture[i].img)
        {
            mlx_destroy_image(cub->game.mlx, cub->game.texture[i].img);
        }
        i++;
    }
    mlx_destroy_image(cub->game.mlx, cub->game.img);
    mlx_destroy_window(cub->game.mlx, cub->game.win); 
	mlx_destroy_display(cub->game.mlx);
    free(cub->game.mlx);
    free_cub(cub);
    exit(0);
}

void put_pixel_to_img(t_cub *cub, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		char	*dst;

		dst = cub->game.addr + (y * cub->game.line_len + x * (cub->game.bpp / 8));
		*(unsigned int*)dst = color;
	}
}
void player_moves(t_cub *cub)
{
    if(cub->game.player == 'N')
	{
        cub->game.dir_y = -1.0; // Direção inicial (virado para Norte)
        cub->game.dir_x = 0;
        cub->game.plane_x = 0.8;   // Plano da camera
        cub->game.plane_y = 0.0;
    }

	if(cub->game.player == 'S')
	{
        cub->game.dir_y = 1.0;
        cub->game.dir_x = 0;
        cub->game.plane_x = -0.8;   // Plano da camera
        cub->game.plane_y = 0.0;
    }
	if(cub->game.player == 'W')
	{
        cub->game.dir_y = 0;
    	cub->game.dir_x = -1.0;
        cub->game.plane_x = 0.1;   // Plano da camera
        cub->game.plane_y = -0.8;
    }
	if(cub->game.player == 'E')
	{
        cub->game.dir_y = 0;
        cub->game.dir_x = 1.0;
        cub->game.plane_x = 0.1;   // Plano da camera
        cub->game.plane_y = 0.8;
    }
}

void init_game(t_cub *cub)
{
    cub->game.mlx = mlx_init();
    cub->game.win = mlx_new_window(cub->game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    cub->game.img = mlx_new_image(cub->game.mlx, WIN_WIDTH, WIN_HEIGHT);
    cub->game.addr = mlx_get_data_addr(cub->game.img, 
                                         &cub->game.bpp, 
                                         &cub->game.line_len, 
                                         &cub->game.endian);
    player_moves(cub);
    cub->game.floor_color = create_rgb(cub->map->f_rgb.r, cub->map->f_rgb.g, cub->map->f_rgb.b);
    cub->game.ceiling_color = create_rgb(cub->map->c_rgb.r, cub->map->c_rgb.g, cub->map->c_rgb.b);
}
