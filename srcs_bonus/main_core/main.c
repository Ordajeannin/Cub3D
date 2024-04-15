/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:20:01 by pkorsako          #+#    #+#             */
/*   Updated: 2024/04/15 16:30:08 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	print_debbug_values(t_grid *grid)
{
	printf("\n\nWidth = %d  |  ", grid->proj_plan_width);
	printf("FOV = %d  |  ", grid->fov);
	printf("DPP = %d  |  ", grid->dist_proj_plan);
	printf("P_F = %d  |  ", grid->projected_factor);
}

void	free_game(t_game *game, t_textures *map_info)
{
	free_tab(map_info->map);
	free_textures(game);
	free_tex(game);
	free(game->grid);
	free(game->player);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	wrong_start(t_textures *map_info, t_game *game)
{
	printf("PARSING OR INIT ERROR\n");
	free_tab((map_info)->map);
	free_textures(game);
	exit (1);
}

int	main(int argc, char **argv)
{
	t_textures	map_info;
	t_game		game;

	if (argc != 2 || !argv[1])
		quit_w_message("you have to put one map as argument");
	game.map_used = argv[1];
	if (!map_parser(argv[1], &map_info, &game) || init_game(&game, &map_info) == -1)
		wrong_start(&map_info, &game);
	if (gettimeofday(&game.time, NULL))
	{
		free_game(&game, &map_info);
		return (0);		
	}
	printf("game start\n");
	render(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask,
		&handle_keypress_test, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask,
		&handle_keyrelease, &game);
	mlx_hook(game.win, DestroyNotify, StructureNotifyMask,
		&handle_close, &game);
	mlx_loop_hook(game.mlx, &render, &game);
	mlx_loop(game.mlx);
	free_game(&game, &map_info);
	return (0);
}
