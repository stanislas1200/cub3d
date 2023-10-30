/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:32:49 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 14:07:01 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	delete_monster(t_mob **list, t_mob *mob);
int		gun_fire(int button, int x, int y, t_game *game);

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
		setup_img (game->sprites.win, game, (int []){0, 0}, 1);
	else if (game->status == 2)
		setup_img (game->sprites.loss, game, (int []){0, 0}, 1);
	mlx_put_image_to_window(game->mlx_ptr, \
	game->mlx_win, game->img.image, 0, 0);
}

void	player_bar(t_game *game)
{
	int	i;

	i = -1;
	while (++i <= game->player.max_hp)
	{
		setup_img(game->sprites.red_b, game, \
		(int []){WIDTH - WIDTH / 4 + i * 32, HEIGHT - 128}, 0.5);
		if (i <= game->player.hp)
			setup_img(game->sprites.green_b, game, \
			(int []){WIDTH - WIDTH / 4 + i * 32, HEIGHT - 128}, 0.5);
	}
}

int	update_frame(t_game *game)
{
	if (game->status)
		return (check_end(game), 1);
	if (game->data->time >= 1000)
		game->data->time = 0;
	if (game->keys[6])
		gun_fire(0, 0, 0, game);
	update_player(game);
	draw_rays(game);
	update_mob(game);
	player_bar(game);
	setup_img(game->crosshair, game, (int []){((WIDTH - \
	(game->crosshair->width * (1 + 0.7 * game->keys[6]))) / 2), \
	((HEIGHT - game->crosshair->width * (1 + 0.7 * game->keys[6])) / 2) - \
	SQUARE}, 1 + 0.7 * game->keys[6]);
	setup_img(game->sprites.gun[(game->data->g_time) % 4], game, \
	(int []){(WIDTH / 2), HEIGHT - GUN_H}, 1);
	mlx_put_image_to_window(game->mlx_ptr, \
	game->mlx_win, game->img.image, 0, 0);
	game->data->time++;
	if (game->data->g_time > 3)
		game->data->g_time = 0;
	render_minimap(game);
	if (game->data->g_time > 0) 
		game->data->g_time++;
	return (0);
}
