/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chubbs_egg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:55:57 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/29 18:03:52 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	add_enemy(t_mob *new_enemy, t_mob *current, t_data *data, int type);

void	mob_track(t_game *game, t_mob *this)
{
	this->state = IDLE;
	astar(game->data, game->data->a, \
	(int []){(int)this->x >> 6, (int)this->y >> 6}, \
	(int []){(int)game->player.px >> 6, (int)game->player.py >> 6});
	game->data->i = 0;
	if (game->data->a->pathCount < 2 || !game->data->a->path || \
	!game->data->a->path[0])
		return (free_list(game->data->a->path, game->data->a->pathCount));
	mob_move(game, this);
	free_list(game->data->a->path, game->data->a->pathCount);
}

void	egg_hatch(t_game *game, t_mob *this)
{
	t_mob	*current;
	t_mob	*new;

	game->mob = game->sprites.egg_e[this->frame / 5 % 4];
	if (this->cd >= 20)
	{
		new = (t_mob *)malloc(sizeof(t_mob));
		if (!new)
			return ;
		current = NULL;
		game->data->i = (int)this->y >> 6;
		game->data->j = (int)this->x >> 6;
		add_enemy(new, current, game->data, CHUBBS);
		this->state = DEAD;
	}
	this->cd++;
}

void	execute_egg(t_game *game, t_mob *this)
{
	game->mob = game->sprites.egg[this->frame / 5 % 2];
	if (this->hp <= 0)
		this->state = DEAD;
	else if (this->state != DYING && \
	distance(this->x, this->y, game->player.px, game->player.py) < 150)
	{
		play_sound("data/sound/egg.mp3", game);
		this->frame = 0;
		this->state = DYING;
	}
	else if (this->state == DYING)
		egg_hatch(game, this);
}

void	chubbs_attack(t_game *game, t_mob *this)
{
	if (this->cd < 1)
	{
		play_sound("data/sound/hit.mp3", game);
		game->player.hurt = 1;
		game->player.hurt_cd = 10;
		game->player.hp--;
		this->cd = 20;
	}
	this->state = IDLE;
}

void	execute_chubbs(t_game *game, t_mob *this)
{
	game->mob = game->sprites.chubb_w[this->frame % 4];
	if (this->hp <= 0 || this->state == DEAD)
	{
		this->state = DEAD;
		play_sound("data/sound/chubbs_dead.mp3", game);
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
		chubbs_attack(game, this);
	if (distance(this->x, this->y, game->player.px, game->player.py) < 100)
		this->state = ATTACK;
	if (distance(this->x, this->y, game->player.px, game->player.py) < 1000 && \
	rand() % 300 <= 0)
		play_sound("data/sound/scream.mp3", game);
	if (this->cd > 0)
		this->cd--;
}
