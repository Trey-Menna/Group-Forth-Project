//main.c

#include "token.h"
#include "variable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char input[100];
    printf("Enter your FORTH code: ");
    fgets(input, 100, stdin);

    char *word = strtok(input, " \n");
    while (word != NULL) {
        Token token;
        strncpy(token.text, word, sizeof(token.text) - 1);
        token.text[sizeof(token.text) - 1] = '\0';
        token.type = get_token_type(word);

        switch (token.type) {
            case TYPE_NUMBER:    printf("Number: %s\n", token.text); break;
            case TYPE_OPERATOR:  printf("Operator: %s\n", token.text); break;
            case TYPE_SYMBOL:    printf("Symbol: %s\n", token.text); break;
            case TYPE_VARIABLE:
                //move to the next token, which should be the variable's name
                word = strtok(NULL, " \n");
                if (word != NULL) {
                    int value;
                    printf("Enter value for variable %s: ", word);
                    scanf("%d", &value);
                    setVariable(word, value);
                    printf("Variable %s set to %d\n", word, getVariableValue(word));
                }
                break;
            case TYPE_WORD:      printf("Word: %s\n", token.text); break;
            default:             printf("Unknown: %s\n", token.text); break;
        }

        word = strtok(NULL, " \n");
    }

    return 0;
}
