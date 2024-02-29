/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:10:09 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/29 19:26:32 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	try_get_texture(char **map,int yt,int xt)
{
	int yi = 0;
	int xi = 0;

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

unsigned int	intersection_found_test(double angle, int dist, t_game *game, int flag, int pos_x, int pos_y)
{
	unsigned int	result;
	char			texture;
	int 			face;

	result = 0;
	//texture = game->grid->map[pos_y >> 6][pos_x >> 6];
	texture = try_get_texture(game->grid->map, pos_y >> 6, pos_x >> 6);
	if (texture == '0')
		return (FLOOR);
	else if (texture == 'a')
		return (OUTMAP);
//	if (flag == 1)
//		printf("\ngrid targeted(y, x) by lines =  [%d][%d]", (pos_y >> 6) + 1, (pos_x >> 6) + 1);
//	else
//		printf("\ngrid targeted(y, x) by col =  [%d][%d]\n", (pos_y >> 6) + 1, (pos_x >> 6) + 1);
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
//	if (flag == 1)
//		printf("correct way line\n");
//	else
//		printf("correct way col\n");
	return (result);
}

unsigned int	lines_intersections_test(t_game *game, t_player *player, double angle)
{
	int i_px = 0;
	int i_py = 0;
	int xi = 0;
	int yi = 64;
	unsigned int result;
	int dist = 0;

	angle = double_modulo(angle, 360);
	if (angle == 0.0 || angle == 180.0)
	{
		printf("\nline : out, angle\n");
		return (OUTMAP);
	}
	xi = 64 / tan(dtor(90 - double_modulo(angle, 90)));
	printf("line : value xi -> %d\n", xi);
	if (angle < 180)
		i_py = ((player->pos_y >> 6) << 6) - 1;
	else
		i_py = ((player->pos_y >> 6) << 6) + 64;
	i_px = player->pos_x + ((player->pos_y - i_py) * tan(dtor(90 - double_modulo(angle, 90))));
	dist = ft_dist(i_px, i_py, player->pos_x, player->pos_y);
	printf("line i0 : (%d, %d) | (%d, %d) | %d\n", i_py, i_px, (i_py >> 6) + 1, (i_px >> 6) + 1, dist);
//	if (dist < player->m_d)
//		result = intersection_found_test(angle, dist, game, 1, i_px, i_py);
//	else
//		return (UINT_MAX);
	result = intersection_found_test(angle, dist, game, 1, i_px, i_py);
	if (result == (OUTMAP))
	{
		printf("\nline : out\n");
		return (OUTMAP);
	}
//	printf("line : result before loop : %d\n", get_value(result, "DISTANCE"));
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
		printf("iteration : (%d, %d) | (%d, %d) | %d\n", i_py, i_px, (i_py >> 6) + 1, (i_px >> 6) + 1, dist);
		result = intersection_found_test(angle, dist, game, 1, i_px, i_py);
	}
	printf("line : result of dist : %d\n\n", get_value(result, "DISTANCE"));
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
	{
		printf("\ncol : out, angle\n");
		return (OUTMAP);
	}
	xi = 64;
	yi = 64 / tan(dtor(90 - double_modulo(angle, 90)));
	printf("col : value de yi -> %d\n", yi);
	if (angle < 90 || angle > 270)
		i_px = ((player->pos_x >> 6) << 6) + 64;
	else
		i_px = ((player->pos_x >> 6) << 6) -1;
	i_py = player->pos_y + ((player->pos_x - i_px) * tan(dtor(90 - double_modulo(angle, 90))));
	dist = ft_dist(i_px, i_py, player->pos_x, player->pos_y);
	printf("col i0 : (%d, %d) | (%d, %d) | %d\n", i_py, i_px, (i_py >> 6) + 1, (i_px >> 6) + 1, dist);
//	printf("\nvalue dist found : %d", dist);
//	if (dist < player->m_d)
//		result = intersection_found_test(angle, dist, game, 0, i_px, i_py);
//	else
//		return (UINT_MAX);
	result = intersection_found_test(angle, dist, game, 0, i_px, i_py);
	if (result == (OUTMAP))
	{
		printf("\ncol : out\n");
		return (OUTMAP);
	}
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
		printf("iteration : (%d, %d) | (%d, %d) | %d\n", i_py, i_px, (i_py >> 6) + 1, (i_px >> 6) + 1, dist);
		result = intersection_found_test(angle, dist, game, 0, i_px, i_py);
	}
	printf("col : result of dist : %d\n", get_value(result, "DISTANCE"));
	return (result);
}

unsigned int proj_plan_col_test(t_game *game, double angle)
{
	unsigned int result;
	unsigned int line;
	unsigned int col;

	result = 0;
//	max_dist(game);
//	printf("\nvalue max_dist : %d", game->player->m_d);
	line = lines_intersections_test(game, game->player, angle);
	col = col_intersections_test(game, game->player, angle);
	if (get_value(line, "DISTANCE") < get_value(col, "DISTANCE"))
		result = no_fish_eye(game, line, angle);
	else
		result = no_fish_eye(game, col, angle);
	view_stocked_image(&result);
	return (result);
}















