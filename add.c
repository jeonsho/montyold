#include "monty.h"

/**
 *add - Adds the top two elements of the stack.
 *@stack: A pointer to the top of the stack.
 *@line_number: The line number in the Monty bytecode file.
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *first, *second;
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	first = *stack;
	second = first->next;

	second->n += first->n;
	*stack = second;
	if (second->next != NULL)
	{
		second->next->prev = NULL;
	}

	free(first);
}
