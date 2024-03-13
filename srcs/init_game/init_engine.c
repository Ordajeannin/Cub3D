/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:30:02 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/13 15:56:12 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_grid	*init_grid(t_game *game)
{
	t_grid	*grid;

	grid = malloc(sizeof(t_grid));
	if (!grid)
		return (NULL);
	grid->fov = 60;
	grid->half_fov = grid->fov >> 1;
//	grid->proj_plan_width = 320;
//	grid->proj_plan_height = 200;
	grid->proj_plan_width = SCREEN_WIDTH;
	grid->proj_plan_height = SCREEN_HEIGHT;
	grid->half_proj_plan_height = grid->proj_plan_height >> 1;
	grid->grid_width = 64;
	grid->dist_proj_plan = round((SCREEN_WIDTH >> 1) / tan(dtor(grid->half_fov)));
	grid->projected_factor = grid->grid_width * grid->dist_proj_plan;
//	printf("fov = %d | proj_plan_width = %d\n", grid->fov, grid->proj_plan_width);
	grid->angle_incr = (float)grid->fov / grid->proj_plan_width;
//	printf("angle_incr = %f\n", grid->angle_incr);
	grid->textures = game->textures;
	grid->map = game->textures->map;
	return (grid);
}

t_player	*init_player(t_game *game)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos_x = (game->textures->p_x * 64) + 32;
	player->pos_y = (game->textures->p_y * 64) + 32;
	player->orientation = (double)game->textures->p_direction;
	player->x_max = 1000000;
	player->y_max = 1000000;
	player->m_d = 1;
//	player.x_max = game->textures->x_max << 6;
//	player.y_max = game->textures->y_max << 6;
	return (player);
}
