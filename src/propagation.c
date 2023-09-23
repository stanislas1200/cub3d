#include "../include/cub3d.h"

void	pg_helper(int i, int j, int f, t_data *data)
{
	int		x;
	int		y;

	x = data->stack->x;
	y = data->stack->y;
	pop(&data->stack);
	if (data->map[y][x] == 'F' || data->map[y][x] == 'P')
	{
		data->map[y][x] = f + '0';
		data->i = -2;
		while (++data->i < 2)
		{
			data->j = -2;
			while (++data->j < 2)
				if ((data->i == 0 || data->j == 0) && \
				data->map[data->i + j][data->j + i])
					push(&data->stack, x + data->j, y + data->i);
		}
	}
}

void	pg(int x, int y, int f, t_data *data)
{
	data->stack = NULL;
	push(&data->stack, x, y);
	while (data->stack)
		pg_helper(x, y, f, data);
	cleanup_stack(data);
}
