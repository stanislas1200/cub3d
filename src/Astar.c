/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:14:10 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/28 18:54:42 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_anode	*new_node(t_astar *a, int x, int y)
{
	t_anode	*node;

	node = malloc(sizeof(t_anode));
	if (!node)
		return (printf(RED "Node faill\n" RESET), NULL);
	node->x = x;
	node->y = y;
	node->g = 0;
	node->f = 0;
	node->previous = NULL;
	return (node);
}

void	add_arr(t_anode **arr, t_anode *node, int i)
{
	arr[i] = node;
}

int	is_legal(t_data *data, int x, int y)
{
	return (x >= 0 && y >= 0 && x < data->biggest_w && y < data->height);
}

float	heuristic(t_anode a, t_anode b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y));
}

void	calculate(t_anode *node, t_anode *end)
{
	node->f = node->g + heuristic(*node, *end);
}

void	remove_arr(t_anode *arr[], t_anode *node, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		if (arr[i] == node)
		{
			arr[i] = arr[size - 1];
			size--;
			break ;
		}
		i++;
	}
}

int	get_lowest_f_node(t_astar *a)
{
	int	winner;
	int	i;

	winner = 0;
	i = 0;
	while (i < a->openCount)
	{
		if (a->open[i]->f < a->open[winner]->f)
			winner = i;
		i++;
	}
	return (winner);
}

int	is_close(t_astar *a, t_anode* node)
{
	int	i;

	i = 0;
	while (i < a->closedCount)
	{
		if (a->closed[i] == node)
			return (1);
		i++;
	}
	return (0);
}

int	is_open(t_astar *a, t_anode* node)
{
	int	i;

	i = 0;
	while (i < a->openCount)
	{
		if (a->open[i] == node)
			return (1);
		i++;
	}
	return (0);
}

int	is_in(t_astar *a, int y, int x)
{
	int	i;

	i = 0;
	while (i < a->pathCount)
	{
		if (a->path[i]->x == x && a->path[i]->y == y)
			return (1);
		i++;
	}
	return (0);
}

t_anode	*copy_node(t_anode *node)
{
	t_anode	*new_node;

	new_node = malloc(sizeof(t_anode));
	if (!new_node)
		return (printf(RED "Node faill\n" RESET), NULL);
	new_node->x = node->x;
	new_node->y = node->y;
	return (new_node);
}

void	make_path(t_anode *node, t_astar *a)
{
	a->pathCount = 0;
	while (node->previous)
	{
		a->path[a->pathCount++] = copy_node(node);
		if (!a->path[a->pathCount - 1])
			return (free_list(a->path, a->pathCount));
		node = node->previous;
	}
	a->path[a->pathCount++] = copy_node(node);
	if (!a->path[a->pathCount - 1])
		return (free_list(a->path, a->pathCount));
}

void	find_path(t_data *data, t_astar *a)
{
	while (a->openCount > 0 && a->openCount < 5000)
	{
		int winner = get_lowest_f_node(a);
		a->current = a->open[winner];
		if (a->current->x == a->end->x && a->current->y == a->end->y)
			return (make_path(a->current, a));
		remove_arr(a->open, a->current, a->openCount--);
		add_arr(a->closed, a->current, a->closedCount++);

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) continue;
				if (abs(i) + abs(j) == 2) continue; // Skip diagonals
				int new_x = a->current->x + i;
				int new_y = a->current->y + j;
				if (is_legal(data, new_x, new_y) && a->nodes[new_y][new_x] == NULL)
				{
					t_anode* neighbor = new_node(a, new_x, new_y);

					if (!neighbor)
						return ;
					if (is_close(a, neighbor))
					{
						free(neighbor);
						neighbor = NULL;
						continue ;
					}

					int tentativeG = a->current->g + 1;

					if (tentativeG < neighbor->g || !is_open(a, neighbor)) {
						neighbor->g = tentativeG;
						calculate(neighbor, a->end);
						neighbor->previous = a->current;

						if (!is_open(a, neighbor)) {
							add_arr(a->open, neighbor, a->openCount++);
						}
					}
				}
			}
		}
	}
	printf("NO PATH FOUND\n");
	a->pathCount = 0;
}


void	free_nodes(t_data *data, t_astar *a)
{
	if (!a->nodes)
		return ;
	for (int i = 0; i < data->a->size; i++) {
		for (int j = 0; j < data->a->size; j++) {
			if (a->nodes[i] && a->nodes[i][j] != NULL)
			{
				free(a->nodes[i][j]);
				a->nodes[i][j] = NULL;
			}
		}
	}
	for (int i = 0; i < data->a->size; i++)
	{
		free(a->nodes[i]);
		a->nodes[i] = NULL;
	}
}

void	free_list(t_anode *arr[], int size)
{
	for (int i = 0; i < size; i++) {
		if (arr[i] != NULL) {
			free(arr[i]);
			arr[i] = NULL;
		}
	}
}

void setup_astar(t_data *data, t_astar *a)
{
	a->size = data->height > data->biggest_w ? data->height : data->biggest_w; // DEV CHECK SIZE!!!
	a->open = malloc(sizeof(t_anode) * a->size * a->size * a->size);
	a->closed = malloc(sizeof(t_anode) * a->size * a->size * a->size);
	a->path = malloc(sizeof(t_anode) * a->size * a->size * a->size);
	if (!a->open || !a->closed || !a->path)
		return (e(data, "Malloc error\n" RESET, NULL));
	a->nodes = malloc(sizeof(t_anode **) * a->size);
	if (!a->nodes)
		return (e(data, "Malloc error\n" RESET, NULL));
	for (int i = 0; i < a->size; i++) {
		a->nodes[i] = NULL;
	}
	for (int i = 0; i < a->size; i++) {
		a->nodes[i] = malloc(sizeof(t_anode *) * a->size);
		if (!a->nodes[i])
			return (e(data, "Malloc error\n" RESET, NULL));
		for (int j = 0; j < a->size; j++) { 
			a->nodes[i][j] = NULL;
		}
	}
	for (int i = 0; i < a->size; i++) {
		for (int j = 0; j < a->size; j++) {
			if (i >= 0 && i < data->height && j >= 0 && j < ft_strlen(data->map[i]) && data->map[i][j] == 'X')
			{
				a->nodes[i][j] = new_node(a, i, j);
				if (!a->nodes[i][j])
					return (e(data, "Malloc error\n" RESET, NULL));
			}
		}
	}
	printf(GREEN "SETUP DONE : %d\n", a->size);
}

void init_astar(t_data *data, t_astar *a)
{
	a->closedCount = 0;
	a->openCount = 0;
	a->pathCount = 0;

	for (int i = 0; i < a->size * a->size * a->size; i++) {
		a->open[i] = NULL;
		a->closed[i] = NULL;
		a->path[i] = NULL;
	}
}


void Astar(t_data *data, t_astar *a, int start_x, int start_y, int end_x, int end_y)
{
	init_astar(data, a);
	a->start = new_node(a, start_x, start_y);
	a->end = new_node(a, end_x, end_y);
	if (!a->start || !a->end)
		return (free(a->start), free(a->end));

	add_arr(a->open, a->start, a->openCount++);
	find_path(data, a);
	free(a->end);

	free_list(a->open, a->openCount);
	free_list(a->closed, a->closedCount);
}