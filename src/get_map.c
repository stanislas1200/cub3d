#include "../include/cub3d.h"
#include <string.h>

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

char *read_file(int fd, t_data *data) {
    int read_bytes;
	int size = 0;
    char buff[2];
    char *all_line = malloc(1);

    all_line[0] = '\0';
    while ((read_bytes = read(fd, buff, 1)) != 0) {
        if (read_bytes == -1) {
            perror("Error");
            free(all_line);
            return (NULL);
        }
		buff[1] = '\0';
		char *tmp = all_line;
		all_line = ft_strjoin(all_line, buff);
		free(tmp);
        size++;
    }
	all_line[size] = '\0';
    return (all_line);
}

void get_tile(char *str, t_data *data)
{
	int i = -1;
	int j = 0;

	while (str[++i] && j < 2)
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			j++;
			i++;
		}
	printf("%c", str[i]);
	}
	data->i = i;
}

char **make_map(char *str, t_data *data)
{
	char **map;
	get_tile(str, data);
	int tot = data->i;
	while (str[data->i])
	{
		if (str[data->i] == '\n')
			data->height++;
		data->i++;
	}
	map = malloc(sizeof(char *) * (data->height + 2));
	printf(RED BOLD "%d\n" RESET, data->height);
	for (int i = 0; i < data->height + 1; i++)
	{
		int len = -1;
		while (str[++len + tot] != '\n');
		// printf( RED "%d\n-", len);
		map[i] = malloc(sizeof(char) * (len + 1));
		for (int j = 0; j < len; j++)
		{
			// printf("%c", str[tot + j]);
			if (str[tot + j] == 'N'){
				data->player.x = j;
				data->player.y = i;}
			map[i][j] = str[tot + j];
		}
		tot += len + 1;
		map[i][len + 1] = '\0';
		printf("%s\n", map[i]);
	}
	map[data->height + 1] = NULL;
	// printf("%s\n", map[0]);
	return (map);
}

void play(t_data *data)
{
	while (1)
	{
		printf("\033[2J");
		int i = -1;
		while(data->map[++i])
		{
			int j = -1;
			while (data->map[i][++j])
				data->map[i][j] == 'N' ? printf(RED BOLD "%c" RESET, data->map[i][j]) : data->map[i][j] == '1' ? printf(GREEN "%c" RESET, data->map[i][j]) : printf("%c", data->map[i][j]);
			printf("\n");
		}
		int c = getchar();
		if (c == 'q')
			break ;
		else if (c == 'z' && data->map[data->player.y - 1][data->player.x] == '0')
		{
			data->map[data->player.y - 1][data->player.x] = 'N';
			data->map[data->player.y][data->player.x] = '0';
			data->player.y--;
		}
		else if (c == 's' && data->map[data->player.y + 1][data->player.x] == '0')
		{
			data->map[data->player.y + 1][data->player.x] = 'N';
			data->map[data->player.y][data->player.x] = '0';
			data->player.y++;
		}
		else if (c == 'd' && data->map[data->player.y][data->player.x + 1] == '0')
		{
			data->map[data->player.y][data->player.x + 1] = 'N';
			data->map[data->player.y][data->player.x] = '0';
			data->player.x++;
		}
		else if (c == 'a' && data->map[data->player.y][data->player.x - 1] == '0')
		{
			data->map[data->player.y][data->player.x - 1] = 'N';
			data->map[data->player.y][data->player.x] = '0';
			data->player.x--;
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
	data->map = make_map(all_line, data);
	play(data);
	free(all_line);
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