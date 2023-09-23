/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dspilleb <dspilleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:01:59 by dspilleb          #+#    #+#             */
/*   Updated: 2023/09/23 17:09:04 by dspilleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"



void drawstripes(t_game *game, int x1, int y1, int y2, int color) 
{
    int width;

    while((y1 >= 0 && y1 < y2))
    {
		width = -1;
		while (++width < (WIDTH / 90))
			my_mlx_pixel_put(&game->img, x1 + width, y1, color);
        y1++;
    }
}
