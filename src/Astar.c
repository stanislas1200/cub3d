/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:14:10 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/22 17:28:36 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_anode *new_node(t_astar *a, int x, int y) {
	t_anode *node;
	if (a->nodes[x][y] != NULL) { // NEVER HAPPENS ?
		printf("node already exist\n");
		return a->nodes[x][y];
	}
	node = malloc(sizeof(t_anode));
	if (!node) {
		printf("malloc error\n"); // CHANGE
		return (NULL);
	}
	node->x = x;
	node->y = y;
	node->g = 0;
	node->f	= 0;
	node->previous = NULL;
	return node;
}

void add_arr(t_anode **arr, t_anode *node, int i) {
	arr[i] = node;
}

int isLegal(t_data *data, int x, int y) {
	return (x >= 0 && y >= 0 && x < data->biggest_w && y < data->height);
}

float Heuristic(t_anode a, t_anode b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void calculate(t_anode *node, t_anode *end) { // Changed to pointer
	node->f = node->g + Heuristic(*node, *end); // Changed to pointer access
}

void remove_arr(t_anode *arr[], t_anode *node, int size) {
	for (int i = 0; i <= size; i++) {
		if (arr[i] == node) {
			arr[i] = arr[size - 1];
			size--;
			break;
		}
	}
}

int get_lowest_f_node(t_astar *a) {
	int winner = 0;
	for (int i = 0; i < a->openCount; i++) {
		if (a->open[i]->f < a->open[winner]->f) {
			winner = i;
		}
	}
	return winner;
}

int is_close(t_astar *a, t_anode* node) {
	for (int i = 0; i < a->closedCount; i++) {
		if (a->closed[i] == node)
			return 1;
	}
	return 0;
}

int is_open(t_astar *a, t_anode* node) {
	for (int i = 0; i < a->openCount; i++) {
		if (a->open[i] == node)
			return 1;
	}
	return 0;
}

void print_path(t_anode **path)
{
	int i = 0;
	while (path[i]) {
		printf("x: %d, y: %d\n", path[i]->x, path[i]->y);
		i++;
	}
}

t_anode *copy_node(t_anode *node) {
	t_anode *new_node = malloc(sizeof(t_anode));
	if (!new_node) {
		printf("malloc error\n");
		return (NULL);
	}
	new_node->x = node->x;
	new_node->y = node->y;
	// new_node->g = node->g; // No need for path
	// new_node->f = node->f;
	// new_node->previous = node->previous;
	return new_node;
}

void make_path(t_anode *node, t_astar *a) {
	a->pathCount = 0;
	while (node->previous) {
		a->path[a->pathCount++] = copy_node(node);
		if (!a->path[a->pathCount - 1]) {
			printf("malloc error\n");
			return ; // HANDLE ERROR // FREE path or move to here ?
		}
		node = node->previous;
	}
	a->path[a->pathCount++] = copy_node(node);
}

void find_path(t_data *data, t_astar *a) {
	while (a->openCount > 0) {
		int winner = get_lowest_f_node(a);
		a->current = a->open[winner];
		
		if (a->current->x == a->end->x && a->current->y == a->end->y) { // END
			make_path(a->current, a);
			printf("FIND ONE");
			return;
		}
		remove_arr(a->open, a->current, a->openCount--);
		add_arr(a->closed, a->current, a->closedCount++);

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) continue;
				if (abs(i) + abs(j) == 2) continue; // Skip diagonals
				int newRow = a->current->x + i;
				int newCol = a->current->y + j;

				if (isLegal(data, newRow, newCol) && a->nodes[newRow][newCol] == NULL) {
					t_anode* neighbor = new_node(a, newRow, newCol);
					if (!neighbor) {
						printf("malloc error\n");
						return ; // HANDLE ERROR // Make path to here or restart ?
					}

					if (is_close(a, neighbor)) {
						free(neighbor);
						neighbor = NULL;
						continue;
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
}

void Astar(t_data *data, t_astar *a, int start_i, int start_j, int end_i, int end_j)
{
	a->start = new_node(a, start_i, start_j);
	a->end = new_node(a, end_i, end_j);
	if (!a->start || !a->end) {
		printf("malloc error\n");
		return ; // HANDLE ERROR // FREE
	}

	add_arr(a->open, a->start, a->openCount++);
	find_path(data, a);
	free(a->end);
}

void free_nodes(t_data *data, t_astar *a) {
	for (int i = 0; i < data->height; i++) {
		for (int j = 0; j < data->biggest_w; j++) {
			if (a->nodes[i][j] != NULL) {
				free(a->nodes[i][j]);
				a->nodes[i][j] = NULL;
			}
		}
	}
}

void free_list(t_anode *arr[], int size) {
	for (int i = 0; i < size; i++) {
		if (arr[i] != NULL) {
			free(arr[i]);
			arr[i] = NULL;
		}
	}
}

void setup_astar(t_data *data, t_astar *a)
{
	a->open = malloc(sizeof(t_anode) * data->height * data->biggest_w);
	a->closed = malloc(sizeof(t_anode) * data->height * data->biggest_w);
	a->path = malloc(sizeof(t_anode) * data->height * data->biggest_w);
	a->nodes = malloc(sizeof(t_anode **) * data->height);
	if (!a->open || !a->closed || !a->path || !a->nodes) {
		printf("malloc error\n");
		exit(1); // HANDLE ERROR // FREE
	}
	for (int i = 0; i < data->height; i++) {
		a->nodes[i] = malloc(sizeof(t_anode *) * data->biggest_w);
		if (!a->nodes[i]) {
			printf("malloc error\n");
			exit(1); // HANDLE ERROR // FREE
		}
	}
}

void init_astar(t_data *data, t_astar *a)
{
	a->closedCount = 0;
	a->openCount = 0;
	a->pathCount = 0;

	for (int i = 0; i < data->height * data->biggest_w; i++) {
		a->open[i] = NULL;
		a->closed[i] = NULL;
		a->path[i] = NULL;
	}
	// Initialize the grid (set NULL for walkable cells)
	for (int i = 0; i < data->height; i++) {
		for (int j = 0; j < data->biggest_w; j++) {
			a->nodes[i][j] = NULL;
		}
	}
}


// int main()
// {
// 	t_data data;
// 	data.height = 5;
// 	data.biggest_w = 5;
// 	t_astar a;
// 	setup_astar(&data, &a);
// 	init_astar(&data, &a);
	
// 	a.nodes[0][1] = new_node(&a, 0, 1); // Example obstacle at row 1, col 2
// 	// a.nodes[1][0] = new_node(&a, 1, 0); // Example obstacle at row 1, col 2
// 	a.nodes[2][2] = new_node(&a, 2, 2); // Example obstacle at row 2, col 2  
// 	a.nodes[2][0] = new_node(&a, 2, 0); // Example obstacle at row 2, col 2  
// 	a.nodes[4][1] = new_node(&a, 4, 1); // Example obstacle at row 2, col 2  

// 	Astar(&data, &a, 0, 0, 4, 4);
// 	// free
// 	free_nodes(&data, &a);
// 	free_list(a.open, a.openCount);
// 	free_list(a.closed, a.closedCount);
// 	free(a.open);
// 	free(a.closed);
// 	print_path(a.path);
// 	free_list(a.path, a.pathCount);
// 	free(a.path);
// 	for (int i = 0; i < data.height; i++) {
// 		free(a.nodes[i]);
// 	}
// 	free(a.nodes);
// 	return 0;
// }