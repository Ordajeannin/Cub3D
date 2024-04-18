/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleporteurs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <ajeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:21:34 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/18 19:20:39 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	apply_telep(t_player *player, t_telep_info *telep, char c)
{
	if (c == telep->name_enter)
	{
		player->pos_x = (telep->x_exit << 6) + 32;
		player->pos_y = (telep->y_exit << 6) + 32;
	}
	else if (c == telep->name_exit)
	{
		player->pos_x = (telep->x_enter << 6) + 32;
		player->pos_y = (telep->y_enter << 6) + 32;
	}
	player->is_in_telep = 1;
}

t_telep	*check_if_telep(t_game *game, char c)
{
	t_telep *telep;

	telep = game->telep;
	while (telep && ft_strchr(telep->name, c) == NULL)
		telep = telep->next;
	if (telep)
		return (telep);
	else
		return (NULL);
}

void	ft_telep(t_game *game, t_player *player)
{
	char	c;
	t_telep	*telep;

	c = try_get_texture(game->grid->map,
			(int)player->pos_y >> 6, (int)player->pos_x >> 6);
	telep = check_if_telep(game, c);
	if (telep && player->is_in_telep == 0)
		apply_telep(player, telep->peer, c);
	else if (!telep)
		player->is_in_telep = 0;
}
