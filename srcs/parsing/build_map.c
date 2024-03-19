/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:14 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/19 17:22:50 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char *str, t_textures *map_info, int y)
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
		i ++;
	}
	return (player);
}

/*
	si un 1 est au début de ligne
	(sans les whitespace), la map commence
*/
int	map_started(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t') //isspace, sans \n
		i ++;
	if (str[i] == '1' || str[i] == '0')
		return (1);
	return (0);
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
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		printf("cannot open map\n");
		return (-1);
	}
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

/*
	avance dans le fichier .cub jusqu'a trouver la map
	si map_utils != NULL va également rechercher les textures
*/
char	*go_to_map(int fd, t_textures *map_utils)
{
	char	*str;
	// int i = 0;

	str = get_next_line(fd);
	while (str)
	{
		if (map_started(str))
			return (str);
		if (map_utils)
		{
			if (!get_textures(str, map_utils))
			{
				printf("je renvoi 0 sur cette sting :%s\n", str);
				free(str);
				return (NULL);	
			}
		}
		free(str);
		str = get_next_line(fd);
		// printf("i :%d\tgnl return string %ld char long\n", i ++, ft_strlen(str));
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

	player = 0;
	map_info->x_max = 0;
	i = 1;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		printf("cannot open map\n");
		return (0);
	}
	map[0] = go_to_map(fd, NULL);
	while (i <= map_y - 1)
	{
		map[i] = get_next_line(fd);
		if (map_info->x_max < (int)ft_strlen(map[i]))
			map_info->x_max = (int)ft_strlen(map[i]);
		player += is_player(map[i], map_info, i);
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
