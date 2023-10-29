/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:11:38 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/29 16:45:32 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	hud_out_img(t_game *game)
{
	game->sprites.heal0[0] = put_img(game, "./Sprites/heal_bar/heall00.xpm");
	game->sprites.heal1[0] = put_img(game, "./Sprites/heal_bar/heall10.xpm");
	game->sprites.heal2[0] = put_img(game, "./Sprites/heal_bar/heall20.xpm");
	game->sprites.heal0[1] = put_img(game, "./Sprites/heal_bar/heall01.xpm");
	game->sprites.heal1[1] = put_img(game, "./Sprites/heal_bar/heall11.xpm");
	game->sprites.heal2[1] = put_img(game, "./Sprites/heal_bar/heall21.xpm");
	game->sprites.win = put_img(game, "./Sprites/screen/victory_c.xpm");
	game->sprites.loss = put_img(game, "./Sprites/screen/game_over_c.xpm");
}

void	mob_put_img(t_game *game)
{
	game->sprites.abutor_w[0] = put_img(game, "./Sprites/mobs/abutor/AW0.xpm");
	game->sprites.abutor_w[1] = put_img(game, "./Sprites/mobs/abutor/AW1.xpm");
	game->sprites.abutor_w[2] = put_img(game, "./Sprites/mobs/abutor/AW1.xpm");
	game->sprites.abutor_w[3] = put_img(game, "./Sprites/mobs/abutor/AW1.xpm");
	game->sprites.abutor_a[0] = put_img(game, "./Sprites/mobs/abutor/A0.xpm");
	game->sprites.abutor_a[1] = put_img(game, "./Sprites/mobs/abutor/A1.xpm");
	game->sprites.abutor_a[2] = put_img(game, "./Sprites/mobs/abutor/A2.xpm");
	game->sprites.abutor_a[3] = put_img(game, "./Sprites/mobs/abutor/A3.xpm");
	game->sprites.abutor_a[4] = put_img(game, "./Sprites/mobs/abutor/A4.xpm");
	game->sprites.abutor_a[5] = put_img(game, "./Sprites/mobs/abutor/A5.xpm");
	game->sprites.abutor_a[6] = put_img(game, "./Sprites/mobs/abutor/A6.xpm");
	game->sprites.abutor_a[7] = put_img(game, "./Sprites/mobs/abutor/A7.xpm");
	game->sprites.abutor_a[8] = put_img(game, "./Sprites/mobs/abutor/A8.xpm");
	game->sprites.abutor_a[9] = put_img(game, "./Sprites/mobs/abutor/A9.xpm");
	game->sprites.abutor_a[10] = put_img(game, "./Sprites/mobs/abutor/A10.xpm");
	game->sprites.abutor_a[11] = put_img(game, "./Sprites/mobs/abutor/A11.xpm");
	game->sprites.abutor_a[12] = put_img(game, "./Sprites/mobs/abutor/A12.xpm");
	game->sprites.abutor_a[13] = put_img(game, "./Sprites/mobs/abutor/A13.xpm");
	game->sprites.abutor_a[14] = put_img(game, "./Sprites/mobs/abutor/A14.xpm");
	mob_put_img2(game);
}

int	init_sprites(t_game *game)
{
	int		i;

	i = -1;
	set_sprites_null(game);
	game->sprites.gun[0] = put_img(game, "./Sprites/gun/0.xpm");
	game->sprites.gun[1] = put_img(game, "./Sprites/gun/1.xpm");
	game->sprites.gun[2] = put_img(game, "./Sprites/gun/2.xpm");
	game->sprites.gun[3] = put_img(game, "./Sprites/gun/3.xpm");
	game->sprites.wall[NO] = put_img(game, game->data->no);
	game->sprites.wall[SO] = put_img(game, game->data->so);
	game->sprites.wall[WE] = put_img(game, game->data->we);
	game->sprites.wall[EA] = put_img(game, game->data->ea);
	game->sprites.wallI[0] = put_img(game, "./Sprites/walls/wallR0.xpm");
	game->sprites.wallI[1] = put_img(game, "./Sprites/walls/wallR1.xpm");
	game->sprites.wallI[2] = put_img(game, "./Sprites/walls/wallR2.xpm");
	game->sprites.wallI[3] = put_img(game, "./Sprites/walls/wallR1.xpm");
	game->sprites.wallM[0] = put_img(game, "./Sprites/walls/wallM0.1.xpm");
	game->sprites.wallM[1] = put_img(game, "./Sprites/walls/wallM0.2.xpm");
	game->sprites.wallM[2] = put_img(game, "./Sprites/walls/wallM0.3.xpm");
	game->sprites.wallM[3] = put_img(game, "./Sprites/walls/wallM0.4.xpm");
	game->crosshair = put_img(game, "./Sprites/crosshair.xpm");
	mob_put_img(game);
	hud_out_img(game);
	return (sprites_addr(game));
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
	data->player.speed = 1.5;
	game->old_x = WIDTH / 2;
	game->keys[0] = 0;
	game->keys[1] = 0;
	game->keys[2] = 0;
	game->keys[3] = 0;
	game->keys[4] = 0;
	game->keys[5] = 0;
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
