/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:42:49 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/29 10:45:46 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	setup_img(t_img *img, int x, int y, double size)
{
	t_idraw	i;

	i.height = img->height;
	i.width = img->width;
	i.img = img;
	i.startx = x;
	i.starty = y;
	i.stepx = (i.width * size) / img->width;
	i.stepy = (i.height * size) / img->height;
	i.endx = x + (i.width * size);
	i.endy = y + (i.height * size);
	i.endx = fmax(fmin(i.endx, WIDTH), 0);
	i.endy = fmax(fmin(i.endy, HEIGHT), 0);
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
		tex_x += i->stepx;
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
		i->startx++;
	}
}