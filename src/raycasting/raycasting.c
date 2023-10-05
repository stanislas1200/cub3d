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
	double	i;
	double	fov;
	double	angle;

	i = 0;
	fov = game->player.pa - (FOV / 2);
	angle = fov;
	while (angle < game->player.pa + (FOV / 2))
	{
		fov = fix_ang(fov);
		ray_cast(game, fov, (i));
		fov += FOV / WIDTH;
		angle += FOV / WIDTH;
		i++;
	}
}

void	init_drawing(t_game *game, t_draw *d, t_ray *ray, double angle)
{
	d->ty_offset = 0;
	d->realdist = ray->dist;
	ray->dist *= cos(deg_to_rad(fix_ang(game->player.pa - angle)));
	d->lineH = (SQUARE * HEIGHT) / ray->dist;
	d->step = (SQUARE / d->lineH);
	if (d->lineH > HEIGHT)
	{
		d->ty_offset = (d->lineH - HEIGHT) / 2.0;
		d->lineH = HEIGHT;
	}
	if (ray->side == 0)
		d->texX = ray->rx - (((int)ray->rx >> 6)<<6);
	else if (ray->side == 1)
		d->texX = ray->ry - (((int)ray->ry >> 6)<<6);
	if((ray->side == 0 && ray->ra > 180) || (ray->side == 1 &&(ray->ra > 90 && ray->ra < 270)))
		d->texX = 64 - d->texX;
	d->tex = texture(ray->side, ray->ra);
	d->lineO = (HEIGHT / 2) - ((int)d->lineH >> 1);
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
	drawstripes(game, s_width, 0, d->lineO, game->data->ceiling[2]);
	render_wall(game, d, (s_width), ray);
	drawstripes(game, s_width, d->lineH + d->lineO, HEIGHT, game->data->floor[2]);
}