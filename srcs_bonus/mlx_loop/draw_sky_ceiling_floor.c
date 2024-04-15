/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky_ceiling_floor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:34:07 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/15 18:53:16 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	get_texture_fsc(t_game *game, char *text, int texture)
{
	int		index;
	char	*pixel;
	int		x;
	int		y;
	t_tex	*tex;

	x = (int)game->floor_x % 64;
	y = (int)game->floor_y % 64;
	index = texture;
	tex = game->tex;
	while (tex && (char)texture != tex->name)
		tex = tex->next;
	if (!tex || tex->image[0].im_ptr == NULL || tex->image[1].im_ptr == NULL)
		return (0);
	if (ft_strncmp(text, "FLOOR", 5) == 0)
	{
		index = y * tex->image[0].line_size + x * (tex->image[0].bpp >> 3);
		pixel = tex->image[0].im_addr + index;
	}
	else
	{
		index = y * tex->image[1].line_size + x * (tex->image[1].bpp >> 3);
		pixel = tex->image[1].im_addr + index;
	}
	return (*(unsigned int *)pixel);
}

char	ceiling_or_sky(t_game *game, char c)
{
	int	i;

	i = -1;
	while (game->ceiling[++i])
		if (game->ceiling[i] == c)
			return (c);
	return (0);
}

void	render_floor(t_game *game, int x, int y)
{
	double	dist;
	double	beta;
	double	alpha;
	double	hyp;

	alpha = game->angle[x];
	beta = fabs(game->angle[x] - game->player->orientation);
	dist = (double)(32 * game->grid->dist_proj_plan)
		/ (double)(y - game->player->view_y);
	hyp = dist / cos(dtor(beta));
	game->floor_x = game->player->pos_x + (cos(dtor(alpha)) * hyp);
	game->floor_y = game->player->pos_y - (sin(dtor(alpha)) * hyp);
	my_mlx_pixel_put(game, x, y, get_texture_fsc(game, "FLOOR",
			try_get_texture(game->grid->map,
				(int)game->floor_y >> 6, (int)game->floor_x >> 6)));
}

void	render_ceiling_sky(t_game *game, int x, int y)
{
	double	dist;
	double	beta;
	double	alpha;
	double	hyp;

	alpha = game->angle[x];
	beta = fabs(game->angle[x] - game->player->orientation);
	dist = (double)(32 * game->grid->dist_proj_plan)
		/ (double)(game->player->view_y - y);
	hyp = dist / cos(dtor(beta));
	game->floor_x = game->player->pos_x + (cos(dtor(alpha)) * hyp);
	game->floor_y = game->player->pos_y - (sin(dtor(alpha)) * hyp);
	if (ceiling_or_sky(game, try_get_texture(game->grid->map,
				(int)game->floor_y >> 6, (int)game->floor_x >> 6)) == 0)
		my_mlx_pixel_put(game, x, y, get_sky(game, x, y));
	else
		my_mlx_pixel_put(game, x, y, get_texture_fsc(game, "CEILING",
				try_get_texture(game->grid->map,
					(int)game->floor_y >> 6, (int)game->floor_x >> 6)));
}

unsigned int	get_sky(t_game *game, int x, int y)
{
	int		index;
	char	*pixel;
	t_tex	*tex;

	tex = game->tex;
	while (tex->name != '2')
		tex = tex->next;
	if (!tex)
		return (0);
	// y = y % SKY_HEIGHT;
	y = y % tex->image[1].im_height;//ICI donne plusieur platypus je pense
	index = y * tex->image[1].line_size
		+ ((int)round((game->angle[x] * tex->image[1].im_width/*SKY_WIDTH*/ / 360.0)))// 64 selon texture sky valide
		* (tex->image[1].bpp >> 3);
	pixel = tex->image[1].im_addr + index;
	return (*(unsigned int *)pixel);
}
