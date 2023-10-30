/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:03:47 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 14:22:28 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"
#include <errno.h>
#include <string.h>

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

void	read_file(int fd, t_data *data)
{
	int		read_bytes;
	char	buff[2];
	char	*tmp;

	data->all_line = malloc(1);
	if (!data->all_line)
		return (e(data, "Malloc error\n" RESET, NULL));
	data->all_line[0] = '\0';
	read_bytes = -1;
	while (read_bytes)
	{
		read_bytes = read(fd, buff, 1);
		if (read_bytes == -1)
			return (e(data, strerror(errno), "\n"));
		buff[read_bytes] = '\0';
		tmp = data->all_line;
		data->all_line = ft_strjoin(data->all_line, buff);
		free(tmp);
		if (!data->all_line)
			return (e(data, "Malloc error\n" RESET, NULL));
	}
}
