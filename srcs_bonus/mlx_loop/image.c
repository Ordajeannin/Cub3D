/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:14:15 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/28 17:45:19 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

//ll stand for "line lenght"
//bpp for "bits per pixels"
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*pixel;
	int		index;

	index = (y * game->ll + x * (game->bpp >> 3));
	pixel = game->img_addr + index;
	*(unsigned int *) pixel = color;
}

/*
 * WIP
 * fonction qui permettra de gerer les affichages de floor sky et ceiling
 * sous la forme
 * node
 *   name = texture
 *   image[0] = text.floor
 *   image[1] = text.ceiling or text.sky
 *
 * :warning: pour sky, il va falloir modulo la position par les dimensions de
 * la texture sky, sinon bah... on va avoir des dalles de sky quoi
 * et c'est pas vraiment l'idee d un ciel
 *
 * pour l'instant, segfault car pas de texture correspondante? (pq pas de return wtf?)
*/
unsigned int	get_texture_fsci_test(t_game *game, char *text, int texture)
{
	int		index;
	char	*pixel;
	int		x;
	int		y;
	t_tex	*tex;

	x = game->floor_x % 64;
	y = game->floor_y % 64;
	index = texture;
	tex = game->tex;
	printf("BITE\n");
	while (tex && (char)index != tex->name)
		tex = tex->next;
	if (!tex)
		return (0);
	if (ft_strncmp(text, "FLOOR", 5) == 0)
	{
		index = y * tex->image[0].line_size + x * (tex->image[0].bpp >> 3);
		pixel = tex->image[0].im_addr + index;
	}
	else if (ft_strncmp(text, "SKY", 3) == 0)
	{
		x = game->floor_x % 800;
		y = game->floor_y % 600;
		index = y * tex->image[1].line_size + x * (tex->image[1].bpp >> 3);
		pixel = tex->image[1].im_addr + index;
	}
	else
	{
		index = y * tex->image[1].line_size + x
			* (game->tex->image[1].bpp >> 3);
		pixel = game->tex->image[1].im_addr + index;
	}
	return (*(unsigned int *)pixel);
}

unsigned int	get_texture_fsc(t_game *game, char *text, int texture)
{
	int		index;
	char	*pixel;
	int		x;
	int		y;

	x = game->floor_x % 64;
	y = game->floor_y % 64;
	texture = 1;
	if (ft_strncmp(text, "FLOOR", 5) == 0)
	{
		index = y * game->tex->image[texture].line_size + x
			* (game->tex->image[texture].bpp >> 3);
		pixel = game->tex->image[texture].im_addr + index;
	}
	else if (ft_strncmp(text, "SKY", 3) == 0)
	{
//		x = game->floor_x % 600;
//		y = game->floor_y % 600;
		index = y * game->tex->image[texture].line_size + x
			* (game->tex->image[texture].bpp >> 3);
		pixel = game->tex->image[texture].im_addr + index;
	}
	else
	{
		index = y * game->tex->image[texture].line_size + x
			* (game->tex->image[texture].bpp >> 3);
		pixel = game->tex->image[texture].im_addr + index;
	}
	return (*(unsigned int *)pixel);
}


char	ceiling_or_sky(t_game *game, char c)
{
	int	i = -1;

	while (game->ceiling[++i])
		if (game->ceiling[i] == c)
			return (c);
	return (0);
}

void	render_floor_test_test(t_game *game, int x, int y)
{
	double	dist;
	double	beta;
	double	alpha;
	double	hyp;

	alpha = game->angle[x];
	beta = fabs(game->angle[x] - game->player->orientation);
	dist = (double)(32 * game->grid->dist_proj_plan) / (double)(y - game->player->view_y);
	hyp = dist / cos(dtor(beta));
	game->floor_x = game->player->pos_x + (cos(dtor(alpha)) * hyp);
	game->floor_y = game->player->pos_y - (sin(dtor(alpha)) * hyp);
	my_mlx_pixel_put(game, x, y, get_texture_fsc(game, "FLOOR",
			try_get_texture(game->grid->map,
				game->floor_x >> 6, game->floor_y >> 6)));
}

void	render_ceiling_sky_test_test(t_game *game, int x, int y)
{
	double	dist;
	double	beta;
	double	alpha;
	double	hyp;

	alpha = game->angle[x];
	beta = fabs(game->angle[x] - game->player->orientation);
	dist = (double)(32 * game->grid->dist_proj_plan) / (double)(game->player->view_y - y);
	hyp = dist / cos(dtor(beta));
	game->floor_x = game->player->pos_x + (cos(dtor(alpha)) * hyp);
	game->floor_y = game->player->pos_y - (sin(dtor(alpha)) * hyp);
	if (ceiling_or_sky(game, try_get_texture(game->grid->map,
					game->floor_x >> 6, game->floor_y >> 6)) == 0)
		my_mlx_pixel_put(game, x, y, get_texture_fsc(game, "SKY",
				try_get_texture(game->grid->map,
					game->floor_x >> 6, game->floor_y >> 6)));
	else
		my_mlx_pixel_put(game, x, y, get_texture_fsc(game, "CEILING",
					try_get_texture(game->grid->map,
						game->floor_x >> 6, game->floor_y >> 6)));
}

void	create_col_norme(t_game *game, int projected, unsigned int value, int x)
{
	int	y;
	int	y_start;
	int	y_end;

	y = 0;
	y_start = game->player->view_y - (projected >> 1);
	y_end = game->player->view_y + (projected >> 1) - 1;
	while (y < y_start && y_start > 0)
	{
		render_ceiling_sky_test_test(game, x, y++);
	}
	while (y < y_end && y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game, x, y,
			get_texture_pixel(projected, value, game, y - y_start));
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		render_floor_test_test(game, x, y++);
	}
}

void	create_col_test(t_game *game, unsigned int value, int x)
{
//	int	y;
//	int	y_start;
//	int y_end;
	int	projected;

//	y = 0;
	projected = get_value(value, "DISTANCE");
//	y_start = game->player->view_y - (projected >> 1);
//	y_end = game->player->view_y + (projected >> 1) - 1;
	/*if (projected >= SCREEN_HEIGHT)
	{
		printf("BIIIIIITE, %d\n", projected);
		y_start = game->grid->half_proj_plan_height - (projected >> 1);
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(game, x, y,
				get_texture_pixel(projected, value, game, y - y_start));
			y++;
		}
	}
	else
		*/
//	printf("AYA?\n");
	create_col_norme(game, projected, value, x);
}

int	render(t_game *game)
{
	int				i;
	unsigned int	*image;

	if (game->win == NULL)
		return (1);
	i = 0;
	ft_moove(game->player, game);
	image = proj_plan_image_test(game, game->player->orientation);
	while (image[i])
	{
		create_col_test(game, image[i], i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	free(image);
	return (0);
}

int	loop(void)
{
	while (1 != 1)
		break ;
	return (1);
}
