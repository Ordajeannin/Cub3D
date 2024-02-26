/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <ajeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:43:49 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/26 21:36:19 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	double_modulo(double value, double modulo)
{
	while (value > modulo)
		value -= modulo;
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
	image = malloc(sizeof(unsigned int) * SCREEN_WIDTH + 1);
	if (!image)
		return (0);
//	angle = (game->player->orientation + grid->half_fov) % 360;
	angle = double_modulo((game->player->orientation + grid->half_fov), 360);
//	printf("2.1\n");
	while (i < SCREEN_WIDTH)
	{
		image[i] = proj_plan_col(game, angle);
		angle -= grid->angle_incr;
		if (angle < 0)
			angle += 360;
		i++;
//		printf("2.x\n");
	}
//	printf("HEYYYYYYYYYY\n");
	image[i] = '\0';
	return (image);
}


//il faut transmettre l'offset aussi!
//valeur max : 63
//stockage sur 6 bits
//donc on aura :
//face (2 bits)
//offset (6 bits)
//texture (4 bits)
//distance (20 bits)
