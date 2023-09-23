#include "../include/cub3d.h"

void	cleanup_stack(t_data *data)
{
	t_node	*temp;

	while (data->stack != NULL)
	{
		temp = data->stack;
		data->stack = data->stack->next;
		free(temp);
	}
	data->stack = NULL;
}

void	push(t_node	**top, int x, int y)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return ;
	node->x = x;
	node->y = y;
	node->next = *top;
	*top = node;
}

void	pop(t_node	**top)
{
	t_node	*temp;

	if (*top == NULL)
		return ;
	temp = *top;
	*top = (*top)->next;
	free(temp);
}
