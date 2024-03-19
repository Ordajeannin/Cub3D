/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:35:50 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/19 19:46:56 by pkorsako         ###   ########.fr       */
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

int	rgb_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	// printf("rgb atoi received :|%s|\n", str);
	i = 0;
	sign = 0;
	result = 0;
	if (!str)
		return (-1);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
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
		free(str);
		return (-1);
	}
	free(str);
	return (result * sign);
}

char	*strcp_to_n(const char *str, char n)
{
	int		i;
	char	*cp;

	i = 0;
	cp = malloc(sizeof(char) * 4);
	if (!str || !cp)
		return (NULL);
	ft_bzero(cp, 4);
	while (str[i] && str[i] != n)
	{
		// printf("cp building :%s\tthen\t", cp);
		if (i == 4)
			return (NULL);
		cp[i] = str[i];
		i ++;
	}
	cp[3] = 0;
	// printf("\nfinally |%s| is geting out of strcp to n\n", cp);
	return (cp);
}

int	atorgb(char *str)
{
	int	color;
	int	tmp;
	int	i;

	tmp = 0;
	i = 0;
	color = 0;
	while (i < 3)
	{
		tmp = rgb_atoi(strcp_to_n(str, ','));
		str = ft_strchr(str, ',');
		if (str && str[0] == ',')
			str ++;
		if (tmp < 0)
			return (-1);
		// printf("color before bitshift :%d\n", color);
		color += tmp;
		i ++;
		if (i < 3)
			color = color << 8;
	}
	// printf("last color value :%d\n", color);
	return (color);
}

int	get_fandc_rgb(char *str, t_textures *map_info)
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
		printf("map_info->f :%d\n", map_info->f);
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
		printf("map_info->c :%d\n", map_info->c);
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
	if (!get_fandc_rgb(str, map_info))
		return (0);
	return (1);
}

int	get_textures(char *str, t_textures *map_info)
{
	// printf("this line is tested :%s\n", str);
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
