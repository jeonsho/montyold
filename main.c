#define _GNU_SOURCE
#include "monty.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file;
    stack_t *stack = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read_line;
    char *opcode, *value_str;

    unsigned int line_number = 0;
    
    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while ((read_line = getline(&line, &len, file)) != -1) {
        line_number++;
        opcode = strtok(line, " $\t\n");
        if (opcode != NULL && opcode[0] != '#') {
            if (strcmp(opcode, "push") == 0) {
                value_str = strtok(NULL, " \t\n");
                if (value_str == NULL) {
                    fprintf(stderr, "L%u: usage: push integer\n", line_number);
                    exit(EXIT_FAILURE);
                }
                push(&stack, atoi(value_str));
            } else if (strcmp(opcode, "pall") == 0) {
                pall(&stack, line_number);
            } else {
                fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);
    free(line);

    /* Free any allocated memory and clean up */
    free_stack(&stack);

    return 0;
}

