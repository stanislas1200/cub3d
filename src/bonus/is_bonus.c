/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:50:55 by sgodin            #+#    #+#             */
/*   Updated: 2023/11/15 14:09:51 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_d(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_el(char *str, t_data *d)
{
	return ((str[d->i + 2] == ' ' || \
		str[d->i + 2] == '	') && (!ft_strncmp(&str[d->i], "NO", 2) || \
		!ft_strncmp(&str[d->i], "SO", 2) || !ft_strncmp(&str[d->i], "WE", 2) || \
		!ft_strncmp(&str[d->i], "EA", 2)));
}

void	check_element(t_data *d)
{
	int	i;

	if (!d->no || !d->so || !d->we || !d->ea)
		return (e(d, E_M RESET ": ", "Missing Texture path\n"));
	if (d->floor[0] == -1 || d->floor[1] == -1 || d->floor[2] == -1)
		return (e(d, E_M RESET ": ", "Missing floor color\n"));
	if (d->ceiling[0] == -1 || d->ceiling[1] == -1 || d->ceiling[2] == -1)
		return (e(d, E_M RESET ": ", "Missing ceiling color\n"));
	i = -1;
	while (++i < 3)
		if (d->floor[i] > 255 || d->ceiling[i] > 255)
			return (e(d, E_M RESET ": ", "Colors must be in range [0,255]\n"));
}
