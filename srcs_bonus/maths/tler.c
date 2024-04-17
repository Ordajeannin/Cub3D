/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tler.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:32:16 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/17 17:47:02 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	get_xi(double angle)
{
	double	result;

	if (angle <= 90.0)
		result = 64 * tan(dtor(90.0 - angle));
	else if (angle > 90 && angle < 180)
		result = 64 * tan(dtor(angle - 90.0));
	else if (angle < 270)
		result = 64 * tan(dtor(270 - angle));
	else
		result = 64 * tan(dtor(angle - 270));
	return (result);
}

double	get_yi(double angle)
{
	double	result;

	if (angle <= 90)
		result = 64 * tan(dtor(angle));
	else if (angle > 90 && angle < 180)
		result = 64 * tan(dtor(180.0 - angle));
	else if (angle < 270)
		result = 64 * tan(dtor(angle - 180.0));
	else
		result = 64 * tan(dtor(360.0 - angle));
	return (result);
}

double	get_ipx(t_player *p, double i_py, double angle)
{
	double	i_px;

	i_px = 0;
	if (angle < 90.0)
		i_px = p->pos_x + ((p->pos_y - i_py) * tan(dtor(90.0 - angle)));
	else if (angle < 180.0)
		i_px = p->pos_x - ((p->pos_y - i_py) * tan(dtor(angle - 90.0)));
	else if (angle < 270.0)
		i_px = p->pos_x - ((i_py - p->pos_y) * tan(dtor(270.0 - angle)));
	else
		i_px = p->pos_x + ((i_py - p->pos_y) * tan(dtor(angle - 270.0)));
	return (i_px);
}

double	get_ipy(t_player *p, double i_px, double angle)
{
	double	i_py;

	i_py = 0;
	if (angle < 90.0)
		i_py = p->pos_y - ((i_px - p->pos_x) * tan(dtor(angle)));
	else if (angle < 180.0)
		i_py = p->pos_y - ((p->pos_x - i_px) * tan(dtor(180.0 - angle)));
	else if (angle < 270.0)
		i_py = p->pos_y + ((p->pos_x - i_px) * tan(dtor(angle - 180.0)));
	else
		i_py = p->pos_y + ((i_px - p->pos_x) * tan(dtor(360.0 - angle)));
	return (i_py);
}
