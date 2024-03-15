/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:33:33 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/15 19:34:27 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Permet de corriger l'effet fish-eye, qui deformerait l'image sinon.
 * extrait la distance, effectue les calculs, et remplace par la valeur correcte
*/
unsigned int	no_fish_eye(t_game *game, unsigned int value, double angle)
{
	double	alpha;
	int		distorted;
	int		correct;
	static int prev = 0;
	static int prev_prev = 0;
//	static int prev_prev_prev = 0;

//	view_stocked_image(&value);
	if (angle < game->player->orientation)
		alpha = double_modulo(game->player->orientation - angle, 360);
	else
		alpha = double_modulo(angle - game->player->orientation, 360);
	distorted = (value >> 12) & DIST_MASK;
	correct = round(distorted * cos(dtor(alpha)));
//	correct = distorted * cos(dtor(alpha));
//	if (correct == prev + 1 || correct == prev - 1)
//	{
//		if (prev == prev_prev || prev == prev_prev_prev)
//			correct = prev;
//	}
	if (correct == prev + 1 || correct == prev - 1)
	{
		if (prev == prev_prev)
			correct = prev;
	}
	value &= ~(DIST_MASK << 12);
	value |= (correct & DIST_MASK) << 12;
//	prev_prev_prev = prev_prev;
	prev_prev = prev;
	prev = correct;
	return (value);
}

unsigned int no_fish_eye_test(t_game *game, unsigned int value, double angle)
{
	int distorted;
	int correct;
//	static int prev = 0;
//	static int prev_prev = 0;
//	static int prev_prev_prev = 0;

	if (angle < game->player->orientation)
		angle = double_modulo(game->player->orientation - angle, 360);
	else
		angle = double_modulo(angle - game->player->orientation, 360);
	distorted = get_value(value, "DISTANCE");
	correct = round(game->grid->projected_factor / (distorted * cos(dtor(angle))));
//	if (correct == prev + 1 || correct == prev - 1)
//	{
//		if (prev == prev_prev || prev == prev_prev_prev)
//			correct = prev;
//	}
	value &= ~(DIST_MASK << 12);
	value |= (correct & DIST_MASK) << 12;
//	prev_prev_prev = prev_prev;
//	prev_prev = prev;
//	prev = correct;
	return (value);
}
