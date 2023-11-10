/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:14:10 by sgodin            #+#    #+#             */
/*   Updated: 2023/11/10 14:08:35 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

int		is_legal(t_data *data, int x, int y);
void	calculate(t_anode *node, t_anode *end);
int		get_lowest_f_node(t_astar *a);
int		is_close(t_astar *a, t_anode	*node);
int		is_open(t_astar *a, t_anode	*node);

void	make_path(t_anode *node, t_astar *a)
{
	a->path_count = 0;
	while (node->previous)
	{
		a->path[a->path_count++] = copy_node(node);
		if (!a->path[a->path_count - 1])
			return (free_list(a->path, a->path_count));
		node = node->previous;
	}
	a->path[a->path_count++] = copy_node(node);
	if (!a->path[a->path_count - 1])
		return (free_list(a->path, a->path_count));
}

int	do_neighbor(t_astar *a, t_anode *neighbor)
{
	if (is_close(a, neighbor))
	{
		free(neighbor);
		neighbor = NULL;
		return (0);
	}
	if (a->current->g + 1 < neighbor->g || !is_open(a, neighbor))
	{
		neighbor->g = a->current->g + 1;
		calculate(neighbor, a->end);
		neighbor->previous = a->current;
		if (!is_open(a, neighbor))
			a->open[a->open_count++] = neighbor;
	}
	return (1);
}

int	check_neighbor(t_data *data, t_astar *a, t_anode *neighbor)
{
	int		new_x;
	int		new_y;

	while (++data->i <= 1)
	{
		data->j = -2;
		while (++data->j <= 1)
		{
			if (data->i == 0 && data->j == 0)
				continue ;
			if (abs(data->i) + abs(data->j) == 2)
				continue ;
			new_x = a->current->x + data->i;
			new_y = a->current->y + data->j;
			if (is_legal(data, new_x, new_y))
			{
				neighbor = new_node(new_x, new_y);
				if (!neighbor)
					return (0);
				if (!do_neighbor(a, neighbor))
					continue ;
			}
		}
	}
	return (1);
}

void	find_path(t_data *data, t_astar *a)
{
	int		winner;
	t_anode	*neighbor;

	neighbor = NULL;
	while (a->open_count > 0 && a->open_count < 1000 && a->closed_count < 1000)
	{
		winner = get_lowest_f_node(a);
		a->current = a->open[winner];
		if (a->current->x == a->end->x && a->current->y == a->end->y)
			return (make_path(a->current, a));
		remove_arr(a->open, a->current, a->open_count--);
		a->closed[a->closed_count++] = a->current;
		data->i = -2;
		if (!check_neighbor(data, a, neighbor))
			return ;
	}
	a->path_count = 0;
}

void	astar(t_data *data, t_astar *a, int start[], int end[])
{
	init_astar(a);
	a->start = new_node(start[0], start[1]);
	a->end = new_node(end[0], end[1]);
	if (!a->start || !a->end)
		return (free(a->start), free(a->end));
	a->open[a->open_count++] = a->start;
	find_path(data, a);
	free(a->end);
	free_list(a->open, a->open_count);
	free_list(a->closed, a->closed_count);
}
