/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:09:09 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/30 17:49:54 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	render_monster(t_game *game, t_mdraw *d, double x);
void	init_mob_drawing(t_game *game, t_mdraw *d, double dist, double screenx);
double	fov_side(t_game *game);
int		check_bullet_wall(t_game *game, double angle, double dist);

int	in_view(t_game *game)
{
	double	a;
	double	b;
	double	c;
	double	angle;
	double	angle2;

	b = distance(game->player.px, game->player.py, \
	game->player.px + game->player.pdx, game->player.py + game->player.pdy);
	a = distance(game->player.px + game->player.pdx, \
	game->player.py + game->player.pdy, game->monster.x, game->monster.y);
	c = distance (game->player.px, game->player.py, \
	game->monster.x, game->monster.y);
	angle = acos((b * b + c * c - a * a) / (2 * b * c));
	angle *= 180 / PI;
	angle2 = angle;
	if (fov_side(game) >= 0)
		angle = (FOV / 2) - angle;
	else
		angle = (FOV / 2) + angle;
	return (angle2 <= 10 && \
	check_bullet_wall(game, game->player.pa - FOV / 2 + angle, c));
}

int	check_bullet_wall(t_game *game, double angle, double dist)
{
	t_ray	hray;
	t_ray	vray;
	t_ray	*ray;

	init_ray(&hray, game, angle, 'H');
	init_ray(&vray, game, angle, 'V');
	if (hray.dist < vray.dist)
		ray = &hray;
	else
		ray = &vray;
	return (dist < ray->dist && dist < 500);
}

void	draw_monster(t_game *game)
{
	double	a;
	double	b;
	double	c;
	double	angle;
	t_mdraw	d;

	if (game->monster.state == DEAD)
		return ;
	b = distance(game->player.px, game->player.py, \
	game->player.px + game->player.pdx, game->player.py + game->player.pdy);
	a = distance(game->player.px + game->player.pdx, \
	game->player.py + game->player.pdy, game->monster.x, game->monster.y);
	c = distance (game->player.px, game->player.py, \
	game->monster.x, game->monster.y);
	angle = acos((b * b + c * c - a * a) / (2 * b * c));
	angle *= 180 / PI;
	if (fov_side(game) >= 0)
		angle = (FOV / 2) + angle;
	else
		angle = (FOV / 2) - angle;
	init_mob_drawing(game, &d, c, angle * (WIDTH / FOV));
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

void	init_mob_drawing(t_game *game, t_mdraw *d, double dist, double screenx)
{
	d->ty_offset = 0;
	d->dist = dist;
	d->line_h = ((SQUARE * HEIGHT) / dist);
	d->stepy = (game->mob->height / d->line_h);
	d->stepx = (game->mob->width / d->line_h);
	d->fog = d->dist / 400;
	d->endx = screenx + d->line_h / 2;
	d->startx = screenx - d->line_h / 2;
	d->tex_x = 0;
	d->tex_x = 0;
	d->endx = fmin(d->endx, WIDTH);
	if (d->line_h > HEIGHT)
	{
		d->ty_offset = (d->line_h - HEIGHT) / 2.0;
		d->line_h = HEIGHT;
	}
	d->line_o = (HEIGHT / 2) - ((int)d->line_h >> 1);
}
