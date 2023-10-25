/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:38:26 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/25 13:51:38 by sgodin           ###   ########.fr       */
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
void free_list(t_anode *arr[], int size);

void	execute_mob(t_game *game)
{
	if (game->monster.state == FOLLOW)
	{
		Astar(game->data, game->data->a, ((int)game->monster.x >> 6) , ((int)game->monster.y >> 6), ((int)game->player.px >> 6) , ((int)game->player.py >> 6));
		// print_path(game->data->a->path);
		game->data->i = 0;
		game->monster.state = MOVE;
	}
	else if (game->monster.state == IDLE)
	{
		if (distance(game->monster.x, game->monster.y, game->player.px, game->player.py) < 20000)
			game->monster.state = FOLLOW;
	}
	else if (game->monster.state == MOVE)
	{
		if (game->data->a->pathCount < 2 || !game->data->a->path || !game->data->a->path[0])
			return (free_list(game->data->a->path, game->data->a->pathCount), game->monster.state = IDLE, (void)0);
		game->monster.speed = 10;
		// game->monster.x = game->data->a->path[0]->x << 6;
		// game->monster.y = game->data->a->path[0]->y << 6;
		if (game->monster.x > game->data->a->path[game->data->a->pathCount - 2]->x << 6)
			game->monster.x -= game->monster.speed;
		if (game->monster.x < game->data->a->path[game->data->a->pathCount - 2]->x << 6)
			game->monster.x += game->monster.speed;
		if (game->monster.y >= game->data->a->path[game->data->a->pathCount - 2]->y << 6)
			game->monster.y -= game->monster.speed;
		if (game->monster.y <= game->data->a->path[game->data->a->pathCount - 2]->y << 6)
			game->monster.y += game->monster.speed;
		// remove_arr(game->data->a->path, game->data->a->path[0], 1);
		printf(GREEN "Moved to : %d, %d \nHP: %d, %d\n", (int)game->monster.x >> 6 , (int)game->monster.y >> 6, game->monster.hp, game->monster.max_hp);
		free_list(game->data->a->path, game->data->a->pathCount);
		game->data->a->pathCount = 0;
		game->monster.state = IDLE; // DEV TEMP
	}
}
