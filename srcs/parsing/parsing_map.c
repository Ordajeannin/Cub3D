/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:27:02 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/21 18:22:07 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_point_e_s(char **map, int x, int y)
{
	if (map[y][x + 1] != '1' && !is_inside(map[y][x + 1]))
		return (0);
	if (map[y + 1] && x <= (int)ft_strlen(map[y + 1]))
	{
		if (map[y + 1][x] != '1' && !is_inside(map[y + 1][x]))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	can_access(char **map, int limit_x, int y)
{
	int	x;

	x = 0;
	while (map && map[y][x])
	{
		if (x == limit_x)
			return (1);
		x ++;
	}
	return (0);
}

int	check_point_n_w(char **map, int x, int y)
{
	if (y > 0)
	{
		if (can_access(map, x, y - 1) && map[y - 1][x] != '1'
			&& !is_inside(map[y - 1][x]))
			return (0);
	}
	else
		return (0);
	if (x > 0)
	{
		if (map[y][x - 1] != '1' && !is_inside(map[y][x - 1]))
			return (0);
	}
	else
		return (0);
	if (!check_point_e_s(map, x, y))
		return (0);
	return (1);
}

/*
map info est la juste pour le P position et direction
*/
int	is_map_closed(char **map, int map_y)
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
			if (is_inside(map[y][x]))
			{
				if (!check_point_n_w(map, x, y))
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
	map_ok = is_map_closed(map_info->map, map_y);
	if (map_ok && texture_good(map_info))
		return (1);
	return (0);
}
