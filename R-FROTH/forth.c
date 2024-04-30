#include "token.h"
#include "token_stack.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function to classify tokens
void classify_token(token_t *token) {
    if (strcmp(token->text, "SWAP") == 0 || strcmp(token->text, "DUP") == 0 ||
               strcmp(token->text, "OVER") == 0 || strcmp(token->text,"ROT") == 0 ||
               strcmp(token->text, "DROP") == 0 || strcmp(token->text, "2SWAP") == 0 ||
               strcmp(token->text, "2DUP") == 0 || strcmp(token->text, "2OVER") == 0 || 
               strcmp(token->text, "2DROP") == 0 || strcmp(token->text, "EMIT") == 0 ) {
    token->type = FORTH;
    }
    else if (isdigit(token->text[0]) || (token->text[0] == '-' && isdigit(token->text[1]))) {
        token->type = NUMBER;
    } else if (strcmp(token->text, "+") == 0 || strcmp(token->text, "-") == 0 ||
               strcmp(token->text, "*") == 0 || strcmp(token->text, "/") == 0) {
        token->type = OPERATOR;
    } else if (strcmp(token->text, "VAR") == 0 || strcmp(token->text, "CONST") == 0 ||
               strcmp(token->text, "GET") == 0) {
        token->type = VARIABLE;
    } else if (strcmp(token->text, ".") == 0 || strcmp(token->text, "wq") == 0) {
        token->type = SYMBOL;
    } else if (strcmp(token->text, ">=") == 0 || strcmp(token->text, "<=") == 0 ||
               strcmp(token->text, "==") == 0 || strcmp(token->text, "!=") == 0 ||
               strcmp(token->text, ">") == 0 || strcmp(token->text, "<") == 0 || 
               strcmp(token->text, "&&") == 0 || strcmp(token->text, "||") == 0) {
        token->type = COMPARISON;
    } else if (strcmp(token->text, "IF") == 0 || strcmp(token->text, "ELSE") == 0 ||
               strcmp(token->text, "Then") == 0 || strcmp(token->text, ":") == 0 ||
               strcmp(token->text, "(") == 0 || strcmp(token->text, ")") == 0  || strcmp(token->text, ";") == 0) {
        token->type = CONDITIONAL;
    } else if (strcmp(token->text, ".") == 0 || strcmp(token->text, "man") == 0 
                || strcmp(token->text, "...") == 0) {
        token->type = SYMBOL;
    } else {
        token->type = WORD; // Assume everything else is a word
    }
    //printf("Token %s is now Type: %d" , token->text, token->type);
}

int main() {
    char input[1024];  // Assuming a maximum input length of 1024 characters
    printf("Enter R-FORTH program (type 'quit' to exit):\n");
    while (1) { // Game loop continues until user decides to exit
        // Read input from standard input
        fgets(input, sizeof(input), stdin);

        //***Ignore the enter the user will use to submit the line of code
        // Remove the newline character if it exists
        char *newline = strchr(input, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        // Check if the user wants to exit
        if (strcmp(input, "quit") == 0){
            printf("Exiting...\n");
            break; // Exit the game loop
        } else if (strcmp(input, "wq") == 0){
            printf("Quitting...\n");
            break;
        }

        // Tokenize the input
        char *token_str = strtok(input, " ");
        while (token_str != NULL) {
            // Create token
            token_t *new_token = create_token(WORD, token_str);

            // Classify each token based on basic checks
            classify_token(new_token);

            // Push the token onto the stack
            push_token(new_token);

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

        // Print the stack after executing the input
        print_stack();
    }

    return 0;
}
