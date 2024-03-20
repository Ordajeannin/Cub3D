/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:14:15 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/20 14:18:18 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	create_col_norme(t_game *game, int projected, unsigned int value, int x)
{
	int	y;
	int	y_start;
	int	y_end;

	y = 0;
	y_start = game->grid->half_proj_plan_height - (projected >> 1);
	y_end = game->grid->half_proj_plan_height + (projected >> 1) - 1;
	while (y < y_start)
		my_mlx_pixel_put(game, x, y++, game->textures->c);
	while (y < y_end)
	{
		my_mlx_pixel_put(game, x, y,
			get_texture_pixel(projected, value, game, y, y - y_start));
		y++;
	}
	while (y < SCREEN_HEIGHT)
		my_mlx_pixel_put(game, x, y++, game->textures->f);
}

void	create_col_test(t_game *game, unsigned int value, int x)
{
	int	y;
	int	y_start;
	int	projected;

	y = 0;
	projected = get_value(value, "DISTANCE");
	if (projected >= SCREEN_HEIGHT)
	{
		y_start = game->grid->half_proj_plan_height - (projected >> 1);
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(game, x, y,
				get_texture_pixel(projected, value, game, y, y - y_start));
			y++;
		}
	}
	else
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
