/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:14:15 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/26 18:30:25 by ajeannin         ###   ########.fr       */
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
		if (game->ceiling[i] == 'c')
			return (c);
	return (0);
}

void	render_ceiling_sky(t_game *game, int x, int y)
{
	double	beta;
	double	dist;
	double	hyp;

	beta = fabs(game->angle[x] - game->player->orientation);
	dist = ((game->player->view_y * game->grid->dist_proj_plan) / (y - (SCREEN_HEIGHT >> 1)));
	hyp = dist / cos(dtor(beta));
	game->floor_x = (int)(game->player->pos_x + cos(dtor(game->angle[x])));
	game->floor_y = (int)(game->player->pos_y - sin(dtor(game->angle[x])));
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

//https://wynnliam.github.io/raycaster/news/tutorial/2019/04/09/raycaster-part-03.html
//+cf brouillon
void	render_floor(t_game *game, int x, int y)
{
	double	beta;
	double	dist;
	double	hyp;

	beta = fabs(game->angle[x] - game->player->orientation);
	dist = ((game->player->view_y * game->grid->dist_proj_plan) / (y - (SCREEN_HEIGHT >> 1)));
	hyp = dist / cos(dtor(beta));
	game->floor_x = (int)(game->player->pos_x + cos(dtor(game->angle[x])));
	game->floor_y = (int)(game->player->pos_y - sin(dtor(game->angle[x])));
	my_mlx_pixel_put(game, x, y, get_texture_fsc(game, "FLOOR",
			try_get_texture(game->grid->map,
				game->floor_x >> 6, game->floor_y >> 6)));

}

void	create_col_norme(t_game *game, int projected, unsigned int value, int x)
{
	int	y;
	int	y_start;
	int	y_end;

	y = 0;
	printf("wtf");
	y_start = game->player->view_y - (projected >> 1);
	y_end = game->player->view_y + (projected >> 1) - 1;
	printf("bite");
	while (y < y_start && y_start > 0)
	{
			render_ceiling_sky(game, x, y++);
		//my_mlx_pixel_put(game, x, y++, game->textures->c);
	}
	printf("bite");
	while (y < y_end && y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game, x, y,
			get_texture_pixel(projected, value, game, y - y_start));
		y++;
	}
	printf("bite");
	while (y < SCREEN_HEIGHT)
	{
		render_floor(game, x, y++);
		//my_mlx_pixel_put(game, x, y++, game->textures->f);
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
	printf("AYA?\n");
	create_col_norme(game, projected, value, x);
}

int	render(t_game *game)
{
	int				i;
	unsigned int	*image;

	if (game->win == NULL)
		return (1);
	i = 0;
	printf("1\n");
	ft_moove(game->player, game);
	printf("2\n");
	image = proj_plan_image_test(game, game->player->orientation);
	printf("3\n");
	while (image[i])
	{
		create_col_test(game, image[i], i);
		i++;
	}
	printf("4\n");
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
