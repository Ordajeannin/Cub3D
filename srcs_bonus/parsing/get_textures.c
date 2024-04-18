/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:35:50 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/18 21:06:52 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_textures(t_game *game)
{
	if (game->ceiling)
		free(game->ceiling);
	if (game->floor)
		free(game->floor);
	if (game->wall)
		free(game->wall);
}

int	how_much_c_in_str(char c, const char *str)
{
	int	c_count;
	int	i;

	c_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			c_count ++;
		i ++;
	}
	return (c_count);
}

char	*build_list(const char *str)
{
	char	*list;
	int		i;
	int		list_i;

	i = 0;
	list_i = 0;
	if (*str == 0)
		return (NULL);
	list = malloc(sizeof(char) * how_much_c_in_str(';', str) + 2);
	if (!list)
		return (NULL);
	while (str[i] && str[i] != '\n' && list_i < how_much_c_in_str(';', str) + 1)
	{
		if (str[i] != ';')
		{
			if (!ft_isalnum(str[i]))
				return (free(list), NULL);
			list[list_i] = str[i];
			list_i ++;
		}
		i ++;
	}
	list[list_i] = 0;
	return (list);
}

int	build_next_list(char *str, t_game *game)
{
	if (str && !strncmp(str, "CEILING=", 8))
	{
		if (game->ceiling)
		{
			printf("wall already exist\n");
			return (0);
		}
		game->ceiling = build_list(str + 8);
	}
	if (str && !strncmp(str, "TELEP=", 6))
	{
		if (game->telep_str)
		{
			printf("telep already exist\n");
			return (0);
		}
		game->telep_str = build_telep_str(str + 6);
		printf("game->telep_str :%s\n", game->telep_str);
	}
	return (1);
}

int	build_texture_list(char *str, t_game *game)
{
	if (str && !strncmp(str, "WALL=", 5))
	{
		if (game->wall)
		{
			printf("wall already exist\n");
			return (0);
		}
		game->wall = build_list(str + 5);
	}
	if (str && !strncmp(str, "FLOOR=", 6))
	{
		if (game->floor)
		{
			printf("wall already exist\n");
			return (0);
		}
		game->floor = build_list(str + 6);
	}
	if (!build_next_list(str, game))
		return (0);
	return (1);
}
