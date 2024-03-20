/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:10:46 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/20 16:11:52 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_end_of_filename(char const *filename, const char *end)
{
	size_t	i;

	i = ft_strlen(filename) - 4;
	if (filename[i ++] != end[0])
		return (0);
	if (filename[i ++] != end[1])
		return (0);
	if (filename[i ++] != end[2])
		return (0);
	if (filename[i ++] != end[3])
		return (0);
	return (1);
}

int	texture_good(t_textures *map_info)
{	
	int	i;

	i = 0;
	if (!map_info->so || !map_info->we || !map_info->ea || !map_info->no)
	{
		printf("missing wall\n");
		return (0);
	}
	if (!check_end_of_filename(map_info->ea, ".xpm")
		|| !check_end_of_filename(map_info->so, ".xpm")
		|| !check_end_of_filename(map_info->we, ".xpm")
		|| !check_end_of_filename(map_info->no, ".xpm"))
		return (0);
	if (map_info->c == -1 || map_info->f == -1)
	{
		printf("missing f or c\n");
		return (0);
	}
	printf("textures are good\n");
	return (1);
}
