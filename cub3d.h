#ifndef CUB3D_H
# define CUB3D_H

#include "get_next_line.h"
#include <stdio.h>

typedef struct s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		*F;
	int		*C;
	char	**map;
	int		p_y;
	int		p_x;
	int		p_direction;
}	t_textures;

typedef struct s_map_p
{
	int	y;
	int	x;
	int	p_direction;
}	t_map_p;


///////////////Map_things///////////////////

int		map_started(char *str);
int		get_map_y();
char	*go_to_map(int fd, t_textures *map_utils);
void	build_map_line(char **map, int map_y, char *argv);
void	get_textures(char *str, t_textures *map_info);
void	free_tab(char **map);
void	print_textures(t_textures *texture);
void	quit_w_message(char *str);
void	free_textures(t_textures *textures);
int	is_inside(char c);

char	*ft_strdupto_n(char *str, char c);


#endif