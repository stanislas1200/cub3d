/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:59 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/29 12:06:25 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	drawstripes(t_game *game, int x1, int y1, int y2, int color)
{
	while ((y1 >= 0 && y1 < y2) && y1 < HEIGHT)
	{
		my_mlx_pixel_put(&game->img, x1, y1, color);
		y1++;
	}
}

void	render_wall(t_game *game, t_draw *d, double x, int side)
{
	unsigned int	color;
	double			texy;
	double			start;

	start = d->lineO;
	texy = d->ty_offset * d->step;
	while (start <= d->lineO + d->lineH)
	{
		texy += d->step;
		if (texy >= 64)
			texy = 0;
		color = get_color(game->sprites.wall[(int)d->tex], \
		(int)d->texX, (int)texy);
		if (side)
			color /= 2;
		my_mlx_pixel_put(&game->img, x, start, color);
		start++;
	}
}
