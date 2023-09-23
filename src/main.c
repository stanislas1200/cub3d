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

void	init_player(t_data *data, t_game *game)
{
	if (data->player.dir == 'S')
		data->player.pa = 270;
	else if (data->player.dir == 'W')
		data->player.pa = 180;
	else if (data->player.dir == 'E')
		data->player.pa = 0;
	else if (data->player.dir == 'N')
		data->player.pa = 90;
	data->player.pdx = cos(data->player.pa) * 5;
	data->player.pdy = sin(data->player.pa) * 5;
	game->player = data->player;
	game->data = data;
}

int	main(int ac, char **av)
{
	t_data	data;
	t_game	game;
	init_data(&data);

	if (ac == 2)
		set_map_from_file(av[1], &data);
	else
		return (ft_error(RED BOLD "Error: " RESET "Invalid number of arguments\n"), 1);
	game.mlx_ptr = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "cub3D");
	game.img.image = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.image, &game.img.bits_per_pixel, &game.img.line_length,
								&game.img.endian);
	init_player(&data, &game);
	mlx_do_key_autorepeaton(game.mlx_ptr);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_hook, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
