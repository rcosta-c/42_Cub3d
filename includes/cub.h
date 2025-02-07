#ifndef CUB3D_H
# define CUB3D_H

#include "../lib/mlx/mlx.h"
#include "../lib/libft/libft.h"
#include "../lib/gnl/get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
//#include <mlx.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_error
{
	bool	valid_map;
	bool	no_invalid;
	bool	so_invalid;
	bool	we_invalid;
	bool	ea_invalid;
	bool	char_invalid;
	bool	f_invalid;
	bool	c_invalid;
	bool	valid_color;

}	t_error;

typedef struct s_map
{
	int		map_lines_counter;
	int		coords_counter;
	char	*no_file;
	char	*so_file;
	char	*we_file;
	char	*ea_file;
	char	*c_info;
	char	*f_info;
	int 	fd_no;
	int 	fd_so;
	int 	fd_we;
	int 	fd_ea;
	int		map_lines;
	char    **map;
	char	**file;
	t_color	f_rgb;
	t_color	c_rgb;

}   t_map;

typedef struct s_tex
{
	void	*img;
	char	*path;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_tex;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;

	int		floor_color;
	int		ceiling_color;
	char	player;
	double	plane_x;
	double	plane_y;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	t_tex	*texture;
}	t_game;

typedef struct s_cub
{
	t_map   *map;
	t_error	error;
	t_game	game;
}   t_cub;


//game
int		handle_key(t_cub *cub, int key);
int		clean_exit(t_cub *cub);
void	init_game(t_cub *cub);
void	render_scene(t_cub *cub);








//init
void    init_base(t_cub *cub);
void    init_mlx(t_cub *cub);


//parse_maps
int		map_1st_reading(char *file);
int		map_copy(t_cub *cub, char *file);


//parse_map_utils1//
void    map_info_sniffer(t_cub *cub);
void	search_coords(t_cub *cub, int x);
void	copy_map_file(t_cub *cub, int x, int coord);


//map_analyzer1
void	extract_map(t_cub *cub);
void	analize_map(t_cub *cub);
void    count_char_map(t_cub *cub);
void    analize_char_map(t_cub *cub, int x);


//map_analyzer2
void    check_map_walls(t_cub *cub);


//free
void    free_cub(t_cub *cub);


#endif