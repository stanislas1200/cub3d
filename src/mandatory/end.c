/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:09:51 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 17:37:06 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	destroy_sprites(t_game *game)
{
	int	i;

	i = -1;
	while (++i <= 3)
		if (game->sprites.wall[i])
			mlx_destroy_image(game->mlx_ptr, game->sprites.wall[i]);
}

int	end_game(t_game *game)
{
	printf(GREEN "----------------\nEXITING GAME\n----------------\n");
	destroy_sprites(game);
	free_all(game->data);
	mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	return (exit(0), 0);
}
