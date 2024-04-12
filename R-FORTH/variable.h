//variable.h

#ifndef VARIABLE_H
#define VARIABLE_H

typedef struct {
    char name[20];
    int value;
} Variable;

void setVariable(const char* name, int value);
int getVariableValue(const char* name);

#endif