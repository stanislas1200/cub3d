/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:05:40 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/21 16:24:17 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	*put_img(t_game *data, char *path)
{
	int	img_width;
	int	img_height;

	return (mlx_xpm_file_to_image(data->mlx_ptr, \
				path, &img_width, &img_height));
}

int	get_color(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + \
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
