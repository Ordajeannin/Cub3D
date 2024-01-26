/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:14 by pkorsako          #+#    #+#             */
/*   Updated: 2024/01/26 17:05:48 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_started(char *str)//si un 1 est au début de ligne (sans les whitespace), la map commence
{
	int	i;

	i = 0;
	while(str[i] == ' ' || str[i] == '\t')// isspace, sans \n
		i ++;
	if (str[i] == '1' || str[i] == '0')
		return (1);
	return (0);
}

int	get_map_y(t_textures *map_utils)//récupère la hauteur de la map
{
	int		i;
	char	*str;
	int		fd;

	i = 0;
	fd = open("map.cub", O_RDONLY);
	str = go_to_map(fd, map_utils);
	while(str)
	{
		free(str);
		str = get_next_line(fd);
		i ++;
	}
	free(str);
	close(fd);
	return (i);
}

char	*go_to_map(int fd, t_textures *map_utils)//avance dans le fichier .cub jusqu'a trouver la map
{
	char *str;

	str = get_next_line(fd);
	while (str)
	{
		if (map_started(str))
		{
			// printf("map started on :%s\n", str);
			
			return (str);
		}
		if (map_utils)
			get_textures(str, map_utils);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	printf("no map?\n");
	exit(1);
}

int	is_player(char *str)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while(str && str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E'
			|| str[i] == 'W')
			player ++;	
		i ++;	
	}
	return (player);
}

void	build_map_line(char **map, int map_y)
{
	int	i;
	int	fd;
	int	player;

	player = 0;
	i = 1;
	fd = open("map.cub", O_RDONLY);
	map[0] = go_to_map(fd, NULL);
	// printf("map[0] :%s\n", map[0]);
	while (i <= map_y - 1)
	{
		map[i] = get_next_line(fd);
		player += is_player(map[i]);
		// if (map && map[i] && map[i][0] == '\n')
		// {
		// 	printf("break \n");
		// 	map[i] = NULL;
		// 	break;
		// }
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