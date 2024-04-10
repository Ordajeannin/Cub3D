/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:35:50 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/10 19:17:01 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_textures(t_textures *textures)
{
	if (textures->no)
		free(textures->no);
	if (textures->so)
		free(textures->so);
	if (textures->ea)
		free(textures->ea);
	if (textures->we)
		free(textures->we);
}

char	*ft_str_rm_spaces(char *str)
{
	char	*new;
	int		end;

	while (str && *str && ft_isspace(*str))
		str ++;
	end = ft_strlen(str) - 1;
	while (str && end >= 0 && ft_isspace(str[end]))
		end --;
	new = malloc(sizeof(char) * end + 2);
	ft_strlcpy(new, str, end + 2);
	return (new);
}

int	get_f_and_c(char *str, t_textures *map_info)
{
	static int	floor;
	static int	celling;

	if (str && !ft_strncmp(str, "F ", 2))
	{
		if (floor)
		{
			printf("floor error\n");
			return (0);
		}
		floor = 1;
		map_info->f = atorgb(ft_str_rm_spaces(str + 1));
	}
	if (str && !strncmp(str, "C ", 2))
	{
		if (celling)
		{
			printf("celing error\n");
			return (0);
		}
		celling = 1;
		map_info->c = atorgb(ft_str_rm_spaces(str + 1));
	}
	return (1);
}

int	get_next_textures(char *str, t_textures *map_info)
{
	if (str && !strncmp(str, "WE ", 3))
	{
		if (map_info->we)
		{
			printf("texture error\n");
			return (0);
		}
		map_info->we = ft_str_rm_spaces(str + 2);
	}
	if (str && !strncmp(str, "EA ", 3))
	{
		if (map_info->ea)
		{
			printf("texture error\n");
			return (0);
		}
		map_info->ea = ft_str_rm_spaces(str + 2);
	}
	if (!get_f_and_c(str, map_info))
		return (0);
	return (1);
}

int	get_textures(char *str, t_textures *map_info)
{
	if (str && !strncmp(str, "NO", 2) && ft_isspace(str[2]))
	{
		if (map_info && map_info->no)
		{
			printf("texture error\n");
			return (0);
		}
		map_info->no = ft_str_rm_spaces(str + 2);
	}
	if (str && !strncmp(str, "SO ", 3) && ft_isspace(str[2]))
	{
		if (map_info->so)
		{
			printf("texture error\n");
			return (0);
		}
		map_info->so = ft_str_rm_spaces(str + 2);
	}
	if (!get_next_textures(str, map_info))
		return (0);
	return (1);
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
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ';')
		{
			list[list_i] = str[i];
			list_i ++;
		}
		i ++;
	}
	list[list_i] = 0;
	// printf("list :%s\n", list);
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
		printf("game->ceiling :%s\n", game->ceiling);
	}
	return (1);
}

int	build_texture_list(char *str, t_game *game)
{
	// printf("extracting from str :%s\n", str);
	if (str && !strncmp(str, "WALL=", 5))
	{
		if (game->wall)
		{
			printf("wall already exist\n");
			return (0);
		}
		game->wall = build_list(str + 5);
		printf("game->wall :%s\n", game->wall);
	}
	if (str && !strncmp(str, "FLOOR=", 6))
	{
		if (game->floor)
		{
			printf("wall already exist\n");
			return (0);
		}
		game->floor = build_list(str + 6);
		printf("game->floor :%s\n", game->floor);
	}
	if (!build_next_list(str, game))
		return (0);
	return (1);
}
