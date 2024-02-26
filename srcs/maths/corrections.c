/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:33:33 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/23 15:41:50 by paulk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// unsigned int	no_fish_eye(t_game *game, unsigned int value, double angle)
// {
// 	double	alpha;
// 	int		distorted;
// 	int		correct;

// 	if (angle < game->player->orientation)
// 		alpha = game->player->orientation - angle;
// 	else
// 		alpha = angle - game->player->orientation;
// 	distorted = (value >> 8) & DIST_MASK;
// 	correct = (int)(distorted * cos(dtor(alpha)));
// 	value &= ~(DIST_MASK << 8);
// 	value |= (correct & DIST_MASK) << 8;
// 	return (value);
// }
