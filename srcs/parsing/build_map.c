/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:14 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/18 20:28:36 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_in_line(char *str, t_textures *map_info, int y)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (str && str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E'
			|| str[i] == 'W')
		{
			player ++;
			set_player(map_info, i, y, str[i]);
			str[i] = '0';
		}
		if (str[i] != 'N' && str[i] != 'S' && str[i] != 'E'
			&& str[i] != 'W' && str[i] != '0' && str[i] != '1'
			&& str[i] != ' ' && str[i] != '\n')
			player = 9999;
		i ++;
	}
	return (player);
}

/*
	récupère la hauteur de la map
*/
int	get_map_y(t_textures *map_info, char *map_path)
{
	int		i;
	char	*str;
	int		fd;

	i = 0;
	if (!ft_open(&fd, map_path))
		return (-1);
	str = go_to_map(fd, map_info);
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

int	valide_pre_map_str(const char *str)
{
	int	i;

	i = 0;
	if (!ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "NO", 2)
		|| !ft_strncmp(str, "EA", 2) || !ft_strncmp(str, "SO", 2)
		|| *str == 'F' || *str == 'C')
		return (1);
	while (str && str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i ++;
	}
	return (1);
}

/*
	avance dans le fichier .cub jusqu'a trouver la map
	si map_utils != NULL va également rechercher les textures
*/
char	*go_to_map(int fd, t_textures *map_utils)
{
	char	*str;

	str = get_next_line(fd);
	while (str)
	{
		if (map_started(str))
			return (str);
		if (map_utils)
		{
			if (!valide_pre_map_str(str) || !get_textures(str, map_utils))
			{
				printf("error in textures init\n");
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

int	build_map_line(t_textures *map_info, char **map, int map_y, char *argv)
{
	int	i;
	int	fd;
	int	player;

	if (!init_map(&i, &fd, &player, argv))
		return (0);
	map_info->x_max = 0;
	map[0] = go_to_map(fd, NULL);
	while (i <= map_y - 1)
	{
		map[i] = get_next_line(fd);
		if (map_info->x_max < (int)ft_strlen(map[i]))
			map_info->x_max = (int)ft_strlen(map[i]);
		player += is_player_in_line(map[i], map_info, i);
		i ++;
	}
	map[i] = NULL;
	close(fd);
	if (player != 1)
	{
		printf("invalid number player\n");
		return (0);
	}
	return (1);
}
