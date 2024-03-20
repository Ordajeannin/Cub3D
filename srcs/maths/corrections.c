/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:33:33 by ajeannin          #+#    #+#             */
/*   Updated: 2024/03/20 17:08:05 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	try_get_texture(char **map, int yt, int xt)
{
	int	yi;
	int	xi;

	yi = 0;
	xi = 0;
	while (yi != yt && map[yi] != NULL)
		yi++;
	if (yi != yt || map[yi] == NULL)
		return ('a');
	while (xi != xt && map[yi][xi] != '\0')
		xi++;
	if (xt != xi)
		return ('a');
	return (map[yi][xi]);
}

int	from_dist_to_projected(t_game *game, double angle,
		double i_px, double i_py)
{
	int		result;
	double	dist;

	dist = ft_dist(i_px, i_py, game->player->pos_x, game->player->pos_y);
	if (angle < game->player->orientation)
		angle = double_modulo(game->player->orientation - angle, 360);
	else
		angle = double_modulo(angle - game->player->orientation, 360);
	result = round(game->grid->projected_factor / (dist * cos(dtor(angle))));
	if (game->flag == 0)
		game->dist_c = dist;
	else
		game->dist_l = dist;
	return (result);
}
