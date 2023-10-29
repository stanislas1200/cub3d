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

void	set_event(t_game *game);
void	stop_sound(void);

int	end_game(t_game *game)
{
	printf(GREEN "----------------\nEXITING GAME\n----------------\n");
	destroy_sprites(game);
	if (pthread_cancel(game->t_id))
		return (e(game->data, "thread cancel failed\n", NULL), 1);
	stop_sound();
	if (pthread_join(game->t_id, NULL))
		return (e(game->data, "thread join failed\n", NULL), 1);
	free_all(game->data);
	return (exit(0), 0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_game	game;
	t_astar	a;

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
	if (init_sprites(&game) != 0)
		return (e(&data, "Sprites\n", NULL), 1);
	setup_astar(&data, data.a);
	set_event(&game);
	free_all(&data);
	return (0);
}
