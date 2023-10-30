/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:38:26 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 10:28:15 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	execute_egg(t_game *game, t_mob *this);
void	execute_chubbs(t_game *game, t_mob *this);
void	execute_abutor(t_game *game, t_mob *this);

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
		this->speed = 15;
	}
	else if (type == ABUTOR)
	{
		this->max_hp = 20;
		this->cd = 10;
		this->speed = 13;
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

	x = (game->data->a->path[game->data->a->path_count - 2]->x << 6) \
	+ (SQUARE / 2);
	y = (game->data->a->path[game->data->a->path_count - 2]->y << 6) \
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
