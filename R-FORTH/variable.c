//variable.c

#include "variable.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VARS 100
Variable variables[MAX_VARS];
int varCount = 0;

int findVariable(const char* name) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void setVariable(const char* name, int value) {
    int idx = findVariable(name);
    if (idx == -1) {
        if (varCount < MAX_VARS) {
            strcpy(variables[varCount].name, name);
            variables[varCount].value = value;
            varCount++;
        } else {
            printf("Error: Variable limit reached\n");
            exit(EXIT_FAILURE);
        }
    } else {
        variables[idx].value = value;
    }
}

int getVariableValue(const char* name) {
    int idx = findVariable(name);
    if (idx != -1) {
        return variables[idx].value;
    } else {
        printf("Error: Variable '%s' not defined\n", name);
        exit(EXIT_FAILURE);
    }
}
