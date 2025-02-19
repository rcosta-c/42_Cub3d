/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:56:02 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/02/19 16:58:32 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

# include "../lib/mlx/mlx.h"
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <ctype.h>
# include <string.h>
# include <math.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

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

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	cam;
	double	rd_x;
	double	rd_y;
	double	perp;
	int		lh;
	int		ds;
	int		de;
	double	wall_x;
	int		tex_x;
	t_tex	*tex;
}	t_ray;

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
	int		last_line_info;
	int		map_lines_counter;
	int		coords_counter;
	char	*no_file;
	char	*so_file;
	char	*we_file;
	char	*ea_file;
	char	*c_info;
	char	*f_info;

	int		map_lines;
	int		map_lenght;
	char	**map;
	char	**file;
	t_color	f_rgb;
	t_color	c_rgb;

}	t_map;

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
	t_map	*map;
	t_error	error;
	t_game	game;
}	t_cub;

//render_map
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	render_column(t_cub *cub, int x);
void	render_map(t_cub *cub);

//render_utils
void	perform_dda(t_cub *cub, t_ray *ray);
void	compute_ray_direction(t_cub *cub, int x, t_ray *ray);
void	compute_ray_parameters(t_cub *cub, int x, t_ray *ray);
void	compute_wall(t_cub *cub, t_ray *ray);

//render_utils1
void	compute_initial_values(t_cub *cub, t_ray *ray);
void	compute_steps_and_distances(t_cub *cub, t_ray *ray);

//game
int		create_rgb(int r, int g, int b);
int		clean_exit(t_cub *cub);
void	put_pixel_to_img(t_cub *cub, int x, int y, int color);
void	player_moves_vertical(t_cub *cub);
void	player_moves_horizontal(t_cub *cub);
void	load_textures(t_cub *cub);
int		handle_input(int key, t_cub *cub);

//init
void	init_base(t_cub *cub, char **av);
void	init_mlx(t_cub *cub);
void	init_game(t_cub *cub);

//parse_maps
int		map_1st_reading(char *file, t_cub *cub);
int		map_copy(t_cub *cub, char *file);

//parse_map_utils1//
void	map_info_sniffer(t_cub *cub);
void	search_coords(t_cub *cub, int x);
void	search_coords_player(t_cub *cub, int x);
void	split_color_c(t_cub *cub);
void	split_color_process_p1(t_cub *cub);
void	split_color_process_p2(t_cub *cub);
//parse_map_utils2
void	split_color_f(t_cub *cub);
void	copy_map_file(t_cub *cub, int x, int coord);
void	copy_map_file_helper(t_cub *cub, int x, int coord, char *temp);
void	is_readable_texture(char *file, t_cub *cub);

//parse_map_utils3
void	search_coords_error(t_cub *cub, int x);
void	search_coords_error_2(t_cub *cub);
void	validate_color(t_cub *cub);
void	validate_info(t_cub *cub);

//parse_map_utils4
void	count_spaces(char *line, t_cub *cub);
bool	check_end_wall(char *line);
bool	check_begin_wall(char *line);
void	check_wall_integrity(t_cub *cub);

//map_analyzer1
void	extract_map(t_cub *cub);
void	analize_map(t_cub *cub);
void	count_char_map(t_cub *cub);
void	analize_char_map(t_cub *cub, int x);

//map_analyzer2
void	check_map_walls(t_cub *cub);
void	update_last_line(t_cub *cub);

//map_analyzer3
void	check_walls_p1_p1(t_cub *cub, char **fixed_map);
void	check_walls_p1(t_cub *cub, int cols, char **fixed_map);
void	check_walls_p2(t_cub *cub, int cols, char **fixed_map);
void	check_walls_p3(t_cub *cub, char **fixed_map);
void	check_walls_p4(t_cub *cub, int cols, char **fixed_map);

//free
void	free_cub(t_cub *cub);
void	free_game(t_cub *cub);
void	free_exit(t_cub *cub, char *msg);
void	free_double_pointer(char **ptr, int max);

#endif
