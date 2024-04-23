#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_error(const char *error_message);
void handle_memory_error();
void handle_division_by_zero();
void handle_stack_error(const char *error_type);

#endif

