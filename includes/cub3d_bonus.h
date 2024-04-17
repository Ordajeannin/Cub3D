/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:15:52 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/17 16:25:25 by ajeannin         ###   ########.fr       */
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
# include <sys/time.h>
# include "libft.h"
# include "../mlx/mlx.h"

# define FACE_MASK 0x3
# define OFFSET_MASK 0x3F
# define TEXTURE_MASK 0xFF
# define DIST_MASK 0xFFFF
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
# define SKY_WIDTH 800.0
# define SKY_HEIGHT 600
# define FPS_MAX 30
# define SPHERE 2

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
	char	name;
	t_image	image[4];
	void	*next;
}	t_tex;

typedef struct s_player
{
	double		pos_x;
	double		temp_x;
	double		pos_y;
	double		temp_y;
	double		orientation;
	int			view_y;
	int			moove_head;
	int			x_max;
	int			y_max;
	int			m_d;
	int			moove[5];
}	t_player;

typedef	struct s_sprite
{
	t_image	pacman[8];
}	t_sprite;


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
	char		*map_used;
	double		angle[SCREEN_WIDTH];
	char		*floor;
	char		*ceiling;
	char		*wall;
	double			floor_x;
	double			floor_y;
	struct timeval	time;
	t_sprite	*sprite;
	t_tex		*tex;
	t_player	*player;
	t_grid		*grid;
	t_textures	*textures;
}	t_game;

///////////////Parsing_things///////////////////

int				map_parser(char *argv, t_textures *map_info, t_game *game);
int				map_started(char *str, t_game *game);
int				get_map_y(t_textures *map_utils, char *map_path, t_game *game);
char			*go_to_map(int fd, t_game *game, int flag);
int				build_texture_list(char *str, t_game *game);
int				build_map_line(t_textures *map_info, int map_y,
					char *argv, t_game *game);
int				get_textures(char *str, t_textures *map_info);
void			free_tab(char **map);
void			print_textures(t_textures *texture);
void			quit_w_message(char *str);
void			free_textures(t_game *game);
int				is_inside(char c, t_game *game);
char			*ft_strdupto_n(char *str, char c);
int				check_end_of_filename(char const *filename, const char *end);
void			print_tab(char **tab);
void			free_tex(t_game *game);
void			set_player(t_textures *map_info, int x, int y, char p);
int				get_f_and_c(char *str, t_textures *map_info);
char			*ft_str_rm_spaces(char *str);
int				atorgb(char *str);
int				init_map(int *i, int *fd, int *player, char *argv);
int				ft_open(int *fd, char *path);
void			set_null_map(t_textures *map_info);
int				texture_good(t_textures *map_info);
int				great_mighty_init_tex(t_game *game);
int	check_point_n_w(char **map, int x, int y, t_game *game);
int				is_in_list(const char c, const char *list);

///////////// Init_things //////////////////

int				init_game(t_game *game, t_textures *textures);
t_grid			*init_grid(t_game *game);
t_player		*init_player(t_game *game);
int				init_textures(t_game *game, t_textures *textures);
void			free_game(t_game *game, t_textures *map_info);
int				init_sprites(t_game *game);
t_image			xpm_to_image(t_game *game, char *path);

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
int				is_floor(t_game *game, char c);
unsigned int	get_sky(t_game *game, int x, int y);
int				is_floor(t_game *game, char c);
void			render_ceiling_sky(t_game *game, int x, int y);
void			render_floor(t_game *game, int x, int y);
int				player_sphere(t_game *game, double x, double y);

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
