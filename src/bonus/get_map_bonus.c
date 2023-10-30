/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:17:14 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/02 15:17:14 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	read_file(int fd, t_data *data);
int		open_file(char *path);

void	make_floor(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
			if (data->map[i][j] == 'F')
				pg(j, i, rand() % (2), data);
	}
	return ;
}

void	make_door(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[++i])
	{
		j = 0;
		while (data->map[i][++j])
		{
			if (i > 2 && i < data->height - 2 && j > 2 \
			&& j < ft_strlen(data->map[i]) - 2 && data->map[i][j] == 'X')
			{
				if (((j < ft_strlen(data->map[i - 1]) \
				&& data->map[i - 1][j] == 'F' \
				&& data->map[i][j + 1] == 'X' \
				&& j < ft_strlen(data->map[i + 1]) \
				&& data->map[i + 1][j] == 'F' \
				&& data->map[i][j - 1] == 'X') || \
				(data->map[i][j - 1] == 'F' && data->map[i][j + 1] == 'F' \
				&& data->map[i - 1][j] == 'X' \
				&& data->map[i + 1][j] == 'X')) && rand() * 10 <= 1)
					data->map[i][j] = 'D';
			}
		}
	}
}

void	check_map(t_data *d)
{
	int	i;
	int	j;

	i = -1;
	while (d->map[++i])
	{
		j = -1;
		while (d->map[i][++j])
		{
			if (d->map[i][j] == 'F')
			{
				if (j == 0 || d->map[i][j - 1] == ' ' \
				|| !d->map[i][j + 1] || d->map[i][j + 1] == ' ' \
				|| i == 0 || j >= ft_strlen(d->map[i - 1]) \
				|| d->map[i - 1][j] == ' ' \
				|| !d->map[i + 1] || j >= ft_strlen(d->map[i + 1]) \
				|| d->map[i + 1][j] == ' '
				)
					return (e(d, "Map error : ", "map not close\n"));
			}
		}
	}
}

void	set_map_from_file(char *path, t_data *data)
{
	int		fd;

	fd = open_file(path);
	if (fd == -1)
		perror(RED BOLD "Error" RESET);
	if (fd == -2 || fd == -1)
		exit(1);
	read_file(fd, data);
	make_map(data->all_line, data);
	free(data->all_line);
	data->all_line = NULL;
	check_map(data);
	make_door(data);
}
