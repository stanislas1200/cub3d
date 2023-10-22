/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:32:10 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/22 13:24:39 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	in_minimap(double x1, double y1)
{
	return (distance(x1, y1, MAP_CENTER, MAP_CENTER) <= MAP_CENTER);
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
				my_mlx_pixel_put(&game->map, i, j, 0x001a42);
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
			if (game->data->i >= 0 && game->data->j >= 0 && \
			game->data->i < ft_strlen(game->data->map[game->data->j]))
			{
				if (game->data->map[game->data->j][game->data->i] == 'X')
					s.color = MAP_WALL;
				else
					s.color = MAP_GROUND;
				s.size = map_size;
				s.x = (game->data->i - (px - MAP_C)) * map_size;
				s.y = (game->data->j - (py - MAP_C)) * map_size;
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

	px = ((int)game->player.px) >> 6;
	py = ((int)game->player.py) >> 6;
	fill_map_bg(game);
	fill_map(game, px, py);
	s.color = MAP_PLAYER;
	s.size = map_size;
	s.x = (px - (px - MAP_C)) * map_size;
	s.y = (py - (py - MAP_C)) * map_size;
	draw_square(game, s);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, \
	game->map.image, WIDTH - MAP_W, HEIGHT - MAP_W);
}
