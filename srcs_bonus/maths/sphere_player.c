/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:21:38 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/17 18:02:00 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	collision_wall_sphere(t_game *game, double x, double y)
{
	char	texture;
	int		dist;

	dist = ft_dist(x, y, game->player->temp_x, game->player->temp_y);
	if (dist > SPHERE)
		return (SPHERE + 1);
	texture = try_get_texture(game->grid->map, (int)y >> 6, (int)x >> 6);
	if (is_floor(game, texture) == 0)
		return (SPHERE + 1);
	else if (texture == '&')
		return (0);
	else if (dist >= 1)
		return (dist);
	else
		return (0);
}

int	collision_line_sphere(t_game *game, t_player *player, double angle)
{
	double	i_px;
	double	i_py;
	double	xi;
	double	yi;

	game->flag = 1;
	if (angle == 0.0 || angle == 180.0)
		return (INT_MAX);
	set_value1(&xi, &yi, angle, game->flag);
	set_value2lines_sphere(&i_py, &i_px, player, angle);
	return (collision_wall_sphere(game, i_px, i_py));
}

int	collision_col_sphere(t_game *game, t_player *player, double angle)
{
	double	i_px;
	double	i_py;
	double	xi;
	double	yi;

	game->flag = 0;
	if (angle == 90.0 || angle == 270.0)
		return (INT_MAX);
	set_value1(&xi, &yi, angle, game->flag);
	set_value2col_sphere(&i_py, &i_px, player, angle);
	return (collision_wall_sphere(game, i_px, i_py));
}

int	player_sphere(t_game *game)
{
	double	angle;
	int		dist;
	int		dist2;
	int		result;

	angle = 0;
	result = SPHERE + 1;
	while (angle < 360)
	{
		dist = collision_line_sphere(game, game->player, angle);
		dist2 = collision_col_sphere(game, game->player, angle);
		if (dist > dist2)
			dist = dist2;
		if (result > dist)
			result = dist;
		angle += 10;
	}
	if (result <= SPHERE)
		return (1);
	else
		return (0);
}
