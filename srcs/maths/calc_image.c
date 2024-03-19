/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:43:49 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/15 17:32:03 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
unsigned int *proj_plan_image(t_game *game, t_grid *grid)
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

double itod(double i, int p_d)
{
	double index = (double)i;
	double proj_dist = (double)p_d;
	double result = 0;

	result = index / proj_dist;
//	printf("result = %f  |  ", result);
	return (result);
}

unsigned int *proj_plan_image_test(t_game *game, double orientation)
{
	unsigned int *image;
	double dist;
	int i = 0;
	double angle;

	image = malloc(sizeof(unsigned int) * (SCREEN_WIDTH + 1));
	if (!image)
		return (0);
	dist = 0;
	while (i < SCREEN_WIDTH)
	{
//		printf("i = %d  |  ", i);
		if (i < HALF_WIDTH)
		{
//			dist = (HALF_WIDTH - i) * dist_incr;
			dist = (HALF_WIDTH - i);
//			printf("dist = %f  |  ", dist);
			angle = double_modulo(orientation + rtod(atan(itod(dist, game->grid->dist_proj_plan))), 360);
	//		printf("atan(%f) = %f  |  ", itod(dist, 277), rtod(atan(itod(dist, 277))));
		}
		else
		{
//			dist = (i - HALF_WIDTH) * dist_incr;
			dist = (i - HALF_WIDTH);
//			printf("dist = %f  |  ", dist);
			angle = double_modulo(orientation - rtod(atan(itod(dist, game->grid->dist_proj_plan))), 360);
	//		printf("atan(%f) = %f  |  ", itod(dist, 277), rtod(atan(itod(dist, 277))));
		}
//		printf("angle = %f\n", angle);
		// printf("\n\nindex : %d  |  ", i);
		// printf("angle : %f\n", angle);
	//	printf("player(%d, %d)\n", (game->player->pos_y >> 6) + 1, (game->player->pos_x >> 6) + 1);
		image[i] = proj_plan_col_test(game, angle);
		i++;
	}
	image[i] = '\0';
	return (image);
}