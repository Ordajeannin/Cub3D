/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:27:02 by pkorsako          #+#    #+#             */
/*   Updated: 2024/01/26 17:19:50 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab && tab[i])
	{
		printf("tab[%d] :%s", i, tab[i]);
		i ++;
	}
	// printf("tab[%d] :%s\n", i, tab[i]);
}

int	is_inside(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

int	check_point(char **map, int x, int y, int map_y)
{
	if (y > 0)//check le nord, si ya
	{
		if (map[y - 1][x] != '1' && !is_inside(map[y - 1][x]))
		{
			printf("%c on north\n", map[y - 1][x]);
			return (0);//rien au nord
		}
	}
	else
		return (0);//pas de nord
		
	if (x > 0)//check la gauche, que si yen a
	{
		if (map[y][x - 1] != '1' && !is_inside(map[y][x - 1]))//teste la gauche du point
		{
			printf("%c on the west\n", map[y][x - 1]);
			return (0);//mauvaise map
		}
	}
	else
		return (0);//0 a gauche
		
	if (map[y][x + 1] != '1' && !is_inside(map[y][x + 1]))//teste la droite
	{
		printf("%c on east\n", map[y][x + 1]);
		return (0);//mauvaise map
	}
	
	if (x <= ft_strlen(map[y + 1]))//check le sud, que si ya
	{
		if (map[y + 1][x] != '1' && !is_inside(map[y + 1][x]))
		{
			printf("%c on south\n", map[y + 1][x]);
			return (0);
		}
	}
	else 
		return (0);//rien au sud du 0;
		
	return (1);
}

int	is_map_closed(char **map, int map_y)
{
	int	x;
	int	y;

	x = 0;
	y = 0;

	while (y <= map_y - 1)
	{
		// printf("%s", map[y]);
		x = 0;
		while (map[y][x] != 0)
		{
			// printf("checking :%c\n", map[y][x]);
			if (is_inside(map[y][x]))
			{
				// printf("checkingo :%c\n", map[y][x]);
				if (!check_point(map, x, y, map_y))
					return (0);
			}
			x ++;
		}
		y ++;
	}
	return (1);
}

int	valide_char(char **map, int y, int x)
{
	static int	starter;
	
	if (map[y][x] == '1' || map[y][x] == '0')
		return (1);
	if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
	{
		if (starter)
			return (0);
		starter ++;
		map[y][x] = '0';
		return (1);
	}
	else
		return (0);
}

void	free_tab(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i ++;
	}
	free(map);
}

int	main()///pour parser, on va regarder si les 0 sont entourée de 1 N S E W sinon ca degage
{
	char		**map;
	int			fd;
	int			map_y;
	int 		map_ok;
	t_textures	map_utils;

	map_utils.EA = NULL;
	map_utils.NO = NULL;
	map_utils.WE = NULL;
	map_utils.SO = NULL;
	map_utils.F = NULL;
	map_utils.C = NULL;
	map_y = get_map_y(&map_utils);
	printf("map_y is :%d\n", map_y);
	map = malloc(map_y * (sizeof(char *) + 4));
	build_map_line(map, map_y);//map est construite
	// print_tab(map);
	map_ok = is_map_closed(map, map_y);
	printf("map ok ? :%d\n", map_ok);
	free_tab(map);
}


/*condition :
	if map[0] pas tester nord
	if map[y][x + 1] = \n limite x++
	if map[limite basse] pas tester sud
	if map[y][x], avant de tester sud, check strlen de la ligne d'apres
*/

// char **map_for_parsing(char **map, int map_y)//inutile en fait
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (y < map_y - 1)
// 	{
// 		while (map[y][x] != 0)
// 		{
// 			if (!valide_char(map, y, x))
// 				return (0);
// 		}
// 		printf("%s", map[y]);
// 	}
// 	return (map);
// }
