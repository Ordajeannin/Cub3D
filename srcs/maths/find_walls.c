/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:50 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/23 15:41:40 by paulk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"

//stockage int: face of the block (2 bits) << texture (6 bits) << distance (24)
//flag == 0 if col, 1 if line
// unsigned int intersection_found(double angle, int distance, char **map, int flag)
// {
// 	unsigned int		result;
// 	char				texture;
// 	int					face;

// 	result = 0;
// 	texture = map[pos_y % 64][pos_x % 64];
// 	if (!texture)
// 		return (0);
// 	if (angle < 180 && flag == 1)
// 		face = SOUTH;
// 	if (angle > 90 && angle < 270 && flag == 0)
// 		face = EAST;
// 	if (ange >= 180 && flag == 1)
// 		face = NORTH;
// 	else
// 		face = WEST;
// 	result |= (face & FACE_MASK);
// 	result |= (texture & TEXTURE_MASK) << 2;
// 	result |= (distance & DIST_MASK) << 8;
// 	return (result);
// }

// // :warning: true if grid_width = 64
// // :warning: tan return a double value, any issue with pos_x?
// unsigned int	lines_intersections(t_player *player, t_grid *grid, double angle)
// {
// 	int pos_x = 0;
// 	int pos_y = 0;
// 	int xi = 64/tan(dtor(angle));
// 	int yi = 64;
// 	unsigned int result;

// 	angle = angle % 360;
// 	if (angle < 180)
// 		pos_y = (player->pos_y >> 6) << 6 - 1;
// 	else
// 		pos_y = (player->pos_y >> 6) << 6 + 64;
// 	pos_x = player->pos_x + (player->pos_y - pos_y) / tan(dtor(angle));
// 	result = intersection_found(angle,
// 			ft_dist(pos_x, pos_y, player->pos_x, player->pos_y), grid->map, 1);
// 	while (result == 0)
// 	{
// 		if (angle > 180 || angle < 90)
// 			pos_x = pos_x + xi;
// 		else
// 			pos_x = pos_x - xi;
// 		if (angle < 180)
// 			pos_y = pos_y - yi;
// 		else
// 			pos_y = pos_y + yi;
// 		if (pos_x > 0 && pos_y > 0 && pos_x < x_max && pos_y < y_max)
// 			result = intersection_found(angle,
// 				ft_dist(pos_x, pos_y, player->pos_x, player->pos_y), grid->map, 1);
// 		else
// 			return (0);
// 	}
// 	return (result);
// }

// //same warnings
// void	col_intersections(t_player *player, t_grid *grid, double angle)
// {
// 	int	pos_x = 0;
// 	int	pos_y = 0;
// 	int	xi = 64;
// 	int yi = 64/tan(dtor(angle));

// 	angle = angle % 360;
// 	if (angle < 90 || angle > 270)
// 		pos_x = (player->pos_x >> 6) << 6 + 64;
// 	else
// 		pos_x = (player->pos_x >> 6) << 6 -1;
// 	pos_y = player->pos_y + (player->pos_x - pos_x) * tan(dtor(angle));
// 	result = intersection_found(angle,
// 			ft_dist(pos_x, pos_y, player->pos_x, player->pos_y), grid->map, 0);
// 	while (1)
// 	{
// 		if (angle > 180 || angle < 90)
// 			pos_x = pos_x + xi;
// 		else
// 			pos_x = pos_x - xi;
// 		if (angle < 180)
// 			pos_y = pos_y - yi;
// 		else
// 			pos_y = pos_y + yi;
// 		if (pos_x > 0 && pos_y > 0
// 				&& pos_x < player->x_max && pos_y < player->y_max)
// 			result = intersection_found(angle,
// 				ft_dist(pos_x, pos_y, player->pos_x, player->pos_y), grid->map, 0);
// 		else
// 			return ;
// 	}
// }

// unsigned int proj_plan_col(t_game *game, double angle)
// {
// 	unsigned int result;
// 	unsigned int line;
// 	unsigned int col;

// 	result = 0;
// 	line = lines_intersections(game->player, game->grid, angle);
// 	col = col_intersections(game->player, game->grid, angle);
// 	if (((line >> 8) & DIST_MASK) < ((col >> 8) & DIST_MASK))
// 		result = no_fish_eye(game, line, angle);
// 	else
// 		result = no_fish_eye(game, col, angle);
// 	return (result);
// }

//main, gere l'affichage (hook)
////boucle, fonction qui gere une image plan de proj (tableau de struct, distance + texture)
//////boucle, appelle de fonction gerant une colonne (return une struct dist + texture)
////////boucle, appelle de fonction gerant les intersections du rayon (dist brute int)

//verifier dans l'appel "liste" la texture a chaque inter, renvoyer un int
//texture + distance
