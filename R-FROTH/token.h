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
    SETVARIABLE,
    SETCONST,
    COMPARISON,
    CONDITIONAL,
    CONSTANT,
    FORTH,
    REPL
} token_type_t;

// Struct to represent a token
typedef struct {
    token_type_t type;  // Token class
    char *text;         // Token text
    int *value;
} token_t;

// Function to initialize a token
token_t* create_token(token_type_t type, const char *text);

token_t* create_var_token(const char *text, const int *value);

token_t* create_const_token(const char *text, const int *value);

// Function to free memory allocated for a token
void free_token(token_t *token);

void free_var_token(token_t *token);

#endif  // TOKEN_H
