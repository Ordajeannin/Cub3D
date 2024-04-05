/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:14:15 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/05 16:22:31 by ajeannin         ###   ########.fr       */
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
		render_ceiling_sky(game, x, y++);
	}
	while (y < y_end && y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game, x, y,
			get_texture_pixel(projected, value, game, y - y_start));
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		render_floor(game, x, y++);
	}
}

void	create_col_test(t_game *game, unsigned int value, int x)
{
	int	projected;

	projected = get_value(value, "DISTANCE");
	create_col_norme(game, projected, value, x);
}

int	render(t_game *game)
{
	int				i;
	unsigned int	*image;
	struct timeval	time;
	static size_t	frame;
	int				fps;

	fps = 1000000 / FPS_MAX;
	gettimeofday(&time, NULL);
	if (labs(time.tv_usec - game->time.tv_usec) < fps)
		usleep(fps - labs(time.tv_usec - game->time.tv_usec));
	gettimeofday(&game->time, NULL);
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
	frame ++;
	return (0);
}

int	loop(void)
{
	while (1 != 1)
		break ;
	return (1);
}
