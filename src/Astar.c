/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:14:10 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/25 13:54:56 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_anode *new_node(t_astar *a, int x, int y) {
	t_anode *node;
	// if (a->nodes[x][y] != NULL) { // NEVER HAPPENS ?
	// 	printf("node already exist\n");
	// 	return a->nodes[x][y];
	// }
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

int is_in(t_astar *a, int y, int x) {
	for (int i = 0; i < a->pathCount; i++) {
		if (a->path[i]->x == x && a->path[i]->y == y)
			return 1;
	}
	return 0;
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
void print_path(t_anode **path);

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
	print_path(a->path);
}

void find_path(t_data *data, t_astar *a) {
	while (a->openCount > 0 && a->openCount < 5000) { //limited
		int winner = get_lowest_f_node(a);
		a->current = a->open[winner];
		if (a->current->x == a->end->x && a->current->y == a->end->y) { // END
			make_path(a->current, a);
			printf("FIND ONE %d, %d\n", a->current->x, a->current->y);
			printf("player : %d, %d\n", (int)data->player.px >> 6, (int)data->player.py >> 6);
			return;
		}
		remove_arr(a->open, a->current, a->openCount--);
		add_arr(a->closed, a->current, a->closedCount++);

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) continue;
				if (abs(i) + abs(j) == 2) continue; // Skip diagonals
				int new_x = a->current->x + i;
				int new_y = a->current->y + j;
				if (isLegal(data, new_x, new_y) && a->nodes[new_y][new_x] == NULL)
				{
					t_anode* neighbor = new_node(a, new_x, new_y);
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
	a->pathCount = 0;
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

void print_astar_map(t_data * data) {
	printf("\x1b[H\x1b[2J");
	for (int i = 0; i < data->height; i++) {
		for (int j = 0; j < ft_strlen(data->map[i]); j++) {
			if (data->map[i][j] == 'X')
				printf(RED);
			else
			{
				if (i == (int)data->player.py >> 6 && j == (int)data->player.px >> 6)
					printf(GREEN);
				else
					printf(BOLD);
			}
			printf("0" RESET);
		}
		printf(" %d\n", i);
	}
	for (int i = 0; i < data->a->size; i++) {
		for (int j = 0; j < data->a->size; j++) {
			if (data->a->nodes[i][j])
				printf(RED);
			else
			{
				if (i > 0 && i < data->height && j > 0 && j < ft_strlen(data->map[i]) && i == (int)data->player.py >> 6 && j == (int)data->player.px >> 6)
					printf(GREEN);
				else if (data->a->path && is_in(data->a, i, j))
				{
						printf(MAGENTA);
				}
				else
					printf(RESET BOLD);
			}
			printf("0" RESET);
		}
		printf(" %d\n", i);
	}
}

void setup_astar(t_data *data, t_astar *a)
{
	a->size = data->height > data->biggest_w ? data->height : data->biggest_w; // DEV CHECK SIZE!!!
	a->open = malloc(sizeof(t_anode) * a->size * a->size * a->size);
	a->closed = malloc(sizeof(t_anode) * a->size * a->size * a->size);
	a->path = malloc(sizeof(t_anode) * a->size * a->size * a->size);
	a->nodes = malloc(sizeof(t_anode **) * a->size);
	if (!a->open || !a->closed || !a->path || !a->nodes)
	{
		printf("malloc error\n");
		exit(1); // HANDLE ERROR // FREE
	}
	for (int i = 0; i < a->size; i++) {
		a->nodes[i] = malloc(sizeof(t_anode *) * a->size);
		if (!a->nodes[i]) {
			printf("malloc error\n");
			exit(1); // HANDLE ERROR // FREE
		}
	}
	// Initialize the grid (set NULL for walkable cells)
	for (int i = 0; i < a->size; i++) {
		for (int j = 0; j < a->size; j++) {
			// if (i > 0 && i < data->height && j > 0 && j < ft_strlen(data->map[i]) && data->map[i][j] == 'X')
			//     a->nodes[i][j] = new_node(a, i, j);
			// else
				a->nodes[i][j] = NULL;
		}
	}
	for (int i = 0; i < a->size; i++) {
		for (int j = 0; j < a->size; j++) {
			if (i >= 0 && i < data->height && j >= 0 && j < ft_strlen(data->map[i]) && data->map[i][j] == 'X')
			{
				a->nodes[i][j] = new_node(a, i, j);
			}
			else
				a->nodes[i][j] = NULL;
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
	printf(GREEN "INITED!\n" RESET);
}


void Astar(t_data *data, t_astar *a, int start_x, int start_y, int end_x, int end_y)
{
	// return;
	init_astar(data, a);
	a->start = new_node(a, start_x, start_y);
	a->end = new_node(a, end_x, end_y);
	if (!a->start || !a->end) {
		printf("malloc error\n");
		return ; // HANDLE ERROR // FREE
	}

	add_arr(a->open, a->start, a->openCount++);
	find_path(data, a);
	free(a->end);

	// // free
	// free_nodes(data, a);
	free_list(a->open, a->openCount);
	free_list(a->closed, a->closedCount);
	// // free(a->open);
	// // free(a->closed);
	// free_list(a->path, a->pathCount);
	// // free(a->path);
	// // for (int i = 0; i < data->height; i++) {
	// // 	free(a->nodes[i]);
	// // }
	// // free(a->nodes);
	// init_astar( data, a);
	if (a->path && a->pathCount > 0)
		print_astar_map(data);
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

// 	Astar(&data, &a, 1, 1, 4, 4);
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