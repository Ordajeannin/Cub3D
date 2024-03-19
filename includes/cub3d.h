/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:15:52 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/19 17:20:25 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include <limits.h>
#include "libft.h"
#include "../mlx/mlx.h"

#define FACE_MASK 0x3
#define OFFSET_MASK 0x3F
#define TEXTURE_MASK 0xF
#define DIST_MASK 0xFFFFF
#define EAST 0
#define NORTH 1
#define WEST 2
#define SOUTH 3
#define SCREEN_WIDTH 640
#define HALF_WIDTH 320
#define SCREEN_HEIGHT 400
#define FLOOR 0
#define OUTMAP UINT_MAX - 1
#define DIST_WALK 5
#define FRONT 0
#define LEFT 90
#define RIGHT -90
#define BEHIND 180
#define TURN_RATE 2.0

typedef struct s_textures
{
	char *no;
	char *so;
	char *we;
	char *ea;
	int f;
	int c;
	char **map;
	int p_y;
	int p_x;
	int p_direction;
	int y_max;
	int x_max;
} t_textures;

typedef struct s_grid
{
	int fov;
	int half_fov;
	int proj_plan_width;
	int proj_plan_height;
	int half_proj_plan_height;
	int grid_width;
	int projected_factor;
	double angle_incr;
	int		dist_proj_plan;
	char **map;
	t_textures *textures;
} t_grid;

typedef struct s_image
{
	void	*im_ptr;
	char	*im_addr;
	int		im_width;
	int		im_height;
	int		bpp;
	int		endian;
	int		line_size;
}	t_image;

typedef struct s_tex
{
	t_image	image[4];
	void	*next;
}	t_tex;

// typedef struct s_walls
// {
// 	void 	*no_side_im;
// 	char 	*no_side_addr;
// 	int		no_im_width;
// 	int		no_im_height;
// 	int		no_bpp;
// 	int		no_endian;
// 	int		no_l_size;
// 	void 	*so_side_im;
// 	char 	*so_side_addr;
// 	void	*ea_side_im;
// 	char 	*ea_side_addr;
// 	void	*we_side_im;
// 	char 	*we_side_addr;
// 	// void	*next;
// } t_walls;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double	orientation;
	int		x_max;
	int		y_max;
	int		m_d;
}	t_player;

typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;
	void *img_addr;
	int bpp;
	int ll;
	int endian;
	// t_walls	*walls;
	t_tex	*tex;
	t_player *player;
	t_grid *grid;
	t_textures *textures;
} t_game;

///////////////Map_things///////////////////

int map_parser(char *argv, t_textures *map_info);
int map_started(char *str);
int get_map_y(t_textures *map_utils, char *map_path);
char *go_to_map(int fd, t_textures *map_utils);
int build_map_line(t_textures *map_info, char **map, int map_y, char *argv);
int get_textures(char *str, t_textures *map_info);
void free_tab(char **map);
void print_textures(t_textures *texture);
void quit_w_message(char *str, t_textures *map_info);
void free_textures(t_textures *textures);
int is_inside(char c);
char *ft_strdupto_n(char *str, char c);
int check_end_of_filename(char const *filename, const char *end);
void	print_tab(char **tab);
void	free_tex(t_game *game);
void	set_player(t_textures *map_info, int x, int y, char p);

///////////// Init_things //////////////////

int init_game(t_game *game, t_textures *textures);
t_grid *init_grid(t_game *game);
t_player *init_player(t_game *game);
int		init_textures(t_game *game, t_textures *textures);

///////////// Maths_things /////////////////

unsigned int	*proj_plan_image(t_game *game, t_grid *grid);
unsigned int	no_fish_eye(t_game *game, unsigned int value, double angle);
unsigned int	intersection_found(double angle, int distance, char **map,
					int flag, int pos_x, int pos_y);
unsigned int	lines_intersections(t_player *player,
					t_grid *grid, double angle);
unsigned int	col_intersections(t_player *player, t_grid *grid, double angle);
unsigned int	proj_plan_col(t_game *game, double angle);
double			dtor(double degrees);
double			rtod(double radian);
double			double_modulo(double value, double modulo);
double			ft_dist(double x1, double x2, double y1, double y2);
int				get_value(unsigned int value, const char *flag);
void			view_stocked_image(unsigned int *stock);
void			view_stocked_col(unsigned int stock);
void			max_dist(t_game *game);
double				get_ipx(t_player *player, double i_py, double angle);
double				get_ipy(t_player *player, double i_px, double angle);
char			try_get_texture(char **map, int yt, int xt);

//////////// Maths_tests ///////////////////

unsigned int	proj_plan_col_test(t_game *game, double angle);
unsigned int	col_intersections_test(t_game *game, t_player *player, double angle);
unsigned int	lines_intersections_test(t_game *game, t_player *player, double angle);
unsigned int	intersection_found_test(double angle, double dist, t_game *game, int flag, int pos_x, int pos_y);
unsigned int	*proj_plan_image_test(t_game *game, double orientation);
unsigned int	no_fish_eye_test(t_game *game, unsigned int value, double angle);

///////////// Mlx_things ///////////////////

void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	create_col(t_game *game, unsigned int value, int x);
int		render(t_game *game);
int		get_texture_pixel(int projected, unsigned int value, t_game *game, int y, int i);
int loop();

//////////// Hook_things ///////////////////
//
int handle_close(t_game *game);
int handle_keypress(int keycode, t_game *game);
int handle_mouse(int keycode, int x, int y, t_game *game);
void player_move(t_player *player, double angle);
void player_move_collide(t_game *game, double angle);
#endif
