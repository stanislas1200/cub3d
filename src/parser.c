/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:38:39 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/02 17:38:39 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	get_wall_texture_path(char **dest, char *str, char *str2, t_data *data)
{
	data->j = 0;
	if (!ft_strncmp(&str[data->i], str2, 2))
	{
		if (*dest)
			return (e(data, "Invalid map" RESET ": ", "Duplicate wall texture path\n"));
		if (str[data->i + 2] != ' ' && str[data->i + 2] != '\t') // stricly so also tab ? and can more ?
			return (e(data, "Invalid map" RESET ": ", "Invalid wall texture path\n"));
		while (str[data->i + 2] == ' ' || str[data->i + 2] == '\t')
			data->i++;
		data->i--;
		while (str[data->i + data->j + 2] && str[data->i + data->j + 2] != '\n' && str[data->i + data->j + 2] != '\r')
			data->j++;
		*dest = malloc(sizeof(char) * (data->j + 1));
		if (!*dest)
			return (e(data, "Malloc error\n" RESET, NULL));
		ft_strlcpy(*dest, &str[data->i + 3], data->j);
		(*dest)[data->j] = '\0';
		data->i += data->j + 2;
		// SKIP space and \n ?
		while (str[data->i] == ' ' || str[data->i] == '\t' || str[data->i] == '\n' || str[data->i] == '\r')
			data->i++;
	}
}

void	get_rgb(int dest[3], char c, char *str, t_data *data)
{
	if (str[data->i] == c)
	{
		if (str[data->i + 1] == ' ' && \
		str[data->i + 2] >= '0' && str[data->i + 2] <= '9')
		{
			dest[0] = ft_atoi(&str[data->i + 2]);
			while (str[data->i + 2] >= '0' && str[data->i + 2] <= '9')
				data->i++;
			if (str[data->i + 2] != ',' || \
			str[data->i + 3] < '0' || str[data->i + 3] > '9')
				return (e(data, "Invalid map" RESET ": ", \
				"Invalid floor color\n"));
			dest[1] = ft_atoi(&str[++data->i + 2]);
			while (str[data->i + 2] >= '0' && str[data->i + 2] <= '9')
				data->i++;
			if (str[data->i + 2] != ',' || \
			str[data->i + 3] < '0' || str[data->i + 3] > '9')
				return (e(data, "Invalid map" RESET ": ", \
				"Invalid floor color\n"));
			dest[2] = ft_atoi(&str[++data->i + 2]);
			data->i += 2;
		}
		else
			return (e(data, "Invalid map" RESET ": ", "Invalid floor color\n"));
	}
}

void	get_element(char *str, t_data *d)
{
	d->i = -1;
	while (d->i < ft_strlen(str) && str[++d->i])
	{
		while (!ft_strncmp(&str[data->i], "NO", 2) || !ft_strncmp(&str[data->i], "SO", 2) || !ft_strncmp(&str[data->i], "WE", 2) || !ft_strncmp(&str[data->i], "EA", 2))
		{
			get_wall_texture_path(&data->no, str, "NO", data);
			get_wall_texture_path(&data->so, str, "SO", data);
			get_wall_texture_path(&data->we, str, "WE", data);
			get_wall_texture_path(&data->ea, str, "EA", data);
		}
		get_rgb(d->floor, 'F', str, d);
		get_rgb(d->ceiling, 'C', str, d);
		if (str[d->i] && (str[d->i] == '\n') \
		&& (str[d->i + 1] == ' ' || str[d->i + 1] == '1'))
			break ;
	}
	if (!d->no || !d->so || !d->we || !d->ea)
		return (e(d, "Invalid map" RESET ": ", "Missing Texture path\n"));
	if (d->floor[0] == -1 || d->floor[1] == -1 || d->floor[2] == -1)
		return (e(d, "Invalid map" RESET ": ", "Missing floor color\n"));
	if (d->ceiling[0] == -1 || d->ceiling[1] == -1 || d->ceiling[2] == -1)
		return (e(d, "Invalid map" RESET ": ", "Missing ceiling color\n"));
}

void	make_map(char *str, t_data *d)
{
	int	tot;

	get_element(str, d);
	tot = d->i;
	while (str[d->i])
	{
		if (str[d->i] == '\n')
			d->height++;
		d->i++;
	}
	d->map = malloc(sizeof(char *) * (++d->height + 1));
	if (!d->map)
		return (e(d, "Malloc failed\n", NULL));
	for (int i = 0; i < d->height; i++)
	{
		int len = -1;
		while (str[++len + tot] && str[len + tot] != '\n' && str[len + tot] != '\r');
		d->map[i] = malloc(sizeof(char) * (len + 1));
		if (!d->map[i])
		{
			ft_error(RED BOLD "Error" RESET ": Malloc failed\n");
			return (free_map(d, i - 1));
		}
		for (int j = 0; j < len; j++)
		{
			d->map[i][j] = str[tot + j];
			if (str[tot + j] == 'N' || str[tot + j] == 'S' || str[tot + j] == 'E' || str[tot + j] == 'W')
			{
				d->player.px = j;
				d->player.py = i;
				d->player.dir = str[tot + j];
				d->map[i][j] = 'F';
				if (d->player_nb++ >= 1)
					return (d->height = i, e(d, "Invalid map" RESET ": ", "Only one player is allowed\n"));
			}
			else if (str[tot + j] == '1')
				d->map[i][j] = 'X';
			else if (str[tot + j] == '0')
				d->map[i][j] = 'F';
			else if (str[tot + j] != ' ')
				return (d->height = i, e(d, "Invalid map" RESET ": ", "Invalid character in map\n"));
		}
		while (str[len + tot] == '\n' || str[len + tot] == '\r')
			tot++;
		tot += len;
		d->map[i][len] = '\0';
	}
	d->map[d->height] = NULL;
	if (d->player_nb == 0)
		e(d, "Invalid map" RESET ": ", "No player found\n");
}
