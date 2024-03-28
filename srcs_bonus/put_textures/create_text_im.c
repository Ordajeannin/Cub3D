/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_text_im.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:25:28 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/28 18:03:28 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


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


t_tex    *build_tex_tab(t_game *game, char *path_to_tex_dir, char dir_nm)
{
	t_tex	*tex;
	char	*path;

	printf("%s have been validated ", path_to_tex_dir);
	tex = malloc((sizeof(t_tex)));
	if (!tex)
		return (NULL);
	tex->name = dir_nm;
	path = ft_strjoin(path_to_tex_dir, "ea.xpm");
	tex->image[EAST] = get_tex_image(game, path);
	free(path);
	path = ft_strjoin(path_to_tex_dir, "no.xpm");
	tex->image[NORTH] = get_tex_image(game, path);
	free(path);
	path = ft_strjoin(path_to_tex_dir, "we.xpm");
	tex->image[WEST] = get_tex_image(game, path);
	free(path);
	path = ft_strjoin(path_to_tex_dir, "so.xpm");
	tex->image[SOUTH] = get_tex_image(game, path);
	free(path);
	tex->name = dir_nm;
	tex->next = NULL;
	return (tex);
}

char	*built_texture_path(char dir_nb, const char *map_name)
{
    char	*path;
    char	*tmp;
    char	*itoa_dir;
    char	*map_name_clean;
	char	little_string[2];

	little_string[1] = 0;
	little_string[0] = dir_nb;
	if(!ft_isalnum(dir_nb))
		return (NULL);
    tmp = ft_strtrim(map_name, ".cub");
    map_name_clean = ft_strjoin(tmp, "/");
    free(tmp);

    itoa_dir = ft_strjoin(little_string, "/");

    tmp = ft_strjoin(map_name_clean, itoa_dir);
    free(itoa_dir);

    path = ft_strjoin("textures/", tmp);
    free(tmp);
    return (path);
}


int    great_mighty_init_tex(t_game *game)
{
    char	dir_nm;
    char	*path_to_tex_dir;
    t_tex	*tex;
	t_tex	*first;

    dir_nm = '0';
	first = NULL;
	tex = NULL;
	while (dir_nm <= 'z')
	{
		path_to_tex_dir = built_texture_path(dir_nm, game->map_used);
		// printf("path to tex dir :%s\n", path_to_tex_dir);
		if (path_to_tex_dir && !access(path_to_tex_dir, F_OK | R_OK))
		{
			if (!tex && !first)
				tex = build_tex_tab(game, path_to_tex_dir, dir_nm);
			else
			{
				tex->next = build_tex_tab(game, path_to_tex_dir, dir_nm);
				tex = tex->next;
			}
			printf("his name is :%c\n", dir_nm);
		}
		if (!first && tex)
			first = tex;
		dir_nm ++;
	}
	game->tex = first;
    return (1);
}

/*
int	get_texture_pixel(int projected, unsigned int value, t_game *game, int i)
{
	int		x;
	int		y;
	char	name;
	int		index;
	char	*pixel;
	t_tex	*tex;

	tex = game->tex;
	name = (char)get_value(value, "TEXTURE") + '0';
	// printf("tex name :%c\tindex :%c\n", tex->name, name);
	while (tex && name != tex->name)
	{
		// printf("tex name :%c\tindex :%c\n", tex->name, name);
		tex = tex->next;
	}
	if (!tex)
		return (0);
	printf("index = %c  |  tex->name = %c\n", index, tex->name);
	x = get_value(value, "OFFSET");
	y = round(i * (63.0 / projected));
	index = y * tex->image[get_value(value, "FACE")].line_size + x
		* (tex->image[get_value(value, "FACE")].bpp >> 3);
	pixel = tex->image[get_value(value, "FACE")].im_addr + index;
	// printf("pixel :%d", *pixel);
	return (*(unsigned int *)pixel);
}
*/

int	get_texture_pixel(int projected, unsigned int value, t_game *game, int i)
{
	int	x;
	int	y;
	int	index;
	char *pixel;
	t_tex	*tex;

	tex = game->tex;
	index = get_value(value, "TEXTURE");
	while (tex && (char)index != tex->name)
		tex = tex->next;
	if (!tex)
		return (0);
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
