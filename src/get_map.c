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

#include "../include/cub3d.h"

void	free_map(t_data *data, int height)
{
	while (data->map && height >= 0)
		free(data->map[height--]);
	if (data->map)
		free(data->map);
	data->map = NULL;
}

void	error(t_data *data, char *error)
{
	ft_error(RED BOLD "Error" RESET ": " YELLOW "Invalid map" RESET ": ");
	ft_error(error);
	free_map(data, data->height);
	exit(1);
}

int	find_file(char **path, char **new_path, int *free_path)
{
	int	i;

	i = -1;
	while ((*path)[++i])
	{
		if ((*path)[i] == '.' && !((*path)[i + 1] == '/' && !(*path)[i - 1]))
		{
			if (!ft_strncmp(&(*path)[i + 1], "cub", 4))
				break ;
			else
			{
				ft_error(RED BOLD "Error" RESET ": Map file must be a " \
				MAGENTA ".cub " RESET "file\n");
				return (-2);
			}
		}
		else if ((*path)[i + 1] == '\0')
			*new_path = ft_strjoin((*path), ".cub");
	}
	if (*new_path)
	{
		(*path) = *new_path;
		*free_path = 1;
	}
	return (0);
}

int	open_file(char *path)
{
	char	*new_path;
	int		fd;
	int		free_path;

	new_path = NULL;
	free_path = 0;
	if (find_file(&path, &new_path, &free_path) == -2)
		return (-2);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		new_path = ft_strjoin("./data/map/", path);
		if (new_path)
		{
			fd = open(new_path, O_RDONLY);
			free(new_path);
		}
	}
	if (free_path)
		free(path);
	return (fd);
}

char	*read_file(int fd, t_data *data)
{
	int		read_bytes;
	int		size;
	char	buff[2];
	char	*tmp;
	char	*all_line;

	all_line = malloc(1);
	all_line[0] = '\0';
	read_bytes = -1;
	size = 0;
	while (read_bytes)
	{
		read_bytes = read(fd, buff, 1);
		if (read_bytes == -1)
			return (perror("Error"), free(all_line), NULL);
		buff[1] = '\0';
		tmp = all_line;
		all_line = ft_strjoin(all_line, buff);
		free(tmp);
		size++;
	}
	all_line[size] = '\0';
	return (all_line);
}

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

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (i > 1 && i < data->height - 1 && j > 1 && data->map[i][j] == 'X')
			{
				if ((data->map[i - 1][j] == 'F' && data->map[i][j + 1] == 'X' \
				&& data->map[i + 1][j] == 'F' && data->map[i][j - 1] == 'X' \
				&& j < ft_strlen(data->map[i + 1])) || \
				data->map[i][j - 1] == 'F' && data->map[i][j + 1] == 'F' \
				&& data->map[i - 1][j] == 'X' \
				&& data->map[i + 1][j] == 'X')
				{
					if (rand() % (3))
						data->map[i][j] = 'D';
				}
			}
		}
	}
}

void	check_map(t_data *data)
{
	int	i;
	int j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'F')
			{ // left right top down
				if (j == 0 || data->map[i][j - 1] == ' ' \
				|| !data->map[i][j + 1] || data->map[i][j + 1] == ' ' \
				|| i == 0 || j >= ft_strlen(data->map[i - 1]) || data->map[i - 1][j] == ' ' \
				|| !data->map[i + 1] || j >= ft_strlen(data->map[i + 1]) || data->map[i + 1][j] == ' '
				)
				{
					printf(RED "ERROR: " RESET "x: " MAGENTA "%d, " RESET "y: " MAGENTA "%d\n" RESET, j, i);
					exit(1);
				}
			}
		}
	}
}

void	set_map_from_file(char *path, t_data *data)
{
	int		fd;
	char	*all_line;

	fd = open_file(path);
	if (fd == -1)
		perror(RED BOLD "Error" RESET);
	if (fd == -2 || fd == -1)
		exit(1);
	all_line = read_file(fd, data);
	// generate_random_map(data, 10, 10);
	make_map(all_line, data);
	free(all_line);
	check_map(data);
	// make_door(data);
	// make_floor(data);
	if (!data->map)
		return ;
	// play(data);
	print_map(data);
	// free_map(data, data->height);
}
