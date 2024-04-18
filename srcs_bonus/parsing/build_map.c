/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:14 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/18 17:41:15 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_player_in_line(char *str, t_textures *map_info, int y, t_game *game)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (str && str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			player ++;
			set_player(map_info, i, y, str[i]);
			str[i] = game->floor[0];
		}
		if (str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W'
			&& str[i] != '0' && str[i] != '1' && str[i] != ' ' && str[i] != '\n'
			&& !is_in_list(str[i], game->ceiling)
			&& !is_in_list(str[i], game->floor)
			&& !is_in_list(str[i], game->wall))
		{
			printf("%c is unidentified\n", str[i]);
			player = 42;
		}
		i ++;
	}
	return (player);
}

/*
	récupère la hauteur de la map
*/
int	get_map_y(t_textures *map_info, char *map_path, t_game *game)
{
	int		i;
	char	*str;
	int		fd;

	i = 0;
	if (!ft_open(&fd, map_path))
		return (-1);
	str = go_to_map(fd, game, 1);
	if (!str)
	{
		close(fd);
		return (-1);
	}
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		i ++;
	}
	free(str);
	close(fd);
	map_info->y_max = i;
	return (i);
}

int	w_f_c_set(t_game *game)
{
	if (game->ceiling && game->wall && game->floor)
		return (1);
	return (0);
}

/*
	avance dans le fichier .cub jusqu'a trouver la map
	si map_utils != NULL va également rechercher les textures
*/
char	*go_to_map(int fd, t_game *game, int flag)
{
	char	*str;

	str = get_next_line(fd);
	while (str)
	{
		if (w_f_c_set(game) && map_started(str, game))
			return (str);
		if (flag == 1)
		{
			if (!build_texture_list(str, game))
			{
				printf("je renvoi 0 sur cette sting :%s\n", str);
				free(str);
				return (NULL);
			}
		}
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	printf("no map found in file\n");
	return (NULL);
}

int	build_map_line(t_textures *map_info, int map_y, char *argv, t_game *game)
{
	int	i;
	int	fd;
	int	player;

	if (!init_map(&i, &fd, &player, argv))
		return (0);
	map_info->x_max = 0;
	map_info->map[0] = go_to_map(fd, game, 0);
	while (i <= map_y - 1)
	{
		map_info->map[i] = get_next_line(fd);
		if (map_info->x_max < (int)ft_strlen(map_info->map[i]))
			map_info->x_max = (int)ft_strlen(map_info->map[i]);
		player += is_player_in_line(map_info->map[i], map_info, i, game);
		i ++;
	}
	map_info->map[i] = NULL;
	close(fd);
	if (player != 1)
	{
		printf("invalid number player\n");
		return (0);
	}
	return (1);
}
