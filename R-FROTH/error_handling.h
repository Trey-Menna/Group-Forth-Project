#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//enumeration for different types of errors
typedef enum {
    ERR_GENERAL = 1,
    ERR_MEMORY, 
    ERR_DIV_ZERO,
    ERR_STACK_OVERFLOW,
    ERR_STACK_UNDERFLOW,
    ERR_IO,
    ERR_RUNTIME,
} ErrorCode;

//prototypes for error handling functions
void detailed_handle_error(ErrorCode code, const char *file, int line, const char *function, const char *error_message);
void log_error(const char *error_message);

void handle_memory_error();
void handle_division_by_zero();
void handle_stack_error(const char *error_type);
void handle_io_error();
void handle_runtime_error(const char* message);

//macro to automatically insert file, line, and function information
#define handle_error(code, msg) detailed_handle_error(code, __FILE__, __LINE__, __func__, msg)

#endif 