// token.c

#include "token.h"
#include <ctype.h>
#include <string.h>

TokenType get_token_type(const char *word) {
    if (isdigit(word[0])) {
        return TYPE_NUMBER;
    } else if (strchr("+-*/", word[0]) != NULL && word[1] == '\0') {
        return TYPE_OPERATOR;
    } else if (strchr(":;", word[0]) != NULL && word[1] == '\0') {
        return TYPE_SYMBOL;
    } else if (strcmp(word, "variable") == 0) {
        return TYPE_VARIABLE;  //recognizing 'variable' as a special word for defining variables.
    } else if (strcmp(word, "help") == 0) {
        return TYPE_HELP; // addition of 'help' keyword
    }
    else {
        return TYPE_WORD;
    }
}