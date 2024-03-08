/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:20:01 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/08 15:19:24 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	printf("PARSING PASSED\n");
	render(&game);
	//mlx_loop_hook(game.mlx, &render, &game);
	mlx_loop_hook(game.mlx, &loop, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask,
		&handle_keypress, &game);
	mlx_hook(game.win, DestroyNotify, StructureNotifyMask,
		&handle_close, &game);
	mlx_hook(game.win, ButtonPress, ButtonPressMask,
		&handle_mouse, &game);
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	print_textures(&map_info);
	free_tab((&map_info)->map);
	free_textures(&map_info);
	return (0);
}
