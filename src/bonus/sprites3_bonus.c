/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:00:25 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 13:01:17 by sgodin           ###   ########.fr       */
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
