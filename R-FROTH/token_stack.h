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

//Function to execute special symbol tokens
void executeSymbol(token_t* token);

// Function to execute forth keywords
void executeForth(token_t* token);

//Function to create and add variable to var_token_stack
void createVariable(token_t* token);

//Function to print current token stack
void print_stack();

//Function to retrive current token stack
token_t** get_stack();
token_t** get_var_stack();

//Function to get current token stack's pointer
int get_stack_pointer();
int get_var_stack_pointer();

//Function to call the correct function for the token type
void executeToken(token_t *token);

#endif  // TOKEN_STACK_H
