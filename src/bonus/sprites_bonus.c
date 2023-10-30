/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:19:32 by dspilleb          #+#    #+#             */
/*   Updated: 2023/10/30 17:44:52 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	destroy_sprites3(t_game *game);
void	set_sprites_null2(t_game *game);

void	destroy_sprites(t_game *game)
{
	int	i;

	i = -1;
	while (++i <= 3)
	{
		if (game->sprites.wall[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.wall[i]);
		if (game->sprites.wall_i[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.wall_i[i]);
		if (game->sprites.wall_m[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.wall_m[i]);
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

	i = -1;
	while (++i <= 14)
	{
		if (game->sprites.abutor_a[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.abutor_a[i]);
		if (game->sprites.abutor_s[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.abutor_s[i]);
	}
	destroy_sprites3(game);
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
		game->sprites.wall_i[i] = NULL;
		game->sprites.wall_m[i] = NULL;
	}
	i = -1;
	while (++i <= 14)
	{
		game->sprites.abutor_a[i] = NULL;
		game->sprites.abutor_s[i] = NULL;
	}
	set_sprites_null2(game);
}

void	mob_put_img2(t_game *g)
{
	put_img(g, &g->sprites.abutor_s[1], "./Sprites/mobs/abutor/AS1.xpm");
	put_img(g, &g->sprites.abutor_s[0], "./Sprites/mobs/abutor/AS0.xpm");
	put_img(g, &g->sprites.abutor_s[2], "./Sprites/mobs/abutor/AS2.xpm");
	put_img(g, &g->sprites.abutor_s[3], "./Sprites/mobs/abutor/AS3.xpm");
	put_img(g, &g->sprites.abutor_s[4], "./Sprites/mobs/abutor/AS4.xpm");
	put_img(g, &g->sprites.abutor_s[5], "./Sprites/mobs/abutor/AS5.xpm");
	put_img(g, &g->sprites.abutor_s[6], "./Sprites/mobs/abutor/AS6.xpm");
	put_img(g, &g->sprites.abutor_s[7], "./Sprites/mobs/abutor/AS7.xpm");
	put_img(g, &g->sprites.abutor_s[8], "./Sprites/mobs/abutor/AS8.xpm");
	put_img(g, &g->sprites.abutor_s[9], "./Sprites/mobs/abutor/AS9.xpm");
	put_img(g, &g->sprites.abutor_s[10], "./Sprites/mobs/abutor/AS10.xpm");
	put_img(g, &g->sprites.abutor_s[11], "./Sprites/mobs/abutor/AS11.xpm");
	put_img(g, &g->sprites.abutor_s[12], "./Sprites/mobs/abutor/AS12.xpm");
	put_img(g, &g->sprites.abutor_s[13], "./Sprites/mobs/abutor/AS13.xpm");
	put_img(g, &g->sprites.abutor_s[14], "./Sprites/mobs/abutor/AS14.xpm");
	mob_put_img3(g);
}

void	mob_put_img3(t_game *game)
{
	put_img(game, &game->sprites.chubb_w[0], "./Sprites/mobs/chubbs/C0.xpm");
	put_img(game, &game->sprites.chubb_w[1], "./Sprites/mobs/chubbs/C1.xpm");
	put_img(game, &game->sprites.chubb_w[2], "./Sprites/mobs/chubbs/C2.xpm");
	put_img(game, &game->sprites.chubb_w[3], "./Sprites/mobs/chubbs/C3.xpm");
	put_img(game, &game->sprites.egg[0], "./Sprites/mobs/egg/egg0.xpm");
	put_img(game, &game->sprites.egg[1], "./Sprites/mobs/egg/egg1.xpm");
	put_img(game, &game->sprites.egg[2], "./Sprites/mobs/egg/egg0.xpm");
	put_img(game, &game->sprites.egg[3], "./Sprites/mobs/egg/egg1.xpm");
	put_img(game, &game->sprites.egg_e[0], "./Sprites/mobs/egg/egg2.xpm");
	put_img(game, &game->sprites.egg_e[1], "./Sprites/mobs/egg/egg3.xpm");
	put_img(game, &game->sprites.egg_e[2], "./Sprites/mobs/egg/egg4.xpm");
	put_img(game, &game->sprites.egg_e[3], "./Sprites/mobs/egg/egg5.xpm");
}
