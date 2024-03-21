/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:49:58 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/20 14:27:39 by ajeannin         ###   ########.fr       */
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
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->player->moove[i] == keycode)
			game->player->moove[i] = 0;
		i++;
	}
	return (0);
}

/*
//gestion du point de vue du jouer, sur base d'un vecteur? oldxy / newxy?
int handle_mouse(int keycode, int x, int y, t_game *game)
{
	if (keycode == 1)
	   game->textures->p_y = x - y;
	else
		return (0);
	render(game);
	return (0);
}
*/
/*
 Le programme affiche l’image dans une fenêtre et respecte les règles suivantes :
◦ Les touches flèches du gauche et droite du clavier doivent permettre de faire
une rotation de la caméra (regarder a gauche et a droite)
◦ Les touches W, A, S et D doivent permettre de déplacer la caméra (déplacement
du personnage)
◦ Appuyer sur la touche ESC doit fermer la fenêtre et quitter le programme
proprement
◦ Cliquer sur la croix rouge de la fenêtre doit fermer la fenêtre et quitter le
programme proprement
*/
