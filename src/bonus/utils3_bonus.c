/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:05:40 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 12:45:52 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	put_img(t_game *data, t_img **i, char *path)
{
	int	width;
	int	height;

	*i = mlx_xpm_file_to_image(data->mlx_ptr, \
				path, &width, &height);
	if (*i)
	{
		(**i).width = width;
		(**i).height = height;
	}
}

unsigned int	get_color(t_img *img, int x, int y)
{
	return (*(unsigned int *)(img->addr + \
	(y * img->line_length + x * (img->bits_per_pixel / 8))));
}

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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
