/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:59 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/01 18:19:22 by sgodin           ###   ########.fr       */
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

void	render_wall(t_game *game, t_draw *d, double x, t_ray *ray)
{
	unsigned int	color;
	double			texy;
	double			start;

	start = d->lineO;
	texy = d->ty_offset * d->step;
	while (start < (d->lineO + d->lineH) && start < HEIGHT)
	{
		texy += d->step;
		if (texy >= 64)
			texy = 0;
		color = get_color(game->sprites.wall[(int)d->tex], \
		(int)d->texX, (int)texy);
		my_mlx_pixel_put(&game->img, x, start, color);
		start++;
	}
}
