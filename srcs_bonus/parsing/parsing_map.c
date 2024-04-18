/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:27:02 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/18 17:12:55 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
					printf("map not closed on this line :%s\n", map[y]);
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
	game->ceiling = NULL;
	game->floor = NULL;
	game->wall = NULL;
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
	map_y = get_map_y(map_info, argv, game);
	if (map_y == -1 || !check_end_of_filename(argv, ".cub"))
		return (0);
	map_info->map = malloc(map_y * sizeof(char *) + 8);
	if (!map_info->map)
	{
		printf("malloc failed\n");
		return (0);
	}
	if (!build_map_line(map_info, map_y, argv, game))
		return (0);
	map_ok = is_map_closed(map_info->map, map_y, game);
	if (map_ok)
		return (1);
	return (0);
}
