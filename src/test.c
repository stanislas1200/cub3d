#include "../include/cub3d.h"



void play(t_data *data) // DEV
{
	while (1)
	{
		printf("\033[2J");
		int i = -1;
		while(data->map[++i])
		{
			int j = -1;
			while (data->map[i][++j])
				if (i == data->player.py && j == data->player.px)
					printf(RED BOLD "%c" RESET, data->map[i][j]);
				else if (data->map[i][j] == 'X')
					printf(GREEN BOLD "%c" RESET, data->map[i][j]);
				else
					printf("%c", data->map[i][j]);
				printf("\n");
		}
		int c = getchar();
		if (c == 'q')
			break ;
		else if (c == 'z' && data->map[(int)data->player.py - 1][(int)data->player.px] != 'X')
			data->player.py--;
		else if (c == 's' && data->map[(int)data->player.py + 1][(int)data->player.px] != 'X')
			data->player.py++;
		else if (c == 'd' && data->map[(int)data->player.py][(int)data->player.px + 1] != 'X')
			data->player.px++;
		else if (c == 'a' && data->map[(int)data->player.py][(int)data->player.px - 1] != 'X')
			data->player.px--;
	}
}

void generate_random_map(t_data *data, int height, int width) {
	srand(time(NULL));
	data->map = malloc(sizeof(char *) * height);
    for (int i = 0; i < height; i++) {
		data->map[i] = malloc(sizeof(char) * width);
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                data->map[i][j] = 'X';
            } else {
                data->map[i][j] = rand() % 2 == 0 ? 'X' : 'F';
            }
        }
    }
    data->player.py = rand() % (height - 2) + 1;
    data->player.px = rand() % (width - 2) + 1;
    data->map[(int)data->player.py][(int)data->player.px] = 'P';
}

void	print_map(t_data *data)
{
	
	printf("Map:\n");
	printf("Player: %f %f\n", data->player.px, data->player.py);
	printf("Player dir: %c\n", data->player.dir);
	printf("NO: %s\n", data->no);
	printf("SO: %s\n", data->so);
	printf("WE: %s\n", data->we);
	printf("EA: %s\n", data->ea);
	printf("Floor: %d %d %d\n", data->floor[0], data->floor[1], data->floor[2]);
	printf("Ceiling: %d %d %d\n", data->ceiling[0], data->ceiling[1], data->ceiling[2]);

	int i = -1;
	while (data->map[++i])
	{
		int j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'X')
				printf(GREEN "%c" RESET, data->map[i][j]);
			else if (data->map[i][j] == 'P')
				printf(RED "%c" RESET, data->map[i][j]);
			else
			printf("%c", data->map[i][j]);
		}
		printf("\n");
	}
}