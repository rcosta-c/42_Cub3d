#include "../includes/cub.h"

int clean_exit(t_cub *cub)
{
    int i = 0;
    while (i < 4) {
        if (cub->game.texture[i].img)
            mlx_destroy_image(cub->game.mlx, cub->game.texture[i].img);
        i++;
    }
    if (cub->game.win)
        mlx_destroy_window(cub->game.mlx, cub->game.win);
    if (cub->game.mlx)
        free(cub->game.mlx);
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

void init_game(t_cub *cub)
{
    cub->game.mlx = mlx_init();
    cub->game.win = mlx_new_window(cub->game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    cub->game.img = mlx_new_image(cub->game.mlx, WIN_WIDTH, WIN_HEIGHT);
    cub->game.addr = mlx_get_data_addr(cub->game.img, 
                                         &cub->game.bpp, 
                                         &cub->game.line_len, 
                                         &cub->game.endian);
    cub->game.player_x = 3.5;
    cub->game.player_y = 3.5;
    cub->game.dir_x = -1.0;    // Vetor direcao
    cub->game.dir_y = 0.0;
    cub->game.plane_x = 0.0;   // Plano da camera
    cub->game.plane_y = 0.66;
}
