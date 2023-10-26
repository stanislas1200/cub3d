/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:09:09 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/26 11:40:45 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_drawing(t_game *game, t_draw *d, t_ray *ray, double angle);
void	render_monster(t_game *game, t_draw *d, double x);
void	init_mob_drawing(t_game *game, t_draw *d, double dist);
double	fov_side(t_game *game);

void	draw_monster(t_game *game)
{
	double	a;
	double	b;
	double	c;
	double	angle;
	t_draw	d;

	b = distance(game->player.px, game->player.py, \
	game->player.px + game->player.pdx, game->player.py + game->player.pdy);
	a = distance(game->player.px + game->player.pdx, \
	game->player.py + game->player.pdy, game->monster.x, game->monster.y);
	c = distance (game->player.px, game->player.py, \
	game->monster.x, game->monster.y);
	angle = acos((b * b + c * c - a * a) / (2 * b * c));
	angle *= 180 / PI;
	if (fov_side(game) >= 0)
		angle = (FOV / 2) - angle;
	else
		angle = (FOV / 2) + angle;
	init_mob_drawing(game, &d, c);
	render_monster(game, &d, angle * (WIDTH / FOV));
}

double	fov_side(t_game *game)
{
	double	abx;
	double	aby;
	double	adx;
	double	ady;

	abx = game->player.pdx * SQUARE;
	aby = game->player.pdy * SQUARE;
	adx = game->monster.x - game->player.px;
	ady = game->monster.y - game->player.py;
	return ((abx * ady) - (aby * adx));
}

void	init_mob_drawing(t_game *game, t_draw *d, double dist)
{
	d->ty_offset = 0;
	d->realdist = dist;
	d->line_h = ((SQUARE * HEIGHT) / dist);
	d->step = (SQUARE / d->line_h);
	if (d->line_h > HEIGHT)
		d->line_h = HEIGHT;
	d->line_o = (HEIGHT / 2) - ((int)d->line_h >> 1);
}
