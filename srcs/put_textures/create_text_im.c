/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_text_im.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:25:28 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/12 20:13:19 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	get_tex_image(t_game *game, char *path)
{
	t_image	image;

	image.im_ptr = mlx_xpm_file_to_image(game->mlx, path, &image.im_width, &image.im_height);
	if (!image.im_ptr)
		return (image);//plutot check le im_ptr apres ?
	image.im_addr = mlx_get_data_addr(image.im_ptr, &image.bpp, &image.line_size, &image.endian);
	return (image);
}

int	init_textures(t_game *game, t_textures *texture)
{
	t_tex	*tex;

	(void)game;(void)texture;
	tex = malloc((sizeof(t_tex)));
	if (!tex)
		return (0);
	game->tex = tex;
	game->tex->next = NULL;
	tex->image[EAST] = get_tex_image(game, texture->ea);
	tex->image[NORTH] = get_tex_image(game, texture->no);
	tex->image[WEST] = get_tex_image(game, texture->we);
	tex->image[SOUTH] = get_tex_image(game, texture->so);
	if (!tex->image[EAST].im_ptr || !tex->image[NORTH].im_ptr || !tex->image[WEST].im_ptr || !tex->image[SOUTH].im_ptr)
		return (0);
	return (1);
}

int	init_textures_old(t_game *game, t_textures *texture)
{
	int	widht;
	int	height;
	int	bpp;
	int	size_line;
	int	endian;
	
	t_walls *walls;
	
	walls = malloc(sizeof(t_walls));
	if (!walls)
		return (0);
	game->walls = walls;
	widht = 0;
	height = 0;

	printf("trying to use these paths :\n%s\n%s\n%s\n%s\n", texture->no, texture->we, texture->so, texture->ea);
	game->walls->no_side_im = mlx_xpm_file_to_image(game->mlx, texture->no, &game->walls->no_im_width, &game->walls->no_im_height);
	if (!game->walls->no_side_im)
	{
		printf("O NO\n");
		return (0);
	}
	game->walls->we_side_im = mlx_xpm_file_to_image(game->mlx, texture->we, &widht, &height);
	game->walls->so_side_im = mlx_xpm_file_to_image(game->mlx, texture->so, &widht, &height);
	game->walls->ea_side_im = mlx_xpm_file_to_image(game->mlx, texture->ea, &widht, &height);
	if (!game->walls->no_side_im || !game->walls->we_side_im || !game->walls->so_side_im || !game->walls->ea_side_im)
	{
		printf("cannot xpm to image\n");
		return (0);
	}
	game->walls->no_side_addr = mlx_get_data_addr(game->walls->no_side_im, &game->walls->no_bpp, &game->walls->no_l_size, &game->walls->no_endian);
	game->walls->we_side_addr = mlx_get_data_addr(game->walls->we_side_im, &bpp, &size_line, &endian);
	game->walls->so_side_addr = mlx_get_data_addr(game->walls->so_side_im, &bpp, &size_line, &endian);
	game->walls->ea_side_addr = mlx_get_data_addr(game->walls->ea_side_im, &bpp, &size_line, &endian);
	// game->walls = walls;
	return (1);
}

int	get_texture_pixel(int projected, unsigned int value, t_game *game, int kk, int i)
{
	int	x;
	int	y;
	int	index;
	char	*pixel;
	t_tex	*tex;

	(void)kk;
	tex = game->tex;
	index = get_value(value, "TEXTURE") - 1;
	while (index > 0 && tex->next)
		tex = tex->next;
	x = get_value(value, "OFFSET") % 64;
	y = round(i * (64.0 / (projected * 2)));
	index = y * tex->image[get_value(value, "FACE")].line_size + x * (tex->image[get_value(value, "FACE")].bpp >> 3);
	pixel = tex->image[get_value(value, "FACE")].im_addr + index;
	return (*(unsigned int *)pixel);
}

int	get_texture_pixel_old(int projected, unsigned int value, t_game *game, int y_old, int i)
{
	int x;
	int	y;
	int index;
	char *pixel;

	// (void)projected;
	(void)y_old;
	if (get_value(value, "FACE") == NORTH)
	{
		x = get_value(value, "OFFSET") % 64;//game->walls->no_im_width;//peut etre diviser
		y = round(i * (64.0 / (projected * 2)));
	//	printf("i = %d  |  y = %d  |  projected = %d\n",i, y, projected);
		index = y * game->walls->no_l_size + x * (game->walls->no_bpp >> 3);
		pixel = game->walls->no_side_addr + index;
		return (*(unsigned int *)pixel);
		// return ((int)game->walls->no_side_addr[y * game->walls->no_l_size + x * (game->walls->no_bpp >> 3)]);
	}
	return (0x00000000);
}

