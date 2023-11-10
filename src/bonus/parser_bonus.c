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

#include "../../include/cub3d_bonus.h"

int		is_d(char c);
int		is_el(char *str, t_data *d);
void	check_element(t_data *d);

void	get_rgb(int dest[3], char c, char *s, t_data *d)
{
	if ((d->i == 0 || s[d->i - 1] == '\n') && s[d->i] == c)
	{
		while ((s[d->i + 2] == ' ' || s[d->i + 2] == '\t') \
		&& (s[d->i + 1] == ' ' || s[d->i + 1] == '\t'))
			d->i++;
		if ((s[d->i + 1] == ' ' || s[d->i + 1] == '\t') && is_d(s[d->i + 2]))
		{
			dest[0] = ft_atoi(&s[d->i + 2]);
			while (is_d(s[d->i + 2]))
				d->i++;
			if (s[d->i + 2] != ',' || !is_d(s[d->i + 3]))
				return (e(d, E_M RESET ": ", F));
			dest[1] = ft_atoi(&s[++d->i + 2]);
			while (is_d(s[d->i + 2]))
				d->i++;
			if (s[d->i + 2] != ',' || !is_d(s[d->i + 3]))
				return (e(d, E_M RESET ": ", F));
			dest[2] = ft_atoi(&s[++d->i + 2]);
			while (is_d(s[d->i + 2]))
				d->i++;
			d->i += 2;
		}
		else
			return (e(d, E_M RESET ": ", F));
	}
}

void	get_element(char *str, t_data *d)
{
	d->i = -1;
	while (d->i < ft_strlen(str) && str[++d->i])
	{
		if (d->i - 1 >= 0 && str[d->i - 1] != '\n' && str[d->i] != 'C' \
		&& str[d->i] != 'F' && str[d->i] != '\n' && !is_el(str, d))
			return (e(d, E_M RESET ": ", "Invalid character\n"));
		while ((d->i == 0 || str[d->i - 1] == '\n') \
		&& (is_el(str, d) || str[d->i] == 'F' || str[d->i] == 'C' ))
		{
			get_wall_texture_path(&d->no, str, "SO", d);
			get_wall_texture_path(&d->so, str, "EA", d);
			get_wall_texture_path(&d->we, str, "NO", d);
			get_wall_texture_path(&d->ea, str, "WE", d);
			get_rgb(d->floor, 'F', str, d);
			get_rgb(d->ceiling, 'C', str, d);
		}
		if (str[d->i] && (str[d->i] == '\n') \
		&& (str[d->i + 1] == ' ' || str[d->i + 1] == '1'))
			break ;
	}
	check_element(d);
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
				return (d->height = d->i, e(d, E_M RESET ": ", P));
		}
		else if (str[tot + d->j] == '1')
			d->map[d->i][d->j] = 'X';
		else if (str[tot + d->j] == '0' || str[tot + d->j] == 'B')
		{
			if (str[tot + d->j] == 'B')
				generate_monster(d, ABUTOR);
			generate_monster(d, EGG);
			d->map[d->i][d->j] = 'F';
		}
		else if (str[tot + d->j] != ' ')
			return (d->height = d->i, e(d, E_M RESET ": ", C));
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
		if (d->biggest_w < l)
			d->biggest_w = l;
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
		e(d, E_M RESET ": ", "No player found\n");
}
