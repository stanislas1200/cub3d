/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:11:38 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/29 18:56:12 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player2(t_data *data, t_game *game);

void	init_data(t_data *data)
{
	data->height = 0;
	data->player_nb = 0;
	data->map = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->floor[0] = -1;
	data->floor[1] = -1;
	data->floor[2] = -1;
	data->ceiling[0] = -1;
	data->ceiling[1] = -1;
	data->ceiling[2] = -1;
	data->time = 0;
	data->g_time = 0;
	data->biggest_w = 0;
	data->a->open = NULL;
	data->a->closed = NULL;
	data->a->path = NULL;
	data->a->nodes = NULL;
	data->mob_list = NULL;
}

void	init_player(t_data *data, t_game *game)
{
	if (data->player.dir == 'S')
		data->player.pa = 270.0;
	else if (data->player.dir == 'W')
		data->player.pa = 180.0;
	else if (data->player.dir == 'E')
		data->player.pa = 0.0;
	else if (data->player.dir == 'N')
		data->player.pa = 90.0;
	data->player.px *= SQUARE;
	data->player.py *= SQUARE;
	data->player.pdx = cos(deg_to_rad(data->player.pa)) * 5;
	data->player.pdy = -sin(deg_to_rad(data->player.pa)) * 5;
	data->player.speed = 0.5;
	game->old_x = WIDTH / 2;
	game->keys[0] = 0;
	game->keys[1] = 0;
	game->keys[2] = 0;
	game->keys[3] = 0;
	game->keys[4] = 0;
	game->keys[5] = 0;
	init_player2(data, game);
}

void	init_player2(t_data *data, t_game *game)
{
	data->player.px += (SQUARE / 2);
	data->player.py += (SQUARE / 2);
	data->player.max_hp = 10;
	data->player.hp = data->player.max_hp;
	data->player.trip = 0;
	data->player.hurt = 0;
	data->player.hurt_cd = 0;
	data->player.trip_cd = 0;
	data->fired = 0;
	game->player = data->player;
	game->data = data;
	game->status = 0;
	data->fade_cd = 0.5;
}

int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (1);
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx_win)
		return (1);
	game->img.image = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->img.image)
		return (1);
	game->img.addr = mlx_get_data_addr(game->img.image, \
	&game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		return (1);
	game->map.image = mlx_new_image(game->mlx_ptr, MAP_W, MAP_W);
	if (!game->map.image)
		return (1);
	game->map.addr = mlx_get_data_addr(game->map.image, \
	&game->map.bits_per_pixel, &game->map.line_length, &game->map.endian);
	if (!game->map.addr)
		return (1);
	return (0);
}
