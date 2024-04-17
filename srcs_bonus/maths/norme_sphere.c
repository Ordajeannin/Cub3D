/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:03:41 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/17 17:11:52 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	get_ipx_sphere(t_player *p, double i_py, double angle)
{
	double	i_px;

	i_px = 0;
	if (angle < 90.0)
		i_px = p->temp_x + ((p->temp_y - i_py) * tan(dtor(90.0 - angle)));
	else if (angle < 180.0)
		i_px = p->temp_x - ((p->temp_y - i_py) * tan(dtor(angle - 90.0)));
	else if (angle < 270.0)
		i_px = p->temp_x - ((i_py - p->temp_y) * tan(dtor(270.0 - angle)));
	else
		i_px = p->temp_x + ((i_py - p->temp_y) * tan(dtor(angle - 270.0)));
	return (i_px);
}

double	get_ipy_sphere(t_player *p, double i_px, double angle)
{
	double	i_py;

	i_py = 0;
	if (angle < 90.0)
		i_py = p->temp_y - ((i_px - p->temp_x) * tan(dtor(angle)));
	else if (angle < 180.0)
		i_py = p->temp_y - ((p->temp_x - i_px) * tan(dtor(180.0 - angle)));
	else if (angle < 270.0)
		i_py = p->temp_y + ((p->temp_x - i_px) * tan(dtor(angle - 180.0)));
	else
		i_py = p->temp_y + ((i_px - p->temp_x) * tan(dtor(360.0 - angle)));
	return (i_py);
}

void	set_value2lines_sphere(double *i_py, double *i_px,
		t_player *player, double angle)
{
	if (angle < 180)
		*i_py = (floor(player->pos_y / 64) * 64) - 0.000001;
	else
		*i_py = (floor(player->pos_y / 64) * 64) + 64;
	*i_px = get_ipx_sphere(player, *i_py, angle);
}

void	set_value2col_sphere(double *i_py, double *i_px,
		t_player *player, double angle)
{
	if (angle < 90 || angle > 270)
		*i_px = (floor(player->pos_x / 64) * 64) + 64;
	else
		*i_px = (floor(player->pos_x / 64) * 64) - 0.000001;
	*i_py = get_ipy_sphere(player, *i_px, angle);
}
