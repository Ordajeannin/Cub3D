/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_teleporteurs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <ajeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:13:52 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/18 20:03:53 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	add_used(char *used, char c)
{
	int	i;

	i = 0;
	while (used[i] && used[i] != c)
		i++;
	if (used[i] != c)
	{
		used[i] = c;
		return ('\0');
	}
	else
		return (c);
}

char *build_telep_str(char *str)
{
	char *result;
	char *used;
	int	i;
	int	flag;

	if (!str)
		return (NULL);
	printf("telep string = %s\n", str);
	result = calloc(sizeof(char), ft_strlen(str) + 1);
	used = calloc(sizeof(char), ft_strlen(str) + 1);
	if (!used || !result)
		return (NULL);
	i = 0;
	flag = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == '[' && flag == 0)
		{
			printf("on ouvre [\n");
			result[i] = str[i];
			flag = 1;
		}
		else if (flag != 0 && flag < 3
				&& !add_used(used, str[i]) && ft_isalnum(str[i]))
		{
			printf("on add un char\n");
			result[i] = str[i];
			flag++;
		}
		else if (str[i] == ']' && flag == 3)
		{
			printf("on ferme ]\n");
			result[i] = str[i];
			flag = 0;
		}
		else
		{
			printf("str[i] = %c  |  ", str[i]);
			printf("Bad syntax telep : [xy][ab][wd]\neach char should be unique both in peer and map\n");
			free(used);
			free(result);
			return (NULL);
		}
		i++;
	}
	free(used);
	return (result);
}

int	is_in_map_and_floor(char **map, char *floor, char c)
{
	int	x;
	int	y;
	int	flag;

	if (!ft_strchr(floor, c))
		return (0);
	y = 0;
	flag = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
				flag++;
			x++;
		}
		y++;
	}
	if (flag == 1)
		return (1);
	else
		return (0);
}

int	pos_in_map(char **map, char c, char flag_xy)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
			{
				if (flag_xy == 'x')
					return (x);
				else
					return (y);
			}
			x++;
		}
		y++;
	}
	return (0);
}

t_telep_info	*build_info_telep(char *name, char **map)
{
	t_telep_info	*node;

	node = malloc(sizeof(t_telep_info));
	if (!node)
		return (NULL);
	printf("STEP 3\n");
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
	printf("STEP 2\n");
	node->name = name;
	node->peer = build_info_telep(name, map);
	node->next = NULL;
	return (node);
	/*
	if (telep)
		telep->next = node;
	else
		telep = node;
*/
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
	printf("STEP 1\n");
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
	printf("name : %s\n", name);
}

void display_telep_liste(t_game *game)
{
	t_telep *telep;

	telep = game->telep;
	printf("\n\nHey, i want to display the list\n");
	while (telep)
	{
		printf("telep->name = %s\n", telep->name);
		telep = telep->next;
	}
}

int	build_telep(t_game *game)
{
	int	i;

	i = 0;
	if (!game->telep_str)
		return (0);
	printf("\n\n");
	while (game->telep_str[i])
	{
		build_node_telep(game, game->telep_str[i + 1], game->telep_str[i + 2]);
		i += 4;
	}
	display_telep_liste(game);
	return (0);
}
