
#include "token.h"
#include <stdio.h>
#include <string.h>

int main() {
    char input[100]; //assume the input will not be longer than 99 characters.
    printf("Enter your FORTH code: ");
    fgets(input, 100, stdin); //get the input from the user.

    // Tokenization process.
    char *word = strtok(input, " \n");
    while (word != NULL) {
        Token token;
        strncpy(token.text, word, sizeof(token.text) - 1); //copy the word into the token's text.
        token.text[sizeof(token.text) - 1] = '\0'; //ensure null-termination.
        token.type = get_token_type(word); //classify the token.

        //print the token type and text.
        switch (token.type) {
            case TYPE_NUMBER:    printf("Number: %s\n", token.text); break;
            case TYPE_OPERATOR:  printf("Operator: %s\n", token.text); break;
            case TYPE_SYMBOL:    printf("Symbol: %s\n", token.text); break;
            case TYPE_WORD:      printf("Word: %s\n", token.text); break;
            default:             printf("Unknown: %s\n", token.text); break;
        }

        word = strtok(NULL, " \n"); //gcd et the next word.
    }

    return 0;
}