/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:38:23 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/29 12:57:54 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	free_nodes(t_data *data, t_astar *a)
{
	int	i;
	int	j;

	if (!a->nodes)
		return ;
	i = -1;
	while (++i < data->a->size)
	{
		j = -1;
		while (++j < data->a->size)
		{
			if (a->nodes[i] && a->nodes[i][j] != NULL)
			{
				free(a->nodes[i][j]);
				a->nodes[i][j] = NULL;
			}
		}
	}
	i = -1;
	while (++i < data->a->size)
	{
		free(a->nodes[i]);
		a->nodes[i] = NULL;
	}
}

void	free_list(t_anode *arr[], int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (arr[i] != NULL)
		{
			free(arr[i]);
			arr[i] = NULL;
		}
	}
}
