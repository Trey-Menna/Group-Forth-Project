#include "error_handling.h"

//detailed error handling function 
void detailed_handle_error(ErrorCode code, const char *file, int line, const char *function, const char *error_message) {
    fprintf(stderr, "Error: [%d] in %s, line %d, function %s: %s\n", code, file, line, function, error_message);
    log_error(error_message);
    exit(EXIT_FAILURE);
}

//function to log errors to a file
void log_error(const char *error_message) {
    FILE *log = fopen("error_log.txt", "a");
    if (log) {
        fprintf(log, "%s\n", error_message);
        fclose(log);
    } else {
        fprintf(stderr, "Failed to open error log file.\n");
    }
}

//specific error handling functions
void handle_memory_error() {
    handle_error(ERR_MEMORY, "Memory allocation failed. System will terminate.");
}

void handle_division_by_zero() {
    handle_error(ERR_DIV_ZERO, "Division by zero encountered. System will terminate.");
}
//handle overflow and underflow 
void handle_stack_error(const char *error_type) {
    if (strcmp(error_type, "Overflow") == 0) {
        handle_error(ERR_STACK_OVERFLOW, "Stack overflow. System will terminate.");
    } else if (strcmp(error_type, "Underflow") == 0) {
        handle_error(ERR_STACK_UNDERFLOW, "Stack underflow. System will terminate.");
    }
}

//function to handle I/O errors
void handle_io_error() {
    handle_error(ERR_IO, "I/O error encountered. System will terminate.");
}

//function to handle runtime errors
void handle_runtime_error(const char* message) {
    handle_error(ERR_RUNTIME, message);
}