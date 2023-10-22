/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:11:38 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/22 14:58:34 by dspilleb         ###   ########.fr       */
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
}

int	init_sprites(t_game *game)
{
	int		i;

	i = -1;
	while (++i <= 3)
	{
		game->sprites.wall[i] = NULL;
		// game->sprites.wallI[i] = NULL;
		// game->sprites.wallM[i] = NULL;
		game->sprites.gun[i] = NULL;
	}
	game->sprites.gun[0] = put_img(game, "./Sprites/gun/0.xpm");
	game->sprites.gun[1] = put_img(game, "./Sprites/gun/1.xpm");
	game->sprites.gun[2] = put_img(game, "./Sprites/gun/2.xpm");
	game->sprites.gun[3] = put_img(game, "./Sprites/gun/3.xpm");
	game->sprites.wall[NO] = put_img(game, game->data->no);
	game->sprites.wall[SO] = put_img(game, game->data->so);
	game->sprites.wall[WE] = put_img(game, game->data->we);
	game->sprites.wall[EA] = put_img(game, game->data->ea);
	game->mob = put_img(game, "./Sprites/barrel.xpm");
	// game->sprites.wallI[0] = put_img(game, "./Sprites/walls/wallR0.xpm");
	// game->sprites.wallI[1] = put_img(game, "./Sprites/walls/wallR1.xpm");
	// game->sprites.wallI[2] = put_img(game, "./Sprites/walls/wallR2.xpm");
	// game->sprites.wallI[3] = put_img(game, "./Sprites/walls/wallR1.xpm");
	// game->sprites.wallM[0] = put_img(game, "./Sprites/walls/wallM0.1.xpm");
	// game->sprites.wallM[1] = put_img(game, "./Sprites/walls/wallM0.1.xpm");
	// game->sprites.wallM[2] = put_img(game, "./Sprites/walls/wallM0.1.xpm");
	// game->sprites.wallM[3] = put_img(game, "./Sprites/walls/wallM0.1.xpm");
	if (!game->sprites.wall[NO] || !game->sprites.wall[SO] \
	|| !game->sprites.wall[WE] || !game->sprites.wall[EA] \
	|| !game->sprites.gun[0])
		return (destroy_sprites(game), 1); // need check other
	i = -1;
	while (++i <= 3)
		game->sprites.wall[i]->addr = mlx_get_data_addr(game->sprites.wall[i], \
&game->sprites.wall[i]->bits_per_pixel, &game->sprites.wall[i]->line_length, \
&game->sprites.wall[i]->endian);
		game->mob->addr = mlx_get_data_addr(game->mob, \
&game->mob->bits_per_pixel, &game->mob->line_length, \
&game->mob->endian);
// i = -1;
// 	while (++i <= 3)
// 		game->sprites.wallI[i]->addr = mlx_get_data_addr(game->sprites.wallI[i], \
// &game->sprites.wallI[i]->bits_per_pixel, &game->sprites.wallI[i]->line_length, \
// &game->sprites.wallI[i]->endian);
// i = -1;
// 	while (++i <= 3)
// 		game->sprites.wallM[i]->addr = mlx_get_data_addr(game->sprites.wallM[i], \
// &game->sprites.wallM[i]->bits_per_pixel, &game->sprites.wallM[i]->line_length, \
// &game->sprites.wallM[i]->endian);
	if (!(game->sprites.wall[NO]->addr || game->sprites.wall[SO]->addr \
	|| game->sprites.wall[WE]->addr || game->sprites.wall[EA]->addr))
		return (destroy_sprites(game), 1);
	return (0);
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
	game->player = data->player;
	game->data = data;
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
