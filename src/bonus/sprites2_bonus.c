/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:31:45 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/30 10:28:15 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	sprites_addr(t_game *game)
{
	if (init_addr_array(game->sprites.abutor_w, 4))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.egg_e, 4) || \
	init_addr_array(game->sprites.egg, 4))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.chubb_w, 4))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.abutor_a, 15) || \
	init_addr_array(game->sprites.abutor_s, 15))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.wall, 4) || \
	init_addr_array(game->sprites.wall_i, 4) || \
	init_addr_array(game->sprites.wall_m, 4))
		return (destroy_sprites(game), 1);
	if (init_addr_array(game->sprites.heal0, 2) || \
	init_addr_array(game->sprites.heal1, 2) || \
	init_addr_array(game->sprites.heal2, 2) || \
	init_addr_array((t_img *[]){game->sprites.red_b, \
	game->sprites.green_b}, 2))
		return (destroy_sprites(game), 1);
	if (!game->crosshair || !game->sprites.gun[0] || \
	!game->sprites.gun[1] || !game->sprites.gun[2] || !game->sprites.gun[3] \
	|| !game->sprites.win)
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
	game->sprites.wall_i[0] = put_img(game, "./Sprites/walls/wallR0.xpm");
	game->sprites.wall_i[1] = put_img(game, "./Sprites/walls/wallR1.xpm");
	game->sprites.wall_i[2] = put_img(game, "./Sprites/walls/wallR2.xpm");
	game->sprites.wall_i[3] = put_img(game, "./Sprites/walls/wallR1.xpm");
	game->sprites.wall_m[0] = put_img(game, "./Sprites/walls/wallM0.1.xpm");
	game->sprites.wall_m[1] = put_img(game, "./Sprites/walls/wallM0.2.xpm");
	game->sprites.wall_m[2] = put_img(game, "./Sprites/walls/wallM0.3.xpm");
	game->sprites.wall_m[3] = put_img(game, "./Sprites/walls/wallM0.4.xpm");
	game->crosshair = put_img(game, "./Sprites/crosshair.xpm");
	mob_put_img(game);
	hud_out_img(game);
	return (sprites_addr(game));
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
	game->sprites.red_b = put_img(game, "./Sprites/heal_bar/red_bar.xpm");
	game->sprites.green_b = put_img(game, "./Sprites/heal_bar/green_bar.xpm");
}
