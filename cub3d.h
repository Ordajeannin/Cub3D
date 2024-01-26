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
}	t_textures;


///////////////Map_things///////////////////

int		map_started(char *str);
int		get_map_y();
char	*go_to_map(int fd, t_textures *map_utils);
void	build_map_line(char **map, int map_y);
void	get_textures(char *str, t_textures *map_info);

#endif