/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abutor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:38:49 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/29 17:13:27 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mob_track(t_game *game, t_mob *this);

void	abutor_sp(t_game *game, t_mob *this)
{
	game->mob = game->sprites.abutor_s[this->frame / 2 % 15];
	if (this->frame % 3 == 0)
		play_sound("data/sound/powering.wav", game);
	if (this->frame / 2 % 15 == 14)
	{
		play_sound("data/sound/hit.mp3", game);
		game->player.trip = 1;
		game->player.trip_cd = 50;
		game->player.hp -= 3;
		this->cd = 20;
		this->state = IDLE;
	}
}

void	abutor_attack(t_game *game, t_mob *this)
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
			abutor_sp(game, this);
	}
}

void	execute_abutor(t_game *game, t_mob *this)
{
	int	i;

	i = 0;
	while (++i <= this->hp)
	{
		if (i == 1)
			setup_img(game->sprites.heal0[this->frame/2 % 2], game, (int[]){128 + i * 64, 0, 128 , 128}, 1);
		else if (i == this->max_hp)
			setup_img(game->sprites.heal2[this->frame/2 % 2], game, (int[]){128 + (i + 2) * 64, 0, 128, 128}, 1);
		else
			setup_img(game->sprites.heal1[this->frame/2 % 2], game, (int[]){128 + (i + 1) * 64, 0, 128, 128}, 1);
	}
	game->mob = game->sprites.abutor_w[this->frame / 4 % 2];
	if (this->hp <= 0 || this->state == DEAD)
	{
		this->state = DEAD;
		play_sound("data/sound/dying.mp3", game);
		game->status = 1;
		return ;
	}
	if (this->state == FOLLOW)
		mob_track(game, this);
	else if (this->state == IDLE)
	{
		if (distance(this->x, this->y, game->player.px, game->player.py) < 1000)
			this->state = FOLLOW;
	}
	else if (this->state == ATTACK)
		abutor_attack(game, this);
	if (distance(this->x, this->y, game->player.px, game->player.py) < 75 || \
	this->state == ATTACK)
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
