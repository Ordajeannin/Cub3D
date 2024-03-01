/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tler.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:32:16 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/01 15:54:07 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//i_px, for lines intersections;
//based on the fact that tan(beta) = op/adj
//-> op = adj * tan(beta)
//
//have to find beta from alpha (angle of the ray), so we could use * and not /
//(use less ressources)
int get_ipx(t_player *p, int i_py, double angle)
{
	int	i_px;

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

//same for coll
int get_ipy(t_player *p, int i_px, double angle)
{
	int	i_py;

	i_py = 0;
	if (angle < 90.0)
		i_py = p->pos_y - ((i_px - p->pos_x) * tan(dtor(angle)));
	else if (angle < 180)
		i_py = p->pos_y - ((p->pos_x - i_px) * tan(dtor(180.0 - angle)));
	else if (angle < 270)
		i_py = p->pos_y + ((p->pos_x - i_px) * tan(dtor(angle - 180.0)));
	else
		i_py = p->pos_y + ((i_px - p->pos_x) * tan(dtor(360.0 - angle)));
	return (i_py);
}

