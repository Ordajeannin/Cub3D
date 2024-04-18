/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_usefull_calcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <ajeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:32:36 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/18 16:24:57 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
 * Permet de convertir une variable de degrees a radian
 * (necessaire pour les fonctions trigo)
*/
double	dtor(double degrees)
{
	return (degrees * 0.0174533);
}

double	rtod(double radian)
{
	return (radian * 57.2957795);
}

/*
 * Permet de determiner la distance absolue entre 2 points dans un repere
 * (ici, du joueur a une intersection)
*/
double	ft_dist(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;
	double	value;

	dx = x2 - x1;
	dy = y2 - y1;
	value = sqrt((dx * dx) + (dy * dy));
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
	int	result;

	result = 0;
	if (ft_strncmp(flag, "FACE", 4) == 0)
		return (value & FACE_MASK);
	else if (ft_strncmp(flag, "OFFSET", 6) == 0)
		return ((value >> 2) & OFFSET_MASK);
	else if (ft_strncmp(flag, "TEXTURE", 7) == 0)
		return ((value >> 8) & TEXTURE_MASK);
	else if (ft_strncmp(flag, "DISTANCE", 8) == 0)
	{
		result = (value >> 16) & DIST_MASK;
		if (result != 0)
			return (result);
		else
			return (1);
	}
	else
		return (-1);
}
