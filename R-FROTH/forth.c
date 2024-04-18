#include "token.h"
#include "token_stack.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function to classify tokens
void classify_token(token_t *token) {
    if (isdigit(token->text[0]) || (token->text[0] == '-' && isdigit(token->text[1]))) {
        token->type = NUMBER;
    } else if (strcmp(token->text, "+") == 0 || strcmp(token->text, "-") == 0 ||
               strcmp(token->text, "*") == 0 || strcmp(token->text, "/") == 0) {
        token->type = WORD;
    } else if (strcmp(token->text, "CONST") == 0) {
        token->type = CONSTANT;
    } else if (strcmp(token->text, "VAR") == 0) {
        token->type = VARIABLE;
    } else if (strcmp(token->text, ".") == 0 || strcmp(token->text, "wq") == 0) {
        token->type = SYMBOL;
    } else if (strcmp(token->text, ">=") == 0 || strcmp(token->text, "<=") == 0 ||
               strcmp(token->text, "==") == 0 || strcmp(token->text, "!=") == 0 ||
               strcmp(token->text, ">") == 0 || strcmp(token->text, "<") == 0) {
        token->type = COMPARISON;
    } else if (strcmp(token->text, "SWAP") == 0 || strcmp(token->text, "DUP") == 0 ||
               strcmp(token->text, "OVER") == 0 || strcmp(token->text,"ROT") == 0 ||
               strcmp(token->text, "DROP") == 0 || strcmp(token->text, "2SWAP") == 0 ||
               strcmp(token->text, "2DUP") == 0 || strcmp(token->text, "2OVER") == 0 || strcmp(token->text, "2DROP") == 0 ) {
    token->type = FORTH;
    } else if (strcmp(token->text, "IF") == 0 || strcmp(token->text, "ELSE") == 0 ||
               strcmp(token->text, "Then") == 0 || strcmp(token->text, ":") == 0 ||
               strcmp(token->text, "(") == 0 || strcmp(token->text, ")") == 0  || strcmp(token->text, ";") == 0) {
        token->type = CONDITIONAL;
    } else {
        token->type = WORD; // Assume everything else is a word
    }
    //printf("Token %s is now Type: %d" , token->text, token->type);
}


void executeToken(token_t *token){
    // Execute token
    if (token->type == WORD) {
        if (strcmp(token->text, "+") == 0 || strcmp(token->text, "-") == 0 ||strcmp(token->text, "*") == 0 || strcmp(token->text, "/") == 0){
            // Handle operator tokens
            executeOperator(token); }
            else{
                printf("\nWORD not executed Type: %d, Text: %s\n", token->type, token->text);
            }
    } else if (token->type == SYMBOL) {
        // Handle conditional branching tokens (IF, ELSE, THEN)
    } else if (token->type == COMPARISON){
        // Handle comparison tokens
        executeComparison(token);
    } else if (token->type == FORTH){
        executeForth(token);
    } else if (token -> type == VARIABLE){
        createVariable(token);
    } else {
        // Display the tokens not executed (for now)
        //printf("Token not executed Type: %d, Text: %s\n", token->type, token->text);
    }
}




int main() {
    char input[1024];  // Assuming a maximum input length of 1024 characters

    // Read input from standard input
    printf("Enter R-FORTH program:\n");
    fgets(input, sizeof(input), stdin);

    //***Ignore the enter the user will use to submit the line of code
    // Remove the newline character if it exists
    char *newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }


    // Tokenize the input
     char *token_str = strtok(input, " ");
     while (token_str != NULL) {

        // Create token
        token_t *new_token = create_token(WORD, token_str);

         // Classify each token based on basic checks
        token_type_t type;
        classify_token(new_token);
        //printf("\nToken being pushed to stack: %s , Type: %d", new_token->text , new_token->type);
        push_token(new_token);
        //printf("\nStack after a new token is pushed:  ");
        //print_stack();

        // Free memory allocated for the token
        free_token(new_token);

        // Get the next token
        token_str = strtok(NULL, " ");
    }
    
    // Get the stack array and stack pointer
    token_t** stack = get_stack();
    int stack_pointer = get_stack_pointer();

    // Loop through the stack to execute tokens
    for (int i = 0; i < stack_pointer; i++) {
        executeToken(stack[i]);
    }
    //printf("Printing Stack from main after execute");
    print_stack();

    return 0;
}