/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:10:09 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/19 16:29:58 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	try_get_texture(char **map,int yt,int xt)
{
	int yi = 0;
	int xi = 0;

//	printf("yt = %d  |  xt = %d\n", yt, xt);
	while (yi != yt && map[yi] != NULL)
		yi++;
	if (yi != yt || map[yi] == NULL)
		return ('a');
	while (xi != xt && map[yi][xi] != '\0')
		xi++;
	if (xt != xi)
		return ('a');
	return (map[yi][xi]);
}

int	from_dist_to_projected(t_game *game, double angle, double dist)
{
	int result = 0;

	if (angle < game->player->orientation)
		angle = double_modulo(game->player->orientation - angle, 360);
	else
		angle = double_modulo(angle - game->player->orientation, 360);
	result = round(game->grid->projected_factor / (dist * cos(dtor(angle))));
//	printf("  |  dist = %f  |  projected = %d  |  angle = %f\n", dist, result, angle);
	return result;
}


unsigned int	intersection_found_test(double angle, double dist, t_game *game, int flag, int pos_x, int pos_y)
{
	unsigned int	result;
	char			texture;
	int 			face;

	result = 0;
	texture = try_get_texture(game->grid->map, pos_y >> 6, pos_x >> 6);
	if (texture == '0')
		return (FLOOR);
	else if (texture == 'a')
		return (OUTMAP);
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
//	result |= ((int)dist & DIST_MASK) << 12;
	result |= (from_dist_to_projected(game, angle, dist) & DIST_MASK) << 12;
	return (result);
}

double		get_xi(double angle)
{
	int result = 0;
	double result2 = 0;


	if (angle <= 90.0)
		result2 = 64 * tan(dtor(90.0 - angle));
	else if (angle > 90 && angle < 180)
		result2 = 64 * tan(dtor(angle - 90.0));
	else if (angle < 270)
		result2 = 64 * tan(dtor(270 - angle));
	else
		result2 = 64 * tan(dtor(angle - 270));

	if (angle <= 90.0)
		result = round(64 * tan(dtor(90.0 - angle)));
	else if (angle > 90 && angle < 180)
		result = round(64 * tan(dtor(angle - 90.0)));
	else if (angle < 270)
		result = round(64 * tan(dtor(270 - angle)));
	else
		result = round(64 * tan(dtor(angle - 270)));
	return (result2);
}

double	get_yi(double angle)
{
	int result = 0;
	double result2 = 0;

	if (angle <= 90)
		result2 = 64 * tan(dtor(angle));
	else if (angle > 90 && angle < 180)
		result2 = 64 * tan(dtor(180.0 - angle));
	else if (angle < 270)
		result2 = 64 * tan(dtor(angle - 180.0));
	else
		result2 = 64 * tan(dtor(360.0 - angle));

	if (angle <= 90)
		result = round(64 * tan(dtor(angle)));
	else if (angle > 90 && angle < 180)
		result = round(64 * tan(dtor(180.0 - angle)));
	else if (angle < 270)
		result = round(64 * tan(dtor(angle - 180.0)));
	else
		result = round(64 * tan(dtor(360.0 - angle)));
	return (result2);
}

unsigned int	lines_intersections_test(t_game *game, t_player *player, double angle)
{
	double i_px = 0;
	double i_py = 0;
	double xi = 0;
	double yi = 64;
	unsigned int result;
	double dist = 0;

//	printf("1  | wtffff");
	angle = double_modulo(angle, 360);
	if (angle == 0.0 || angle == 180.0)
		return (OUTMAP);
	xi = get_xi(angle);
	if (angle < 180)
		i_py = (floor(player->pos_y / 64) * 64) - 0.000001;
	else
		i_py = (floor(player->pos_y / 64) * 64) + 64;
	i_px = get_ipx(player, i_py, angle);
	dist = ft_dist(i_px, i_py, player->pos_x, player->pos_y);
	//result = intersection_found_test(angle, dist, game, 1, ceil(i_px), ceil(i_py));
	result = intersection_found_test(angle, dist, game, 1, i_px, i_py);
	if (result == (OUTMAP))
		return (OUTMAP);
//	printf("iteration line (%d, %d)(%d, %d): ",i_py, i_px, (i_py >> 6) + 1, (i_px >> 6) + 1);
//	printf("iteration line (%f, %f)  |  (%d, %d)  |   ", i_py, i_px, (int)floor(i_py / 64) + 1, (int)floor(i_px / 64) + 1);
//	view_stocked_col(result);
	while (result == FLOOR)
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
		//result = intersection_found_test(angle, dist, game, 1, ceil(i_px), ceil(i_py));
		result = intersection_found_test(angle, dist, game, 1, i_px, i_py);
//		printf("\niteration line (%f, %f)  |  (%d, %d)  |   ", i_py, i_px, (int)floor(i_py / 64) + 1, (int)floor(i_px / 64) + 1);
	//	view_stocked_col(result);
	}
	return (result);
}

unsigned int	col_intersections_test(t_game *game, t_player *player, double angle)
{
	double i_px = 0;
	double i_py = 0;
	double xi = 0;
	double yi = 0;
	unsigned int result;
	double dist = 0;

	angle = double_modulo(angle, 360);
	if (angle == 90.0 || angle == 270.0)
		return (OUTMAP);
	xi = 64;
	yi = get_yi(angle);
	if (angle < 90 || angle > 270)
		i_px = (floor(player->pos_x / 64) * 64) + 64;
	else
		i_px = (floor(player->pos_x / 64) * 64) - 0.000001;
	i_py = get_ipy(player, i_px, angle);
	dist = ft_dist(i_px, i_py, player->pos_x, player->pos_y);
	result = intersection_found_test(angle, dist, game, 0, i_px, i_py);
	if (result == (OUTMAP))
		return (OUTMAP);
//	printf("iteration col (%d, %d)(%d, %d): ", i_py, i_px, (i_py >> 6) + 1, (i_px >> 6) + 1);
//	printf("\niteration col (%f, %f)  |  (%d, %d)  |   ", i_py, i_px, (int)floor(i_py / 64) + 1, (int)floor(i_px / 64) + 1);
	//view_stocked_col(result);
	while (result == FLOOR)
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
//		printf("iteration col (%d, %d)(%d, %d): ", i_py, i_px, (i_py >> 6) + 1, (i_px >> 6) + 1);
//		printf("\niteration col (%f, %f)  |  (%d, %d)  |   ", i_py, i_px, (int)floor(i_py / 64) + 1, (int)floor(i_px / 64) + 1);
	//	view_stocked_col(result);
	}
	return (result);
}

unsigned int proj_plan_col_test(t_game *game, double angle)
{
	unsigned int result;
	unsigned int line;
	unsigned int col;

	result = 0;
//	printf("WTF je segfault ici?\n");
//	printf("position du joueur : (%f, %f)\n", game->player->pos_y, game->player->pos_x);
//	printf("angle du joueur : %f\n", game->player->orientation);
//	printf("angle du rayon : %f\n", angle);
	line = lines_intersections_test(game, game->player, angle);
//	printf("la?");
	col = col_intersections_test(game, game->player, angle);
//	printf("\nline : %d  |  col : %d\n", get_value(line, "DISTANCE"), get_value(col, "DISTANCE"));
//	if (get_value(line, "DISTANCE") < get_value(col, "DISTANCE"))
//	{
//	//	result = no_fish_eye(game, line, angle);
//		result = no_fish_eye_test(game, line, angle);
//	}
//	else
//	{
//		//result = no_fish_eye(game, col, angle);
//		result = no_fish_eye_test(game, col, angle);
//	}

	if (line == OUTMAP)
		line = 0;
	if (col == OUTMAP)
		col = 0;
	if (get_value(line, "DISTANCE") > get_value(col, "DISTANCE"))
		result = line;
	else
		result = col;
//	printf("value : ");
//	view_stocked_col(result);
	return (result);
}
