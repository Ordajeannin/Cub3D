/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_teleporteurs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:13:52 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/22 18:25:17 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_telep_info	*build_info_telep(char *name, char **map)
{
	t_telep_info	*node;

	node = malloc(sizeof(t_telep_info));
	if (!node)
		return (NULL);
	node->name_enter = name[0];
	node->x_enter = pos_in_map(map, name[0], 'x');
	node->y_enter = pos_in_map(map, name[0], 'y');
	node->name_exit = name[1];
	node->x_exit = pos_in_map(map, name[1], 'x');
	node->y_exit = pos_in_map(map, name[1], 'y');
	return (node);
}

t_telep	*build_struct_telep(char *name, char **map)
{
	t_telep	*node;

	node = malloc(sizeof(t_telep));
	if (!node)
		return (NULL);
	node->name = name;
	node->peer = build_info_telep(name, map);
	node->next = NULL;
	return (node);
}

void	build_node_telep(t_game *game, char x, char y)
{
	char	*name;
	t_telep	*telep;

	telep = game->telep;
	while (telep && telep->next != NULL)
		telep = telep->next;
	if (!is_in_map_and_floor(game->grid->map, game->floor, x)
		|| !is_in_map_and_floor(game->grid->map, game->floor, y))
		return ;
	name = calloc(sizeof(char), 3);
	if (!name)
		return ;
	name[0] = x;
	name[1] = y;
	if (telep)
		telep->next = build_struct_telep(name, game->grid->map);
	else
		telep = build_struct_telep(name, game->grid->map);
	if (!game->telep)
		game->telep = telep;
}

int	build_telep(t_game *game)
{
	int	i;

	i = 0;
	if (!game->telep_str)
		return (0);
	while (game->telep_str[i])
	{
		build_node_telep(game, game->telep_str[i + 1], game->telep_str[i + 2]);
		i += 4;
	}
	return (0);
}
