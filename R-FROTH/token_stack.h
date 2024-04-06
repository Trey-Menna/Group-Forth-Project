// token_stack.h

#ifndef TOKEN_STACK_H
#define TOKEN_STACK_H

#include "token.h"

// Function to push a token onto the stack
void push_token(token_t* token);

// Function to pop a token from the stack
token_t* pop_token();

void print_stack();

#endif  // TOKEN_STACK_H
