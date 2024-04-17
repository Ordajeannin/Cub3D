/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:05 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/17 16:28:37 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
int	collision_wall(t_game *game, double x, double y)
{
	char	texture;

	if (ft_dist(x, y, game->player->pos_x, game->player->pos_y) > DIST_WALK)
		return (0);
	texture = try_get_texture(game->grid->map, (int)y >> 6, (int)x >> 6);
	if (is_floor(game, texture) == 0)
		return (0);
	else if (texture == '&')
		return (1);
	else
		return (1);
}
*/

int	collision_wall(t_game *game, double x, double y)
{
	char	texture;
	int		dist;

	dist = ft_dist(x, y, game->player->pos_x, game->player->pos_y);
	if (dist > DIST_WALK)
		return (DIST_WALK);
	texture = try_get_texture(game->grid->map, (int)y >> 6, (int)x >> 6);
	if (is_floor(game, texture) == 0)
		return (DIST_WALK);
	else
		return (0);
//	else if (texture == '&')
//		return (0);
	if (dist >= 1)
		return (dist - 1);
	else
		return (0);
}

int	collision_line(t_game *game, t_player *player, double angle)
{
	double	i_px;
	double	i_py;
	double	xi;
	double	yi;

	game->flag = 1;
	if (angle == 0.0 || angle == 180.0)
		return (INT_MAX);
	set_value1(&xi, &yi, angle, game->flag);
	set_value2lines(&i_py, &i_px, player, angle);
	return (collision_wall(game, i_px, i_py));
}

int	collision_col(t_game *game, t_player *player, double angle)
{
	double	i_px;
	double	i_py;
	double	xi;
	double	yi;

	game->flag = 0;
	if (angle == 90.0 || angle == 270.0)
		return (INT_MAX);
	set_value1(&xi, &yi, angle, game->flag);
	set_value2col(&i_py, &i_px, player, angle);
	return (collision_wall(game, i_px, i_py));
//	if (collision_wall(game, i_px, i_py) == 1)
//		return (1);
//	else
//		return (0);
}

/*
void	move_player(t_player *player, double angle, int dist)
{
	if (angle < 90)
	{
		player->pos_x += dist * cos(dtor(angle));
		player->pos_y -= dist * sin(dtor(angle));
	}
	else if (angle < 180)
	{
		player->pos_x -= dist * sin(dtor(angle - 90));
		player->pos_y -= dist * cos(dtor(angle - 90));
	}
	else if (angle < 270)
	{
		player->pos_x -= dist * cos(dtor(angle - 180));
		player->pos_y += dist * sin(dtor(angle - 180));
	}
	else
	{
		player->pos_x += dist * sin(dtor(angle - 270));
		player->pos_y += dist * cos(dtor(angle - 270));
	}
}
*/

/*
void	player_move_collide(t_game *game, double angle)
{
	int		dist;
	int		dist2;

	dist = collision_line(game, game->player, angle);
	dist2 = collision_col(game, game->player, angle);
	if (dist2 < dist)
		dist = dist2;
	move_player(game->player, angle, dist);
}
*/

double	move_player(double angle, int dist, double *y)
{
	double	x;

	x = 0;
	if (angle < 90)
	{
		x += dist * cos(dtor(angle));
		*y -= dist * sin(dtor(angle));
	}
	else if (angle < 180)
	{
		x -= dist * sin(dtor(angle - 90));
		*y -= dist * cos(dtor(angle - 90));
	}
	else if (angle < 270)
	{
		x -= dist * cos(dtor(angle - 180));
		*y += dist * sin(dtor(angle - 180));
	}
	else
	{
		x += dist * sin(dtor(angle - 270));
		*y += dist * cos(dtor(angle - 270));
	}
	return (x);
}

void	player_move_collide(t_game *game, double angle)
{
	int		dist;
	int		dist2;
	double	temp_x;
	double	temp_y;

	dist = collision_line(game, game->player, angle);
	dist2 = collision_col(game, game->player, angle);
	if (dist2 < dist)
		dist = dist2;
	temp_x += move_player(angle, dist, &temp_y);
	if (player_sphere(temp_x, temp_y) == 0)
	{
		player->pos_x += temp_x;
		player->pos_y += temp_y;
	}
}
