/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_usefull_calcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:32:36 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/26 20:52:01 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Permet de convertir une variable de degrees a radian
 * (necessaire pour les fonctions trigo)
*/
double dtor(double degrees)
{
	return (degrees * 0.0174533);
}

// /*
//  * Permet de determiner la distance absolue entre 2 points dans un repere
//  * (ici, du joueur a une intersection)
// */
// int ft_dist(int x1, int y1, int x2, int y2)
// {
// 	return ((int)sqrt(((x2 -x1) ^ 2) + ((y2 - y1) ^ 2)));
// }

/*
 * Permet d'isoler une valeur precise, pour une colonne donnee 
 * A une colonne corespond un unsigned int, ordonnee ainsi :
 * 
 * Face (du block), sur 2 bits (4 faces)
 * Offset (colonne de la texture a considerer), sur 6 bits (0->63)
 * Texture (sprite du block), sur 4 bits (16 textures dispo, on est large)
 * Distance, du joueur au block (en units), sur 20 bits
 *
 * usage : distance = get_value(stock, "DISTANCE")
*/
int	get_value(unsigned int value, const char *flag)
{
	if (ft_strncmp(flag, "FACE", 4) == 0)
		return (value & FACE_MASK);
	else if (ft_strncmp(flag, "OFFSET", 6) == 0)
		return ((value >> 2) & OFFSET_MASK);
	else if (ft_strncmp(flag, "TEXTURE", 7) == 0)
		return ((value >> 8) & TEXTURE_MASK);
	else if (ft_strncmp(flag, "DISTANCE", 8) == 0)
		return ((value >> 12) & DIST_MASK);
	else
		return (-1);
}
