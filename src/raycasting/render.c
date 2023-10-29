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

double	in_circle(double x, double y)
{
	double	radius;
	double	dist;
	double	light;

	radius = 230.0;
	dist = distance(x, y, WIDTH / 2, HEIGHT / 2);
	light = (dist - radius);
	return (light * 0.01);
}

unsigned int	darken_color(t_game *game, unsigned int color, double fog)
{
	int	r;
	int	g;
	int	b;

	r = color / (256 * 256);
	g = (color % (256 * 256)) / 256;
	b = color % 256;
	r -= (int)(r * fog);
	g -= (int)(g * fog);
	b -= (int)(b * fog);
	if (game->player.trip)
		return (((int)(r * 0.9) *256 * 256) + (g / 3 * 256) + b / 3);
	r = fmin(fmax(r, 0), 255);
	g = fmin(fmax(g, 0), 255);
	b = fmin(fmax(b, 0), 255);
	if (game->player.hurt)
		return (((int)(r * 0.9) *256 * 256) + (g / 3 * 256) + b / 3);
	return ((r * 256 * 256) + (g * 256) + b);
}

void	drawstripes(t_game *game, int x1, int y1, int y2)
{
	double			fog;
	double			y3;
	unsigned int	color2;

	while ((y1 >= 0 && y1 < y2) && y1 < HEIGHT)
	{
		y3 = y1;
		color2 = game->color;
		if (y3 <= HEIGHT / 2)
			fog = y3 / ((HEIGHT / 2));
		else
		{
			fog = y3 / ((HEIGHT / 2));
			while (fog > 1)
				fog -= 1;
			fog = 1 - fog;
		}
		color2 = darken_color(game, game->color, fog);
		if (y1 > HEIGHT / 2)
			color2 = darken_color(game, color2, (in_circle(x1, y1)) * 1);
		my_mlx_pixel_put(&game->img, x1, y1, color2);
		y1++;
	}
}

void	render_wall(t_game *game, t_draw *d, double x, t_ray *ray)
{
	unsigned int	color;
	double			texy;
	double			start;
	double			fog;

	start = d->line_o - 1;
	texy = d->ty_offset * d->step;
	fog = d->realdist / 400;
	while (++start < (d->line_o + d->line_h) && start < HEIGHT)
	{
		texy += d->step;
		color = get_color(game->sprites.wall
			[(game->data->time / 10) % 4], (int)d->tex_x, (int)texy % 64);
		if (ray->my > game->data->height / 3)
			color = get_color(game->sprites.wallI
				[(game->data->time / 10) % 4], (int)d->tex_x, (int)texy % 64);
		else if (ray->my <= game->data->height / 3 \
		&& ray->my >= game->data->height / 3 - 1)
			color = get_color(game->sprites.wallM
				[(game->data->time / 10) % 4], (int)d->tex_x, (int)texy % 64);
		color = darken_color(game, color, fog);
		color = darken_color(game, color, in_circle(x, start));
		if (x >= 0 && x < WIDTH && start >= 0)
			my_mlx_pixel_put(&game->img, x, start, color);
	}
}

void	render_monster(t_game *game, t_mdraw *d, double x)
{
	unsigned int	color;
	double			y;

	while (d->startx < d->endx)
	{
		y = d->line_o;
		d->tex_y = d->ty_offset * d->stepy;
		while (d->startx >= 0 && y < (d->line_o + d->line_h) && y < HEIGHT)
		{
			color = get_color(game->mob, \
			(int)d->tex_x % 720, (int)d->tex_y % 1104);
			if (color != 0xFF000000)
			{
				color = darken_color(game, color, d->fog);
				color = darken_color(game, color, in_circle(x, y));
				if (d->startx >= 0 && d->startx < WIDTH \
				&& y >= 0 && d->dist < game->depths[d->startx])
					my_mlx_pixel_put(&game->img, d->startx, y, color);
			}
			d->tex_y += d->stepy;
			y++;
		}
		d->tex_x += d->stepx;
		d->startx++;
	}
}
