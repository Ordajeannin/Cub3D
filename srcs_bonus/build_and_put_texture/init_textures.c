/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:30:11 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/18 19:24:02 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_image	xpm_to_image(t_game *game, char *path)
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

t_tex	*build_tex_tab(t_game *game, char *path_to_tex_dir, char dir_nm)
{
	t_tex	*tex;
	char	*path;

	printf("%s have been validated \n", path_to_tex_dir);
	tex = malloc((sizeof(t_tex)));
	if (!tex)
		return (NULL);
	tex->name = dir_nm;
	path = ft_strjoin(path_to_tex_dir, "ea.xpm");
	tex->image[EAST] = xpm_to_image(game, path);
	free(path);
	path = ft_strjoin(path_to_tex_dir, "no.xpm");
	tex->image[NORTH] = xpm_to_image(game, path);
	free(path);
	path = ft_strjoin(path_to_tex_dir, "we.xpm");
	tex->image[WEST] = xpm_to_image(game, path);
	free(path);
	path = ft_strjoin(path_to_tex_dir, "so.xpm");
	tex->image[SOUTH] = xpm_to_image(game, path);
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
	if (!ft_isalnum(dir_nb))
		return (NULL);
	tmp = ft_strtrim(map_name, ".cub");
	map_name_clean = ft_strjoin(tmp, "/");
	if (tmp)
		free(tmp);
	itoa_dir = ft_strjoin(little_string, "/");
	tmp = ft_strjoin(map_name_clean, itoa_dir);
	if (itoa_dir)
		free(itoa_dir);
	if (map_name_clean)
		free(map_name_clean);
	path = ft_strjoin("textures/", tmp);
	if (tmp)
		free(tmp);
	return (path);
}

int	init_tex_help(t_tex **tex, t_tex **first, char *path_to_tex_dir)
{
	if (!*first && *tex)
		*first = *tex;
	free(path_to_tex_dir);
	return (1);
}

int	great_mighty_init_tex(t_game *game)
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
		if (path_to_tex_dir && !access(path_to_tex_dir, F_OK | R_OK))
		{
			if (!tex && !first)
				tex = build_tex_tab(game, path_to_tex_dir, dir_nm);
			else
			{
				tex->next = build_tex_tab(game, path_to_tex_dir, dir_nm);
				tex = tex->next;
			}
		}
		dir_nm = dir_nm + init_tex_help(&tex, &first, path_to_tex_dir);
	}
	game->tex = first;
	return (1);
}
