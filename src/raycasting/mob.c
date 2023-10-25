/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:09:09 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/25 14:07:07 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	in_view(t_game *game)
{
	double	a;
	double	b;
	double	c;
	double	angle;
	t_ray	hray;
	t_ray	vray;
	t_ray	*ray;
	
	if (game->monster.state == DEAD)
		return (0);
	init_ray(&hray, game, game->player.pa, 'H');
	init_ray(&vray, game, game->player.pa, 'V');
	if (hray.dist < vray.dist)
		ray = &hray;
	else
		ray = &vray;
	b = distance(game->player.px, game->player.py, \
	game->player.px + game->player.pdx, game->player.py + game->player.pdy);
	a = distance(game->player.px + game->player.pdx, \
	game->player.py + game->player.pdy, game->monster.x, game->monster.y);
	c = distance (game->player.px, game->player.py, \
	game->monster.x, game->monster.y);
	angle = acos((b * b + c * c - a * a) / (2 * b * c));
	angle *= 180/PI;
	if (angle <= 45.0 && c < ray->dist)
		return (printf(RED "je le vois\n"), 1);
	printf(MAGENTA "je le vois pas\n");
	return (0);
}