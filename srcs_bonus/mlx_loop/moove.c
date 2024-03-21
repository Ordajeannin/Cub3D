/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:11:20 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/20 14:19:48 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//deplacement constant? trigo? si droit ou diagonale, distance variable?
void	ft_moove_pos(int key_x, int key_y, t_game *game)
{
	if (key_x != 0)
	{
		if (key_x == XK_a)
			player_move_collide(game, game->player->orientation + LEFT);
		else
			player_move_collide(game, game->player->orientation + RIGHT);
	}
	if (key_y != 0)
	{
		if (key_y == XK_w)
			player_move_collide(game, game->player->orientation + FRONT);
		else
			player_move_collide(game, game->player->orientation + BEHIND);
	}
}

void	ft_moove_view(t_player *player, int key_x, int key_y)
{
	if (key_x != 0)
	{
		if (key_x == 65361)
			player->orientation = double_modulo(player->orientation
					+ TURN_RATE, 360);
		else
			player->orientation = double_modulo(player->orientation
					- TURN_RATE, 360);
	}
	if (key_y != 0)
		return ;
}

void	ft_moove(t_player *player, t_game *game)
{
	ft_moove_view(player, player->moove[0], player->moove[1]);
	ft_moove_pos(player->moove[2], player->moove[3], game);
}
