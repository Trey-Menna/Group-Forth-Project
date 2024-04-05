// token.c
#include "token.h"
#include <ctype.h>
#include <string.h>

TokenType get_token_type(const char *word) {
    //check if the token is a number.
    if (isdigit(word[0])) {
        return TYPE_NUMBER;
    }
    //check if the token is an operator.
    else if (strchr("+-*/", word[0]) != NULL && word[1] == '\0') {
        return TYPE_OPERATOR;
    }
    //check if the token is a symbol.
    else if (strchr(":;", word[0]) != NULL && word[1] == '\0') {
        return TYPE_SYMBOL;
    }
    //if it's not a number, operator or symbol, it's a word.
    else {
        return TYPE_WORD;
    }
}