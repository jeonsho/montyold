
#define _GNU_SOURCE
#include "monty.h"
#include <string.h>
#include <stdio.h>
/**
 *Validates whether a string is a valid integer.
 *@str: The string to be validated.
 *@line_number: Line number for error reporting.
 *Return:
 * - Returns 1 if the string is a valid integer.
 * - Returns 0 otherwise.
 */
int is_valid_integer(const char *str, unsigned int line_number)
{
	int converted;
	if (str == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	converted = atoi(str);
	if (converted == 0 && str[0] != '0')
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	return (1);
}
/**
 *main - Entry point for the Monty interpreter.
 *@argc: Number of command-line arguments.
 *@argv: Array of command-line argument strings
 *Return: 0 on successful execution.
 */

int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read_line;
	char *opcode, *value_str;
	unsigned int line_number = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read_line = getline(&line, &len, file)) != -1)
	{
		line_number++;
		opcode = strtok(line, " $\t\n");
		if (opcode != NULL && opcode[0] != '#')
		{
			if (strcmp(opcode, "push") == 0)
			{
				value_str = strtok(NULL, " \t\n");
				if (!is_valid_integer(value_str, line_number)) {
				 }
				if (value_str == NULL)
				{
					fprintf(stderr, "L%d: usage: push integer\n", line_number);
					exit(EXIT_FAILURE);
				}
				push(&stack, atoi(value_str));
			}
			else if (strcmp(opcode, "pall") == 0)
				pall(&stack, line_number);
			else if (strcmp(opcode, "pint") == 0)
				pint(&stack, line_number);
			else if (strcmp(opcode, "pop") == 0)
				pop(&stack, line_number);
			else if (strcmp(opcode, "swap") == 0) 
				swap(&stack, line_number);
			else
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
				exit(EXIT_FAILURE);
			}
		}
	}

	fclose(file);
	free(line);
	free_stack(&stack);

	return (0);
}
