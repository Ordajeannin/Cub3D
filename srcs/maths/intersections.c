/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:10:09 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/28 21:30:46 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	intersection_found_test(double angle, int dist, t_game *game, int flag, int pos_x, int pos_y)
{
	unsigned int	result;
	char			texture;
	int 			face;

	result = 0;
	texture = map[pos_y >> 6][pos_x >> 6];
	if (texture == '0')
		return (UINT_MAX);
	face = WEST;
	if (angle < 180 && flag)
		face = SOUTH;
	else if (flag)
		face = NORTH;
	else if (angle > 90 && angle < 270)
		face = EAST;
	result |= (face & FACE_MASK);
	if (flag)
		result |= ((pos_x % 64) & OFFSET_MASK) << 2;
	else
		result |= ((pos_y % 64) & OFFSET_MASK) << 2;
	result |= (texture & TEXTURE_MASK) << 8;
	result |= (dist & DIST_MASK) << 12;
	return (result);
}

unsigned int	lines_intersections_test(t_game *game, t_player *player, double angle)
{
	int i_px = 0;
	int i_py = 0;
	int xi = 0;
	int yi = 64;
	unsigned int result;
	int m_d = 0;
	int dist = 0;

	angle = double_modulo(angle, 360);
	if (angle == 0.0 || angle == 180.0)
		return (UINT_MAX);
	xi = 64 / tan(dtor(90 - double_modulo(angle, 90)));
	if (angle < 180)
		i_py = ((player->pos_y >> 6) << 6) - 1;
	else
		i_py = ((player->pos_y >> 6) << 6) + 64;
	i_px = player->pos_x + ((player->pos_y - i_py) * tan(dtor(90 - double_modulo(angle, 90))));
	dist = ft_dist(i_px, i_py, player->pos_x, player->pos_y);
	if (dist < player->md)
		result = intersection_found_test();
	else
		return (UINT_MAX);
	while (result == UINT_MAX)
	{
		if (angle > 270 || angle < 90)
			i_px = i_px + xi;
		else
			i_px = i_px - xi;
		if (angle < 180)
			i_py = i_py - yi;
		else
			i_py = i_py + yi;
		dist = ft_dist(i_px, i_py, player->pos_x, player->pos_y);
		result = intersection_found_test(angle, dist, game, 1, i_px, i_py);
	}
	return (result);
}

unsigned int	col_intersections_test(t_game *game, t_player *player, double angle)
{
	int i_px = 0;
	int i_py = 0;
	int xi = 0;
	int yi = 0;
	unsigned int result;
	int dist = 0;

	angle = double_modulo(angle, 360);
	if (angle == 90.0 || angle == 270.0)
		return (UINT_MAX);
	xi = 64;
	yi = 64 / tan(dtor(90 - double_modulo(angle, 90)));
	if (angle < 90 || angle > 270)
		i_px = ((player->pos_x >> 6) << 6) + 64;
	else
		i_px = ((player->pos_x >> 6) << 6) -1;
	i_py = player->pos_y + ((player->pos_x - i_px) * tan(dtor(90 - double_modulo(angle, 90))));
	if (dist < player->md)
		result = intersection_found_test(angle, dist, game, 0, i_px, i_py);
	else
		return (UINT_MAX);
	while (result == UINT_MAX)
	{
		if (angle > 270 || angle < 90)
			i_px = i_px + xi;
		else
			i_px = i_px - xi;
		if (angle < 180)
			i_py = i_py - yi;
		else
			i_py = i_py + yi;
		dist = ft_dist(i_px, i_py, player->pos_x, player->pos_y);
		result = intersection_found_test(angle, dist, game, 0, i_px, i_py);
	}
	return (result);
}

