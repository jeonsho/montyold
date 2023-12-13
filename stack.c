#include "monty.h"

void push(stack_t **stack, unsigned int n) {
	 stack_t *new_node;
    /* Check if n is a valid integer */
   /* if (!isdigit(n)) {
        fprintf(stderr, "L%u: usage: push integer\n", n);
        exit(EXIT_FAILURE);
    }*/

    /* Implement push logic */
    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = n;
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack != NULL) {
        (*stack)->prev = new_node;
    }

    *stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number) {
    /* Implement pall logic */
    stack_t *current = *stack;
    (void)line_number;

    while (current != NULL) {
        printf("%d\n", current->n);
        current = current->next;
    }
}

void free_stack(stack_t **stack) {
    /* Implement memory deallocation logic */
    stack_t *current = *stack;
    stack_t *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *stack = NULL;
}

