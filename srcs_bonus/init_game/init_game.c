/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:51:53 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/27 17:32:02 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	free_init(t_game *game)
{
	free_tex(game);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	free(game->grid);
	free(game->player);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (-1);
}

void	set_init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->bpp = 0;
	game->ll = 0;
	game->endian = 0;
	game->flag = 0;
}

int	quick_free(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (-1);
}

void	init_floor_ceiling_wall(t_game *game)
{
	game->floor[0] = '0';
	game->floor[1] = '\0';
	game->floor[2] = '\0';
	game->ceiling[0] = '0';
	game->ceiling[1] = '\0';
	game->ceiling[2] = '\0';
	game->wall[0] = '1';
	game->wall[1] = '2';
	game->wall[2] = '\0';
}

int	init_game(t_game *game, t_textures *textures)
{
	set_init_game(game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (-1);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (game->win == NULL || game->img == NULL)
		return (quick_free(game));
	game->img_addr = mlx_get_data_addr(game->img, &game->bpp,
			&game->ll, &game->endian);
	if (!game->img_addr)
		return (quick_free(game));
	game->textures = textures;
	game->player = init_player(game);
	game->grid = init_grid(game);
	if (!great_mighty_init_tex(game))
		return (free_init(game));
	init_floor_ceiling_wall(game);
	return (0);
}
