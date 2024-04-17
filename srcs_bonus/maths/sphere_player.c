/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:21:38 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/17 16:30:49 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_shpere(t_game *game, double x, double y)
{
	double	angle;
	int		dist;
	int		dist2;
	int		result;

	angle = 0;
	result = 0;
	while (angle < 360)
	{
		dist = collision_line(game, game->player, angle);
		dist2 = collision_col(game, game->player, angle);
		if (dist > dist2)
			dist = dist2;
		if (result < dist)
			result = dist;
		angle += 30;
	}
	if (result <= SPHERE)
		return (1);
	else
		return (0);
}

