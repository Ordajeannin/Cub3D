/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_usefull_calcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:32:36 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/22 21:33:06 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double dtor(double degrees)
{
	return (radian * 0.0174533);
}

int ft_dist(int x1, int y1, int x2, int y2)
{
	return ((int)sqrt(((x2 -x1) ^ 2) + ((y2 - y1) ^ 2)));
}
