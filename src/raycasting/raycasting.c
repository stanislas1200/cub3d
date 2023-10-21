/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:48:01 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/30 15:52:57 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_wall(t_game *game, t_draw *d, double x, t_ray *ray);
void	draw(t_game *game, t_ray *ray, t_draw *d, int s_width);
int		texture(int side, double ra);

void	draw_rays(t_game *game)
{
	int		i;
	double	fov;
	double	angle;

	i = 0;
	fov = game->player.pa - (FOV / 2);
	angle = 0;
	while (angle < FOV)
	{
		ray_cast(game, fix_ang(fov), i++);
		angle += (FOV / WIDTH);
		fov += (FOV / WIDTH);
	}
}

void	init_drawing(t_game *game, t_draw *d, t_ray *ray, double angle)
{
	d->ty_offset = 0;
	ray->dist *= cos(deg_to_rad(fix_ang(game->player.pa - angle)));
	d->line_h = (SQUARE * HEIGHT) / ray->dist;
	d->step = (SQUARE / d->line_h);
	if (d->line_h > HEIGHT)
	{
		d->ty_offset = (d->line_h - HEIGHT) / 2.0;
		d->line_h = HEIGHT;
	}
	if (ray->side == 0)
		d->tex_x = ray->rx - (((int)ray->rx >> 6) << 6);
	else if (ray->side == 1)
		d->tex_x = ray->ry - (((int)ray->ry >> 6) << 6);
	if ((ray->side == 0 && ray->ra > 180) || \
	(ray->side == 1 && (ray->ra > 90 && ray->ra < 270)))
		d->tex_x = 64 - d->tex_x;
	d->tex = texture(ray->side, ray->ra);
	d->line_o = (HEIGHT / 2) - ((int)d->line_h >> 1);
}

void	ray_cast(t_game *game, double angle, int s_width)
{
	t_ray	hray;
	t_ray	vray;
	t_ray	*ray;
	t_draw	d;

	init_ray(&hray, game, angle, 'H');
	init_ray(&vray, game, angle, 'V');
	if (hray.dist < vray.dist)
		ray = &hray;
	else
		ray = &vray;
	init_drawing(game, &d, ray, angle);
	draw(game, ray, &d, s_width);
}

int	texture(int side, double ra)
{
	if (side == 0 && ra < 180)
		return (0);
	else if (side == 0 && ra >= 180)
		return (2);
	else if (side == 1 && ra > 90 && ra < 270)
		return (1);
	else if (side == 1 && ra <= 90 || ra >= 270)
		return (3);
	return (0);
}

void	draw(t_game *game, t_ray *ray, t_draw *d, int s_width)
{
	game->color = game->data->ceiling[2];
	drawstripes(game, s_width, 0, d->line_o);
	render_wall(game, d, (s_width), ray);
	game->color = game->data->floor[2];
	drawstripes(game, s_width, d->line_h + d->line_o, HEIGHT);
}
