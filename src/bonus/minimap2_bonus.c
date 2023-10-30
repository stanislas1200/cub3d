/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:09:47 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/30 10:28:15 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	init_line(t_game *game, int x, int y, double size)
{
	t_line	l;

	l.x1 = x + (size / 2);
	l.y1 = y + (size / 2);
	l.x2 = x + (size / 2) + game->player.pdx * 6;
	l.y2 = y + (size / 2) + game->player.pdy * 6;
	if (l.x1 < l.x2)
		l.sx = 1;
	else
		l.sx = -1;
	if (l.y1 < l.y2)
		l.sy = 1;
	else
		l.sy = -1;
	l.dx = abs(l.x2 - l.x1);
	l.dy = abs(l.y2 - l.y1);
	drawline(game, l);
}

void	draw_entity(t_game *game, int x, int y, unsigned int color)
{
	t_square		s;

	s.color = color;
	s.size = square_size();
	s.x = (x - (((int)game->player.px >> 6) - MAP_C)) * s.size;
	s.y = (y - (((int)game->player.py >> 6) - MAP_C)) * s.size;
	draw_square(game, s);
}

double	square_size(void)
{
	return (MAP_W / (MAP_C * 2));
}

int	in_minimap(double x1, double y1)
{
	return (distance(x1, y1, MAP_CENTER, MAP_CENTER) < MAP_CENTER);
}
