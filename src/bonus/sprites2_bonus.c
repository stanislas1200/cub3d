/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:31:45 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/30 12:38:05 by dspilleb         ###   ########.fr       */
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
	if (init_addr_array((t_img *[]){game->crosshair}, 1) || \
	init_addr_array(game->sprites.gun, 4) 
	|| init_addr_array((t_img *[]){game->sprites.win, \
	game->sprites.loss}, 2))
		return (destroy_sprites(game), 1);
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
	put_img(game, &game->sprites.abutor_w[0], "./Sprites/mobs/abutor/AW0.xpm");
	put_img(game, &game->sprites.abutor_w[1], "./Sprites/mobs/abutor/AW1.xpm");
	put_img(game, &game->sprites.abutor_w[2], "./Sprites/mobs/abutor/AW1.xpm");
	put_img(game, &game->sprites.abutor_w[3], "./Sprites/mobs/abutor/AW1.xpm");
	put_img(game, &game->sprites.abutor_a[0], "./Sprites/mobs/abutor/A0.xpm");
	put_img(game, &game->sprites.abutor_a[1], "./Sprites/mobs/abutor/A1.xpm");
	put_img(game, &game->sprites.abutor_a[2], "./Sprites/mobs/abutor/A2.xpm");
	put_img(game, &game->sprites.abutor_a[3], "./Sprites/mobs/abutor/A3.xpm");
	put_img(game, &game->sprites.abutor_a[4], "./Sprites/mobs/abutor/A4.xpm");
	put_img(game, &game->sprites.abutor_a[5], "./Sprites/mobs/abutor/A5.xpm");
	put_img(game, &game->sprites.abutor_a[6], "./Sprites/mobs/abutor/A6.xpm");
	put_img(game, &game->sprites.abutor_a[7], "./Sprites/mobs/abutor/A7.xpm");
	put_img(game, &game->sprites.abutor_a[8], "./Sprites/mobs/abutor/A8.xpm");
	put_img(game, &game->sprites.abutor_a[9], "./Sprites/mobs/abutor/A9.xpm");
	put_img(game, &game->sprites.abutor_a[10], "./Sprites/mobs/abutor/A10.xpm");
	put_img(game, &game->sprites.abutor_a[11], "./Sprites/mobs/abutor/A11.xpm");
	put_img(game, &game->sprites.abutor_a[12], "./Sprites/mobs/abutor/A12.xpm");
	put_img(game, &game->sprites.abutor_a[13], "./Sprites/mobs/abutor/A13.xpm");
	put_img(game, &game->sprites.abutor_a[14], "./Sprites/mobs/abutor/A14.xpm");
	mob_put_img2(game);
}

int	init_sprites(t_game *game)
{
	int		i;

	i = -1;
	set_sprites_null(game);
	put_img(game, &game->sprites.gun[0], "./Sprites/gun/0.xpm");
	put_img(game, &game->sprites.gun[1], "./Sprites/gun/1.xpm");
	put_img(game, &game->sprites.gun[2], "./Sprites/gun/2.xpm");
	put_img(game, &game->sprites.gun[3], "./Sprites/gun/3.xpm");
	put_img(game, &game->sprites.wall[NO], game->data->no);
	put_img(game, &game->sprites.wall[SO], game->data->so);
	put_img(game, &game->sprites.wall[WE], game->data->we);
	put_img(game, &game->sprites.wall[EA], game->data->ea);
	put_img(game, &game->sprites.wall_i[0], "./Sprites/walls/wallR0.xpm");
	put_img(game, &game->sprites.wall_i[1], "./Sprites/walls/wallR1.xpm");
	put_img(game, &game->sprites.wall_i[2], "./Sprites/walls/wallR2.xpm");
	put_img(game, &game->sprites.wall_i[3], "./Sprites/walls/wallR1.xpm");
	put_img(game, &game->sprites.wall_m[0], "./Sprites/walls/wallM0.1.xpm");
	put_img(game, &game->sprites.wall_m[1], "./Sprites/walls/wallM0.2.xpm");
	put_img(game, &game->sprites.wall_m[2], "./Sprites/walls/wallM0.3.xpm");
	put_img(game, &game->sprites.wall_m[3], "./Sprites/walls/wallM0.4.xpm");
	put_img(game, &game->crosshair, "./Sprites/crosshair.xpm");
	mob_put_img(game);
	hud_out_img(game);
	return (sprites_addr(game));
}

void	hud_out_img(t_game *game)
{
	put_img(game, &game->sprites.heal0[0],  "./Sprites/heal_bar/heall00.xpm");
	put_img(game, &game->sprites.heal1[0],  "./Sprites/heal_bar/heall10.xpm");
	put_img(game, &game->sprites.heal2[0],  "./Sprites/heal_bar/heall20.xpm");
	put_img(game, &game->sprites.heal0[1],  "./Sprites/heal_bar/heall01.xpm");
	put_img(game, &game->sprites.heal1[1],  "./Sprites/heal_bar/heall11.xpm");
	put_img(game, &game->sprites.heal2[1],  "./Sprites/heal_bar/heall21.xpm");
	put_img(game, &game->sprites.win,  "./Sprites/screen/victory_c.xpm");
	put_img(game, &game->sprites.loss,  "./Sprites/screen/game_over_c.xpm");
	put_img(game, &game->sprites.red_b,  "./Sprites/heal_bar/red_bar.xpm");
	put_img(game, &game->sprites.green_b,  "./Sprites/heal_bar/green_bar.xpm");
}
