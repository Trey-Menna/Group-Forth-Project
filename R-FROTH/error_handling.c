#include "error_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function to handle general errors with a custom message and stop execution
void handle_error(const char *error_message) {
    fprintf(stderr, "Error: %s\n", error_message);
    exit(EXIT_FAILURE);
}

//function to handle memory allocation failures
void handle_memory_error() {
    handle_error("Memory allocation failed. System will terminate.");
}

//function for handling division by zero
void handle_division_by_zero() {
    handle_error("Division by zero encountered. System will terminate");
}

//function to handle stack overflow or underflow
void handle_stack_error(const char *error_type) {
    if (strcmp(error_type, "Overflow") == 0) {
        handle_error("Stack overflow. System will terminate.");
    } else if (strcmp(error_type, "Underflow") == 0) {
        handle_error("Stack underflow. System will terminate");
    }
    
}