/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_text_im.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:25:28 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/20 17:39:46 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	get_tex_image(t_game *game, char *path)
{
	t_image	image;

	image.im_ptr = mlx_xpm_file_to_image(game->mlx, path, &image.im_width,
			&image.im_height);
	if (!image.im_ptr)
	{
		printf("cannot convert .xpm\n");
		return (image);
	}
	image.im_addr = mlx_get_data_addr(image.im_ptr, &image.bpp,
			&image.line_size, &image.endian);
	return (image);
}

int	init_textures(t_game *game, t_textures *texture)
{
	t_tex	*tex;

	tex = malloc((sizeof(t_tex)));
	if (!tex)
		return (0);
	game->tex = tex;
	game->tex->next = NULL;
	tex->image[EAST] = get_tex_image(game, texture->ea);
	tex->image[NORTH] = get_tex_image(game, texture->no);
	tex->image[WEST] = get_tex_image(game, texture->we);
	tex->image[SOUTH] = get_tex_image(game, texture->so);
	if (!tex->image[EAST].im_ptr || !tex->image[NORTH].im_ptr
		|| !tex->image[WEST].im_ptr || !tex->image[SOUTH].im_ptr)
	{
		return (0);
	}
	return (1);
}

int	get_texture_pixel(int projected, unsigned int value, t_game *game, int i)
{
	int		x;
	int		y;
	int		index;
	char	*pixel;
	t_tex	*tex;

	tex = game->tex;
	index = get_value(value, "TEXTURE") - 1;
	while (index > 0 && tex->next)
		tex = tex->next;
	x = get_value(value, "OFFSET");
	y = round(i * (63.0 / projected));
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
