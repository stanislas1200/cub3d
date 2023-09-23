/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:59:57 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/23 16:59:41 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	movement(int key, t_game *game)
{
	if (key == Z)
	{
		printf(RED "%f %f\n", game->player.px, game->player.pdx);
		game->player.px += game->player.pdx;
		game->player.py += game->player.pdy;
	}
	if (key == S)
	{
		printf(RED "%f %f\n", game->player.px, game->player.pdx);
		game->player.px -= game->player.pdx;
		game->player.py -= game->player.pdy;
	}
	if (key == Q)
	{
		game->player.pa -= 5;
		fix_ang(game->player.pa);
		game->player.pdx = cos(deg_to_rad(game->player.pa)) * 5;
		game->player.pdy = -sin(deg_to_rad(game->player.pa)) * 5;
	}
	if (key == D)
	{
		game->player.pa += 5;
		fix_ang(game->player.pa);
		game->player.pdx = cos(deg_to_rad(game->player.pa)) * 5;
		game->player.pdy = -sin(deg_to_rad(game->player.pa)) * 5;
	}
}

int	can_move(int key, t_game *game)
{
	int	mx;
	int	my;

	if (key == Z)
	{
		my = ((int)(game->player.px + game->player.pdx)) >> 6;
		mx = ((int)(game->player.py + game->player.pdy)) >> 6;
	}
	else if (key == S)
	{
		my = ((int)(game->player.px - game->player.pdx)) >> 6;
		mx = ((int)(game->player.py - game->player.pdy)) >> 6;
	}
	else
		return (1);
	return ((my >=0 && mx >=0) && my < game->data->height && mx < ft_strlen(game->data->map[my]) && game->data->map[my][mx] != 'X');
}

int	key_hook(int key, t_game *game)
{
	printf(YELLOW "%f %f \n", game->data->player.px,  game->data->player.py);
	if (can_move(key, game))
		movement(key, game);
	draw_rays(game);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img.image, 0, 0);
	return (0);
}
