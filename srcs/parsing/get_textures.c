/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:35:50 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/17 18:35:17 by pkorsako         ###   ########.fr       */
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

int	get_f_and_c(char *str, t_textures *map_info)
{
	static int	floor;
	static int	celling;

	if (str && !ft_strncmp(str, "F", 1))
	{
		if (floor)
		{
			printf("floor error\n");
			return (0);
		}
		floor = 1;
		map_info->f = atorgb(ft_str_rm_spaces(str + 1));
	}
	if (str && !ft_strncmp(str, "C", 1))
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
	if (str && !ft_strncmp(str, "WE", 2))
	{
		if (map_info->we)
		{
			printf("texture error\n");
			return (0);
		}
		map_info->we = ft_str_rm_spaces(str + 2);
	}
	if (str && !ft_strncmp(str, "EA", 2))
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
	if (str && !ft_strncmp(str, "NO", 2) && ft_isspace(str[2]))
	{
		if (map_info && map_info->no)
		{
			printf("texture error\n");
			return (0);
		}
		map_info->no = ft_str_rm_spaces(str + 2);
	}
	if (str && !ft_strncmp(str, "SO", 2) && ft_isspace(str[2]))
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
