// token_stack.c

#include "token_stack.h"
#include <stdio.h>
#include <stdlib.h>

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

void print_stack() {
    printf("Stack contents:\n");
    for (int i = 0; i < stack_pointer; i++) {
        printf("%d\n", token_stack[i]);
    }
    printf("End of Stack\n");
}