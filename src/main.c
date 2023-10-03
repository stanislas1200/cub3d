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

// TEMPORARY
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	init_data(t_data *data)
{
	data->height = 0;
	data->player_nb = 0;
	data->map = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->floor[0] = -1;
	data->floor[1] = -1;
	data->floor[2] = -1;
	data->ceiling[0] = -1;
	data->ceiling[1] = -1;
	data->ceiling[2] = -1;
}

// void	destroy_sprites(t_game *game)
// {
// 	int	i;

// 	i = -1;
// 	while (++i <= 3)
// 		if (game->sprites.wall[i])
// 			mlx_destroy_image(game->mlx_ptr, game->sprites.wall[i]);
// }

// int	init_sprites(t_game *game)
// {
// 	int		i;

// 	i = -1;
// 	while (++i <= 3)
// 		game->sprites.wall[i] = NULL;
// 	game->sprites.wall[NO] = put_img(game, game->data->no);
// 	game->sprites.wall[SO] = put_img(game, game->data->so);
// 	game->sprites.wall[WE] = put_img(game, game->data->we);
// 	game->sprites.wall[EA] = put_img(game, game->data->ea);
// 	if (!game->sprites.wall[NO] || !game->sprites.wall[SO] \
// 	|| !game->sprites.wall[WE] || !game->sprites.wall[EA])
// 		return (destroy_sprites(game), 1);
// 	i = -1;
// 	while (++i <= 3)
// 		game->sprites.wall[i]->addr = mlx_get_data_addr(game->sprites.wall[i], \
// &game->sprites.wall[i]->bits_per_pixel, &game->sprites.wall[i]->line_length, \
// &game->sprites.wall[i]->endian);
// 	if (!(game->sprites.wall[NO]->addr || game->sprites.wall[SO]->addr \
// 	|| game->sprites.wall[WE]->addr || game->sprites.wall[EA]->addr))
// 		return (destroy_sprites(game), 1);
// 	return (0);
// }

// void	init_player(t_data *data, t_game *game)
// {
// 	if (data->player.dir == 'S')
// 		data->player.pa = 270.0;
// 	else if (data->player.dir == 'W')
// 		data->player.pa = 180.0;
// 	else if (data->player.dir == 'E')
// 		data->player.pa = 0.0;
// 	else if (data->player.dir == 'N')
// 		data->player.pa = 90.0;
// 	data->player.px *= SQUARE;
// 	data->player.py *= SQUARE;
// 	data->player.pdx = cos(deg_to_rad(data->player.pa)) * 5;
// 	data->player.pdy = -sin(deg_to_rad(data->player.pa)) * 5;
// 	data->player.speed = 1.5;
// 	game->old_x = WIDTH/2;
// 	game->keys[0] = 0;
// 	game->keys[1] = 0;
// 	game->keys[2] = 0;
// 	game->keys[3] = 0;
// 	game->keys[4] = 0;
// 	game->keys[5] = 0;
// 	data->player.px += (SQUARE/2);
// 	data->player.py += (SQUARE/2);
// 	game->player = data->player;
// 	game->data = data;
// }

// void stop_sound()
// {
// 	pid_t pid;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execlp("pkill", "pkill", "afplay", NULL);
// 		exit(0);
// 	} else if (pid > 0)
// 	{
// 		waitpid(pid, NULL, 0);
// 	}
// }

// int	end_game(t_game *game)
// {
// 	destroy_sprites(game);
//     pthread_cancel(game->Tid);
//     stop_sound();
//     pthread_join(game->Tid, NULL);
// 	printf(GREEN "----------------\nEXITING GAME\n----------------\n");
// 	return(exit(0), 0);
// }

// int	event_hook(int x, int y, t_game *game)
// {
// 	game->player.pa += (x - game->old_x);
// 	game->player.pa = fix_ang(game->player.pa);
// 	game->player.pdx = cos(deg_to_rad(game->player.pa)) * 5.0;
// 	game->player.pdy = -sin(deg_to_rad(game->player.pa)) * 5.0;
// 	game->old_x = x;
// 	return (0);
// }

// int keyPressed(int key, t_game *game)
// {
// 	if (key == Z)
// 		game->keys[0] = 1;
// 	if (key == S)
// 		game->keys[1] = 1;
// 	if (key == 123)
// 		game->keys[2] = 1;
// 	if (key == 124)
// 		game->keys[3] = 1;
// 	if (key == Q)
// 		game->keys[4] = 1;
// 	if (key == D)
// 		game->keys[5] = 1;
// 	if (key == ESC)
// 		end_game(game);
// 	return (0);
// }

// int keyReleased(int key, t_game *game)
// {
// 	if (key == Z)
// 		game->keys[0] = 0;
// 	if (key == S)
// 		game->keys[1] = 0;
// 	if (key == 123)
// 		game->keys[2] = 0;
// 	if (key == 124)
// 		game->keys[3] = 0;
// 	if (key == Q)
// 		game->keys[4] = 0;
// 	if (key == D)
// 		game->keys[5] = 0;
// 	return (0);
// }

// int update_frame(t_game *game)
// {
// 	if (game->keys[0] && can_move(Z, game))
// 	{
// 		if (can_move(Z, game))
// 		game->player.px += game->player.pdx * game->player.speed;
// 		game->player.py += game->player.pdy * game->player.speed;
// 	}
// 	if (game->keys[1] && can_move(S, game))
// 	{
// 		game->player.px -= game->player.pdx * game->player.speed / 2;
// 		game->player.py -= game->player.pdy * game->player.speed / 2;
// 	}
// 	if (game->keys[4] && can_move(Q, game))
// 	{
// 		game->player.px -= game->player.pdy * game->player.speed / 5;
// 		game->player.py += game->player.pdx * game->player.speed / 5;
// 	}
// 	if (game->keys[5] && can_move(D, game))
// 	{
// 		game->player.px += game->player.pdy * game->player.speed / 5;
// 		game->player.py -= game->player.pdx * game->player.speed / 5;
// 	}
// 	if (game->keys[2])
// 	{
// 		game->player.pa -= 5.0 * game->player.speed / 2;
// 		game->player.pa = fix_ang(game->player.pa);
// 		game->player.pdx = cos(deg_to_rad(game->player.pa)) * 5.0;
// 		game->player.pdy = -sin(deg_to_rad(game->player.pa)) * 5.0;
// 	}
// 	if (game->keys[3])
// 	{
// 		game->player.pa += 5.0 * game->player.speed / 2;
// 		game->player.pa = fix_ang(game->player.pa);
// 		game->player.pdx = cos(deg_to_rad(game->player.pa)) * 5.0;
// 		game->player.pdy = -sin(deg_to_rad(game->player.pa)) * 5.0;
// 	}
// 	draw_rays(game);
// 	// mlx_mouse_move(game->mlx_win, WIDTH/2, HEIGHT/2);
// 	// mlx_mouse_hide();
// 	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, game->img.image, 0, 0);
// 	return (0);
// }

// void* embient_sound()
// {
// 	while (1)
// 		system("afplay -v 0.5 data/sound/test.wav ");
// 	return (NULL);
// }

// void play_sound(char *sound)
// {
// 	pid_t pid;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		printf(RED "FIRE\n" RESET);
// 		execlp("afplay", "afplay", sound, NULL);
// 		printf(GREEN "FIRE\n" RESET);
// 		exit(0);
// 	}
// }

// int	gun_fire()
// {
// 	play_sound("data/sound/gun.wav");
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_data	data;
	t_game	game;

	init_data(&data);
	if (ac == 2)
		set_map_from_file(av[1], &data);
	else
		return (ft_error(RED BOLD "Error: " RESET "Invalid number of arguments\n"), 1);

	// game.mlx_ptr = mlx_init();
	// game.mlx_win = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "cub3D");
	// game.img.image = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT);
	// game.img.addr = mlx_get_data_addr(game.img.image, &game.img.bits_per_pixel, &game.img.line_length,
	// 							&game.img.endian);
	// init_player(&data, &game);
	// if (init_sprites(&game) != 0)
	// 	return (ft_error(RED BOLD "Error: " RESET "Sprites\n"), 1);
	// draw_rays(&game);
	// mlx_put_image_to_window(game.mlx_ptr, game.mlx_win, game.img.image, 0, 0);
	// // mlx_do_key_autorepeaton(game.mlx_ptr);
	// mlx_hook(game.mlx_win, 2, 0, keyPressed, &game);
	// mlx_hook(game.mlx_win, 3, 1L << 1, keyReleased, &game);
	// mlx_hook(game.mlx_win, 6, 0L, event_hook, &game);
	// mlx_hook(game.mlx_win, 4, 0L, gun_fire, &game);
	// // mlx_hook(game.mlx_win, 2, 1L << 0, key_hook, &game);
	// mlx_loop_hook(game.mlx_ptr, update_frame, &game);
	// mlx_hook(game.mlx_win, 17, 1L << 2, end_game, &game);
	// pthread_create(&game.Tid, NULL, embient_sound, NULL);
	// mlx_loop(game.mlx_ptr);
	free_all(&data);
	return (0);
}
