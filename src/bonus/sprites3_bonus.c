/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:00:25 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 17:40:46 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	hud_out_img(t_game *game)
{
	put_img(game, &game->sprites.heal0[0], "./Sprites/heal_bar/heall00.xpm");
	put_img(game, &game->sprites.heal1[0], "./Sprites/heal_bar/heall10.xpm");
	put_img(game, &game->sprites.heal2[0], "./Sprites/heal_bar/heall20.xpm");
	put_img(game, &game->sprites.heal0[1], "./Sprites/heal_bar/heall01.xpm");
	put_img(game, &game->sprites.heal1[1], "./Sprites/heal_bar/heall11.xpm");
	put_img(game, &game->sprites.heal2[1], "./Sprites/heal_bar/heall21.xpm");
	put_img(game, &game->sprites.win, "./Sprites/screen/victory_c.xpm");
	put_img(game, &game->sprites.loss, "./Sprites/screen/game_over_c.xpm");
	put_img(game, &game->sprites.red_b, "./Sprites/heal_bar/red_bar.xpm");
	put_img(game, &game->sprites.green_b, "./Sprites/heal_bar/green_bar.xpm");
}

void	destroy_sprites3(t_game *game)
{
	int	i;

	if (game->crosshair)
		mlx_destroy_image(game->mlx_ptr, game->crosshair);
	if (game->sprites.win)
		mlx_destroy_image(game->mlx_ptr, game->sprites.win);
	if (game->sprites.loss)
		mlx_destroy_image(game->mlx_ptr, game->sprites.loss);
	if (game->sprites.green_b)
		mlx_destroy_image(game->mlx_ptr, game->sprites.green_b);
	if (game->sprites.red_b)
		mlx_destroy_image(game->mlx_ptr, game->sprites.red_b);
	i = -1;
	while (++i <= 1)
	{
		if (game->sprites.heal0[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.heal0[i]);
		if (game->sprites.heal1[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.heal1[i]);
		if (game->sprites.heal2[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.heal2[i]);
	}
}

void	set_sprites_null2(t_game *game)
{
	int	i;

	i = -1;
	while (++i <= 1)
	{
		game->sprites.heal0[i] = NULL;
		game->sprites.heal1[i] = NULL;
		game->sprites.heal2[i] = NULL;
	}
	game->crosshair = NULL;
	game->mob = NULL;
	game->sprites.win = NULL;
	game->sprites.loss = NULL;
	game->sprites.green_b = NULL;
	game->sprites.red_b = NULL;
}
