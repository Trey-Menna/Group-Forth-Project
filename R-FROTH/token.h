// token.h

#ifndef TOKEN_H
#define TOKEN_H

// Enum to represent different token types
typedef enum {
    NUMBER,
    OPERATOR,
    SYMBOL,
    WORD,
    VARIABLE,
    CONSTANT
} token_type_t;

// Struct to represent a token
typedef struct {
    token_type_t type;  // Token class
    char *text;         // Token text
} token_t;

// Function to initialize a token
token_t* create_token(token_type_t type, const char *text);

// Function to free memory allocated for a token
void free_token(token_t *token);

#endif  // TOKEN_H
