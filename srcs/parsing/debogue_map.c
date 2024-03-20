/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debogue_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:02:28 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/20 16:03:28 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_textures(t_textures *texture)
{
	printf("NO :%s\nSO :%s\nWE :%s\nEA :%s\n", texture->no,
		texture->so, texture->we, texture->ea);
	if (texture->f)
		printf("F :%d\n", texture->f);
	if (texture->c)
		printf("C :%d\n", texture->c);
	printf("player is in [%d][%d] and is lookin at %d°\n", texture->p_x,
		texture->p_y, texture->p_direction);
	printf("max_y is :%d and max_x is :%d\n", texture->y_max, texture->x_max);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		printf("tab[%d] :%s", i, tab[i]);
		i ++;
	}
}
