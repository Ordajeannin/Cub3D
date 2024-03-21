/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_max_dist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:43 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/20 15:39:47 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	define_axe(double orientation)
{
	if (orientation < 45 || orientation > 315
		|| (orientation > 135 && orientation < 225))
		return ('x');
	else
		return ('y');
}

int	define_move(double orientation)
{
	if (orientation > 45 && orientation < 225)
		return (-1);
	return (1);
}

void	make_move_x(t_game *game, int move, int x, int y)
{
	int	max_dist;

	max_dist = 0;
	while (game->grid->map[y][x] != '1')
	{
		x = x + move;
		max_dist ++;
	}
	game->player->m_d = max_dist * 64 + 1;
}

void	make_move_y(t_game *game, int move, int x, int y)
{
	int	max_dist;

	max_dist = 0;
	while (game->grid->map[y][x] != '1')
	{
		y = y + move;
		max_dist ++;
	}
	game->player->m_d = (max_dist - 1) * 64;
}

void	max_dist(t_game *game)
{
	char	axe;
	int		move;
	int		x;
	int		y;

	axe = define_axe(game->player->orientation);
	move = define_move(game->player->orientation);
	x = game->player->pos_x / 64;
	y = game->player->pos_y / 64;
	if (axe == 'x')
		make_move_x(game, move, x, y);
	else
		make_move_y(game, move, x, y);
	return ;
}
