/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:39:50 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/20 20:50:21 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_grid(t_grid *grid)
{
	grid->fov = 60;
	grid->half_fov = fov/2;
	grid->proj_plan_width = 320;
	grid->proj_plan_height = 200;
	grid->grid_width = 64;
	grid->angle_incr = fov/proj_plan_width;
	t_inter *lines = NULL;
	t_inter *col = NULL;
}

void	init_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->orientation = 0;
}

void	init_intersection(t_inter *list)
{
	list->grid_x = 0;
	list->grid_y = 0;
	list->pos_x = 0;
	list->pos_y = 0;
	list->next = NULL;
}

t_inter *create_arg(int pos_x, int pos_y)
{
	t_inter	*new_arg;

	new_arg = ft_calloc(1, sizeof(t_inter));
	if (!new_arg)
		return (NULL);
	new_arg->pos_x = pos_x;
	new_arg->pos_y = pos_y;
	new_arg->next = NULL;
	return (new_arg);
}

void	add_arg(t_inter **list, int pos_x, int pos_y)
{
	t_args	*new_arg;
	t_args	*current;

	new_arg = create_arg(pos_x, pos_y);
	if (!new_arg)
		return ;
	if (*list == NULL)
		*list = new_arg;
	else
	{
		current = *list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_arg;
	}
}

// :warning: true if grid_width = 64
// :warning: tan return a double value, any issue with pos_x?
void	list_lines_intersections(t_player player, t_grid grid, int angle)
{
	int pos_x = 0;
	int pos_y = 0;
	int xi = 64/tan(angle);
	int yi = 64;

	angle = angle % 360;
	if (angle < 180)
		pos_y = (player->pos_y >> 6) << 6 - 1;
	else
		pos_y = (player->pos_y >> 6) << 6 + 64;
	pos_x = player->pos_x + (player->pos_y - pos_y) / tan(angle);
	add_arg(pos_x, pos_y);
//	while (pos_x > 0 && pos_y > 0 && pos_x < x_max && pos_y < y_max)
	while (1)
	{
		if (angle > 180 || angle < 90)
			pos_x = pos_x + xi;
		else
			pos_x = pos_x - xi;
		if (angle < 180)
			pos_y = pos_y - yi;
		else
			pos_y = pos_y +yi;
		if (pos_x > 0 && pos_y > 0 && pos_x < x_max && pos_y < y_max)
			add_arg(pos_x, pos_y);
		else
			return ;
	}
}



