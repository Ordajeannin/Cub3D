/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:20:01 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/26 18:20:58 by ajeannin         ###   ########.fr       */
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
	free_textures(map_info);
	free_tex(game);
	free(game->grid);
	free(game->player);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int	main(int argc, char **argv)
{
	t_textures	map_info;
	t_game		game;

	if (argc != 2 || !argv[1])
		quit_w_message("you have to put one map as argument", &map_info);
	game.map_used = argv[1];
	if (!map_parser(argv[1], &map_info) || init_game(&game, &map_info) == -1)
	{
		printf("PARSING OR INIT ERROR\n");
		free_tab((&map_info)->map);
		free_textures(&map_info);
		exit (1);
	}
//	printf("BIIIIIIIITE\n");
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
