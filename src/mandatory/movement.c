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

#include "../../include/cub3d.h"

void	movement(t_game *g)
{
	if (g->keys[0])
		can_move(g, g->player.px + g->player.pdx * g->player.speed, \
		g->player.py + g->player.pdy * g->player.speed);
	if (g->keys[1])
	{
		can_move(g, g->player.px - g->player.pdx * g->player.speed / 2, \
		g->player.py - g->player.pdy * g->player.speed / 2);
	}
	if (g->keys[5])
		can_move(g, g->player.px - g->player.pdy * g->player.speed / 5, \
		g->player.py + g->player.pdx * g->player.speed / 5);
	if (g->keys[4])
		can_move(g, g->player.px + g->player.pdy * g->player.speed / 5, \
		g->player.py - g->player.pdx * g->player.speed / 5);
	if (g->keys[2])
		g->player.pa += 10.0 * g->player.speed / 2;
	if (g->keys[3])
		g->player.pa -= 10.0 * g->player.speed / 2;
	g->player.pa = fix_ang(g->player.pa);
	g->player.pdx = cos(deg_to_rad(g->player.pa)) * 5.0;
	g->player.pdy = -sin(deg_to_rad(g->player.pa)) * 5.0;
}

void	can_move(t_game *game, double fx, double fy)
{
	game->player.px = fx;
	game->player.py = fy;
}
