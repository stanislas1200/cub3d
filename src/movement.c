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

void	movement(int key, t_game *game)
{
	if (key == Z)
	{
		game->player.px += game->player.pdx * game->player.speed;
		game->player.py += game->player.pdy * game->player.speed;
	}
	if (key == S)
	{
		game->player.px -= game->player.pdx * game->player.speed;
		game->player.py -= game->player.pdy * game->player.speed;
	}
	if (key == Q)
	{
		game->player.pa -= 5.0 * game->player.speed / 2;
		game->player.pa = fix_ang(game->player.pa);
		game->player.pdx = cos(deg_to_rad(game->player.pa)) * 5.0;
		game->player.pdy = -sin(deg_to_rad(game->player.pa)) * 5.0;
	}
	if (key == D)
	{
		game->player.pa += 5.0 * game->player.speed / 2;
		game->player.pa = fix_ang(game->player.pa);
		game->player.pdx = cos(deg_to_rad(game->player.pa)) * 5.0;
		game->player.pdy = -sin(deg_to_rad(game->player.pa)) * 5.0;
	}
}

int	can_move(int key, t_game *game)
{
	int	mx;
	int	my;

	if (key == Z)
	{
		mx = ((int)(game->player.px + game->player.pdx  * game->player.speed)) >> 6;
		my = ((int)(game->player.py + game->player.pdy * 6)) >> 6;
	}
	else if (key == S)
	{
		mx = ((int)(game->player.px - game->player.pdx  * game->player.speed)) >> 6;
		my = ((int)(game->player.py - game->player.pdy  * game->player.speed)) >> 6;
	}
	else if (key == Q)
	{
		mx = ((int)(game->player.px - game->player.pdy  * game->player.speed)) >> 6;
		my = ((int)(game->player.py + game->player.pdx  * game->player.speed)) >> 6;
	}
	else if (key == D)
	{
		mx = ((int)(game->player.px + game->player.pdy  * game->player.speed)) >> 6;
		my = ((int)(game->player.py - game->player.pdx  * game->player.speed)) >> 6;
	}
	else
		return (1);
	return ((my >=0 && mx >=0) && my < game->data->height && mx < ft_strlen(game->data->map[my]) && game->data->map[my][mx] != 'X');
}

int	key_hook(int key, t_game *game)
{
	if (can_move(key, game))
	{
		movement(key, game);
		update_frame(game);
		// draw_rays(game);
		// mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img.image, 0, 0);
	}
	if (key == ESC)
		end_game(game);
	return (0);
}
