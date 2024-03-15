/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:27:02 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/15 13:28:47 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player(t_textures *map_info, int x, int y, char p)
{
	map_info->p_x = x;
	map_info->p_y = y;
	if (p == 'N')
		map_info->p_direction = 90;
	if (p == 'E')
		map_info->p_direction = 0;
	if (p == 'W')
		map_info->p_direction = 180;
	if (p == 'S')
		map_info->p_direction = 270;
}


int	check_point_e_s(char **map, int x, int y, int map_y)
{
	(void)map_y;
	if (map[y][x + 1] != '1' && !is_inside(map[y][x + 1])) //teste la droite
	{
//		printf("%c on east\n", map[y][x + 1]);
		return (0); //mauvaise map
	}
	if (map[y + 1] && x <= (int)ft_strlen(map[y + 1])) //check le sud, que si ya
	{
		if (map[y + 1][x] != '1' && !is_inside(map[y + 1][x]))
		{
//			printf("%c on south\n", map[y + 1][x]);
			return (0);
		}
	}
	else
		return (0); //rien au sud du 0;
	return (1);
}
int	can_access(char **map,int limit_x,int y)
{
	int x;

	x = 0;
	while(map && map[y][x])
	{
		if (x == limit_x)
			return (1);
		x ++;
	}
	return (0);
}

int	check_point_n_w(char **map, int x, int y, int map_y)
{
	if (y > 0) //check le nord, si ya
	{
		if (can_access(map, x, y - 1) && map[y - 1][x] != '1' && !is_inside(map[y - 1][x]))
		{
//			printf("%c on north\n", map[y - 1][x]);
			return (0); //rien au nord
		}
	}
	else
		return (0); //pas de nord
	if (x > 0) //check la gauche, que si yen a
	{
		if (map[y][x - 1] != '1' && !is_inside(map[y][x - 1]))//teste la gauche du point
		{
//			printf("%c on the west\n", map[y][x - 1]);
			return (0); //mauvaise map
		}
	}
	else
		return (0); //0 a gauche
	if (!check_point_e_s(map, x, y, map_y))
		return (0);
	return (1);
}

/*
map info est la juste pour le P position et direction
*/
int	is_map_closed(t_textures *map_info, char **map, int map_y)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y <= map_y - 1)
	{
		x = 0;
		while (map[y][x] != 0)
		{
			if (is_inside(map[y][x]) == 2)
				set_player(map_info, x, y, map[y][x]);
			if (is_inside(map[y][x]))
			{
				if (!check_point_n_w(map, x, y, map_y))
				{
					printf("map not closed\n");
					return (0);
				}
			}
			x ++;
		}
		y ++;
	}
	printf("map closed\n");
	return (1);
}

int	texture_good(t_textures *map_info)
{	
	int i;
	
	i = 0;
	if (!map_info->so || !map_info->we || !map_info->ea || !map_info->no)
	{
		printf("missing wall\n");
		return (0);	
	}
	if (!check_end_of_filename(map_info->ea, ".xpm")
		||	!check_end_of_filename(map_info->so, ".xpm")
		|| !check_end_of_filename(map_info->we, ".xpm")
		|| !check_end_of_filename(map_info->no, ".xpm"))
		return (0);
	if (map_info->c == -1 || map_info->f == -1)
	{
		printf("missing f or c\n");
		return (0);
	}
	printf("textures are good\n");
	return (1);
}


void	set_null_map(t_textures *map_info)
{
	map_info->ea = NULL;
	map_info->no = NULL;
	map_info->we = NULL;
	map_info->so = NULL;
	map_info->f = 0;
	map_info->c = 0;
	map_info->map = NULL;
}

int	check_end_of_filename(char const *filename, const char *end)
{
	size_t i;

	i = ft_strlen(filename) - 4;
	// printf("filename - 4 :%c\n", filename[i]);
	if (filename[i ++] != end[0])
		return (0);
	if (filename[i ++] != end[1])
		return (0);
	if (filename[i ++] != end[2])
		return (0);
	if (filename[i ++] != end[3])
		return (0);
	printf("NICE FILENAME\n");
	return (1);
}

/*
pour parser, on va regarder si les 0 N S E W sont entourée de 1, sinon ca degage	
*/
int	map_parser(char *argv, t_textures *map_info)
{
	int		map_y;
	int		map_ok;

	set_null_map(map_info);
	map_y = get_map_y(map_info, argv);
	if (map_y == -1 || !check_end_of_filename(argv, ".cub"))
		return (0);
	map_info->map = malloc(map_y * (sizeof(char *) + 4));
	if (!map_info->map)
	{
		printf("malloc failed\n");
		return (0);
	}
	if (!build_map_line(map_info, map_info->map, map_y, argv))
		return (0);
	map_ok = is_map_closed(map_info, map_info->map, map_y);
	if (map_ok && texture_good(map_info))
		return (1);
	return (0);
}
