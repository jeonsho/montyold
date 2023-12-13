#include "monty.h"

/**
 *mul - Multiplies the second top element of the stack with the top element.
 *@stack: Double pointer to the beginning of the stack.
 *@line_number: Line number of the opcode in the Monty file.
 */
void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n *= (*stack)->n;

	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;

	free(temp);
}
