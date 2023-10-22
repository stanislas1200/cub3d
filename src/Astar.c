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
#include <stdlib.h> // Added for `abs` function

float **grid;

typedef struct s_anode {
	int isWall;
	float g;
	float h;
	float f;
	int x;
	int y;
	struct s_anode *neighbors[4]; // Changed to an array of pointers
	struct s_anode *previous;
} t_anode;

t_anode new_node(int x, int y) {
	t_anode node;
	node.x = x;
	node.y = y;
	node.isWall = 0;
	node.g = 0;
	node.previous = NULL;
	return node;
}

void add_arr(t_anode *arr[], t_anode *node) {
	// TODO: Implement the function to add an element to the array
}

int isLegal(t_data *data, int x, int y) {
	if (x >= 0 && y >= 0 && x < data->biggest_w && y < data->height) {
		return 1;
	} else {
		return 0;
	}
}

void assignNeighbors(t_data *data, t_anode node, t_anode **list) {
	int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Define the four cardinal directions

	for (int k = 0; k < 4; k++) {
		int dir[2] = {directions[k][0], directions[k][1]};
		int i = (int) node.x + dir[0];
		int j = (int) node.y + dir[1];

		if (isLegal(data, i, j)) {
			t_anode *n = &list[i][j]; // Changed to pointer
			if (!n->isWall) { // Changed to pointer access
				add_arr(node.neighbors, n);
			}
		}
	}
}

float Heuristic(t_anode a, t_anode b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void calculate(t_anode *node, t_anode end) { // Changed to pointer
	node->f = node->g + Heuristic(*node, end); // Changed to pointer access
}

int get_arr_size(t_anode *arr[]) {
	int i = -1;
	while (arr[++i]);
	return i;
}

void makePath(t_anode *n, t_anode *path[]) {
	t_anode *tmp = n;
	while (tmp->previous) {
		grid[tmp->x][tmp->y] = -1;
		add_arr(path, tmp->previous);
		tmp = tmp->previous;
	}
}

int Contains(t_anode *A[], t_anode e) {
	int contains = 0;
	for (int i = 0; i < get_arr_size(A); i++) {
		if (A[i]->x == e.x && A[i]->y == e.y) {
			contains = 1;
		}
	}
	return contains;
}

void find_path(t_anode *open[], t_anode *end, t_anode *path[], t_anode *closed) {
	while (open[0]) {
		int winner = 0;
		for (int i = 0; i < get_arr_size(open); i++) {
			if (open[i]->f < open[winner]->f) {
				winner = i;
			}
		}
		t_anode *current = open[winner];
		if (current->x == end->x && current->y == end->y) {
			makePath(current, path);
			printf("FIND ONE");
			return;
		}
		// remove_arr(open, winner); // Implement this function
		add_arr(closed, current);

		for (int i = 0; i < get_arr_size(current->neighbors); i++) {
			t_anode *n = current->neighbors[i]; // Changed to pointer
			if (Contains(closed, *n)) { // Changed to pointer access
				continue;
			}
			if (!Contains(open, *n)) { // Changed to pointer access
				add_arr(open, n); // Changed to pointer
			}
			float tgs = current->g + distance(current->x, current->y, n->x, n->y);
			if (tgs < n->g) { // Changed to pointer access
				n->g = tgs; // Changed to pointer access
			}
			n->previous = current; // Changed to pointer access
			n->g = tgs; // Changed to pointer access
			calculate(n, *end); // Changed to pointer access
		}
	}
}

void Astar(t_data *data, int start_i, int start_j, int end_i, int end_j) {
	data->biggest_w = 5; // dev
	t_anode **nodes;
	// Allocate memory for nodes and initialize grid and data if not already done
	nodes = malloc(data->height * sizeof(t_anode *));

	for (int i = 0; i < data->height; i++) {
		nodes[i] = (t_anode *)malloc(data->biggest_w * sizeof(t_anode));
	}

	// Initialize nodes and grid

	t_anode closed[100];
	t_anode *open[100];
	t_anode *path[100];

	t_anode start = new_node(start_i, start_j);
	t_anode end = new_node(end_i, end_j);

	// Populate nodes and assign neighbors
	for (int i = 0; i < data->height; i++) {
		for (int j = 0; j < data->biggest_w; j++) {
			assignNeighbors(data, nodes[i][j], nodes);
			calculate(&nodes[i][j], end); // Changed to pointer access
			printf( MAGENTA "%d: %d\n", i + j,  nodes[i][j].f);
		}
	}
	// find_path(open, &end, path, closed);
}
