/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:23:00 by paulk             #+#    #+#             */
/*   Updated: 2024/04/18 20:12:18 by pkorsako         ###   ########.fr       */
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

void	quit_w_message(char *str)
{
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

int	is_inside(char c, t_game *game)
{
	if (is_in_list(c, game->floor))
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (2);
	else
		return (0);
}
