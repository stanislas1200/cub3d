/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:43:45 by sgodin            #+#    #+#             */
/*   Updated: 2023/11/10 14:31:10 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	free_mob_list(t_mob *lst)
{
	t_mob	*current;

	while (lst)
	{
		current = lst;
		lst = lst->next;
		free(current);
	}
}

void	free_map(t_data *data, int height)
{
	while (data->map && height >= 0)
	{
		free(data->map[height--]);
		data->map[height + 1] = NULL;
	}
	free(data->map);
	data->map = NULL;
}

void	free_all(t_data *data)
{
	free(data->all_line);
	free_map(data, data->height);
	free(data->no);
	free(data->so);
	free(data->we);
	free(data->ea);
	free(data->a->open);
	free(data->a->closed);
	free_nodes(data, data->a);
	free(data->a->nodes);
	free(data->a->path);
	free_mob_list(data->mob_list);
}

void	e(t_data *data, char *error, char *info)
{
	ft_error(RED BOLD "Error" RESET ": " YELLOW);
	if (error)
		ft_error(error);
	if (info)
		ft_error(info);
	free_all(data);
	exit(1);
}

void	get_wall_texture_path(char **dest, char *str, char *str2, t_data *d)
{
	d->j = 0;
	if (d->i != 0 && str[d->i - 1] != '\n')
		return ;
	if (!ft_strncmp(&str[d->i], str2, 2))
	{
		if (*dest)
			return (e(d, "Invalid map" RESET ": ", "Duplicate wall path\n"));
		if (str[d->i + 2] != ' ' && str[d->i + 2] != '\t')
			return (e(d, "Invalid map" RESET ": ", "Invalid wall path\n"));
		while (str[d->i + 2] == ' ' || str[d->i + 2] == '\t')
			d->i++;
		d->i--;
		while (str[d->i + d->j + 2] && str[d->i + d->j + 2] \
		!= '\n' && str[d->i + d->j + 2] != '\r')
			d->j++;
		*dest = malloc(sizeof(char) * (d->j + 1));
		if (!*dest)
			return (e(d, "Malloc error\n" RESET, NULL));
		ft_strlcpy(*dest, &str[d->i + 3], d->j);
		(*dest)[d->j] = '\0';
		d->i += d->j + 2;
		while (str[d->i] == ' ' || str[d->i] == '\t' \
		|| str[d->i] == '\n' || str[d->i] == '\r')
			d->i++;
	}
}
