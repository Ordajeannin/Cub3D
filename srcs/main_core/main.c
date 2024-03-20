/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:20:01 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/20 16:38:56 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_debbug_values(t_grid *grid)
{
	printf("\n\nWidth = %d  |  ", grid->proj_plan_width);
	printf("FOV = %d  |  ", grid->fov);
	printf("DPP = %d  |  ", grid->dist_proj_plan);
	printf("P_F = %d  |  ", grid->projected_factor);
}

int	main(int argc, char **argv)
{
	t_textures	map_info;
	t_game		game;

	(void)game;
	if (argc != 2 || !argv[1])
		quit_w_message("you have to put one map as argument", &map_info);
	if (!map_parser(argv[1], &map_info) || init_game(&game, &map_info) == -1)
	{
		printf("PARSING ERROR\n");
		free_tab((&map_info)->map);
		free_textures(&map_info);
		exit (1);
	}
	// print_tab(map_info.map);
	printf("PARSING PASSED\n");
	render(&game);
//	mlx_loop_hook(game.mlx, &render, &game);
//	mlx_loop_hook(game.mlx, &loop, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask,
		&handle_keypress_test, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask,
		&handle_keyrelease, &game);
	mlx_hook(game.win, DestroyNotify, StructureNotifyMask,
		&handle_close, &game);
//	mlx_hook(game.win, ButtonPress, ButtonPressMask,
//		&handle_mouse, &game);
	mlx_loop_hook(game.mlx, &render, &game);
	mlx_loop(game.mlx);
	print_textures(&map_info);
	free_tab((&map_info)->map);
	free_textures(&map_info);
	free_tex(&game);
	free(game.grid);
	free(game.player);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (0);
}
