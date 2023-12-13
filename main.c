#define _GNU_SOURCE
#include "monty.h"

/**
 *is_valid_integer - Validates whether a string is a valid integer.
 *@str: The string to be validated.
 *@line_number: Line number for error reporting.
 *
 *Return:
 *  - Returns 1 if the string is a valid integer.
 *  - Returns 0 otherwise.
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
 *process_instruction - Processes an instruction based on opcode.
 *@stack: Pointer to the stack.
 *@opcode: The opcode to be processed.
 *@value_str: String representation of a value (for push instruction).
 *@line_number: Line number of the opcode.
 */
void process_instruction(stack_t **stack,
		const char *opcode, char *value_str, unsigned int line_number)
{
	if (strcmp(opcode, "push") == 0)
	{
		is_valid_integer(value_str, line_number);
		if (value_str == NULL)
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}

		push(stack, atoi(value_str));
	}
	else if (strcmp(opcode, "pall") == 0)
		pall(stack, line_number);
	else if (strcmp(opcode, "pint") == 0)
		pint(stack, line_number);
	else if (strcmp(opcode, "pop") == 0)
		pop(stack, line_number);
	else if (strcmp(opcode, "swap") == 0)
		swap(stack, line_number);
	else if (strcmp(opcode, "add") == 0)
		add(stack, line_number);
	else if (strcmp(opcode, "nop") == 0)
		nop(stack, line_number);
	else if (strcmp(opcode, "sub") == 0)
		sub(stack, line_number);
	else if (strcmp(opcode, "div") == 0)
		my_div(stack, line_number);
	else if (strcmp(opcode, "mul") == 0)
		mul(stack, line_number);
	else if (strcmp(opcode, "mod") == 0)
		mod(stack, line_number);
	else if (strcmp(opcode, "pchar") == 0)
		pchar(stack, line_number);
	else
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
		exit(EXIT_FAILURE);
	}
}

/**
 *process_file - Reads and processes the Monty bytecode file.
 *@file: Pointer to the opened file.
 *@stack: Pointer to the stack.
 */
void process_file(FILE *file, stack_t **stack)
{
	char *line = NULL,  *opcode, *value_str;
	size_t len = 0;
	ssize_t read_line;
	unsigned int line_number = 0;

	while ((read_line = getline(&line, &len, file)) != -1)
	{
		line_number++;
		opcode = strtok(line, " $\t\n");
		if (opcode != NULL && opcode[0] != '#')
		{
			value_str = strtok(NULL, " ");
			process_instruction(stack, opcode, value_str, line_number);
		}
	}

	free(line);
}

/**
 *main - Entry point for the Monty interpreter.
 *@argc: Number of command-line arguments.
 *@argv: Array of command-line argument strings.
 *
 *Return: 0 on successful execution.
 */
int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack = NULL;

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

	process_file(file, &stack);

	fclose(file);
	free_stack(&stack);

	return (0);
}
