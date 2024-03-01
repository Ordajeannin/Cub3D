/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:49:58 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/01 18:01:10 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

//fermeture propre de la fenetre, rien de +
int	handle_close(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	mlx_destroy_image(game->mlx, game->img);
	return (0);
}

void	player_move(t_player *player, double angle)
{
	int dist;

	dist = DIST_WALK;
	angle = double_modulo(angle, 360);
	if (angle < 90)
	{
		player->pos_x += dist * cos(dtor(angle));
		player->pos_y -= dist * sin(dtor(angle));
	}
	else if (angle < 180)
	{
		player->pos_x -= dist * sin(dtor(angle - 90.0));
		player->pos_y -= dist * cos(dtor(angle - 90.0));
	}
	else if (angle < 270)
	{
		player->pos_x -= dist * cos(dtor(angle - 180.0));
		player->pos_y += dist * sin(dtor(angle - 180.0));
	}
	else
	{
		player->pos_x += dist * sin(dtor(angle - 270.0));
		player->pos_y += dist * cos(dtor(angle - 270.0));
	}
}

//typiquement, gestion de la position du joueur avec les fleches
//futur lampe torche etc.
//ET escape!
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
		mlx_destroy_image(game->mlx, game->img);
	}
	if (keycode == XK_w || keycode == 65362)
		player_move(game->player, game->player->orientation + FRONT);
	if (keycode == XK_d)
		player_move(game->player, game->player->orientation + RIGHT);
	if (keycode == XK_s || keycode == 65364)
		player_move(game->player, game->player->orientation + BEHIND);
	if (keycode == XK_a)
		player_move(game->player, game->player->orientation + LEFT);
	if (keycode == 65361)
		game->player->orientation = double_modulo(game->player->orientation + TURN_RATE, 360);
	if (keycode == 65363)
		game->player->orientation = double_modulo(game->player->orientation - TURN_RATE, 360);
	printf("keycode : %d\n", keycode);
//	else if //keycode == x
			//alors y
//	else if //keycode == a
			//alors b
	//etc
	return (0);
}

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
