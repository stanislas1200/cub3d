#include "../include/cub3d.h"

void	print_map(t_data *data)
{
	
	printf(BOLD "--------MAP INFO--------\n" RESET);
	printf(BOLD "Player: " MAGENTA "%f %f %c\n" RESET, data->player.px, data->player.py, data->player.dir);
	printf(BOLD "NO: " MAGENTA "%s\n" RESET, data->no);
	printf(BOLD "SO: " MAGENTA "%s\n" RESET, data->so);
	printf(BOLD "WE: " MAGENTA "%s\n" RESET, data->we);
	printf(BOLD "EA: " MAGENTA "%s\n" RESET, data->ea);
	printf(BOLD "Floor: " MAGENTA "%d %d %d\t" RESET, data->floor[0], data->floor[1], data->floor[2]);
	printf(BOLD "Ceiling: " MAGENTA "%d %d %d\n" RESET, data->ceiling[0], data->ceiling[1], data->ceiling[2]);
	printf(BOLD "----------MAP----------\n" RESET);

	int i = -1;
	while (data->map[++i])
	{
		int j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'X')
				printf(GREEN "%c" RESET, data->map[i][j]);
			else if (data->map[i][j] == '0')
				printf(RED BOLD "%c" RESET, data->map[i][j]);
			else
			printf("%c", data->map[i][j]);
		}
		printf("\n");
	}
}