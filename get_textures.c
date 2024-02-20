/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:35:50 by pkorsako          #+#    #+#             */
/*   Updated: 2024/02/20 17:11:49 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

void	free_textures(t_textures *textures)
{
	if (textures->NO)
		free(textures->NO);
	if (textures->SO)
		free(textures->SO);
	if (textures->EA)
		free(textures->EA);
	if (textures->WE)
		free(textures->WE);
	if (textures->C)
		free(textures->C);
	if (textures->F)
		free(textures->F);
}

int	*atorgb(char *str)
{
	int		*rgb;
	int		i;
	char	*tmp;

	i = 0;
	rgb = malloc(sizeof(int) * 4);
	if (!rgb)
	{
		printf("malloc error\n");
		exit (1);
	}
	while (i < 3)
	{
		tmp = ft_strdupto_n(str, ',');
		rgb[i] = atoi(str);
		str = strchr(str, ',') + 1;
		free(tmp);
		i ++;
	}
	rgb[3] = 0;
	return (rgb);
}

void	get_fandc_rgb(char *str, t_textures *map_info)
{
	if (str && !strncmp(str, "F ", 2))
	{
		if (map_info->F)
		{
			printf("floor error\n");
			exit (1);
		}
		map_info->F = atorgb(str + 2);
	}
	if (str && !strncmp(str, "C ", 2))
	{
		if (map_info->C)
		{
			printf("celing error\n");
			exit (1);
		}
		map_info->C = atorgb(str + 2);
	}
}

void	get_next_textures(char *str, t_textures *map_info)
{
	if (str && !strncmp(str, "WE ", 3))
	{
		if (map_info->WE)
		{
			printf("texture error\n");
			exit (1);
		}
		map_info->WE = ft_strdup(str + 3);
		map_info->WE[ft_strlen(map_info->WE) - 1] = 0;
	}
	if (str && !strncmp(str, "EA ", 3))
	{
		if (map_info->EA)
		{
			printf("texture error\n");
			exit (1);
		}
		map_info->EA = ft_strdup(str + 3);
		map_info->EA[ft_strlen(map_info->EA) - 1] = 0;
	}
	get_fandc_rgb(str, map_info);
}

void	get_textures(char *str, t_textures *map_info)
{
	if (str && !strncmp(str, "NO ", 3))
	{
		if (map_info->NO)
		{
			printf("texture error\n");
			exit (1);
		}
		map_info->NO = ft_strdup(str + 3);
		map_info->NO[ft_strlen(map_info->NO) - 1] = 0;
	}
	if (str && !strncmp(str, "SO ", 3))
	{
		if (map_info->SO)
		{
			printf("texture error\n");
			exit (1);
		}
		map_info->SO = ft_strdup(str + 3);
		map_info->SO[ft_strlen(map_info->SO) - 1] = 0;
	}
	get_next_textures(str, map_info);
}
