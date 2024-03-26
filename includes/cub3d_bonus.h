/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:15:52 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/26 18:19:24 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <limits.h>
# include "libft.h"
# include "../mlx/mlx.h"

# define FACE_MASK 0x3
# define OFFSET_MASK 0x3F
# define TEXTURE_MASK 0xF
# define DIST_MASK 0xFFFFF
# define EAST 0
# define NORTH 1
# define WEST 2
# define SOUTH 3
# define SCREEN_WIDTH 640
# define HALF_WIDTH 320
# define SCREEN_HEIGHT 400
# define FLOOR 0
# define OUTMAP 4294967294
# define DIST_WALK 5
# define FRONT 0
# define LEFT 90
# define RIGHT -90
# define BEHIND 180
# define TURN_RATE 2.0

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	char	**map;
	int		p_y;
	int		p_x;
	int		p_direction;
	int		y_max;
	int		x_max;
}	t_textures;

typedef struct s_grid
{
	int			fov;
	int			half_fov;
	int			proj_plan_width;
	int			proj_plan_height;
	int			half_proj_plan_height;
	int			grid_width;
	int			projected_factor;
	double		angle_incr;
	int			dist_proj_plan;
	char		**map;
	t_textures	*textures;
}	t_grid;

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

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		orientation;
	int			view_y;
	int			moove_head;
	int			x_max;
	int			y_max;
	int			m_d;
	int			moove[5];
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*img_addr;
	int			bpp;
	int			ll;
	int			endian;
	int			flag;
	double		dist_l;
	double		dist_c;
	double		angle[SCREEN_WIDTH];
	char		floor[10];
	char		ceiling[10];
	int			floor_x;
	int			floor_y;
	t_tex		*tex;
	t_player	*player;
	t_grid		*grid;
	t_textures	*textures;
}	t_game;

///////////////Parsing_things///////////////////

int				map_parser(char *argv, t_textures *map_info);
int				map_started(char *str);
int				get_map_y(t_textures *map_utils, char *map_path);
char			*go_to_map(int fd, t_textures *map_utils);
int				build_map_line(t_textures *map_info, char **map,
					int map_y, char *argv);
int				get_textures(char *str, t_textures *map_info);
void			free_tab(char **map);
void			print_textures(t_textures *texture);
void			quit_w_message(char *str, t_textures *map_info);
void			free_textures(t_textures *textures);
int				is_inside(char c);
char			*ft_strdupto_n(char *str, char c);
int				check_end_of_filename(char const *filename, const char *end);
void			print_tab(char **tab);
void			free_tex(t_game *game);
void			set_player(t_textures *map_info, int x, int y, char p);
int				get_f_and_c(char *str, t_textures *map_info);
char			*ft_str_rm_spaces(char *str);
int				atorgb(char *str);
int				init_map(int *i, int *fd, int *player, char *argv);
int				map_started(char *str);
int				ft_open(int *fd, char *path);
void			set_null_map(t_textures *map_info);
int				texture_good(t_textures *map_info);

///////////// Init_things //////////////////

int				init_game(t_game *game, t_textures *textures);
t_grid			*init_grid(t_game *game);
t_player		*init_player(t_game *game);
int				init_textures(t_game *game, t_textures *textures);
void			free_game(t_game *game, t_textures *map_info);

///////////// Maths_things /////////////////

unsigned int	*proj_plan_image(t_game *game, t_grid *grid);
unsigned int	no_fish_eye(t_game *game, unsigned int value, double angle);
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
double			get_ipx(t_player *player, double i_py, double angle);
double			get_ipy(t_player *player, double i_px, double angle);
double			get_xi(double angle);
double			get_yi(double angle);
char			try_get_texture(char **map, int yt, int xt);

//////////// Maths_tests ///////////////////

unsigned int	proj_plan_col_test(t_game *game, double angle);
unsigned int	col_intersections_test(t_game *game, t_player *player,
					double angle);
unsigned int	lines_intersections_test(t_game *game, t_player *player,
					double angle);
unsigned int	intersection_found_test(double angle, t_game *game,
					double pos_x, double pos_y);
unsigned int	*proj_plan_image_test(t_game *game, double orientation);
unsigned int	no_fish_eye_test(t_game *game, unsigned int value,
					double angle);
int				from_dist_to_projected(t_game *game, double angle, double x,
					double y);
void			set_value1(double *y, double *x, double angle, int flag);
void			set_value2lines(double *y, double *x, t_player *player,
					double angle);
void			set_value2col(double *y, double *x, t_player *player,
					double angle);
void			update_ipx(double *ipx, double xi, double angle);
void			update_ipy(double *ipy, double yi, double angle);

///////////// Mlx_things ///////////////////

void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
void			create_col(t_game *game, unsigned int value, int x);
int				render(t_game *game);
int				get_texture_pixel(int projected, unsigned int value,
					t_game *game, int i);
int				loop(void);

//////////// Hook_things ///////////////////

int				handle_close(t_game *game);
int				handle_keypress(int keycode, t_game *game);
int				handle_keyrelease(int keycode, t_game *game);
int				handle_mouse(int keycode, int x, int y, t_game *game);
void			player_move(t_player *player, double angle);
void			player_move_collide(t_game *game, double angle);
void			ft_moove(t_player *player, t_game *game);
void			view_stocked_input(int *moove);

/////////// Hook_tests ////////////////////

int				handle_keypress_test(int keycode, t_game *game);
#endif
