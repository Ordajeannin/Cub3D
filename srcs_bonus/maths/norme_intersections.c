/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:15:56 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/20 17:43:29 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_value1(double *xi, double *yi, double angle, int flag)
{
	if (flag == 1)
	{
		*xi = get_xi(angle);
		*yi = 64;
	}
	else
	{
		*xi = 64;
		*yi = get_yi(angle);
	}
}

void	set_value2lines(double *i_py, double *i_px,
		t_player *player, double angle)
{
	if (angle < 180)
		*i_py = (floor(player->pos_y / 64) * 64) - 0.000001;
	else
		*i_py = (floor(player->pos_y / 64) * 64) + 64;
	*i_px = get_ipx(player, *i_py, angle);
}

void	set_value2col(double *i_py, double *i_px,
		t_player *player, double angle)
{
	if (angle < 90 || angle > 270)
		*i_px = (floor(player->pos_x / 64) * 64) + 64;
	else
		*i_px = (floor(player->pos_x / 64) * 64) - 0.000001;
	*i_py = get_ipy(player, *i_px, angle);
}

void	update_ipx(double *ipx, double xi, double angle)
{
	if (angle > 270 || angle < 90)
		*ipx = *ipx + xi;
	else
		*ipx = *ipx - xi;
}

void	update_ipy(double *ipy, double yi, double angle)
{
	if (angle < 180)
		*ipy = *ipy - yi;
	else
		*ipy = *ipy + yi;
}
