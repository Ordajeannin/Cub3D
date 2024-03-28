/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:43:49 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/26 21:05:59 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	double_modulo(double value, double modulo)
{
	while (value > modulo)
		value -= modulo;
	if (value < 0)
		value += modulo;
	return (value);
}

/*
 * Permet de gerer l'appel, en boucle, de toutes les colonnes composant l'image
 * Stock les unsigned int dans un tableau, image[SCREEN_WIDTH]
 * appel en boucle proj_plan_col, gerant le casting d'un rayon
 * dont l'angle s'incremente (de gauche a droite... donc, en verite, decremente)
 * :warning: il faudra s'assurer que grid->angle_incr est correctement set
*/
unsigned int	*proj_plan_image(t_game *game, t_grid *grid)
{
	unsigned int	*image;
	int				i;
	double			angle;

	i = 0;
	image = malloc(sizeof(unsigned int) * (SCREEN_WIDTH + 1));
	if (!image)
		return (0);
	angle = double_modulo((game->player->orientation + grid->half_fov), 360);
	while (i < SCREEN_WIDTH)
	{
		printf("___________________\ni : %d\nangle value : %f\n", i, angle);
		image[i] = proj_plan_col_test(game, angle);
		angle -= grid->angle_incr;
		if (angle < 0)
			angle += 360;
		i++;
	}
	image[i] = '\0';
	return (image);
}

double	itod(double i, int p_d)
{
	double	index;
	double	proj_dist;
	double	result;

	index = (double)i;
	proj_dist = (double)p_d;
	result = index / proj_dist;
	return (result);
}

double	proj_plan_image_norme(int i, double orientation, t_game *game)
{
	double	dist;
	double	angle;

	dist = 0;
	if (i < HALF_WIDTH)
	{
		dist = (HALF_WIDTH - i);
		angle = double_modulo(orientation
				+ rtod(atan(itod(dist, game->grid->dist_proj_plan))), 360);
	}
	else
	{
		dist = (i - HALF_WIDTH);
		angle = double_modulo(orientation
				- rtod(atan(itod(dist, game->grid->dist_proj_plan))), 360);
	}
	return (angle);
}

unsigned int	*proj_plan_image_test(t_game *game, double orientation)
{
	unsigned int	*image;
	int				i;
//	double			angle;

	i = 0;
	image = malloc(sizeof(unsigned int) * (SCREEN_WIDTH + 1));
	if (!image)
		return (0);
	while (i < SCREEN_WIDTH)
	{
		game->angle[i] = proj_plan_image_norme(i, orientation, game);
		image[i] = proj_plan_col_test(game, game->angle[i]);
		i++;
	}
//	view_stocked_image(image);
	image[i] = '\0';
	return (image);
}
