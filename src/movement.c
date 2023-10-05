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

#include "../include/cub3d.h"

void	movement(t_game *game)
{
	double fx, fy;
	if (game->keys[0])
	{
		fx = game->player.px + game->player.pdx + game->player.speed;
		fy = game->player.py + game->player.pdy + game->player.speed;
		if (can_move(game, fx, fy, 0))
		{
			game->player.px += game->player.pdx * game->player.speed;
			game->player.py += game->player.pdy * game->player.speed;
		}
	}
	if (game->keys[1])
	{
		fx = game->player.px - game->player.pdx * game->player.speed / 2;
		fy = game->player.py - game->player.pdy * game->player.speed / 2;
		if (can_move(game, fx, fy, 180))
		{
			game->player.px -= game->player.pdx * game->player.speed / 2;
			game->player.py -= game->player.pdy * game->player.speed / 2;
		}
	}
	if (game->keys[4])
	{
		fx = game->player.px - game->player.pdy * game->player.speed / 5;
		fy = game->player.py + game->player.pdx * game->player.speed / 5;
		if (can_move(game, fx, fy, -90))
		{
			game->player.px -= game->player.pdy * game->player.speed / 5;
			game->player.py += game->player.pdx * game->player.speed / 5;
		}
	}
	if (game->keys[5])
	{
		fx = game->player.px + game->player.pdy * game->player.speed / 5;
		fy = game->player.py - game->player.pdx * game->player.speed / 5;
		if (can_move(game, fx, fy, 90))
		{
			game->player.px += game->player.pdy * game->player.speed / 5;
			game->player.py -= game->player.pdx * game->player.speed / 5;
		}
	}
	if (game->keys[2])
		game->player.pa -= 5.0 * game->player.speed / 2;
	if (game->keys[3])
		game->player.pa += 5.0 * game->player.speed / 2;
	game->player.pa = fix_ang(game->player.pa);
	game->player.pdx = cos(deg_to_rad(game->player.pa)) * 5.0;
	game->player.pdy = -sin(deg_to_rad(game->player.pa)) * 5.0;
}

int	can_move(t_game *game, double fx, double fy, int side)
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
		return (1);
	return (0);
};