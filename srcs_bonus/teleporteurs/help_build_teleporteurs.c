/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_build_teleporteurs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <ajeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:14:17 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/18 20:15:46 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_in_map_and_floor(char **map, char *floor, char c)
{
	int	x;
	int	y;
	int	flag;

	if (!ft_strchr(floor, c))
		return (0);
	y = 0;
	flag = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
				flag++;
			x++;
		}
		y++;
	}
	if (flag == 1)
		return (1);
	else
		return (0);
}

int	pos_in_map(char **map, char c, char flag_xy)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
			{
				if (flag_xy == 'x')
					return (x);
				else
					return (y);
			}
			x++;
		}
		y++;
	}
	return (0);
}
