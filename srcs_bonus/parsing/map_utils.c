/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:23:00 by paulk             #+#    #+#             */
/*   Updated: 2024/03/20 16:02:52 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_strdupto_n(char *str, char c)
{
	char	*tab;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!str || !str[i])
		return (NULL);
	while (str[i] && str[i] != c)
	{
		len ++;
		i ++;
	}
	tab = calloc((len +1), sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		tab[i] = str[i];
		i ++;
	}
	tab[i] = '\0';
	return (tab);
}

void	quit_w_message(char *str, t_textures *map_info)
{
	if (map_info && 1 == 2)
		free_textures(map_info);
	printf("%s\n", str);
	exit(1);
}

void	free_tab(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i ++;
	}
	free(map);
}

int	valid_char(char **map, int y, int x)
{
	static int	starter;

	if (map[y][x] == '1' || map[y][x] == '0')
		return (1);
	if (map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'E' || map[y][x] == 'W')
	{
		if (starter)
			return (0);
		starter ++;
		map[y][x] = '0';
		return (1);
	}
	else
		return (0);
}

int	is_inside(char c)
{
	if (c == '0' )
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (2);
	else
		return (0);
}
