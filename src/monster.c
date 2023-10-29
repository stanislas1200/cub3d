/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:38:26 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/28 20:37:37 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	execute_abutor(t_game *game, t_mob *this);

void	delete_monster(t_mob **list, t_mob *mob)
{
	t_mob	*current;

	if (*list == mob)
	{
		*list = mob->next;
		free(mob);
		return ;
	}
	current = *list;
	while (current && current->next != mob)
	{
		current = current->next;
	}
	if (current)
	{
		current->next = mob->next;
		free(mob);
	}
}

void	free_mob_list(t_mob *lst)
{
	t_mob	*current;

	while (lst)
	{
		current = lst;
		lst = lst->next;
		free(current);
	}
}

void	set_stats(t_mob *this, int type)
{
	if (type == EGG)
	{
		this->max_hp = 1;
		this->cd = 0;
	}
	else if (type == CHUBBS)
	{
		this->max_hp = 5;
		this->cd = 5;
	}
	else if (type == ABUTOR)
	{
		this->max_hp = 100;
		this->cd = 10;
	}
}

void	add_enemy(t_mob *new_enemy, t_mob *current, t_data *data, int type)
{
	set_stats(new_enemy, type);
	new_enemy->frame = rand() % 1001;
	new_enemy->x = (data->j << 6) + SQUARE / 2;
	new_enemy->y = (data->i << 6) + SQUARE / 2;
	new_enemy->state = IDLE;
	new_enemy->hp = new_enemy->max_hp;
	new_enemy->next = NULL;
	new_enemy->type = type;
	new_enemy->attack_type = 0;

	if (data->mob_list == NULL)
		data->mob_list = new_enemy;
	else
	{
		current = data->mob_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_enemy;
	}
}

void	generate_monster(t_data *data, int type)
{
	t_mob	*current;
	t_mob	*new;

	if (data->i > data->height / 3 && rand() % 100 < 5 || type == ABUTOR)
	{
		new = NULL;
		current = NULL;
		new = (t_mob *)malloc(sizeof(t_mob));
		if (!new)
			return ((void)printf(RED "ADD Mob faill\n" RESET));
		add_enemy(new, current, data, type);
	}
}

void	mob_move(t_game *game, t_mob *this)
{
	int	x;
	int	y;

	x = (game->data->a->path[game->data->a->pathCount - 2]->x << 6) \
	+ (SQUARE / 2);
	y = (game->data->a->path[game->data->a->pathCount - 2]->y << 6) \
	+ (SQUARE / 2);
	if (this->x > x)
		this->x -= this->speed;
	if (this->x < x)
		this->x += this->speed;
	if (this->y >= y)
		this->y -= this->speed;
	if (this->y <= y)
		this->y += this->speed;
}

void	execute_egg(t_game *game, t_mob *this)
{
	t_mob	*current;
	t_mob	*new;

	game->mob = game->sprites.egg[this->frame / 5 % 2];
	if (this->hp <=0)
		this->state = DEAD;
	else if (this->state != DYING && distance(this->x, this->y, game->player.px, game->player.py) < 150)
	{
		play_sound("data/sound/egg.mp3", game);
		this->frame = 0;
		this->state = DYING;
	}
	else if (this->state == DYING)
	{
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
			play_sound("data/sound/hit.mp3", game);
			game->player.hurt = 1;
			game->player.hurt_cd = 10;
			game->player.hp--;
			this->cd = 20;
		}
		this->state = IDLE;
	}
	if (distance(this->x, this->y, game->player.px, game->player.py) < 100)
			this->state = ATTACK;
	if (distance(this->x, this->y, game->player.px, game->player.py) < 1000 && rand() % 300 <= 0)
		play_sound("data/sound/scream.mp3", game);
	if (this->cd > 0)
		this->cd--;
}


void	execute_mob(t_game *game, t_mob *this)
{
	if (this->frame > 1000)
		this->frame = 0;
	this->frame++;
	if (this->type == EGG)
		execute_egg(game, this);
	else if (this->type == CHUBBS)
		execute_chubbs(game, this);
	if (this->type == ABUTOR)
		execute_abutor(game, this);
	if (distance(game->monster.x, game->monster.y, \
	game->player.px, game->player.py) < 500)
		draw_monster(game);
}
