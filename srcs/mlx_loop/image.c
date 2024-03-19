/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:14:15 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/19 17:20:32 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//ll stand for "line lenght"
//bpp for "bits per pixels"
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*pixel;
	int		index;

//	printf("i");

	index = (y * game->ll + x * (game->bpp >> 3));
	pixel = game->img_addr + index;
	*(unsigned int *) pixel = color;
}

/*
 * :warning: les murs sont en noir par defaut, il faudra calculer quel pixel de
 * la texture doit etre affiche, base sur l'offset... mais pas que?
*/
void	create_col(t_game *game, unsigned int value, int x)
{
	int	y;
	int y_start;
	int	y_end;
	int	projected;

	y = 0;
	projected = round((game->grid->projected_factor / get_value(value, "DISTANCE")));
	if (projected >= SCREEN_HEIGHT)
	{	y_start = game->grid->half_proj_plan_height - (projected >> 1);
//		printf("projected = %d\n", projected);
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(game, x, y, get_texture_pixel(projected, value, game, y, y - y_start));
			y ++;
		}
	}
	else
	{
		y_start = game->grid->half_proj_plan_height - (projected >> 1);
		y_end = game->grid->half_proj_plan_height + (projected >> 1);
		while (y < y_start)
			my_mlx_pixel_put(game, x, y++, game->textures->c);
		while (y < y_end)
		{
			my_mlx_pixel_put(game, x, y, get_texture_pixel(projected, value, game, y, y - y_start));
			y++;
		}
		while (y < SCREEN_HEIGHT)
			my_mlx_pixel_put(game, x, y++, game->textures->f);
	}
}

void	create_col_test(t_game *game, unsigned int value, int x)
{
	int y;
	int y_start;
	int y_end;
	int projected;

	y = 0;
	projected = get_value(value, "DISTANCE");
//	if (projected % 2 == 1)
//		projected += 1;
	if (projected >= SCREEN_HEIGHT)
	{
		y_start = game->grid->half_proj_plan_height - (projected >> 1);
		while (y < SCREEN_HEIGHT)
		{
			y ++;
			my_mlx_pixel_put(game, x, y, get_texture_pixel(projected, value, game, y, y - y_start));
		}
	}
	else
	{
		y_start = game->grid->half_proj_plan_height - (projected >> 1);
		y_end = game->grid->half_proj_plan_height + (projected >> 1);
		while (y < y_start)
			my_mlx_pixel_put(game, x, y++, game->textures->c);
		while (y < y_end)
		{
			y ++;
			my_mlx_pixel_put(game, x, y, get_texture_pixel(projected, value, game, y, y - y_start));
		}
		while (y < SCREEN_HEIGHT)
			my_mlx_pixel_put(game, x, y++, game->textures->f);
	}
}

void view_stocked_col(unsigned int stock)
{
    unsigned int value = stock;
    int face = get_value(value, "FACE");
    int offset = get_value(value, "OFFSET");
    int texture = get_value(value, "TEXTURE");
    int distance = get_value(value, "DISTANCE");
    printf("[%d, %d, %d, %d]", face, offset, texture, distance);
}

//debug function
void view_stocked_image(unsigned int *stock)
{
    if (stock == NULL) {
        printf("The stock is empty.\n");
        return;
    }
    int index = 0;
    while (stock[index] != 0)
	{
        unsigned int value = stock[index];
        int face = get_value(value, "FACE");
        int offset = get_value(value, "OFFSET");
        int texture = get_value(value, "TEXTURE");
        int distance = get_value(value, "DISTANCE");

        printf("[%d][%d, %d, %d, %d]\n", index, face, offset, texture, distance);
        index++;
    }
}

int	render(t_game *game)
{
	int				i;
	unsigned int	*image;

	if (game->win == NULL)
		return (1);
	i = 0;
	image = proj_plan_image_test(game, game->player->orientation);
//	view_stocked_image(image);
	while (image[i])
	{
	//	printf("index = %d  |  ", i);
		create_col_test(game, image[i], i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	free(image);
	return (0);
}

int	loop()
{
	while (1 != 1)
		break;
	return (1);
}
