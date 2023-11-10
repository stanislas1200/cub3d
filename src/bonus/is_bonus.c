/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:50:55 by sgodin            #+#    #+#             */
/*   Updated: 2023/11/10 16:03:00 by sgodin           ###   ########.fr       */
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
