#include "monty.h"

/**
 *push - Adds a new node with the specified integer value to the top.
 *@stack: A double pointer to the top of the stack.
 *@n: An unsigned integer representing the value to be added to the stack.
 *Return: nothing
 */

void push(stack_t **stack, unsigned int n)
{
	stack_t *new_node;

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = n;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
	{
		(*stack)->prev = new_node;
	}

	*stack = new_node;
}

/**
 *pall - Prints all elements in the stack.
 *@stack: A double pointer to the top of the stack.
 *@line_number: Line number of the opcode (unused in this function).
 *Return: nothing
 */

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	(void) line_number;
	if (current == NULL)
		return;
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 *free_stack - Frees the memory allocated for all nodes in the stack.
 *@stack: A double pointer to the top of the stack.
 *Return: nothing
 */

void free_stack(stack_t **stack)
{
	stack_t *current = *stack;
	stack_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	*stack = NULL;
}
