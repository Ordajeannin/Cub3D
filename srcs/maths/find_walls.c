/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:50 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/23 18:23:18 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Permet de condenser les informations necessaire a l'affichage de la colonne
 * correspondant au rayon, SI la texture existe (!= sol)
 * SI elle existe, determine la face qu'elle presente au joueur, son offset,
 * puis return un unsigned int contenant :
 * la face du block (sur 2 bits)
 * l'offset (sur 6 bits)
 * la texture (sur 4 bits)
 * la distance (a corriger, sur 20 bits)
*/
unsigned int intersection_found(double angle, int distance, char **map, int flag, int pos_x, int pos_y)
{
	unsigned int		result;
	char				texture;
	int					face;

	result = 0;
	texture = map[pos_y % 64][pos_x % 64];
	if (!texture)
		return (0);
	if (angle < 180 && flag == 1)
		face = SOUTH;
	if (angle > 90 && angle < 270 && flag == 0)
		face = EAST;
	if (ange >= 180 && flag == 1)
		face = NORTH;
	else
		face = WEST;
	result |= (face & FACE_MASK);
	if (flag == 0)
		result |= ((pos_y % 64) & OFFSET_MASK) << 2;
	else
		result |= ((pos_x % 64) & OFFSET_MASK) << 2;
	result |= (texture & TEXTURE_MASK) << 8;
	result |= (distance & DIST_MASK) << 12;
	return (result);
}

/*
 * Permet de determiner les intersections lignes/colonnes
 * Calculs de la position de la premiere intersection,
 * puis incrementation jusqu'a intersection avec une texture
 * lines et col fonctionnent de la meme maniere, mais avec des valeurs
 * differentes.
 * :warning: true if grid_width = 64
 * :warning: tan return a double value, any issue with pos_x?
*/
unsigned int	lines_intersections(t_player *player, t_grid *grid, double angle)
{
	int pos_x = 0;
	int pos_y = 0;
	int xi = 64/tan(dtor(angle));
	int yi = 64;
	unsigned int result;

	angle = angle % 360;
	if (angle < 180)
		pos_y = (player->pos_y >> 6) << 6 - 1;
	else
		pos_y = (player->pos_y >> 6) << 6 + 64;
	pos_x = player->pos_x + (player->pos_y - pos_y) / tan(dtor(angle));
	result = intersection_found(angle,
			ft_dist(pos_x, pos_y, player->pos_x, player->pos_y), grid->map, 1, pos_x, pos_y);
	while (result == 0)
	{
		if (angle > 180 || angle < 90)
			pos_x = pos_x + xi;
		else
			pos_x = pos_x - xi;
		if (angle < 180)
			pos_y = pos_y - yi;
		else
			pos_y = pos_y + yi;
		if (pos_x > 0 && pos_y > 0 && pos_x < x_max && pos_y < y_max)
			result = intersection_found(angle,
				ft_dist(pos_x, pos_y, player->pos_x, player->pos_y), grid->map, 1, pos_x, pos_y);
		else
			return (0);
	}
	return (result);
}

/*
 * Permet de determiner les intersections rayon/colonnes
 * Calculs de la position de la premiere intersecion,
 * puis si ca n est pas != d'un sol on incremente avec xi et yi
 * return les valeurs brutes de la colonne de pixels potentielle
 * (distance a comparer avec l'intersection ligne, seule la plus faible est affichee)
 * 
 * meme warnings que pour lines_intersections
*/
unsigned int	col_intersections(t_player *player, t_grid *grid, double angle)
{
	int	pos_x = 0;
	int	pos_y = 0;
	int	xi = 64;
	int yi = 64/tan(dtor(angle));
	unsigned int result;

	angle = angle % 360;
	if (angle < 90 || angle > 270)
		pos_x = (player->pos_x >> 6) << 6 + 64;
	else
		pos_x = (player->pos_x >> 6) << 6 -1;
	pos_y = player->pos_y + (player->pos_x - pos_x) * tan(dtor(angle));
	result = intersection_found(angle,
			ft_dist(pos_x, pos_y, player->pos_x, player->pos_y), grid->map, 0, pos_x, pos_y);
	while (result == 0)
	{
		if (angle > 180 || angle < 90)
			pos_x = pos_x + xi;
		else
			pos_x = pos_x - xi;
		if (angle < 180)
			pos_y = pos_y - yi;
		else
			pos_y = pos_y + yi;
		if (pos_x > 0 && pos_y > 0
				&& pos_x < player->x_max && pos_y < player->y_max)
			result = intersection_found(angle,
				ft_dist(pos_x, pos_y, player->pos_x, player->pos_y), grid->map, 0, pos_x, pos_y);
		else
			return (0);
	}
	return (result);
}

/*
 * Permet de fournir les valeurs necessaires a la generation d'une image,
 * pour une colonne de pixel.
 * Determine le bloc le plus proche du joueur sur la trajectoire du rayon,
 * corrige la distance pour eviter l'effet fish-eye, puis renvoie :
 * la face du bloc, la colonne de pixels de la texture (offset), 
 * la texture cocernee, et la distance au joueur
*/
unsigned int proj_plan_col(t_game *game, double angle)
{
	unsigned int result;
	unsigned int line;
	unsigned int col;

	result = 0;
	line = lines_intersections(game->player, game->grid, angle);
	col = col_intersections(game->player, game->grid, angle);
//	if (((line >> 12) & DIST_MASK) < ((col >> 12) & DIST_MASK))
	if (get_value(line, "DISTANCE") < get_value(col, "DISTANCE"))	
		result = no_fish_eye(game, line, angle);
	else
		result = no_fish_eye(game, col, angle);
	return (result);
}

//main, gere l'affichage (hook)
////boucle, fonction qui gere une image plan de proj (tableau de struct, distance + texture)
//////boucle, appelle de fonction gerant une colonne (return une struct dist + texture)
////////boucle, appelle de fonction gerant les intersections du rayon (dist brute int)
//verifier dans l'appel "liste" la texture a chaque inter, renvoyer un int
//texture + distance
