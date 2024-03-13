/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tler.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:32:16 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/13 16:47:45 by ajeannin         ###   ########.fr       */
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
	int i_px2;
	int i_px3;
	double res;

	i_px = 0;
	i_px2 = 0;
	i_px3 = 0;
	res = 0;

	if (angle < 90.0)
		i_px3 = p->pos_x + ((p->pos_y - i_py) * tan(dtor(90.0 - angle)));
	else if (angle < 180.0)
		i_px3 = p->pos_x - ((p->pos_y - i_py) * tan(dtor(angle - 90.0)));
	else if (angle < 270.0)
		i_px3 = p->pos_x - ((i_py - p->pos_y) * tan(dtor(270.0 - angle)));
	else
		i_px3 = p->pos_x + ((i_py - p->pos_y) * tan(dtor(angle - 270.0)));

	if (angle < 90.0)
		i_px2 = round(p->pos_x + ((p->pos_y - i_py) * tan(dtor(90.0 - angle))));
	else if (angle < 180.0)
		i_px2 = round(p->pos_x - ((p->pos_y - i_py) * tan(dtor(angle - 90.0))));
	else if (angle < 270.0)
		i_px2 = round(p->pos_x - ((i_py - p->pos_y) * tan(dtor(270.0 - angle))));
	else
		i_px2 = round(p->pos_x + ((i_py - p->pos_y) * tan(dtor(angle - 270.0))));

	if (angle < 90)
	{
		res = (((double)p->pos_y - (double)i_py) * tan(dtor(90.0 - angle)));
		i_px = p->pos_x + (int)res;
	}
	else if (angle < 180)
	{
		res = (((double)p->pos_y - (double)i_py) * tan(dtor(angle - 90.0)));
		i_px = p->pos_x - (int)res;
	}
	else if (angle < 270)
	{
		res = (((double)i_py - (double)p->pos_y) * tan(dtor(270.0 - angle)));
		i_px = p->pos_x - (int)res;
	}
	else
	{
		res = (((double)i_py - (double)p->pos_y) * tan(dtor(angle - 270.0)));
		i_px = p->pos_x + (int)res;
	}
	return (i_px2);
}

//same for coll
int get_ipy(t_player *p, int i_px, double angle)
{
	int	i_py;
	int i_py2;
	int i_py3;
	double res;

	i_py = 0;
	i_py2 = 0;
	i_py3 = 0;
	res = 0;

	if (angle < 90.0)
		i_py3 = p->pos_y - ((i_px - p->pos_x) * tan(dtor(angle)));
	else if (angle < 180.0)
		i_py3 = p->pos_y - ((p->pos_x - i_px) * tan(dtor(180.0 - angle)));
	else if (angle < 270.0)
		i_py3 = p->pos_y + ((p->pos_x - i_px) * tan(dtor(angle - 180.0)));
	else
		i_py3 = p->pos_y + ((i_px - p->pos_x) * tan(dtor(360.0 - angle)));

	if (angle < 90.0)
		i_py2 = round(p->pos_y - ((i_px - p->pos_x) * tan(dtor(angle))));
	else if (angle < 180)
		i_py2 = round(p->pos_y - ((p->pos_x - i_px) * tan(dtor(180.0 - angle))));
	else if (angle < 270)
		i_py2 = round(p->pos_y + ((p->pos_x - i_px) * tan(dtor(angle - 180.0))));
	else
		i_py2 = round(p->pos_y + ((i_px - p->pos_x) * tan(dtor(360.0 - angle))));

	if (angle < 90.0)
	{
		res = (((double)i_px - (double)(p->pos_x)) * tan(dtor(angle)));
		i_py = p->pos_y - (int)res;
	}
	else if (angle < 180.0)
	{
		res = (((double)p->pos_x - (double)i_px) * tan(dtor(180.0 - angle)));
		i_py = p->pos_y - (int)res;
	}
	else if (angle < 270.0)
	{
		res = (((double)p->pos_x - (double)i_px) * tan(dtor(angle - 180.0)));
		i_py = p->pos_y + (int)res;
	}
	else
	{
		res = (((double)i_px - (double)p->pos_x) * tan(dtor(360.0 - angle)));
		i_py = p->pos_y + (int)res;
	}
//	printf("old = %d | new = %d\n", i_py2, i_py);
	return (i_py2);
}

