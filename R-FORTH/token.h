// token.h

#ifndef TOKEN_H
#define TOKEN_H

//define the types of tokens that can be identified.
typedef enum {
    TYPE_NUMBER,
    TYPE_OPERATOR,
    TYPE_SYMBOL,
    TYPE_WORD,
    TYPE_UNKNOWN,
    TYPE_END
} TokenType;

TokenType get_token_type(const char *word);

//simple structure for a token.
typedef struct {
    TokenType type;
    char text[20]; //assume a token is not longer than 19 characters for simplicity.
} Token;

#endif // TOKEN_H