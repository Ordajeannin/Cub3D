/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:20:01 by pkorsako          #+#    #+#             */
/*   Updated: 2024/02/22 17:41:26 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_textures	map_info;

	if (argc != 2 || !argv[1])
		quit_w_message("you have to put one map as argument");
	map_parser(argv[1], &map_info);
	print_textures(&map_info);
	free_tab((&map_info)->map);
	free_textures(&map_info);
	return (0);
}
