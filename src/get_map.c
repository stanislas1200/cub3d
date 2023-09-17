#include "../include/cub3d.h"

size_t  ft_strlcpy(char *dest, char *src, size_t size)
{
        size_t  j;

        j = 0;
        if (size != 0)
        {
                while (size - 1 > j && size != 0 && src[j])
                {
                        dest[j] = src[j];
                        j++;
                }
                dest[j] = '\0';
        }
        return (ft_strlen(src));
}

size_t  ft_strlcat(char *dest, char *src, size_t size)
{
        size_t  i;
        size_t  j;
        size_t  k;

        i = 0;
        j = 0;
        k = 0;
        while (dest[i] && i < size)
                i++;
        while (src[j])
                j++;
        if (i == size)
                return (j + size);
        while (src[k] && i + k < size - 1)
        {
                dest[i + k] = src[k];
                k++;
        }
        dest[i + k] = '\0';
        return (i + j);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
		char    *str;
		int             len1;
		int             len2;

		if (!s1 || !s2)
				return (NULL);
		len1 = ft_strlen((char *)s1);
		len2 = ft_strlen((char *)s2);
		str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (!str)
				return (NULL);
		ft_strlcpy(str, (char *)s1, len1 + 1);
		ft_strlcat(str, (char *)s2, len1 + len2 + 1);
		return (str);
}

int	find_file(char **path, char **new_path, int *free_path)
{
	int	i;

	i = -1;
	while ((*path)[++i])
	{
		if ((*path)[i] == '.' && !((*path)[i + 1] == '/' && !(*path)[i - 1]))
		{
			if ((*path)[i + 1] == 'c' && (*path)[i + 2] == 'u' && \
			(*path)[i + 3] == 'b' && (*path)[i + 4] == '\0')
				break ;
			else
			{
				printf("\x1b[1;31mError\x1b[0m: Map file must be a\x1b[1;35m .cub\x1b[0m file\n");
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

/**
 * Opens a file at the specified path or in ../data/map/ and returns its file descriptor.
 *
 * @param path The path of the file to open.
 *
 * @return Returns the file descriptor of the opened file, or -1 on error.
 */
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

void	set_map_from_file(char *path, t_data *data)
{
	int		fd;
	char	*all_line;

	fd = open_file(path);
	if (fd == -1)
		perror(RED BOLD "Error" RESET);
	if (fd == -2 || fd == -1)
		exit(1);
	// all_line = read_file(fd, data);
	// if (all_line)
	// 	data->map = split_lines(all_line, data->map_width, NULL, 0);
	// data->map_copy = new_mapcpy(data->map, data->map_height, data->map_width);
	// data->map_cave = new_mapcpy(data->map, data->map_height, data->map_width);
	// if (!data->map_cave || !data->map_copy || !data->map)
	// {
	// 	free_all(data);
	// 	free(all_line);
	// 	exit(1);
	// }
	// free(all_line);
}