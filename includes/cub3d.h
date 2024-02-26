/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:15:52 by pkorsako          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/26 19:43:34 by paulk            ###   ########.fr       */
=======
/*   Updated: 2024/02/26 20:45:41 by ajeannin         ###   ########.fr       */
>>>>>>> aj/engine2
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include "libft.h"
# include "../mlx/mlx.h"

#define FACE_MASK 0x3
#define OFFSET_MASK 0x3F
#define TEXTURE_MASK 0xF
#define DIST_MASK 0xFFFFF
#define EAST 0
#define NORTH 1
#define WEST 2
#define SOUTH 3
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200


typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*f;
	int		*c;
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
<<<<<<< HEAD
=======
	char		**map;
>>>>>>> aj/engine2
	t_textures	*textures;
}	t_grid;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	double	orientation;
	int		x_max;
	int		y_max;
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
	t_player	*player;
	t_grid		*grid;
	t_textures	*textures;
}	t_game;

///////////////Map_things///////////////////

<<<<<<< HEAD
int		map_parser(char *argv, t_textures *map_info);
int		map_started(char *str);
int		get_map_y(t_textures *map_utils, char *map_path);
char	*go_to_map(int fd, t_textures *map_utils);
int		build_map_line(t_textures *map_info, char **map, int map_y, char *argv);
int		get_textures(char *str, t_textures *map_info);
void	free_tab(char **map);
void	print_textures(t_textures *texture);
void	quit_w_message(char *str, t_textures *map_info);
void	free_textures(t_textures *textures);
int		is_inside(char c);
=======
int				map_parser(char *argv, t_textures *map_info);
int				map_started(char *str);
int				get_map_y(t_textures *map_utils, char *map_path);
char			*go_to_map(int fd, t_textures *map_utils);
void			build_map_line(char **map, int map_y, char *argv);
void			get_textures(char *str, t_textures *map_info);
void			free_tab(char **map);
void			print_textures(t_textures *texture);
void			quit_w_message(char *str);
void			free_textures(t_textures *textures);
int				is_inside(char c);
>>>>>>> aj/engine2

char			*ft_strdupto_n(char *str, char c);


///////////// Init_things //////////////////

int				init_game(t_game *game, t_textures *textures);
t_grid			*init_grid(t_game *game);
t_player		*init_player(t_game *game);


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
double			double_modulo(double value, double modulo);
int				ft_dist(int x1, int x2, int y1, int y2);
int				get_value(unsigned int value, const char *flag);


///////////// Mlx_things ///////////////////

void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
void			create_col(t_game *game, unsigned int value, int x);
int				render(t_game *game);
int				handle_close(t_game *game);
int				handle_keypress(int keycode, t_game *game);
int				handle_mouse(int keycode, int x, int y, t_game *game);

#endif
