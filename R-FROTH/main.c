#include "token.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Define stack structure
#define STACK_SIZE 100
int stack[STACK_SIZE];
int stack_pointer = 0;

// Function to push a value onto the stack
void push(int value) {
    if (stack_pointer < STACK_SIZE) {
        stack[stack_pointer++] = value;
    } else {
        printf("Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

// Function to pop a value from the stack
int pop() {
    if (stack_pointer > 0) {
        return stack[--stack_pointer];
    } else {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}


// Maximum number of variables
#define MAX_VARIABLES 100

// Structure to hold variables
typedef struct {
    char name[20];  // Assuming maximum variable name length of 20 characters
    int value;
} Variable;

// Array to store variables
Variable variables[MAX_VARIABLES];

// Number of variables currently defined
int num_variables = 0;

// Function to find a variable by name
int find_variable(const char* name) {
    for (int i = 0; i < num_variables; ++i) {
        if (strcmp(variables[i].name, name) == 0) {
            return i;
        }
    }
    return -1;  // Variable not found
}

// Function to execute a conditional operation token
void execute_conditional_token(token_t *token) {
    if (token->type == OPERATOR) {
        // Handle comparison operators
        // For simplicity, let's assume we only support "<" for now
        if (strcmp(token->text, "<") == 0) {
            int operand2 = pop();
            int operand1 = pop();
            push(operand1 < operand2); // Push true (1) or false (0) based on comparison result
        }
    } else if (token->type == SYMBOL) {
        // Handle conditional branching tokens (IF, ELSE, THEN)
        // For simplicity, let's skip implementation for now
    }
}

int main() {
    char input[1024];  // Assuming a maximum input length of 1024 characters

    // Read input from standard input
    printf("Enter R-FORTH program:\n");
    fgets(input, sizeof(input), stdin);

    // Tokenize the input
     char *token_str = strtok(input, " ");
    while (token_str != NULL) {

        // Create token
        token_t *new_token = create_token(WORD, token_str);

         // Classify each token based on basic checks
        token_type_t type;
        if (isdigit(token_str[0]) || (token_str[0] == '-' && isdigit(token_str[1]))) {
            new_token->type = NUMBER;
        } else if (strchr("+-*/", token_str[0]) != NULL) {
            new_token->type = OPERATOR;
        } else if (strcmp(token_str, "CONSTANT") == 0) {
            new_token->type = CONSTANT;
        } else if (strcmp(token_str, "VARIABLE") == 0) {
            new_token->type = VARIABLE;
        } else if (strchr(":;", token_str[0]) != NULL) {
            new_token->type = SYMBOL;
        } else {
            new_token->type = WORD;
        }

        // Execute token
        if (new_token->type == CONSTANT || new_token->type == VARIABLE || new_token->type == OPERATOR || new_token->type == SYMBOL) {
            execute_conditional_token(new_token);
        } else {
            // Display the token (for now)
            printf("Type: %d, Text: %s\n", new_token->type, new_token->text);
        }

        // Free memory allocated for the token
        free_token(new_token);

        // Get the next token
        token_str = strtok(NULL, " ");
    }

    return 0;
}