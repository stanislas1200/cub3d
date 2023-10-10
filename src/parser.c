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


void	get_wall_texture_path(char **dest, char *str, char *str2, t_data *d)
{
	d->j = 0;
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
		while (!ft_strncmp(&str[d->i], "NO", 2) || \
		!ft_strncmp(&str[d->i], "SO", 2) || !ft_strncmp(&str[d->i], "WE", 2) || \
		!ft_strncmp(&str[d->i], "EA", 2))
		{
			get_wall_texture_path(&d->no, str, "NO", d);
			get_wall_texture_path(&d->so, str, "SO", d);
			get_wall_texture_path(&d->we, str, "WE", d);
			get_wall_texture_path(&d->ea, str, "EA", d);
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

void	read_map2(t_data *d, char *str, int tot, int l)
{
	while (++d->j < l)
	{
		d->map[d->i][d->j] = str[tot + d->j];
		if (str[tot + d->j] == 'N' || str[tot + d->j] == 'S' \
		|| str[tot + d->j] == 'E' || str[tot + d->j] == 'W')
		{
			d->player.px = d->j;
			d->player.py = d->i;
			d->player.dir = str[tot + d->j];
			d->map[d->i][d->j] = 'F';
			if (d->player_nb++ >= 1)
				return (d->height = d->i, e(d, "Invalid map" RESET ": ", \
				"Only one player is allowed\n"));
		}
		else if (str[tot + d->j] == '1')
			d->map[d->i][d->j] = 'X';
		else if (str[tot + d->j] == '0')
			d->map[d->i][d->j] = 'F';
		else if (str[tot + d->j] != ' ')
			return (d->height = d->i, e(d, "Invalid map" RESET ": ", \
			"Invalid character in map\n"));
	}
}

void	read_map(t_data *d, char *str, int tot)
{
	int	l;

	d->i = -1;
	while (++d->i < d->height)
	{
		l = -1;
		d->j = -1;
		while (str[++l + tot] && str[l + tot] != '\n' && str[l + tot] != '\r')
			;
		d->map[d->i] = malloc(sizeof(char) * (l + 1));
		if (!d->map[d->i])
		{
			ft_error(RED BOLD "Error" RESET ": Malloc failed\n");
			return (free_map(d, d->i - 1));
		}
		read_map2(d, str, tot, l);
		while (str[l + tot] == '\n' || str[l + tot] == '\r')
			tot++;
		tot += l;
		d->map[d->i][l] = '\0';
	}
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
	read_map(d, str, tot);
	d->map[d->height] = NULL;
	if (d->player_nb == 0)
		e(d, "Invalid map" RESET ": ", "No player found\n");
}
