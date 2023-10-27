/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:38:26 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/27 19:30:47 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
void print_path(t_anode **path)
{
	int i = 0;
	while (path[i]) {
		printf("x: %d, y: %d\n", path[i]->x, path[i]->y);
		i++;
	}
}
void remove_arr(t_anode *arr[], t_anode *node, int size);

void	free_mob_list(t_mob *lst)
{
	while (lst)
	{
		t_mob *current = lst;
		lst = lst->next;
		free(current);
	}
}

void	add_enemy(t_mob *new_enemy, t_mob *current, t_data *data, int type)
{
	if (type == EGG)
	{
		new_enemy->max_hp = 1;
		new_enemy->cd = 0;
	}
	else if (type == CHUBBS)
	{
		new_enemy->max_hp = 5;
		new_enemy->cd = 5;
	}
	else if (type == ABUTOR)
	{
		new_enemy->max_hp = 100;
		new_enemy->cd = 10;
	}
	new_enemy->x = (data->j << 6) + SQUARE/2;
	new_enemy->y = (data->i << 6) + SQUARE/2;
	new_enemy->state = IDLE;
	new_enemy->hp = new_enemy->max_hp;
	new_enemy->next = NULL;
	new_enemy->type = type;

	if (data->mob_list == NULL)
	{
		data->mob_list = new_enemy;
	}
	else
	{
		current = data->mob_list;
		while (current->next != NULL)
		{
			current = current->next;
		}
	current->next = new_enemy;
	}
	printf(GREEN "New enemy in : %d, %d\n", (int)new_enemy->x >> 6, (int)new_enemy->y >> 6);
}

void	generate_monster(t_data *data, int type)
{
	t_mob	*current;
	t_mob	*new;

	if (data->i > data->height / 3 && rand() % 100 < 5)
	{
		new = NULL;
		current = NULL;
		new = (t_mob *)malloc(sizeof(t_mob));
		if (!new)
			return (printf(RED "ADD Mob faill\n" RESET), (void)0) ;
		add_enemy(new, current, data, type);
	}
}

void	execute_egg(t_game *game, t_mob *this)
{
	t_mob	*current;
	t_mob	*new;

	if (this->state == DYING)
	{
		if (this->cd >= 40)
		{
			new = (t_mob *)malloc(sizeof(t_mob));
			if (!new)
				return ;
			current = NULL;
			game->data->i = (int)this->y >> 6;
			game->data->j = (int)this->x >> 6;
			add_enemy(new, current, game->data, CHUBBS);
			this->state = DEAD; // remove from list;
		}
		this->cd++;
	}
	else if (distance(this->x, this->y, game->player.px, game->player.py) < 100)
	{
		play_sound("data/sound/egg.mp3", game);
		this->state = DYING;
	}
}

void	execute_mob(t_game *game, t_mob *this)
{
	if (this->state == DEAD)
		return;
	if (this->hp <= 0)
	{
		if (this->type != EGG)
			play_sound("data/sound/dying.mp3", game);
		this->state = DEAD;
		return ;
	}
	if (this->type == EGG)
	{
		execute_egg(game, this);
		return ;
	}
	if (distance(this->x, this->y, game->player.px, game->player.py) < 100)
	{
		if (this->cd < 1)
		{
			play_sound("data/sound/hit.mp3", game);
			game->player.trip = 1;
			game->player.trip_cd = 10;
			game->player.hp--;
			this->cd = 20;
		}
		this->cd--;
		if (game->player.hp <= 0)
		{
			play_sound("data/sound/game_over.mp3", game);
			end_game(game);
		}
	}
	if (distance(this->x, this->y, game->player.px, game->player.py) < 1000 && rand() % 300 <= 0)
		play_sound("data/sound/scream.mp3", game);
	else if (this->state == FOLLOW)
	{
		Astar(game->data, game->data->a, ((int)this->x >> 6) , ((int)this->y >> 6), ((int)game->player.px >> 6) , ((int)game->player.py >> 6));
		game->data->i = 0;
		// this->state = MOVE;
		// move part
		if (game->data->a->pathCount < 2 || !game->data->a->path || !game->data->a->path[0])
			return (free_list(game->data->a->path, game->data->a->pathCount), this->state = IDLE, (void)0);
		this->speed = 10;
		if (this->x > game->data->a->path[game->data->a->pathCount - 2]->x << 6)
			this->x -= this->speed;
		if (this->x < game->data->a->path[game->data->a->pathCount - 2]->x << 6)
			this->x += this->speed;
		if (this->y >= game->data->a->path[game->data->a->pathCount - 2]->y << 6)
			this->y -= this->speed;
		if (this->y <= game->data->a->path[game->data->a->pathCount - 2]->y << 6)
			this->y += this->speed;
		free_list(game->data->a->path, game->data->a->pathCount);
		game->data->a->pathCount = 0;
		this->state = IDLE; // DEV TEMP
	}
	else if (this->state == IDLE)
	{
		if (distance(this->x, this->y, game->player.px, game->player.py) < 1000)
			this->state = FOLLOW;
	}
	// else if (this->state == MOVE)
	// {
	// 	if (game->data->a->pathCount < 2 || !game->data->a->path || !game->data->a->path[0])
	// 		return (free_list(game->data->a->path, game->data->a->pathCount), this->state = IDLE, (void)0);
	// 	this->speed = 10;
	// 	// if (this->x > game->data->a->path[game->data->a->pathCount - 2]->x << 6)
	// 	// 	this->x -= this->speed;
	// 	// if (this->x < game->data->a->path[game->data->a->pathCount - 2]->x << 6)
	// 	// 	this->x += this->speed;
	// 	// if (this->y >= game->data->a->path[game->data->a->pathCount - 2]->y << 6)
	// 	// 	this->y -= this->speed;
	// 	// if (this->y <= game->data->a->path[game->data->a->pathCount - 2]->y << 6)
	// 	// 	this->y += this->speed;
	// 	printf(GREEN "Moved to : %d, %d \nHP: %d, %d\n", (int)this->x >> 6 , (int)this->y >> 6, this->hp, this->max_hp);
	// 	free_list(game->data->a->path, game->data->a->pathCount);
	// 	game->data->a->pathCount = 0;
	// 	this->state = IDLE; // DEV TEMP
	// }
	// printf(MAGENTA BOLD "Enemy at: %d, %d \nHP: %d, %d\n" RESET, (int)this->x >> 6 , (int)this->y >> 6, this->hp, this->max_hp);
}
