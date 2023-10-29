/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:32:49 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/29 17:12:53 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	update_player(t_game *game)
{
	if (game->player.hp <= 0)
	{
		play_sound("data/sound/game_over.mp3", game);
		game->status = 2;
	}
	if (game->player.trip_cd < 1)
		game->player.trip = 0;
	if (game->player.hurt_cd < 1)
		game->player.hurt = 0;
	game->player.trip_cd--;
	game->player.hurt_cd--;
	movement(game);
}

void	update_mob(t_game *game)
{
	t_mob	*current;
	t_mob	*next;

	current = game->data->mob_list;
	while (current)
	{
		game->monster = *current;
		if (game->data->fired && game->monster.state != DEAD && in_view(game))
		{
			play_sound("data/sound/impact.mp3", game);
			current->hp--;
			game->data->fired = 0;
		}
		execute_mob(game, current);
		if (current->state == DEAD)
		{
			next = current->next;
			delete_monster(&game->data->mob_list, current);
			current = next;
		}
		else
			current = current->next;
	}
	game->data->fired = 0;
}

void	check_end(t_game *game)
{
	if (game->status == 1)
		mlx_put_image_to_window(game->mlx_ptr, \
	game->mlx_win, game->sprites.win, 0, 0);
	else if (game->status == 2)
		mlx_put_image_to_window(game->mlx_ptr, \
	game->mlx_win, game->sprites.loss, 0, 0);
}

int	update_frame(t_game *game)
{
	if (game->status)
		return (check_end(game), 1);
	if (game->data->time >= 1000)
		game->data->time = 0;
	update_player(game);
	draw_rays(game);
	update_mob(game);
	mlx_put_image_to_window(game->mlx_ptr, \
	game->mlx_win, game->img.image, 0, 0);
	game->data->time++;
	if (game->data->g_time > 4)
		game->data->g_time = 0;
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, \
	game->crosshair, (WIDTH / 2), (HEIGHT / 2) - SQUARE);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, \
	game->sprites.gun[(game->data->g_time) % 4], (WIDTH / 2), HEIGHT - GUN_H);
	render_minimap(game);
	if (game->data->g_time > 0) 
		game->data->g_time++;
	return (0);
}
