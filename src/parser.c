#include "../include/cub3d.h"


void get_wall_texture_path(char **dest, char *str, char *str2, t_data *data)
{
	data->j = 0;
	if (!ft_strncmp(&str[data->i], str2, 2))
	{
		if (*dest)
			return (error(data, "Duplicate wall texture path\n"));
		if (str[data->i + 2] != ' ')
			return (error(data, "Invalid wall texture path\n"));
		while (str[data->i + data->j + 2] && str[data->i + data->j + 2] != '\n')
			data->j++;
		*dest = malloc(sizeof(char) * (data->j + 1));
		if (!*dest)
			return (ft_error(RED BOLD "Error" RESET ": Malloc failed\n"));
		ft_strlcpy(*dest, &str[data->i + 3], data->j);
		(*dest)[data->j] = '\0';
		data->i += data->j + 2;
		// SKIP space and \n ?
		while (str[data->i] == ' ' || str[data->i] == '\n')
			data->i++;
	}
}

void	get_RGB(int dest[3], char c, char *str, t_data *data)
{
	if (str[data->i] == c)
	{
		if (str[data->i + 1] == ' ' && str[data->i + 2] >= '0' && str[data->i + 2] <= '9')
		{
			dest[0] = ft_atoi(&str[data->i + 2]);
			while (str[data->i + 2] >= '0' && str[data->i + 2] <= '9')
				data->i++;
			if (str[data->i + 2] != ',' || str[data->i + 3] < '0' || str[data->i + 3] > '9')
				return (error(data, "Invalid floor color\n"));
			dest[1] = ft_atoi(&str[++data->i + 2]);
			while (str[data->i + 2] >= '0' && str[data->i + 2] <= '9')
				data->i++;
			if (str[data->i + 2] != ',' || str[data->i + 3] < '0' || str[data->i + 3] > '9')
				return (error(data, "Invalid floor color\n"));
			dest[2] = ft_atoi(&str[++data->i + 2]);
			data->i += 2;
		}
		else
			return (error(data, "Invalid floor color\n"));
	}
}

void get_element(char *str, t_data *data)
{
	data->i = -1;
	while (str[++data->i]) //  followed by all specific informations for each object in a strict order such as 
	{
		get_wall_texture_path(&data->no, str, "NO", data);
		get_wall_texture_path(&data->so, str, "SO", data);
		get_wall_texture_path(&data->we, str, "WE", data);
		get_wall_texture_path(&data->ea, str, "EA", data);
		get_RGB(data->floor, 'F', str, data);
		get_RGB(data->ceiling,'C', str, data);
		if (str[data->i] == '\n' && (str[data->i + 1] == ' ' || str[data->i + 1] == '1'))
			break ;
	}
}

void	make_map(char *str, t_data *data)
{
	get_element(str, data);
	if (!data->no || !data->so || !data->we || !data->ea)
		return (error(data, "Missing wall texture path\n"));
	if (data->floor[0] == -1 || data->floor[1] == -1 || data->floor[2] == -1)
		return (error(data, "Missing floor color\n"));
	if (data->ceiling[0] == -1 || data->ceiling[1] == -1 || data->ceiling[2] == -1)
		return (error(data, "Missing ceiling color\n"));
	int tot = data->i;
	while (str[data->i])
	{
		if (str[data->i] == '\n')
			data->height++;
		data->i++;
	}
	data->map = malloc(sizeof(char *) * (++data->height + 1));
	if (!data->map)
		return (ft_error(RED BOLD "Error" RESET ": Malloc failed\n"));
	for (int i = 0; i < data->height; i++)
	{
		int len = -1;
		while (str[++len + tot] && str[len + tot] != '\n');
		data->map[i] = malloc(sizeof(char) * (len + 1));
		if (!data->map[i])
		{
			ft_error(RED BOLD "Error" RESET ": Malloc failed\n");
			return (free_map(data, i - 1));
		}
		for (int j = 0; j < len; j++)
		{
			data->map[i][j] = str[tot + j];
			if (str[tot + j] == 'N' || str[tot + j] == 'S' || str[tot + j] == 'E' || str[tot + j] == 'W')
			{
				data->player.px = j;
				data->player.py = i;
				data->player.dir = str[tot + j];
				data->map[i][j] = '0';
				if (data->player_nb++ >= 1)
					return (data->height = i, error(data, "Only one player is allowed\n"));
			}
			else if (str[tot + j] == '1')
				data->map[i][j] = 'X';
			else if (str[tot + j] == '0')
				data->map[i][j] = 'F';
		}
		tot += len + 1;
		data->map[i][len] = '\0';
	}
	data->map[data->height] = NULL;
	if (data->player_nb == 0)
		error(data, "No player found\n");
}