/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:35:50 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/01 18:41:24 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (textures->c)
		free(textures->c);
	if (textures->f)
		free(textures->f);
}

int	rgb_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	// printf("rgb atoi received :|%d|\n", str[0]);
	i = 0;
	sign = 0;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		||str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	else
		sign = 1;
	if (sign == -1 || str[i] == '+')
		i++;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	if ((str[i] != 0 && str[i] != '\n') || str[0] == '\n')
	{
		printf("non str or alpha in color\n");
		return (-1);
	}
	return (result * sign);
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
		return (NULL);
	}
	while (i < 3)
	{
		tmp = ft_strdupto_n(str, ',');
		rgb[i] = rgb_atoi(tmp);
		str = ft_strchr(str, ',') + 1;
		free(tmp);
		if ((rgb[i] < 0 || rgb[i] > 255) || (str == (char *)0x1 && i < 2))
		{
			free(rgb);
			return (NULL);
		}
		i ++;
	}
	rgb[3] = 0;
	return (rgb);
}

int	get_fandc_rgb(char *str, t_textures *map_info)
{
	if (str && !ft_strncmp(str, "F ", 2))
	{
		if (map_info->f)
		{
			printf("floor error\n");
			return (0);
		}
		map_info->f = atorgb(str + 2);
	}
	if (str && !strncmp(str, "C ", 2))
	{
		if (map_info->c)
		{
			printf("celing error\n");
			return (0);
		}
		map_info->c = atorgb(str + 2);
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
		map_info->we = ft_strdup(str + 3);
		map_info->we[ft_strlen(map_info->we) - 1] = 0;
	}
	if (str && !strncmp(str, "EA ", 3))
	{
		if (map_info->ea)
		{
			printf("texture error\n");
			return (0);
		}
		map_info->ea = ft_strdup(str + 3);
		map_info->ea[ft_strlen(map_info->ea) - 1] = 0;
	}
	if (!get_fandc_rgb(str, map_info))
		return (0);
	return (1);
}

int	get_textures(char *str, t_textures *map_info)
{
	// printf("this line is tested :%s\n", str);
	if (str && !strncmp(str, "NO ", 3))
	{
		if (map_info->no)
		{
			printf("texture error\n");
			return (0);
		}
		map_info->no = ft_strdup(str + 3);
		map_info->no[ft_strlen(map_info->no) - 1] = 0;
	}
	if (str && !strncmp(str, "SO ", 3))
	{
		if (map_info->so)
		{
			printf("texture error\n");
			return (0);
		}
		map_info->so = ft_strdup(str + 3);
		map_info->so[ft_strlen(map_info->so) - 1] = 0;
	}
	if (!get_next_textures(str, map_info))
		return (0);
	return (1);
}
