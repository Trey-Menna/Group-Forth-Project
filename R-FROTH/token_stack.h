// token_stack.h

#ifndef TOKEN_STACK_H
#define TOKEN_STACK_H

#include "token.h"

// Function to push a token onto the stack
void push_token(token_t* token);

// Function to pop a token from the stack
token_t* pop_token();

//// Function to execute operator tokens
void executeOperator(token_t* token);

//// Function to execute comparison tokens
void executeComparison(token_t* token);

// Function to execute forth keywords
void executeForth(token_t* token);

void print_stack();

token_t** get_stack();

int get_stack_pointer();

#endif  // TOKEN_STACK_H
