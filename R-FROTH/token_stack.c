// token_stack.c

#include "token_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100
token_t* token_stack[STACK_SIZE];
int stack_pointer = 0;

#define VAR_STACK_SIZE 100
token_t* var_token_stack[VAR_STACK_SIZE];
int var_stack_pointer = 0;



void executeToken(token_t *token){
    // Execute token
    if (token->type == WORD) {
                printf("\nWORD not executed Type: %d, Text: %s\n", token->type, token->text);
    } else if (token->type == OPERATOR) {
        executeOperator(token);
    } else if (token->type == SYMBOL) {
        executeSymbol(token);
    } else if (token->type == COMPARISON){
        // Handle comparison tokens
        executeComparison(token);
    } else if (token->type == FORTH){
        executeForth(token);
    } else if (token -> type == VARIABLE){
        createVariable(token);
    } else if (token -> type == CONSTANT){
        createVariable(token);
    }else {
        // Display the tokens not executed (for now)
        //printf("Token not executed Type: %d, Text: %s\n", token->type, token->text);
    }
}


// Function to push a var_token onto the stack
void push_var_token(token_t* token) {
    if (var_stack_pointer < VAR_STACK_SIZE) {
        //token_t* new_token = create_token(token->type, token->text);
        var_token_stack[var_stack_pointer++] = token;
    } else {
        printf("Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

// Function to push a token onto the stack
void push_token(token_t* token) {
    if (stack_pointer < STACK_SIZE) {
        token_t* new_token = create_token(token->type, token->text);
        token_stack[stack_pointer++] = new_token;
    } else {
        printf("Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

// Function to pop a token from the stack
token_t* pop_token() {
    if (stack_pointer > 0) {
        return token_stack[--stack_pointer];
    } else {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

//Functionn to print stack
void print_stack() {
    system("clear");
    printf("\n");
    for (int i = 0; i < stack_pointer; i++) {
        printf("%s ", token_stack[i]->text);
    }
    printf(" <- top\n");
}

// Function to get the entire stack
token_t** get_stack() {
    return token_stack;
}

// Function to get the current stack pointer
int get_stack_pointer() {
    return stack_pointer;
}

//Var Stack functions
// Function to get the entire stack
token_t** get_var_stack() {
    return var_token_stack;
}

// Function to get the current stack pointer
int get_var_stack_pointer() {
    return var_stack_pointer;
}

// Function to execute arithmetic operation tokens
void executeOperator(token_t* token) {
    // Ensure the stack has at least two operands
    if (stack_pointer < 2) {
        printf("Error: Insufficient operands on the stack\n");
        exit(EXIT_FAILURE);
    }

    // Retrieve operands from the stack
    token_t* pop_operator = pop_token();
    token_t* operand_token1 = pop_token();
    token_t* operand_token2 = pop_token();

    // Check if the popped tokens are valid
    if (operand_token1 == NULL || operand_token2 == NULL) {
        printf("Error: Invalid tokens on the stack\n");
        exit(EXIT_FAILURE);
    }

    // Perform the appropriate arithmetic operation based on the operator token
    int result;
    if (strcmp(token->text, "+") == 0) {
        result = atoi(operand_token1->text) + atoi(operand_token2->text);
    } else if (strcmp(token->text, "-") == 0) {
        result = atoi(operand_token1->text) - atoi(operand_token2->text);
    } else if (strcmp(token->text, "*") == 0) {
        result = atoi(operand_token1->text) * atoi(operand_token2->text);
    } else if (strcmp(token->text, "/") == 0) {
        // Check for division by zero
        int operand2 = atoi(operand_token2->text);
        if (operand2 == 0) {
            printf("Error: Division by zero\n");
            exit(EXIT_FAILURE);
        }
        result = atoi(operand_token1->text) / operand2;
    } else {
        // If the operator is not recognized, print an error message
        printf("Error: Unsupported operator\n");
        exit(EXIT_FAILURE);
    }

    // Convert the result to a string using sprintf
    char result_str[20]; // Assuming a maximum of 20 characters for the result
    sprintf(result_str, "%d", result);
    // Push the result onto the stack
    push_token(create_token(NUMBER, result_str));
    //printf("Printing Stack from token_stack after executing operator: ");
    //print_stack();
}

// Function to execute comparison tokens
void executeComparison(token_t* token) {
    // Handle comparison operators
    token_t* pop_operator = pop_token();
    if (strcmp(token->text, "<") == 0) {
        int operand2 = atoi(pop_token()->text); // Retrieve the value from token_t
        int operand1 = atoi(pop_token()->text); // Retrieve the value from token_t
        push_token(create_token(NUMBER, (operand1 < operand2) ? "1" : "0")); // Push true (1) or false (0) based on comparison result
    } else if (strcmp(token->text, ">") == 0) {
        int operand1 = atoi(pop_token()->text); // Retrieve the value from token_t
        int operand2 = atoi(pop_token()->text); // Retrieve the value from token_t
        push_token(create_token(NUMBER, (operand1 > operand2) ? "1" : "0"));
    } else if (strcmp(token->text, "<=") == 0) {
        // Retrieve operands from the stack
        int operand2 = atoi(pop_token()->text);
        int operand1 = atoi(pop_token()->text);
        // Perform the logical AND operation and push the result onto the stack
        push_token(create_token(NUMBER, (operand1 <= operand2) ? "1" : "0"));
    } else if (strcmp(token->text, ">=") == 0) {
        int operand1 = atoi(pop_token()->text);
        int operand2 = atoi(pop_token()->text);
        push_token(create_token(NUMBER, (operand1 >= operand2) ? "1" : "0"));
    } else if (strcmp(token->text, "==") == 0) {
        int operand2 = atoi(pop_token()->text);
        int operand1 = atoi(pop_token()->text);
        push_token(create_token(NUMBER, (operand1 == operand2) ? "1" : "0"));
    } else if (strcmp(token->text, "!=") == 0) {
        int operand2 = atoi(pop_token()->text);
        int operand1 = atoi(pop_token()->text);
        push_token(create_token(NUMBER, (operand1 != operand2) ? "1" : "0"));
    } else if (strcmp(token->text, "&&") == 0) {
        int operand2 = atoi(pop_token()->text);
        int operand1 = atoi(pop_token()->text);
        push_token(create_token(NUMBER, (operand1 && operand2) ? "1" : "0"));
    } else if (strcmp(token->text, "||") == 0) {
        int operand2 = atoi(pop_token()->text);
        int operand1 = atoi(pop_token()->text);
        push_token(create_token(NUMBER, (operand1 || operand2) ? "1" : "0"));
    }else {
        printf("Error: Unsupported operator\n");
    }
}

void executeForth(token_t* token) {
    //SWAP, DUP, OVER, ROT, DROP, 2SWAP, 2DUP, 2OVER, and 2DROP
    token_t* pop_keyword = pop_token();
    if (strcmp(token->text, "SWAP") == 0) {
        // SWAP the top two elements on the stack
        token_t* temp = pop_token();
        token_t* top = pop_token();
        push_token(temp);
        push_token(top);
    } else if (strcmp(token->text, "DUP") == 0) {
        // Duplicate the top element on the stack
        token_t* top = pop_token();
        push_token(top);
        push_token(create_token(top->type, top->text));
    } else if (strcmp(token->text, "OVER") == 0) {
        // Copy the second element from the top onto the top of the stack
        token_t* second = pop_token();
        token_t* top = pop_token();
        push_token(top);
        push_token(second);
        push_token(create_token(second->type, second->text));
    } else if (strcmp(token->text, "ROT") == 0) {
        // Rotate the top three elements on the stack
        token_t* temp1 = pop_token();
        token_t* temp2 = pop_token();
        token_t* top = pop_token();
        push_token(temp1);
        push_token(temp2);
        push_token(top);
    } else if (strcmp(token->text, "DROP") == 0) {
        // Remove the top element from the stack
        pop_token(); // Simply pop the top element
    } else if (strcmp(token->text, "2SWAP") == 0) {
        // Swap the top two pairs of stack items
        token_t* temp1 = pop_token();
        token_t* temp2 = pop_token();
        token_t* top1 = pop_token();
        token_t* top2 = pop_token();
        push_token(temp2);
        push_token(temp1);
        push_token(top2);
        push_token(top1);
    } else if (strcmp(token->text, "2DUP") == 0) {
        // Duplicate the top two pairs of stack items
        token_t* top1 = pop_token();
        token_t* top2 = pop_token();
        push_token(top2);
        push_token(top1);
        push_token(create_token(top2->type, top2->text));
        push_token(create_token(top1->type, top1->text));
    } else if (strcmp(token->text, "2OVER") == 0) {
        // Copy the second pair from the top onto the top of the stack
        token_t* second1 = pop_token();
        token_t* second2 = pop_token();
        token_t* top1 = pop_token();
        token_t* top2 = pop_token();
        push_token(top2);
        push_token(top1);
        push_token(second2);
        push_token(second1);
        push_token(create_token(second2->type, second2->text));
        push_token(create_token(second1->type, second1->text));
    } else if (strcmp(token->text, "2DROP") == 0) {
        // Remove the top two pairs from the stack
        printf("Executing 2DROP");
        pop_token();
        pop_token();
    } else {
        printf("Error: Unsupported Forth keyword\n");
    }
}



void executeConditionals(token_t* token){
    // Handle conditional branching tokens (IF, ELSE, THEN)
    token_t* pop_operator = pop_token();
    if (strcmp(token->text, "IF") == 0) {
        int operand2 = atoi(pop_token()->text);
        int operand1 = atoi(pop_token()->text); 
        // execute conditonal
    } else if (strcmp(token->text, "ELSE") == 0) {
        //ELSE
    } else if (strcmp(token->text, "THEN") == 0) {
        //THEN
    }else{
        printf("Error: Unsupported Conditional\n");
    }
}

void createVariable(token_t* token) {
    // Add support for variables and constants.
    if (strcmp(token->text, "VAR") == 0) {
        // Retrieve the value for var value
        token_t* value_token = pop_token();
        if (value_token == NULL) {
            printf("Error: Insufficient operands on the stack for variable creation\n");
            exit(EXIT_FAILURE);
        }
        int value = atoi(value_token->text);

        // Retrieve the value for var name
        token_t* name_token = pop_token();
        if (name_token == NULL) {
            printf("Error: Insufficient operands on the stack for variable creation\n");
            exit(EXIT_FAILURE);
        }

        token_t* pop_VarKeyword = pop_token();
        // Create and Store variable for later use
        printf("Creating Var Token: %s with value: %d\n", name_token->text, value);
        token_t* new_var_token = create_var_token(name_token->text, value);
        //token_t* new_token = create_token(VARIABLE, name_token->text);
        printf("Adding Var Token to VarToken stack name: %s and value: %d\n", new_var_token->text, new_var_token->value);
        push_var_token(new_var_token);
        //printf("Adding New Token to Stack: %s\n", new_token->text);
        //push_token(new_token);

        // Free the memory allocated for the tokens
        //free_token(name_token);
        //free_token(value_token);
        //free_token(new_var_token);
        //free_token(new_token);
    } else if (strcmp(token->text, "CONST") == 0) {
        //CONSTANT
        // Here you can implement the logic to handle constants if needed
        token_t* value_token = pop_token();
        if (value_token == NULL) {
            printf("Error: Insufficient operands on the stack for variable creation\n");
            exit(EXIT_FAILURE);
        }
        int value = atoi(value_token->text);

        // Retrieve the value for var name
        token_t* name_token = pop_token();
        if (name_token == NULL) {
            printf("Error: Insufficient operands on the stack for variable creation\n");
            exit(EXIT_FAILURE);
        }

        token_t* pop_VarKeyword = pop_token();
        // Create and Store variable for later use
        printf("Creating Var Token: %s with value: %d\n", name_token->text, value);
        token_t* new_var_token = create_var_token(name_token->text, value);
        //token_t* new_token = create_token(VARIABLE, name_token->text);
        printf("Adding Var Token to VarToken stack name: %s and value: %d\n", new_var_token->text, new_var_token->value);
        push_var_token(new_var_token);
        //printf("Adding New Token to Stack: %s\n", new_token->text);
        //push_token(new_token);

        // Free the memory allocated for the tokens
        free_token(name_token);
        free_token(value_token);
        free_token(new_var_token);
    } else if (strcmp(token->text, "GET") == 0) {
    printf("Executing GET\n");
    
    // Pop tokens
    token_t* varName = pop_token(); //Pop Token for VAR name
    printf("Popped token: %s\n", varName->text); // Print popped token for debugging
    token_t* pop_Get = pop_token(); //Pop Get token
    printf("Popped token: %s\n", pop_Get->text); // Print popped token for debugging

    // Get the stack array and stack pointer
    token_t** varStack = get_var_stack();
    int varStack_pointer = get_var_stack_pointer();
    printf("Var stack pointer: %d\n", varStack_pointer); // Print var stack pointer for debugging

    // Loop through the stack to find the variables value
    for (int i = var_stack_pointer -1; i >= 0; i--) {
        printf("Checking var name: %s\n", varStack[i]->text); // Print var name for debugging
        printf("Checking target name: %s\n", varName->text); // Print var name for debugging
        if (strcmp(varStack[i]->text, varName->text) == 0) {
            printf("Value found: %d\n", varStack[i]->value); // Print value found for debugging
            // Modify the print statement to store the value as text
            char valueText[20]; // Assuming the maximum length of the integer value is 20 characters
            sprintf(valueText, "%d", varStack[i]->value);
            printf("Value as text: %s\n", valueText); // Print value as text for debugging

            // Create token using the value as text
            token_t* varValue = create_token(NUMBER, valueText);
            printf("Token Created: Type: %d, Text: %s\n", varValue->type, varValue->text);
            //push token with VAR's value from Var_Token_Stack to main token stack
            push_token(varValue);
        }
    }
}else{
        printf("Error: Unsupported Variable\n");
    }
}


void createFunction(){
}


void forthREPL(){
        //Add support for the "REPL" of FORTH
}

void executeSymbol(token_t* token){
    //Add support for custom shortcuts, ex. . to pop stack and wq to quit out forth
    token_t* pop_operator = pop_token();
    if (strcmp(token->text, ".") == 0) {
        pop_token();
    }
        else{
        printf("Error: Unsupported Symbol\n");
    }
} 
