/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <ajeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:49:58 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/18 16:26:45 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//fermeture propre de la fenetre, rien de +
int	handle_close(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	mlx_destroy_image(game->mlx, game->img);
	return (0);
}

/*
 * tableau d'int :
 * moove[0] = vue, axe x;
 * moove[1] = vue, axe y;
 * moove[2] = deplacement, axe x;
 * moove[3] = deplacement, axe y;
 * NO_INPUT = 0
*/
int	handle_keypress_test(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
		mlx_destroy_image(game->mlx, game->img);
	}
	if (game->player->moove[0] == 0 && (keycode == 65361 || keycode == 65363))
		game->player->moove[0] = keycode;
	if (game->player->moove[1] == 0 && (keycode == 65362 || keycode == 65364))
		game->player->moove[1] = keycode;
	if (game->player->moove[2] == 0 && (keycode == XK_a || keycode == XK_d))
		game->player->moove[2] = keycode;
	if (game->player->moove[3] == 0 && (keycode == XK_w || keycode == XK_s))
		game->player->moove[3] = keycode;
	if (game->player->moove[4] == 0 && keycode == 65505)
		game->player->moove[4] = keycode;
	if (keycode == XK_r)
		game->player->moove[5] = abs(game->player->moove[5] - XK_r);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	int	i;

	i = 0;
	while (i <= 4)
	{
		if (game->player->moove[i] == keycode)
			game->player->moove[i] = 0;
		i++;
	}
	return (0);
}
