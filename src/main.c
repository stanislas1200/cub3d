#include "../include/cub3d.h"

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

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
		set_map_from_file(av[1], &data);
	else
		ft_error(RED BOLD "Error: " RESET "Invalid number of arguments\n");
	return (0);
}