/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_usefull_calcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:32:36 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/08 16:54:41 by ajeannin         ###   ########.fr       */
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

double rtod(double radian)
{
	return (radian * 57.2958);
}

// /*
//  * Permet de determiner la distance absolue entre 2 points dans un repere
//  * (ici, du joueur a une intersection)
// */
int ft_dist(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int value = (int)sqrt((dx * dx) + (dy * dy));
//	printf("distance from P(%d, %d) to I(%d, %d) = %d\n", x1, y1, x2, y2, value);
	return (value);
}

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
	int result = 0;
	if (ft_strncmp(flag, "FACE", 4) == 0)
		return (value & FACE_MASK);
	else if (ft_strncmp(flag, "OFFSET", 6) == 0)
		return ((value >> 2) & OFFSET_MASK);
	else if (ft_strncmp(flag, "TEXTURE", 7) == 0)
		return ((value >> 8) & TEXTURE_MASK);
	else if (ft_strncmp(flag, "DISTANCE", 8) == 0)
	{
		result = (value >> 12) & DIST_MASK;
		if (result != 0)
			return result;
		else
			return (1);
//		printf("distance recuperee : %d\n", ((value >> 12) & DIST_MASK));
//		return ((value >> 12) & DIST_MASK);
	}
	else
		return (-1);
}
