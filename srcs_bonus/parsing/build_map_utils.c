/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:54:43 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/18 20:23:46 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_null_map(t_textures *map_info)
{
	map_info->ea = NULL;
	map_info->no = NULL;
	map_info->we = NULL;
	map_info->so = NULL;
	map_info->f = 0;
	map_info->c = 0;
	map_info->map = NULL;
}

void	set_player(t_textures *map_info, int x, int y, char p)
{
	map_info->p_x = x;
	map_info->p_y = y;
	if (p == 'N')
		map_info->p_direction = 90;
	if (p == 'E')
		map_info->p_direction = 0;
	if (p == 'W')
		map_info->p_direction = 180;
	if (p == 'S')
		map_info->p_direction = 270;
}

int	ft_open(int *fd, char *path)
{
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
	{
		printf("cannot open map\n");
		return (0);
	}
	return (1);
}

int	map_started(char *str, t_game *game)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i ++;
	if (str[i] == '1' || str[i] == '0' || is_in_list(str[i], game->wall))
		return (1);
	return (0);
}

int	init_map(int *i, int *fd, int *player, char *argv)
{
	*player = 0;
	*i = 1;
	if (!ft_open(fd, argv))
	{
		printf("open error\n");
		return (0);
	}
	return (1);
}
