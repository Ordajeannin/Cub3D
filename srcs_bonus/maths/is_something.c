/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <ajeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:57:37 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/18 16:24:23 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_floor(t_game *game, char c)
{
	int	i;

	i = -1;
	while (game->floor[++i])
	{
		if (game->floor[i] == c)
			return (0);
	}
	return (c);
}
