/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:15:52 by pkorsako          #+#    #+#             */
/*   Updated: 2024/02/22 17:39:10 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "get_next_line.h"
# include <stdio.h>

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
}	t_textures;

typedef struct s_intersections
{
	int				pos_x;
	int				pos_y;
	int				grid_x;
	int				grid_y;
	t_intersections *next;
}	t_intersections;

typedef struct s_grid
{
	int		fov;
	int		half_fov;
	int		proj_plan_width;
	int		proj_plan_height;
	int		grid_width;
	double	angle_incr;
	t_inter *lines;
	t_inter *cols;
}	t_grid;

typedef struct s_player
{
	int pos_x;
	int	pos_y;
	int	orientation = 0;
}	t_player;

typedef struct s_game
{
	t_player	*player;
	t_grid		*grid;
	t_textures	*textures;
}	t_game;


///////////////Map_things///////////////////

int		map_started(char *str);
int		get_map_y(void);
char	*go_to_map(int fd, t_textures *map_utils);
void	build_map_line(char **map, int map_y, char *argv);
void	get_textures(char *str, t_textures *map_info);
void	free_tab(char **map);
void	print_textures(t_textures *texture);
void	quit_w_message(char *str);
void	free_textures(t_textures *textures);
int		is_inside(char c);

char	*ft_strdupto_n(char *str, char c);

#endif
