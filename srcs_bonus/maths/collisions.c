/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:05 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/16 18:22:23 by ajeannin         ###   ########.fr       */
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

int	collision_line(t_game *game, t_player *player, double angle)
{
	double	i_px;
	double	i_py;
	double	xi;
	double	yi;

	game->flag = 1;
	if (angle == 0.0 || angle == 180.0)
		return (0);
	set_value1(&xi, &yi, angle, game->flag);
	set_value2lines(&i_py, &i_px, player, angle);
	if (collision_wall(game, i_px, i_py) == 1)
		return (1);
	else
		return (0);
}

int	collision_col(t_game *game, t_player *player, double angle)
{
	double	i_px;
	double	i_py;
	double	xi;
	double	yi;

	game->flag = 0;
	if (angle == 90.0 || angle == 270.0)
		return (0);
	set_value1(&xi, &yi, angle, game->flag);
	set_value2col(&i_py, &i_px, player, angle);
	if (collision_wall(game, i_px, i_py) == 1)
		return (1);
	else
		return (0);
}

void	player_move_collide(t_game *game, double angle)
{
	double	temp_x;
	double	temp_y;
	char	c;

	if (collision_line(game, game->player, angle)
			|| collision_col(game, game->player, angle))
		return ;
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

