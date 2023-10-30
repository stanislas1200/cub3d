/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:52:26 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/30 10:28:30 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

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

void	setup_astar_wall(t_data *d, t_astar *a)
{
	d->i = -1;
	while (++d->i < a->size)
	{
		a->nodes[d->i] = malloc(sizeof(t_anode *) * a->size);
		if (!a->nodes[d->i])
			return (e(d, "Malloc error\n" RESET, NULL));
		d->j = -1;
		while (++d->j < a->size)
			a->nodes[d->i][d->j] = NULL;
	}
	d->i = -1;
	while (++d->i < a->size)
	{
		d->j = -1;
		while (++d->j < a->size)
		{
			if (d->i >= 0 && d->i < d->height && d->j >= 0 && \
			d->j < ft_strlen(d->map[d->i]) && d->map[d->i][d->j] == 'X')
			{
				a->nodes[d->i][d->j] = new_node(a, d->i, d->j);
				if (!a->nodes[d->i][d->j])
					return (e(d, "Malloc error\n" RESET, NULL));
			}
		}
	}
}

void	setup_astar(t_data *d, t_astar *a)
{
	if (d->height > d->biggest_w)
		a->size = d->height;
	else
		a->size = d->biggest_w;
	a->open = malloc(sizeof(t_anode) * a->size * a->size * a->size);
	a->closed = malloc(sizeof(t_anode) * a->size * a->size * a->size);
	a->path = malloc(sizeof(t_anode) * a->size * a->size * a->size);
	if (!a->open || !a->closed || !a->path)
		return (e(d, "Malloc error\n" RESET, NULL));
	a->nodes = malloc(sizeof(t_anode **) * a->size);
	if (!a->nodes)
		return (e(d, "Malloc error\n" RESET, NULL));
	d->i = -1;
	while (++d->i < a->size)
		a->nodes[d->i] = NULL;
	setup_astar_wall(d, a);
}

void	init_astar(t_data *data, t_astar *a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	a->closed_count = 0;
	a->open_count = 0;
	a->path_count = 0;
	while (i < a->size * a->size * a->size)
	{
		a->open[i] = NULL;
		a->closed[i] = NULL;
		a->path[i] = NULL;
		i++;
	}
}
