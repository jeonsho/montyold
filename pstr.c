#include "monty.h"

/**
 *pstr - Print string starting at the top of the stack.
 *@stack: Double pointer to the top of the stack.
 *@line_number: Line number in the Monty bytecode file.
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	while (current != NULL && current->n != 0 && isprint(current->n))
	{
		putchar(current->n);
		current = current->next;
	}

	putchar('\n');
	(void) line_number;
}
