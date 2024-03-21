/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:10:09 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/20 17:42:59 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	find_face(t_game *game, double angle)
{
	int	face;

	face = WEST;
	if (angle < 180 && game->flag)
		face = SOUTH;
	else if (game->flag)
		face = NORTH;
	else if (angle > 90 && angle < 270)
		face = EAST;
	return (face);
}

unsigned int	intersection_found_test(double angle, t_game *game,
		double pos_x, double pos_y)
{
	unsigned int	result;
	char			texture;

	result = 0;
	texture = try_get_texture(game->grid->map,
			(int)pos_y >> 6, (int)pos_x >> 6);
	if (texture == '0')
		return (FLOOR);
	else if (texture == 'a')
		return (OUTMAP);
	result |= (find_face(game, angle) & FACE_MASK);
	if (game->flag)
		result |= (((int)pos_x % 64) & OFFSET_MASK) << 2;
	else
		result |= (((int)pos_y % 64) & OFFSET_MASK) << 2;
	result |= (texture & TEXTURE_MASK) << 8;
	result |= (from_dist_to_projected(game, angle, pos_x, pos_y)
			& DIST_MASK) << 12;
	return (result);
}

unsigned int	lines_intersections_test(t_game *game,
		t_player *player, double angle)
{
	double			i_px;
	double			i_py;
	double			xi;
	double			yi;
	unsigned int	result;

	game->flag = 1;
	angle = double_modulo(angle, 360);
	if (angle == 0.0 || angle == 180.0)
		return (OUTMAP);
	set_value1(&xi, &yi, angle, game->flag);
	set_value2lines(&i_py, &i_px, player, angle);
	result = intersection_found_test(angle, game, i_px, i_py);
	if (result == (OUTMAP))
		return (OUTMAP);
	while (result == FLOOR)
	{
		update_ipx(&i_px, xi, angle);
		update_ipy(&i_py, yi, angle);
		result = intersection_found_test(angle, game, i_px, i_py);
	}
	return (result);
}

unsigned int	col_intersections_test(t_game *game,
		t_player *player, double angle)
{
	double			i_px;
	double			i_py;
	double			xi;
	double			yi;
	unsigned int	result;

	game->flag = 0;
	angle = double_modulo(angle, 360);
	if (angle == 90.0 || angle == 270.0)
		return (OUTMAP);
	set_value1(&xi, &yi, angle, game->flag);
	set_value2col(&i_py, &i_px, player, angle);
	result = intersection_found_test(angle, game, i_px, i_py);
	if (result == (OUTMAP))
		return (OUTMAP);
	while (result == FLOOR)
	{
		update_ipx(&i_px, xi, angle);
		update_ipy(&i_py, yi, angle);
		result = intersection_found_test(angle, game, i_px, i_py);
	}
	return (result);
}

unsigned int	proj_plan_col_test(t_game *game, double angle)
{
	unsigned int	result;
	unsigned int	line;
	unsigned int	col;

	result = 0;
	line = lines_intersections_test(game, game->player, angle);
	col = col_intersections_test(game, game->player, angle);
	if (line == OUTMAP)
		line = 0;
	if (col == OUTMAP)
		col = 0;
	if (get_value(line, "DISTANCE") == get_value(col, "DISTANCE"))
	{
		if (game->dist_l > game->dist_c)
			result = col;
		else
			result = line;
	}
	else if (get_value(line, "DISTANCE") > get_value(col, "DISTANCE"))
		result = line;
	else
		result = col;
	return (result);
}
