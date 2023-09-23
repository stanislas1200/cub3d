/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:48:01 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/23 17:08:43 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_rays(t_game *game)
{
	int	i;
	int	fov;

	i = -1;
	fov = game->player.pa - (FOV / 2);
	while (++i < 90)
	{
		fix_ang(fov);
		ray_cast(game, fov, (i) * (WIDTH / 90));
		fov++;
	}
}

void	ray_cast(t_game *game, double angle, int s_width)
{
	t_ray *Hray;
	t_ray *Vray;
	double			lineH;
	double			lineO;
	double			dist;

	dist = 1;
	Hray = malloc(sizeof(t_ray));
	Vray = malloc(sizeof(t_ray));
	init_ray(Hray, game, angle, 'H');
	init_ray(Vray, game, angle, 'V');
	if (Hray->dist <= Vray->dist)
		dist = Hray->dist;
	else
		dist = Vray->dist;
	dist *= cos(deg_to_rad(fix_ang(game->player.pa - angle)));
	lineH = (SQUARE * HEIGHT) / dist;
	if (lineH > HEIGHT)
		lineH = HEIGHT;
	lineO = HEIGHT / 2 - lineH / 2;
	drawstripes(game, ((s_width)), 0, lineO, 0x00ffee); // draw Sky
	drawstripes(game, ((s_width)), lineO, lineH + lineO, 0xff2200); // draw wall
	free(Hray);
	free(Vray);
}
