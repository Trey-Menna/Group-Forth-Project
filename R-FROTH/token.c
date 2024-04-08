// token.c
#include "token.h"
#include <stdlib.h>
#include <string.h>

token_t* create_token(token_type_t type, const char *text) {
    token_t *token = (token_t*)malloc(sizeof(token_t));
    if (token == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }

    token->type = type;
    token->text = (char *)malloc(strlen(text) + 1); // Allocate memory for token text
    if (token->text == NULL) {
        // Handle memory allocation failure
        free(token); // Free token memory before exiting
        exit(EXIT_FAILURE);
    }
    strcpy(token->text, text); // Copy text into allocated memory

    return token;
}

void free_token(token_t *token) {
    free(token->text); // Free text memory
    free(token);       // Free token memory
}

