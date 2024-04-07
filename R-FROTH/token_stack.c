// token_stack.c

#include "token_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100
token_t* token_stack[STACK_SIZE];
int stack_pointer = 0;

// Function to push a token onto the stack
void push_token(token_t* token) {
    if (stack_pointer < STACK_SIZE) {
        token_stack[stack_pointer++] = token;
    } else {
        printf("Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

// Function to pop a token from the stack
token_t* pop_token() {
    if (stack_pointer > 0) {
        return token_stack[--stack_pointer];
    } else {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

//Functionn to print stack
void print_stack() {
    printf("\n");
    for (int i = 0; i < stack_pointer; i++) {
        printf("%s ", token_stack[i]->text);
    }
    printf(" <- top\n");
}

// Function to execute arithmetic operation tokens
void executeOperator(token_t* token) {
    // Ensure the stack has at least two operands
    if (stack_pointer < 2) {
        printf("Error: Insufficient operands on the stack\n");
        exit(EXIT_FAILURE);
    }

    // Retrieve operands from the stack
    token_t* operand_token2 = pop_token();
    token_t* operand_token1 = pop_token();

    // Check if the popped tokens are valid
    if (operand_token1 == NULL || operand_token2 == NULL) {
        printf("Error: Invalid tokens on the stack\n");
        exit(EXIT_FAILURE);
    }

    // Convert operand tokens to integers
    int operand2 = atoi(operand_token2->text);
    int operand1 = atoi(operand_token1->text);
    printf("operand1: %d, operand2: %d\n", operand1, operand2);

    // Perform the appropriate arithmetic operation based on the operator token
    int result;
    if (strcmp(token->text, "+") == 0) {
        result = operand1 + operand2;
    } else if (strcmp(token->text, "-") == 0) {
        result = operand1 - operand2;
    } else if (strcmp(token->text, "*") == 0) {
        result = operand1 * operand2;
    } else if (strcmp(token->text, "/") == 0) {
        // Check for division by zero
        if (operand2 == 0) {
            printf("Error: Division by zero\n");
            exit(EXIT_FAILURE);
        }
        result = operand1 / operand2;
    } else {
        // If the operator is not recognized, print an error message
        printf("Error: Unsupported operator\n");
        exit(EXIT_FAILURE);
    }

    // Convert the result to a string using sprintf
    char result_str[20]; // Assuming a maximum of 20 characters for the result
    sprintf(result_str, "%d", result);

    // Push the result onto the stack
    push_token(create_token(NUMBER, result_str));
}







// Function to execute comparison tokens
void executeComparison(token_t* token) {
    // Handle comparison operators
    if (strcmp(token->text, "<") == 0) {
        int operand2 = atoi(pop_token()->text); // Retrieve the value from token_t
        int operand1 = atoi(pop_token()->text); // Retrieve the value from token_t
        push_token(create_token(NUMBER, (operand1 < operand2) ? "1" : "0")); // Push true (1) or false (0) based on comparison result
    } else if (strcmp(token->text, ">") == 0) {
        int operand1 = atoi(pop_token()->text); // Retrieve the value from token_t
        int operand2 = atoi(pop_token()->text); // Retrieve the value from token_t
        push_token(create_token(NUMBER, (operand1 > operand2) ? "1" : "0"));
    } else if (strcmp(token->text, "<=") == 0) {
        int operand2 = atoi(pop_token()->text);
        int operand1 = atoi(pop_token()->text);
        push_token(create_token(NUMBER, (operand1 <= operand2) ? "1" : "0"));
    } else if (strcmp(token->text, ">=") == 0) {
        int operand1 = atoi(pop_token()->text);
        int operand2 = atoi(pop_token()->text);
        push_token(create_token(NUMBER, (operand1 >= operand2) ? "1" : "0"));
    } else if (strcmp(token->text, "==") == 0) {
        int operand2 = atoi(pop_token()->text);
        int operand1 = atoi(pop_token()->text);
        push_token(create_token(NUMBER, (operand1 == operand2) ? "1" : "0"));
    } else if (strcmp(token->text, "!=") == 0) {
        int operand2 = atoi(pop_token()->text);
        int operand1 = atoi(pop_token()->text);
        push_token(create_token(NUMBER, (operand1 != operand2) ? "1" : "0"));
    } else {
        printf("Error: Unsupported operator\n");
       
    }
}


void executeSymbol(){
        // Handle conditional branching tokens (IF, ELSE, THEN)
}