/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <ajeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:11:20 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/18 16:26:55 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_moove_pos(int key_x, int key_y, t_game *game)
{
	double	angle;

	angle = game->player->orientation;
	if (key_y == XK_w && key_x == 0)
		player_move_collide(game, double_modulo(angle + FRONT, 360));
	else if (key_y == XK_w && key_x == XK_a)
		player_move_collide(game, double_modulo(angle + 45.0, 360));
	else if (key_x == XK_a && key_y == 0)
		player_move_collide(game, double_modulo(angle + LEFT, 360));
	else if (key_x == XK_a && key_y == XK_s)
		player_move_collide(game, double_modulo(angle + 135.0, 360));
	else if (key_y == XK_s && key_x == 0)
		player_move_collide(game, double_modulo(angle + BEHIND, 360));
	else if (key_y == XK_s && key_x == XK_d)
		player_move_collide(game, double_modulo(angle - 135.0, 360));
	else if (key_x == XK_d && key_y == 0)
		player_move_collide(game, double_modulo(angle + RIGHT, 360));
	else if (key_x == XK_d && key_y == XK_w)
		player_move_collide(game, double_modulo(angle - 45.0, 360));
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
	{
		if (key_y == 65362)
		{
			if ((player->moove_head + player->view_y) < SCREEN_HEIGHT)
				player->view_y += player->moove_head;
		}
		else
		{
			if ((player->view_y - player->moove_head) > 0)
				player->view_y -= player->moove_head;
		}
	}
}

void	ft_is_running(t_player *player, int key_run, int key_fast)
{
	if (key_run)
		player->speed = DIST_WALK * SPEED_UP;
	if (key_fast)
		player->speed = DIST_WALK * SPEED_UP;
}

void	ft_moove(t_player *player, t_game *game)
{
	player->speed = DIST_WALK;
	ft_is_running(player, player->moove[4], player->moove[5]);
	ft_moove_view(player, player->moove[0], player->moove[1]);
	ft_moove_pos(player->moove[2], player->moove[3], game);
}
