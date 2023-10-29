/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:19:32 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/29 16:16:33 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy_sprites(t_game *game)
{
	int	i;

	i = -1;
	while (++i <= 3)
	{
		if (game->sprites.wall[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.wall[i]);
		if (game->sprites.wallI[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.wallI[i]);
		if (game->sprites.wallM[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.wallM[i]);
		if (game->sprites.abutor_w[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.abutor_w[i]);
		if (game->sprites.chubb_w[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.chubb_w[i]);
		if (game->sprites.egg[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.egg[i]);
		if (game->sprites.egg_e[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.egg_e[i]);
		if (game->sprites.gun[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.gun[i]);
	}
	destroy_sprites2(game);
}

void	destroy_sprites2(t_game *game)
{
	int	i;

	if (game->crosshair)
		mlx_destroy_image(game->mlx_ptr, game->crosshair);
	i = -1;
	while (++i <= 14)
	{
		if (game->sprites.abutor_a[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.abutor_a[i]);
		if (game->sprites.abutor_s[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.abutor_s[i]);
	}
}

void	set_sprites_null(t_game *game)
{
	int	i;

	i = -1;
	while (++i <= 3)
	{
		game->sprites.wall[i] = NULL;
		game->sprites.abutor_w[i] = NULL;
		game->sprites.chubb_w[i] = NULL;
		game->sprites.egg[i] = NULL;
		game->sprites.egg_e[i] = NULL;
		game->sprites.gun[i] = NULL;
		game->sprites.wallI[i] = NULL;
		game->sprites.wallM[i] = NULL;
	}
	i = -1;
	while (++i <= 14)
	{
		game->sprites.abutor_a[i] = NULL;
		game->sprites.abutor_s[i] = NULL;
	}
	game->crosshair = NULL;
	game->mob = NULL;
}

void	mob_put_img2(t_game *g)
{
	g->sprites.abutor_s[0] = put_img(g, "./Sprites/mobs/abutor/AS0.xpm");
	g->sprites.abutor_s[1] = put_img(g, "./Sprites/mobs/abutor/AS1.xpm");
	g->sprites.abutor_s[2] = put_img(g, "./Sprites/mobs/abutor/AS2.xpm");
	g->sprites.abutor_s[3] = put_img(g, "./Sprites/mobs/abutor/AS3.xpm");
	g->sprites.abutor_s[4] = put_img(g, "./Sprites/mobs/abutor/AS4.xpm");
	g->sprites.abutor_s[5] = put_img(g, "./Sprites/mobs/abutor/AS5.xpm");
	g->sprites.abutor_s[6] = put_img(g, "./Sprites/mobs/abutor/AS6.xpm");
	g->sprites.abutor_s[7] = put_img(g, "./Sprites/mobs/abutor/AS7.xpm");
	g->sprites.abutor_s[8] = put_img(g, "./Sprites/mobs/abutor/AS8.xpm");
	g->sprites.abutor_s[9] = put_img(g, "./Sprites/mobs/abutor/AS9.xpm");
	g->sprites.abutor_s[10] = put_img(g, "./Sprites/mobs/abutor/AS10.xpm");
	g->sprites.abutor_s[11] = put_img(g, "./Sprites/mobs/abutor/AS11.xpm");
	g->sprites.abutor_s[12] = put_img(g, "./Sprites/mobs/abutor/AS12.xpm");
	g->sprites.abutor_s[13] = put_img(g, "./Sprites/mobs/abutor/AS13.xpm");
	g->sprites.abutor_s[14] = put_img(g, "./Sprites/mobs/abutor/AS14.xpm");
	mob_put_img3(g);
}

void	mob_put_img3(t_game *game)
{
	game->sprites.chubb_w[0] = put_img(game, "./Sprites/mobs/chubbs/C0.xpm");
	game->sprites.chubb_w[1] = put_img(game, "./Sprites/mobs/chubbs/C1.xpm");
	game->sprites.chubb_w[2] = put_img(game, "./Sprites/mobs/chubbs/C2.xpm");
	game->sprites.chubb_w[3] = put_img(game, "./Sprites/mobs/chubbs/C3.xpm");
	game->sprites.egg[0] = put_img(game, "./Sprites/mobs/egg/egg0.xpm");
	game->sprites.egg[1] = put_img(game, "./Sprites/mobs/egg/egg1.xpm");
	game->sprites.egg[2] = put_img(game, "./Sprites/mobs/egg/egg0.xpm");
	game->sprites.egg[3] = put_img(game, "./Sprites/mobs/egg/egg1.xpm");
	game->sprites.egg_e[0] = put_img(game, "./Sprites/mobs/egg/egg2.xpm");
	game->sprites.egg_e[1] = put_img(game, "./Sprites/mobs/egg/egg3.xpm");
	game->sprites.egg_e[2] = put_img(game, "./Sprites/mobs/egg/egg4.xpm");
	game->sprites.egg_e[3] = put_img(game, "./Sprites/mobs/egg/egg5.xpm");
}

int	sprites_addr(t_game *game)
{
	if (init_addr_array(game->sprites.abutor_w, 4))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.egg_e, 4))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.egg, 4))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.chubb_w, 4))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.abutor_a, 15))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.abutor_s, 15))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.wall, 4))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.wallI, 4))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.wallM, 4))
		return (destroy_sprites(game), 1);
	if (!game->crosshair || !game->sprites.gun[0] || \
	!game->sprites.gun[1] || !game->sprites.gun[2] || !game->sprites.gun[3])
		return (1);
	return (0);
}

int	init_addr_array(t_img **arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (!arr[i])
			return (1);
		arr[i]->addr = mlx_get_data_addr(arr[i], \
&arr[i]->bits_per_pixel, &arr[i]->line_length, \
&arr[i]->endian);
		if (!arr[i]->addr)
			return (1);
	}
	return (0);
}
