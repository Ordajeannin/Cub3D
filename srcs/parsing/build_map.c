/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:14 by pkorsako          #+#    #+#             */
/*   Updated: 2024/02/22 19:44:49 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char *str)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (str && str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E'
			|| str[i] == 'W')
			player ++;
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
		quit_w_message("cannot open map");
	str = go_to_map(fd, map_info);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		i ++;
	}
	free(str);
	close(fd);
	return (i);
}

/*
	avance dans le fichier .cub jusqu'a trouver la map
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
			get_textures(str, map_utils);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	printf("no map found in file\n");
	exit(1);
}

void	build_map_line(char **map, int map_y, char *argv)
{
	int	i;
	int	fd;
	int	player;

	player = 0;
	i = 1;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		quit_w_message("cannot open map");
	map[0] = go_to_map(fd, NULL);
	while (i <= map_y - 1)
	{
		map[i] = get_next_line(fd);
		player += is_player(map[i]);
		i ++;
	}
	map[i] = NULL;
	if (player != 1)
	{
		printf("number of player invalid\n");
		exit(0);
	}
	close(fd);
}
