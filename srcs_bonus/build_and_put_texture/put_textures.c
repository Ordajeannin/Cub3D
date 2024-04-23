/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:25:28 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/23 19:18:00 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_texture_pixel(int projected, unsigned int value, t_game *game, int i)
{
	int		x;
	int		y;
	int		index;
	char	*pixel;
	t_tex	*tex;

	tex = game->tex;
	index = get_value(value, "TEXTURE");
	while (tex && (char)index != tex->name)
		tex = tex->next;
	if (!tex)
		return (0);
	if (!tex->image[get_value(value, "FACE")].im_ptr)
		return (0);
	x = get_value(value, "OFFSET")
		* tex->image[get_value(value, "FACE")].im_width / 64;
	y = round(i * (tex->image[get_value(value, "FACE")].im_height - 1)
			/ projected);
	index = y * tex->image[get_value(value, "FACE")].line_size + x
		* (tex->image[get_value(value, "FACE")].bpp >> 3);
	pixel = tex->image[get_value(value, "FACE")].im_addr + index;
	return (*(unsigned int *)pixel);
}

void	free_tex(t_game *game)
{
	int		i;
	t_tex	*tmp;

	while (game->tex)
	{
		i = 0;
		while (i < 4)
		{
			if (game->tex->image[i].im_ptr)
				mlx_destroy_image(game->mlx, game->tex->image[i].im_ptr);
			i ++;
		}
		tmp = game->tex;
		game->tex = game->tex->next;
		free(tmp);
	}
}

void	free_telep(t_game *game)
{
	t_telep	*tmp;

	while (game->telep)
	{
		free(game->telep->name);
		free(game->telep->peer);
		tmp = game->telep;
		game->telep = game->telep->next;
		free(tmp);
	}
}

char	*get_fc_pixel(t_tex *tex, int x, int y, int flag)
{
	int		index;
	char	*pixel;

	x = x * tex->image[flag].im_width / 64;
	y = y * tex->image[flag].im_height / 64;
	index = y * tex->image[flag].line_size + x * (tex->image[flag].bpp >> 3);
	pixel = tex->image[flag].im_addr + index;
	return (pixel);
}
