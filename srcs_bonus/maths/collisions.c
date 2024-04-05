/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:05 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/05 14:59:18 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	angle_90(double *x, double *y, double angle)
{
	int	dist;

	dist = DIST_WALK;
	*x += dist * cos(dtor(angle));
	*y -= dist * sin(dtor(angle));
}

void	angle_180(double *x, double *y, double angle)
{
	int	dist;

	dist = DIST_WALK;
	*x -= dist * sin(dtor(angle - 90.0));
	*y -= dist * cos(dtor(angle - 90.0));
}

void	angle_270(double *x, double *y, double angle)
{
	int	dist;

	dist = DIST_WALK;
	*x -= dist * cos(dtor(angle - 180.0));
	*y += dist * sin(dtor(angle - 180.0));
}

void	angle_360(double *x, double *y, double angle)
{
	int	dist;

	dist = DIST_WALK;
	*x += dist * sin(dtor(angle - 270.0));
	*y += dist * cos(dtor(angle - 270.0));
}

void	player_move_collide(t_game *game, double angle)
{
	double	temp_x;
	double	temp_y;
	char	c;

	temp_x = game->player->pos_x;
	temp_y = game->player->pos_y;
	if (angle < 90)
		angle_90(&temp_x, &temp_y, angle);
	else if (angle < 180)
		angle_180(&temp_x, &temp_y, angle);
	else if (angle < 270)
		angle_270(&temp_x, &temp_y, angle);
	else
		angle_360(&temp_x, &temp_y, angle);
	c = try_get_texture(game->grid->map, temp_y / 64, temp_x / 64);
	if (is_floor(game, c) == 0)
	{
		game->player->pos_x = temp_x;
		game->player->pos_y = temp_y;
	}
}
