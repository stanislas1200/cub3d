/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:42:49 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/29 15:53:42 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	setup_img(t_img *img, t_game *game, int pos[4], double size)
{
	t_idraw	i;

	i.height = pos[3];
	i.width = pos[2];
	i.img = img;
	i.startx = pos[0];
	i.starty = pos[1];
	i.stepx = pos[2] / (i.width * size);
	i.stepy = pos[3] / (i.height * size);
	i.endx = pos[0] + (i.width * size);
	i.endy = pos[1] + (i.height * size);
	i.endx = fmax(fmin(i.endx, WIDTH), 0);
	i.startx = fmax(i.startx, 0);
	i.starty = fmax(i.starty, 0);
	i.endy = fmax(fmin(i.endy, HEIGHT), 0);
	// printf(RESET "stepx  %fstepy  %fstartx  %dstarty %d endx %d endy %d\n", i.stepx, i.stepy, i.startx, i.starty, i.endx, i.endy);
	draw_img(game, &i);
}


void	draw_img(t_game *game, t_idraw *i)
{
	double			tex_x;
	double			tex_y;
	double			y;
	unsigned int	color;

	tex_x = 0;
	while (i->startx < i->endx)
	{
		tex_y = 0;
		y = i->starty;
		while (y < i->endy)
		{
			color = get_color(i->img, \
			(int)tex_x % i->width, (int)tex_y % i->height);
			if (color != 0xFF000000 && i->startx >= 0 && \
			i->startx < WIDTH && y >= 0 && y < HEIGHT)
				my_mlx_pixel_put(&game->img, i->startx, y, color);
			y++;
			tex_y += i->stepy;
		}
		tex_x += i->stepx;
		i->startx++;
	}
}
