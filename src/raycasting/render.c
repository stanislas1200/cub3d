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
	// if (game->player.trip) // trip // DEV
	// 	return (((r * 256 * 256) + (g * 256) + b));
	if (r > 255)
		r = 255;
	if (r <= 0)
		r = 0;
	if (g > 255)
		g = 255;
	if (g <= 0)
		g = 0;
	if (b > 255)
		b = 255;
	if (b <= 0)
		b = 0;
	if (game->player.trip) // RED // DEV
		return ((((int)(r*0.9) * 256 * 256) + (g/3 * 256) + b/3));
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

	start = d->line_o;
	texy = d->ty_offset * d->step;
	fog = d->realdist / 400;
	if (d->tex_x < 0)
		d->tex_x = 0;
	while (start < (d->line_o + d->line_h) && start < HEIGHT)
	{
		texy += d->step;
		color = get_color(game->sprites.wall[(int)d->tex], \
		(int)d->tex_x, (int)texy);
		if (ray->my > game->data->height / 3) // red propagation
			color = get_color(game->sprites.wallI[(game->data->time / 10 + (int)d->tex) % 4], (int)d->tex_x, (int)texy); // animated wall exemple
		else if (ray->my <= game->data->height / 3 && ray->my >= game->data->height / 3 - 1)
			color = get_color(game->sprites.wallM[(game->data->time / 10 + (int)d->tex) % 4],  (int)d->tex_x, (int)texy); // animated wall exemple
		else
			color = get_color(game->sprites.wall[(game->data->time / 10 + (int)d->tex) % 4],  (int)d->tex_x, (int)texy); // animated wall exemple
		color = darken_color(game, color, fog);
		color = darken_color(game, color, in_circle(x, start));
		if (x >= 0 && x < WIDTH && start >= 0)
			my_mlx_pixel_put(&game->img, x, start, color);
		start++;
	}
}

void	render_monster(t_game *game, t_draw *d, double x)
{
	unsigned int	color;
	double			texy;
	double			start;
	double			fog;
	double			startx = x;
	double			tex_x = 0;

	for (int i = x - d->line_h/2; i < x + d->line_h/2; i++)
	{
		start = d->line_o;
		texy = 0;
		for (int j = 0; j < d->line_h; j++)
		{
			texy += d->step;
			color = get_color(game->mob, \
			(int)tex_x, (int)texy);
			// color = darken_color(color, fog);
			// color = darken_color(color, in_circle(x, start));
			if(i >= 0 && i < WIDTH && start>= 0 && start < HEIGHT)
				my_mlx_pixel_put(&game->img, i, start, color);
			start++;
		}
		tex_x += d->step;
	}
}
