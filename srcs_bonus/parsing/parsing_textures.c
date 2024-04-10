/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:10:46 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/10 16:33:32 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
