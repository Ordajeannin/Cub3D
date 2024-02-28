/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:14:15 by ajeannin          #+#    #+#             */
/*   Updated: 2024/02/28 18:31:08 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//ll stand for "line lenght"
//bpp for "bits per pixels"
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*pixel;
	int		index;

	index = (y * game->ll + x * (game->bpp << 3));
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
//	printf("wow, it s dark here\n");
	projected = (game->grid->projected_factor / get_value(value, "DISTANCE")) >> 1;
	if (projected >= SCREEN_HEIGHT)
	{
//		printf("projected = %d\n", projected);
		while (y < SCREEN_HEIGHT)
			my_mlx_pixel_put(game, x, y++, 0x00000000);
	}
	else
	{
		y_start = game->grid->half_proj_plan_height - projected;
		y_end = game->grid->half_proj_plan_height + projected;
	//	printf("projected factor = %d\n", game->grid->projected_factor);
	//	printf("distance = %d\n", get_value(value, "DISTANCE"));
	//	printf("pojected = %d  |  y_start = %d  |  y_end = %d\n", projected, y_start, y_end);
		while (y < y_start)
			my_mlx_pixel_put(game, x, y++, *(game->textures->c));
	//	printf("...\n");
		while (y < y_end)
			my_mlx_pixel_put(game, x, y++, 0x00000000);
	//	printf("...!!!");
		while (y < SCREEN_HEIGHT)
			my_mlx_pixel_put(game, x, y++, *(game->textures->f));
	}
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

	printf("1\n");
	if (game->win == NULL)
		return (1);
	i = 0;
	printf("2\n");
	image = proj_plan_image(game, game->grid);
//	view_stocked_image(image);
	printf("3\n");
	while (image[i])
	{
		create_col(game, image[i], i);
//		printf("i = %d\n", i);
		i++;
	}
	printf("4\n");
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	free(image);
	return (0);
}
