/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:42:49 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/30 12:30:47 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	setup_img(t_img *img, t_game *game, int pos[2], double size)
{
	t_idraw	i;

	i.height = img->height;
	i.width = img->width;
	i.img = img;
	i.startx = pos[0];
	i.starty = pos[1];
	i.stepx = img->width / (i.width * size);
	i.stepy = img->height / (i.height * size);
	i.endx = pos[0] + (i.width * size);
	i.endy = pos[1] + (i.height * size);
	i.endx = fmax(fmin(i.endx, WIDTH), 0);
	i.startx = fmax(i.startx, 0);
	i.starty = fmax(i.starty, 0);
	i.endy = fmax(fmin(i.endy, HEIGHT), 0);
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

t_img	*get_wall(t_game *game, t_ray *ray)
{
	if (ray->my > game->data->height / 3)
		return (game->sprites.wall_i[(game->data->time / 10) % 4]);
	else if (ray->my <= game->data->height / 3 \
	&& ray->my >= game->data->height / 3 - 1)
		return (game->sprites.wall_m[(game->data->time / 10) % 4]);
	else
		return (game->sprites.wall[(game->data->time / 10) % 4]);
}
