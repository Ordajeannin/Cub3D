/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:43:49 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/26 15:39:18 by paulk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Permet de gerer l'appel, en boucle, de toutes les colonnes composant l'image
 * Stock les unsigned int dans un tableau, image[SCREEN_WIDTH]
 * appel en boucle proj_plan_col, gerant le casting d'un rayon
 * dont l'angle s'incremente (de gauche a droite... donc, en verite, decremente)
 * :warning: il faudra s'assurer que grid->angle_incr est correctement set
*/
// unsigned int *proj_plan_image(t_game *game, t_grid *grid)
// {
// 	unsigned int	image[SCREEN_WIDTH];
// 	int				i;
// 	double			angle;

// 	i = 0;
// 	angle = (game->player->orientation + grid->half_fov) % 360;
// 	while (i < SCREEN_WIDTH)
// 	{
// 		image[i] = proj_plan_col(game, angle);
// 		angle -= grid->angle_incr;
// 		if (angle < 0)
// 			angle += 360;
// 		i++;
// 	}
// 	image[i] = '\0';
// 	return (image);
// }


//il faut transmettre l'offset aussi!
//valeur max : 63
//stockage sur 6 bits
//donc on aura :
//face (2 bits)
//offset (6 bits)
//texture (4 bits)
//distance (20 bits)
