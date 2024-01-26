/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:35:50 by pkorsako          #+#    #+#             */
/*   Updated: 2024/01/26 17:51:52 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

char	*strdupto(char *str, char c)
{
	int		i;
	char	*dup;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c);
			break;
		i ++;
	}
	dup = malloc(i * sizeof(char));
	if (!dup)
		exit(0);
	i = 0;
	while (str && str[i] && str[i] != c)
	{
		dup[i] = str[i];
		i ++;
	}
	dup[i] = 0;
}

int	*atorgb(char *str)
{
	int	rgb[4];
	int	i;

	i = 0;
	while(i < 3)
	{
		rgb[0] = atoi(strdupto(str, ','));
		str = strchr(str, ',') + 1;
		i ++;
	}
	rgb[4] = 0;
}

void	get_textures(char *str, t_textures *map_info)
{
	// printf("%s\n", str);
	if (str && !strncmp(str, "NO ", 3))
	{
		if (map_info->NO)
		{
			printf("texture error\n");
			exit (1);
		}
		map_info->NO = str + 3;
	}
	if (str && !strncmp(str, "SO ", 3))
	{
		if (map_info->SO)
		{
			printf("texture error\n");
			exit (1);
		}
		map_info->SO = str + 3;
	}
	if (str && !strncmp(str, "WE ", 3))
	{
		if (map_info->WE)
		{
			printf("texture error\n");
			exit (1);
		}
		map_info->WE = str + 3;
	}	
	if (str && !strncmp(str, "EA ", 3))
	{
		if (map_info->EA)
		{
			printf("texture error\n");
			exit (1);
		}
		map_info->EA = str + 3;
	}
	if (str && !strncmp(str, "F ", 2))
	{
		if (map_info->F)
		{
			printf("floor error\n");
			exit (1);
		}
		map_info->F = atorgb(str + 2);
	}
}