#include "token.h"
#include "token_stack.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function to execute a conditional operation token
void execute_conditional_token(token_t *token) {
    print_stack();
    if (token->type == OPERATOR) {
        // Handle operator tokens
        executeOperator(token);
    } else if (token->type == SYMBOL) {
        // Handle conditional branching tokens (IF, ELSE, THEN)
    } else if (token->type == COMPARISON){
        // Handle comparison tokens
        executeComparison(token);
    }
}

// Function to classify tokens
void classify_token(token_t *token) {
    if (isdigit(token->text[0]) || (token->text[0] == '-' && isdigit(token->text[1]))) {
        token->type = NUMBER;
    } else if (strchr("+-*/", token->text[0]) != NULL) {
        token->type = OPERATOR;
    } else if (strcmp(token->text, "CONSTANT") == 0) {
        token->type = CONSTANT;
    } else if (strcmp(token->text, "VARIABLE") == 0) {
        token->type = VARIABLE;
    } else if (strchr(":;", token->text[0]) != NULL) {
        token->type = SYMBOL;
    } else if((strchr(">=<", token->text[0]) != NULL)){
        token->type = COMPARISON;
    } 
    else {
        token->type = WORD; // Assume everything else is a word
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
        classify_token(new_token);
        push_token(new_token);
        //print_stack();

        // Execute token
        if (new_token->type == CONSTANT || new_token->type == VARIABLE || new_token->type == OPERATOR || new_token->type == SYMBOL || new_token->type == COMPARISON) {
            execute_conditional_token(new_token);
        } else {
            // Display the token (for now)
            printf("Type: %d, Text: %s\n", new_token->type, new_token->text);
        }

        print_stack();

        // Free memory allocated for the token
        free_token(new_token);

        // Get the next token
        token_str = strtok(NULL, " ");
    }

    return 0;
}