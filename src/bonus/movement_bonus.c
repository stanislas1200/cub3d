/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:59:57 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/02 18:15:47 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	ease_in(t_game *game);

void	movement(t_game *g)
{
	ease_in(g);
	if (g->keys[0])
		can_move(g, g->player.px + g->player.pdx * g->player.speed, \
		g->player.py + g->player.pdy * g->player.speed, 0);
	if (g->keys[1])
	{
		can_move(g, g->player.px - g->player.pdx * g->player.speed / 2, \
		g->player.py - g->player.pdy * g->player.speed / 2, 180);
	}
	if (g->keys[5])
		can_move(g, g->player.px - g->player.pdy * g->player.speed / 5, \
		g->player.py + g->player.pdx * g->player.speed / 5, -90);
	if (g->keys[4])
		can_move(g, g->player.px + g->player.pdy * g->player.speed / 5, \
		g->player.py - g->player.pdx * g->player.speed / 5, 90);
	if (g->keys[2])
		g->player.pa += 10.0 * g->player.speed / 2;
	if (g->keys[3])
		g->player.pa -= 10.0 * g->player.speed / 2;
	g->player.pa = fix_ang(g->player.pa);
	g->player.pdx = cos(deg_to_rad(g->player.pa)) * 5.0;
	g->player.pdy = -sin(deg_to_rad(g->player.pa)) * 5.0;
}

void	can_move(t_game *game, double fx, double fy, int side)
{
	t_ray	hray;
	t_ray	vray;
	t_ray	*ray;

	init_ray(&hray, game, game->player.pa + side, 'H');
	init_ray(&vray, game, game->player.pa + side, 'V');
	if (hray.dist < vray.dist)
		ray = &hray;
	else
		ray = &vray;
	if (ray->dist > distance(game->player.px, game->player.py, fx, fy) + 10)
	{
		game->player.px = fx;
		game->player.py = fy;
	}
}

void	ease_in(t_game *g)
{
	if (g->keys[0] || g->keys[1] || \
	g->keys[5] || g->keys[4] || g->keys[2] || g->keys[3])
	{
		g->player.speed += fmax(fmin(g->data->fade_cd, 1.5), 0);
		g->player.speed = fmin(g->player.speed, 1.5);
		g->data->fade_cd += 0.5 * fmax(g->data->fade_cd, 0.5);
		g->data->fade_cd = fmin(g->data->fade_cd, 1.5);
	}
	else
	{
		g->data->fade_cd = 0.5;
		g->player.speed = 0.5;
	}
}
