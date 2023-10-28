/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abutor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:38:49 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/28 17:57:32 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	execute_abutor(t_game *game, t_mob *this)
{
	game->mob = game->sprites.abutor_w[this->frame / 4 % 2];
	if (this->hp <= 0 || this->state == DEAD)
	{
     this->state = DEAD; // temp dev need remove from arr
		play_sound("data/sound/dying.mp3", game);
		return ;
	}
	if (this->state == FOLLOW)
	{
		this->state = IDLE;
		Astar(game->data, game->data->a, ((int)this->x >> 6) , ((int)this->y >> 6), ((int)game->player.px >> 6) , ((int)game->player.py >> 6));
		game->data->i = 0;
		if (game->data->a->pathCount < 2 || !game->data->a->path || !game->data->a->path[0])
			return (free_list(game->data->a->path, game->data->a->pathCount));
		this->speed = 10;
		mob_move(game, this);
		free_list(game->data->a->path, game->data->a->pathCount);
		game->data->a->pathCount = 0;
	}
	else if (this->state == IDLE)
	{
		if (distance(this->x, this->y, game->player.px, game->player.py) < 1000)
			this->state = FOLLOW;
	}
	else if (this->state == ATTACK)
	{
		if (this->cd < 1)
		{
			if (this->attack_type == 0)
			{
				game->mob = game->sprites.abutor_a[this->frame / 2 % 15];
				if (this->frame / 2 % 15 == 4)
					play_sound("data/sound/Ascream.wav", game);
				if (this->frame / 2 % 15 == 14)
				{
					play_sound("data/sound/hit.mp3", game);
					game->player.hurt = 1;
					game->player.hurt_cd = 10;
					game->player.hp--;
					this->cd = 20;
				}
				this->state = IDLE;
			}
			else
			{
				game->mob = game->sprites.abutor_a[this->frame / 2 % 15];
				play_sound("data/sound/powering.wav", game);
				if (this->frame / 2 % 15 == 14)
				{
					play_sound("data/sound/hit.mp3", game);
					game->player.trip = 1;
					game->player.trip_cd = 50;
					game->player.hp -= 5;
					this->cd = 20;
					this->state = IDLE;
				}
			}
		}
	}
	if (distance(this->x, this->y, game->player.px, game->player.py) < 50 || this->state == ATTACK)
	{
		if (this->cd == 0)
		{
			this->frame = 0;
			this->cd = -1;
			this->attack_type = rand() % 2;
		}
		this->state = ATTACK;
	}
	if (this->cd > 0)
		this->cd--;
}
