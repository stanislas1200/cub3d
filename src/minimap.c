/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:32:10 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/28 16:25:57 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_line(t_game *game, int x, int y, double size);

void	drawline(t_game *game, t_line l)
{
	int	err;
	int	e2;

	err = l.dx - l.dy;
	while ((l.x1 >= 0 && l.x1 < MAP_W - 1) && (l.y1 >= 0 && l.y1 < MAP_W - 1)) 
	{
		my_mlx_pixel_put(&game->map, l.x1, l.y1, MAP_PLAYER);
		my_mlx_pixel_put(&game->map, l.x1 + 1, l.y1 + 1, MAP_PLAYER);
		my_mlx_pixel_put(&game->map, l.x1, l.y1 + 1, MAP_PLAYER);
		my_mlx_pixel_put(&game->map, l.x1 + 1, l.y1, MAP_PLAYER);
		if (l.x1 == l.x2 && l.y1 == l.y2)
			break ;
		e2 = 2 * err;
		if (e2 > -l.dy) 
		{
			err -= l.dy;
			l.x1 += l.sx;
		}
		if (e2 < l.dx) 
		{
			err += l.dx;
			l.y1 += l.sy;
		}
	}
}

void	draw_square(t_game *game, t_square square)
{
	int				x;
	int				y;

	x = -1;
	while (++x < square.size - 1)
	{
		y = -1;
		while (++y < square.size - 1)
			if (in_minimap(x + square.x, y + square.y))
				my_mlx_pixel_put(&game->map, x + square.x, \
				y + square.y, square.color);
	}
}

void	fill_map_bg(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MAP_W)
	{
		j = -1;
		while (++j < MAP_W)
		{
			if (in_minimap(i, j))
				my_mlx_pixel_put(&game->map, i, j, MAP_BG);
			else
				my_mlx_pixel_put(&game->map, i, j, 0xFF000000);
		}
	}
}

void	fill_map(t_game *game, int px, int py)
{
	t_square	s;

	game->data->i = (px - MAP_C) - 1;
	while (++game->data->i < px + MAP_C)
	{
		game->data->j = py - MAP_C;
		while (game->data->j < py + MAP_C && game->data->j < game->data->height)
		{
			if (in_map(game, game->data->i, game->data->j))
			{
				if (game->data->map[game->data->j][game->data->i] == 'X')
					s.color = MAP_WALL;
				else if (game->data->map[game->data->j][game->data->i] == 'D')
					s.color = MAP_DOOR;
				else
					s.color = MAP_GROUND;
				s.size = square_size();
				s.x = (game->data->i - (px - MAP_C)) * square_size();
				s.y = (game->data->j - (py - MAP_C)) * square_size();
				draw_square(game, s);
			}
			game->data->j++;
		}
	}
}

void	render_minimap(t_game *game)
{
	int			px;
	int			py;
	t_square	s;
	t_line		l;
	t_mob		*current;

	px = ((int)game->player.px) >> 6;
	py = ((int)game->player.py) >> 6;
	fill_map_bg(game);
	fill_map(game, px, py);
	current = game->data->mob_list;
	while (current)
	{
		draw_entity(game, (((int)current->x) >> 6), \
		(((int)current->y) >> 6), MAP_MOB);
		current = current->next;
	}
	draw_entity(game, px, py, MAP_PLAYER);
	init_line(game, (px - (px - MAP_C)) * square_size(), \
	(py - (py - MAP_C)) * square_size(), square_size());
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, \
	game->map.image, WIDTH - MAP_W - SQUARE / 2, SQUARE / 2);
}
