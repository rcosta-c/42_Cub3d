#include "../includes/cub.h"

static int create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

static int is_valid_move(t_cub *cub, double new_x, double new_y)
{
    if (cub->map->map[(int)new_y][(int)new_x] == '0')
	{
        return 1; // Movimento permitido
    }
    return 0; // Movimento bloqueado por parede
}

static void load_texture(t_cub *cub, int x, char *path)
{
    cub->game.texture[x].img = mlx_xpm_file_to_image(cub->game.mlx, path, 
		&cub->game.texture[x].width, &cub->game.texture[x].height);
    if (!cub->game.texture[x].img)
        free_exit(cub, "Loading Texture");
    cub->game.texture[x].addr = (int *)mlx_get_data_addr(cub->game.texture[x].img,
		&cub->game.texture[x].bpp, 
		&cub->game.texture[x].line_len,
		&cub->game.texture[x].endian);
}

int handle_key(t_cub *cub, int key) 
{
    double	new_x;
	double	new_y;
	double	old_dir_x;
	double	old_plane_x;

    if (key == KEY_ESC)
	{
		clean_exit(cub);
		exit(1);
	}

    // Movimento para frente (W)
    if (key == KEY_W) {
        new_x = cub->game.player_x + cub->game.dir_x * MOVE_SPEED;
        new_y = cub->game.player_y + cub->game.dir_y * MOVE_SPEED;
        if (is_valid_move(cub, new_x, new_y))
		{
			cub->game.player_x = new_x;
			cub->game.player_y = new_y;
        }
    }
    // Movimento para trás (S)
    if (key == KEY_S)
	{
        new_x = cub->game.player_x - cub->game.dir_x * MOVE_SPEED;
        new_y = cub->game.player_y - cub->game.dir_y * MOVE_SPEED;
        if (is_valid_move(cub, new_x, new_y))
		{
			cub->game.player_x = new_x;
			cub->game.player_y = new_y;
        }
    }
    // Movimento para a esquerda (A)
    if (key == KEY_A)
	{
        new_x = cub->game.player_x - cub->game.plane_x * MOVE_SPEED;
        new_y = cub->game.player_y - cub->game.plane_y * MOVE_SPEED;
        if (is_valid_move(cub, new_x, new_y))
		{
			cub->game.player_x = new_x;
			cub->game.player_y = new_y;
        }
    }
    // Movimento para a direita (D)
    if (key == KEY_D) {
        new_x = cub->game.player_x + cub->game.plane_x * MOVE_SPEED;
        new_y = cub->game.player_y + cub->game.plane_y * MOVE_SPEED;
        if (is_valid_move(cub, new_x, new_y))
		{
			cub->game.player_x = new_x;
			cub->game.player_y = new_y;
        }
    }
    // Rotação para a esquerda (seta esquerda)
    if (key == KEY_LEFT)
	{
        old_dir_x = cub->game.dir_x;
        cub->game.dir_x = cub->game.dir_x * cos(-ROT_SPEED) - cub->game.dir_y * sin(-ROT_SPEED);
        cub->game.dir_y = old_dir_x * sin(-ROT_SPEED) + cub->game.dir_y * cos(-ROT_SPEED);
        
        old_plane_x = cub->game.plane_x;
        cub->game.plane_x = cub->game.plane_x * cos(-ROT_SPEED) - cub->game.plane_y * sin(-ROT_SPEED);
        cub->game.plane_y = old_plane_x * sin(-ROT_SPEED) + cub->game.plane_y * cos(-ROT_SPEED);
    }
    // Rotação para a direita (seta direita)
    if (key == KEY_RIGHT)
	{
        old_dir_x = cub->game.dir_x;
        cub->game.dir_x = cub->game.dir_x * cos(ROT_SPEED) - cub->game.dir_y * sin(ROT_SPEED);
        cub->game.dir_y = old_dir_x * sin(ROT_SPEED) + cub->game.dir_y * cos(ROT_SPEED);
        
        old_plane_x = cub->game.plane_x;
        cub->game.plane_x = cub->game.plane_x * cos(ROT_SPEED) - cub->game.plane_y * sin(ROT_SPEED);
        cub->game.plane_y = old_plane_x * sin(ROT_SPEED) + cub->game.plane_y * cos(ROT_SPEED);
    }

    return 0;
}

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
	if (!cub->game.mlx)
		free_exit(cub, "Mlx error");

	cub->game.win = mlx_new_window(cub->game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!cub->game.win)
        free_exit(cub, "Mlx win error");

	cub->game.img = mlx_new_image(cub->game.mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->game.addr = mlx_get_data_addr(cub->game.img, &cub->game.bpp, &cub->game.line_len, &cub->game.endian);

	cub->game.floor_color = create_rgb(cub->map->f_rgb.r, cub->map->f_rgb.g, cub->map->f_rgb.b);
	cub->game.ceiling_color = create_rgb(cub->map->c_rgb.r, cub->map->c_rgb.g, cub->map->c_rgb.b);

	load_texture(cub, 0, cub->map->no_file);
	load_texture(cub, 1, cub->map->so_file);
	load_texture(cub, 2, cub->map->we_file);
	load_texture(cub, 3, cub->map->ea_file);

	cub->game.dir_x = 0.0;
	cub->game.dir_y = 0.0;
	if(cub->game.player == 'N')
		cub->game.dir_x = -1.0; // Direção inicial (virado para Norte)
	if(cub->game.player == 'S')
		cub->game.dir_x = 1.0;
	if(cub->game.player == 'W')
		cub->game.dir_y = -1.0;
	if(cub->game.player == 'E')
		cub->game.dir_y = 1.0;
}

void render_scene(t_cub *cub)
{
    int x = 0;

    while (x < WIN_WIDTH)
	{
        // Calcula a posição do raio na câmara
        double camera_x = 2 * x / (double)WIN_WIDTH - 1;
        double ray_dir_x = cub->game.dir_x + cub->game.plane_x * camera_x;
        double ray_dir_y = cub->game.dir_y + cub->game.plane_y * camera_x;

        // Posição inicial do jogador no mapa
        int map_x = (int)cub->game.player_x;
        int map_y = (int)cub->game.player_y;

        // Distância percorrida pelo raio em cada eixo
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);

        // Passo da DDA
        int step_x, step_y;
        double side_dist_x, side_dist_y;

        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (cub->game.player_x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - cub->game.player_x) * delta_dist_x;
        }

        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (cub->game.player_y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - cub->game.player_y) * delta_dist_y;
        }

        // Algoritmo DDA (Digital Differential Analysis)
        int hit = 0;
        int side;
        while (hit == 0) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (cub->map->map[map_y][map_x] == '1') hit = 1;
        }

        // Calcula a distância até a parede
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - cub->game.player_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - cub->game.player_y + (1 - step_y) / 2) / ray_dir_y;

        // Calcula a altura da linha a ser desenhada
        int line_height = (int)(WIN_HEIGHT / perp_wall_dist);

        // Calcula onde começa e termina a parede na tela
        int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + WIN_HEIGHT / 2;
        if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

        // Define cor baseada na direção do impacto
        int color = (side == 1) ? 0xAAAAAA : 0xFFFFFF;

        // Desenha a linha vertical representando a parede
        int y = draw_start;
        while (y < draw_end)
		{
			put_pixel_to_img(cub, x, y, color);
            y++;
        }

        x++;
    }
	mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.img, 0, 0);

}
