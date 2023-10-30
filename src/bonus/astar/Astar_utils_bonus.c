/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:25:56 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 10:28:30 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

int	is_legal(t_data *data, int x, int y)
{
	return (x >= 0 && y >= 0 && x < data->biggest_w \
	&& y < data->height && data->a->nodes[y][x] == NULL);
}

void	calculate(t_anode *node, t_anode *end)
{
	float	h;

	h = abs(node->x - end->x) + abs(node->y - end->y);
	node->f = node->g + h;
}

int	get_lowest_f_node(t_astar *a)
{
	int	winner;
	int	i;

	winner = 0;
	i = 0;
	while (i < a->open_count)
	{
		if (a->open[i]->f < a->open[winner]->f)
			winner = i;
		i++;
	}
	return (winner);
}

int	is_close(t_astar *a, t_anode	*node)
{
	int	i;

	i = 0;
	while (i < a->closed_count)
	{
		if (a->closed[i] == node)
			return (1);
		i++;
	}
	return (0);
}

int	is_open(t_astar *a, t_anode	*node)
{
	int	i;

	i = 0;
	while (i < a->open_count)
	{
		if (a->open[i] == node)
			return (1);
		i++;
	}
	return (0);
}
