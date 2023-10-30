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

#include "../../../include/cub3d_bonus.h"

void	render_wall(t_game *game, t_draw *d, double x, t_ray *ray);
void	draw(t_game *game, t_ray *ray, t_draw *d, int s_width);
int		create_trgb(int t, int r, int g, int b);

void	draw_rays(t_game *game)
{
	double	i;
	double	fov;

	i = 0;
	fov = game->player.pa - (FOV / 2);
	i = WIDTH;
	while (--i >= 0)
	{
		fov = fix_ang(fov);
		ray_cast(game, fov, i);
		fov += FOV / WIDTH;
	}
}

void	init_drawing(t_game *game, t_draw *d, t_ray *ray, double angle)
{
	d->ty_offset = 0;
	d->realdist = ray->dist;
	ray->dist *= cos(deg_to_rad(fix_ang(game->player.pa - angle)));
	d->line_h = (SQUARE * HEIGHT) / ray->dist;
	d->step = (SQUARE / d->line_h);
	if (d->line_h > HEIGHT)
	{
		d->ty_offset = (d->line_h - HEIGHT) / 2.0;
		d->line_h = HEIGHT;
	}
	if (ray->side == 0)
		d->tex_x = (int)ray->rx % 256;
	else
		d->tex_x = (int)ray->ry % 256;
	if ((ray->side == 0 && ray->ra < 180) || ray->side == 1)
		d->tex_x = (256 - 1) - d->tex_x;
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
	if (hray.dist < vray.dist && hray.hit == 1)
		ray = &hray;
	else
		ray = &vray;
	if (ray->hit == 1)
	{
		game->depths[s_width] = ray->dist;
		init_drawing(game, &d, ray, angle);
		draw(game, ray, &d, s_width);
	}
}

void	draw(t_game *game, t_ray *ray, t_draw *d, int s_width)
{
	game->color = create_trgb(0, game->data->ceiling[0], \
	game->data->ceiling[1], game->data->ceiling[2]);
	drawstripes(game, s_width, 0, d->line_o);
	render_wall(game, d, (s_width), ray);
	game->color = create_trgb(0, game->data->floor[0], game->data->floor[1], \
	game->data->floor[2]);
	drawstripes(game, s_width, d->line_h + d->line_o, HEIGHT);
}

int	in_map(t_game *game, int x, int y)
{
	return (y >= 0 && x >= 0 && y < game->data->height && \
	x < ft_strlen(game->data->map[y]) && game->data->map[y][x]);
}