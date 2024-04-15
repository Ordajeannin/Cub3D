/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:57:37 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/15 16:53:36 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_floor(t_game *game, char c)
{
	int	i;

	i = -1;
	while (game->floor[++i])
	{
	//	printf("is '%c' floor?  |  floor test : '%c'\n", c, game->floor[i]);
		if (game->floor[i] == c)
			return (0);
	}
	return (c);
}
