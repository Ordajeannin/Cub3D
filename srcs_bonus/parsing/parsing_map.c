/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:27:02 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/04 15:52:11 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_in_list(const char c, const char *list)
{
	int		i;
	
	i = 0;
	while (list[i])
	{
		if (list[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

int	check_point_e_s(char **map, int x, int y, t_game *game)
{
	if (!is_in_list(map[y][x + 1], game->wall)&& !is_inside(map[y][x + 1], game))
		return (0);
	if (map[y + 1] && x <= (int)ft_strlen(map[y + 1]))
	{
		if (!is_in_list(map[y + 1][x], game->wall) && !is_inside(map[y + 1][x], game))
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

int	check_point_n_w(char **map, int x, int y, t_game *game)
{
	if (y > 0)
	{
		printf("can_access :%d\tis_in_list :%d\tis_inside :%d\n", can_access(map, x, y - 1), !is_in_list(map[y - 1][x], game->wall), !is_inside(map[y - 1][x], game));
		if (can_access(map, x, y - 1) && !is_in_list(map[y - 1][x], game->wall)
			&& !is_inside(map[y - 1][x], game))
			return (0);
	}
	else
		return (0);
	if (x > 0)
	{
		if (!is_in_list(map[y][x - 1], game->wall) && !is_inside(map[y][x - 1], game))
			return (0);
	}
	else
		return (0);
	if (!check_point_e_s(map, x, y, game))
		return (0);
	return (1);
}

/*
map info est la juste pour le P position et direction
*/
int	is_map_closed(char **map, int map_y, t_game *game)
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
			if (is_inside(map[y][x], game))
			{
				if (!check_point_n_w(map, x, y, game))
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

void	init_floor_ceiling_wall(t_game *game)
{
	ft_bzero(game->floor, 10);
	ft_bzero(game->ceiling, 10);
	ft_bzero(game->wall, 10);
	game->floor[0] = '0';
	game->floor[1] = '2';
	game->floor[2] = '\0';
	game->ceiling[0] = '0';
	game->ceiling[1] = '2';
	game->ceiling[2] = '\0';
	game->wall[0] = '1';
	game->wall[1] = '7';
	game->wall[2] = '8';
}

/*
pour parser, on va regarder si les 0 N S E W sont entourée de 1, sinon ca degage	
*/
int	map_parser(char *argv, t_textures *map_info, t_game *game)
{
	int		map_y;
	int		map_ok;

	init_floor_ceiling_wall(game);
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
	if (!build_map_line(map_info, map_y, argv, game))
		return (0);
	map_ok = is_map_closed(map_info->map, map_y, game);
	if (map_ok && texture_good(map_info))
		return (1);
	return (0);
}
