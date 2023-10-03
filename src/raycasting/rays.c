/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:48:52 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/29 12:12:14 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_for_hit(t_game *game, t_ray *ray)
{
	int	stop;

	stop = 0;
	while (ray->hit == 0 && !stop)
	{
		ray->mx = ((int)ray->rx) >> 6;
		ray->my = ((int)ray->ry) >> 6;
		if ((ray->my >= 0 && ray->mx >= 0) && ray->my < game->data->height && \
		ray->mx < ft_strlen(game->data->map[ray->my]) \
		&& game->data->map[ray->my][ray->mx])
		{
			if (game->data->map[ray->my][ray->mx] == 'X')
			{
				ray->hit = 1;
				ray->dist = distance(game->player.px, \
				game->player.py, ray->rx, ray->ry);
			}
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
			}
		}
		else
			stop++;
	}
}

void	setup_horizontal_ray(t_ray *ray, t_game *game)
{
	double	ray_tan;

	ray_tan = 1.0 / tan(deg_to_rad(ray->ra));
	if (sin(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->ry = ((((int)game->player.py >> 6) << 6) + 64);
		ray->rx = ((game->player.py - ray->ry) * ray_tan) + game->player.px;
		ray->yo = 64;
		ray->xo = -ray->yo * ray_tan;
	}
	else if (sin(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->ry = (((int)game->player.py >> 6) << 6) - 0.0001;
		ray->rx = ((game->player.py - ray->ry) * ray_tan) + game->player.px;
		ray->yo = -64;
		ray->xo = -ray->yo * ray_tan;
	}
	else
	{
		ray->rx = game->player.px;
		ray->ry = game->player.py;
		ray->hit = -1;
	}
}

void	setup_vertical_ray(t_ray *ray, t_game *game)
{
	double	ray_tan;

	ray_tan = tan(deg_to_rad(ray->ra));
	if (cos(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->rx = ((((int)game->player.px >> 6) << 6) + 64);
		ray->ry = ((game->player.px - ray->rx) * ray_tan) + game->player.py;
		ray->xo = 64;
		ray->yo = -ray->xo * ray_tan;
	}
	else if (cos(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->rx = ((((int)game->player.px >> 6) << 6) - 0.0001);
		ray->ry = ((game->player.px - ray->rx) * ray_tan) + game->player.py;
		ray->xo = -64;
		ray->yo = -ray->xo * ray_tan;
	}
	else
	{
		ray->ry = game->player.py;
		ray->ra = game->player.py;
		ray->hit = -1;
	}
}

void	init_ray(t_ray *ray, t_game *game, double angle, char type)
{
	ray->rx = game->player.px;
	ray->ry = game->player.py;
	ray->ra = angle;
	ray->xo = 0;
	ray->yo = 0;
	ray->hit = 0;
	ray->mx = (int)game->player.px;
	ray->my = (int)game->player.py;
	ray->dist = INT_MAX;
	if (type == 'H')
	{
		ray->side = 0;
		setup_horizontal_ray(ray, game);
	}
	else
	{
		ray->side = 1;
		setup_vertical_ray(ray, game);
	}
	check_for_hit(game, ray);
}
