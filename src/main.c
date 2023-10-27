/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:17:11 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/02 18:12:33 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy_sprites(t_game *game)
{
	int	i;

	i = -1;
	while (++i <= 3)
		if (game->sprites.wall[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.wall[i]);
}

void	stop_sound(void) // make a function to execute a function in a child ? void exec_func(void (*func)())
{
	pid_t	pid;

	pid = fork(); // check -1 ? send error exit 1 ? FOR ALL FORK
	if (pid == 0)
	{
		sleep(1);
		execlp("pkill", "pkill", "afplay", NULL);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

int	end_game(t_game *game)
{
	printf(GREEN "----------------\nEXITING GAME\n----------------\n");
	destroy_sprites(game);
	pthread_cancel(game->t_id); // Give error message ? exit 1 ?
	stop_sound();
	if (pthread_join(game->t_id, NULL))
		return (e(game->data, "thread join failed\n", NULL), exit(1), 1); // Give error message ? exit 1 ?
	free_all(game->data);
	return (exit(0), 0);
}

int	event_hook(int x, int y, t_game *game)
{
	game->player.pa += (x - game->old_x);
	game->player.pa = fix_ang(game->player.pa);
	game->player.pdx = cos(deg_to_rad(game->player.pa)) * 5.0;
	game->player.pdy = -sin(deg_to_rad(game->player.pa)) * 5.0;
	game->old_x = x;
	return (0);
}

int	key_pressed(int key, t_game *game)
{
	if (key == Z)
		game->keys[0] = 1;
	if (key == S)
		game->keys[1] = 1;
	if (key == A_E)
		game->keys[2] = 1;
	if (key == A_W)
		game->keys[3] = 1;
	if (key == Q)
		game->keys[4] = 1;
	if (key == D)
		game->keys[5] = 1;
	if (key == ESC)
		end_game(game);
	return (0);
}

int	key_released(int key, t_game *game)
{
	if (key == Z)
		game->keys[0] = 0;
	if (key == S)
		game->keys[1] = 0;
	if (key == A_E)
		game->keys[2] = 0;
	if (key == A_W)
		game->keys[3] = 0;
	if (key == Q)
		game->keys[4] = 0;
	if (key == D)
		game->keys[5] = 0;
	return (0);
}

int	update_frame(t_game *game)
{
	if (game->player.trip_cd < 1)
		game->player.trip = 0;
	game->player.trip_cd--;
	if (game->data->time >= 1000)
		game->data->time = 0;
	movement(game);
	draw_rays(game);
	// mlx_mouse_move(game->mlx_win, WIDTH/2, HEIGHT/2);
	// mlx_mouse_hide();
	mlx_put_image_to_window(game->mlx_ptr, \
	game->mlx_win, game->img.image, 0, 0);
	t_mob *current = game->data->mob_list;
	while (current)
	{
		game->monster = *current;
		// if (in_view(game))

	if (game->monster.state != DEAD || distance(game->monster.x, game->monster.y, game->player.px, game->player.py) < 1000)
			draw_monster(game);
		execute_mob(game, current);
		current = current->next;
	}
	mlx_put_image_to_window(game->mlx_ptr, \
	game->mlx_win, game->img.image, 0, 0);
	game->data->time++;
	if (game->data->g_time > 4)
		game->data->g_time = 0;
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->sprites.gun[(game->data->g_time) % 4], WIDTH / 1.3 - GUN_W, HEIGHT - GUN_H);
	if (game->data->g_time > 0) 
		game->data->g_time++;
	render_minimap(game);
	// in_view(game);
	// A*
	return (0);
}

void	*embient_sound(void *nop)
{
	(void)nop;
	while (1)
		system("afplay -v 0.5 data/sound/test.wav ");
	return (NULL);
}

void	play_sound(char *sound, t_game *game)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("afplay", "afplay", sound, NULL);
		exit(0);
	}
}

int	gun_fire(int button, int x, int y, t_game *game)
{
	if (game->data->g_time > 1)
		return (0);
	game->data->g_time = 1;
	play_sound("data/sound/gun.wav", game);
	t_mob *current = game->data->mob_list;
	while (current)
	{
		game->monster = *current;
		if (in_view(game))
		{
			play_sound("data/sound/impact.mp3", game);
			current->hp--;
		}
		current = current->next;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_game	game;
	t_astar a;
	data.a = &a;

	init_data(&data);
	if (ac == 2)
		set_map_from_file(av[1], &data);
	else
		return (ft_error(RED BOLD "Error: " RESET \
		"Invalid number of arguments\n"), 1);
	if (init_mlx(&game))
		return (e(&data, "mlx faill\n", NULL), 1);
	init_player(&data, &game);
	// data.i = (int)game.player.py >> 6;
	// data.j = (int)(game.player.px + SQUARE * 2) >> 6;
	// generate_monster(&data, 0);
	// data.i = (int)game.player.py >> 6;
	// data.j = (int)(game.player.px - SQUARE * 2) >> 6;
	// generate_monster(&data, 0);
	if (init_sprites(&game) != 0)
		return (e(&data, "Sprites\n", NULL), 1);
	// A*
	setup_astar(&data, data.a);
	// init_astar(&data, data.a);

	mlx_hook(game.mlx_win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_released, &game);
	mlx_hook(game.mlx_win, 6, 1L << 0, event_hook, &game);
	mlx_hook(game.mlx_win, 4, 1L << 0, gun_fire, &game);
	// game.monster.x = game.player.px + SQUARE * 2;
	// game.monster.y = game.player.py;
	mlx_loop_hook(game.mlx_ptr, update_frame, &game);
	mlx_hook(game.mlx_win, 17, 1L << 2, end_game, &game);
	if (pthread_create(&game.t_id, NULL, embient_sound, NULL))
		return (ft_error(RED BOLD "Error: " RESET "Thread\n"), 1); // exit ? use errno to specify error ?
	mlx_loop(game.mlx_ptr);
	free_all(&data);
	return (0);
}
