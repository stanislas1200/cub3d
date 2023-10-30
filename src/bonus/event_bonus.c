/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:17:49 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 10:28:15 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	*embient_sound(void *nop);

int	event_hook(int x, int y, t_game *game)
{
	game->player.pa -= (x - game->old_x);
	game->player.pa = fix_ang(game->player.pa);
	game->player.pdx = cos(deg_to_rad(game->player.pa)) * 5.0;
	game->player.pdy = -sin(deg_to_rad(game->player.pa)) * 5.0;
	game->old_x = x;
	return (0);
}

int	gun_fire(int button, int x, int y, t_game *game)
{
	if (game->data->g_time > 1)
		return (0);
	game->data->g_time = 1;
	play_sound("data/sound/gun.wav", game);
	game->data->fired = 1;
	return (0);
}

int	key_pressed(int key, t_game *game)
{
	game->data->player.speed = 0.5;
	game->data->fade_cd = 0.5;
	if (key == SPACE)
		gun_fire(0, 0, 0, game);
	if (key == Z)
		game->keys[0] = 1;
	if (key == S)
		game->keys[1] = 1;
	if (key == A_E)
		game->keys[2] = 1;
	if (key == A_W)
		game->keys[3] = 1;
	if (key == Q)
		game->keys[4] = 1;
	if (key == D)
		game->keys[5] = 1;
	if (key == ESC)
		end_game(game);
	return (0);
}

int	key_released(int key, t_game *game)
{
	if (key == Z)
		game->keys[0] = 0;
	if (key == S)
		game->keys[1] = 0;
	if (key == A_E)
		game->keys[2] = 0;
	if (key == A_W)
		game->keys[3] = 0;
	if (key == Q)
		game->keys[4] = 0;
	if (key == D)
		game->keys[5] = 0;
	return (0);
}

void	set_event(t_game *game)
{
	mlx_hook(game->mlx_win, 2, 1L << 0, key_pressed, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, key_released, game);
	mlx_hook(game->mlx_win, 6, 1L << 0, event_hook, game);
	mlx_hook(game->mlx_win, 4, 1L << 0, gun_fire, game);
	mlx_loop_hook(game->mlx_ptr, update_frame, game);
	mlx_hook(game->mlx_win, 17, 1L << 2, end_game, game);
	if (pthread_create(&game->t_id, NULL, embient_sound, NULL))
		return (e(game->data, "Thread: " RESET, "creation faill\n"));
	mlx_loop(game->mlx_ptr);
}
