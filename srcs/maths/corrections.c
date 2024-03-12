/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:33:33 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/12 20:19:41 by ajeannin         ###   ########.fr       */
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

//	view_stocked_image(&value);
	if (angle < game->player->orientation)
		alpha = double_modulo(game->player->orientation - angle, 360);
	else
		alpha = double_modulo(angle - game->player->orientation, 360);
	distorted = (value >> 12) & DIST_MASK;
	//correct = round(distorted * cos(dtor(alpha)));
	correct = distorted * cos(dtor(alpha));
	value &= ~(DIST_MASK << 12);
	value |= (correct & DIST_MASK) << 12;
	return (value);
}
