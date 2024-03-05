/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:51:53 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/01 17:05:18 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_game *game, t_textures *textures)
{
	game->mlx = NULL;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (-1);
	game->win = NULL;
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (game->win == NULL)
	{
		free(game->mlx);
		return (-1);
	}
	game->bpp = 0;
	game->ll = 0;
	game->endian = 0;
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img_addr = mlx_get_data_addr(game->img, &game->bpp,
		&game->ll, &game->endian);
	game->textures = textures;
	game->player = init_player(game);
	game->grid = init_grid(game);
	return (0);
}