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

int	key_pressed(int key, t_game *game)
{
	if (key == Z)
		game->keys[0] = 1;
	if (key == S)
		game->keys[1] = 1;
	if (key == 123)
		game->keys[2] = 1;
	if (key == 124)
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
	if (key == 123)
		game->keys[2] = 0;
	if (key == 124)
		game->keys[3] = 0;
	if (key == Q)
		game->keys[4] = 0;
	if (key == D)
		game->keys[5] = 0;
	return (0);
}

int	update_frame(t_game *game)
{
	movement(game);
	draw_rays(game);
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, \
	game->img.image, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_game	game;

	init_data(&data);
	if (ac == 2)
		set_map_from_file(av[1], &data);
	else
		return (ft_error(RED BOLD "Error: " RESET \
		"Invalid number of arguments\n"), 1);
	if (init_mlx(&game))
		return (e(&data, "mlx faill\n", NULL), 1);
	init_player(&data, &game);
	if (init_sprites(&game) != 0)
		return (e(&data, "Sprites\n", NULL), 1);
	mlx_hook(game.mlx_win, 2, 0, key_pressed, &game);
	mlx_hook(game.mlx_win, 3, 1L << 1, key_released, &game);
	mlx_loop_hook(game.mlx_ptr, update_frame, &game);
	mlx_hook(game.mlx_win, 17, 1L << 2, end_game, &game);
	mlx_loop(game.mlx_ptr);

	free_all(&data);
	return (0);
}
