#include "../include/cub3d.h"

// TEMPORARY
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	init_data(t_data *data)
{
	data->height = 0;
	data->player_nb = 0;
	data->map = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->floor[0] = -1;
	data->floor[1] = -1;
	data->floor[2] = -1;
	data->ceiling[0] = -1;
	data->ceiling[1] = -1;
	data->ceiling[2] = -1;
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data);
	if (ac == 2)
		set_map_from_file(av[1], &data);
	else
		ft_error(RED BOLD "Error: " RESET "Invalid number of arguments\n");
	return (0);
}
