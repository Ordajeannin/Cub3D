/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:34:23 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/18 17:48:48 by pkorsako         ###   ########.fr       */
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
	if (!is_in_list(map[y][x + 1], game->wall)
		&& !is_inside(map[y][x + 1], game))
		return (0);
	if (map[y + 1] && x <= (int)ft_strlen(map[y + 1]))
	{
		if (!is_in_list(map[y + 1][x], game->wall)
			&& !is_inside(map[y + 1][x], game))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	can_access(char **map, int dest_x, int dest_y)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	if (dest_y < 0 || dest_x < 0)
		return (0);
	while (map && map[y])
	{
		if (y == dest_y)
			break ;
		y ++;
	}
	if (y != dest_y || !map[y])
		return (0);
	while (map[y][x])
	{
		if (x == dest_x)
			return (1);
		x ++;
	}
	return (0);
}

int	check_point_n_w(char **map, int x, int y, t_game *game)
{
	if (y > 0)
	{
		if (can_access(map, x, y - 1) && !is_in_list(map[y - 1][x], game->wall)
			&& !is_inside(map[y - 1][x], game))
			return (0);
	}
	else
		return (0);
	if (x > 0)
	{
		if (!is_in_list(map[y][x - 1], game->wall)
			&& !is_inside(map[y][x - 1], game))
			return (0);
	}
	else
		return (0);
	if (!check_point_e_s(map, x, y, game))
		return (0);
	return (1);
}
