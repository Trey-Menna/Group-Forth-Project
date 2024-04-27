#include <gtest/gtest.h>
#include "token_stack.hh"
#include "token.hh"
//gtest_discover_tests(token_stack_test), from CMakelists

// Test cases for token_stack.c
TEST(TokenStackTest, PushToken) {
    // Create a token
    token_t* token = create_token(NUMBER, "123");

    // Push the token onto the stack
    push_token(token);

    // Check if the token is correctly pushed onto the stack
    ASSERT_EQ(get_stack_pointer(), 1); // Check if stack pointer is incremented
    ASSERT_EQ(get_stack()[0]->type, NUMBER); // Check if the token type is correct
    ASSERT_STREQ(get_stack()[0]->text, "123"); // Check if the token text is correct

    // Free the token memory
    free_token(token);
    pop_token();
}

TEST(TokenStackTest, PopToken) {
    // Create and push a token onto the stack
    token_t* token = create_token(NUMBER, "123");
    push_token(token);

    // Pop the token from the stack
    token_t* poppedToken = pop_token();

    // Check if the popped token matches the expected values
    ASSERT_NE(poppedToken, nullptr); // Check if the popped token is not null
    ASSERT_EQ(poppedToken->type, NUMBER); // Check if the token type is correct
    ASSERT_STREQ(poppedToken->text, "123"); // Check if the token text is correct

    // Free the memory allocated for the token
    free_token(poppedToken);
}

TEST(TokenStackTest, Add) {
    // Create a token
    token_t* token1 = create_token(NUMBER, "12");
    token_t* token2 = create_token(NUMBER, "24");
    token_t* token3 = create_token(OPERATOR, "+");

    // Push the token onto the stack
    push_token(token1);
    push_token(token2);
    push_token(token3);

    //Get and execute stack
    int stack_pointer = get_stack_pointer();
    token_t** stack = get_stack();
    for (int i = 0; i < stack_pointer; i++) {
            executeToken(stack[i]);
        }

    // Check if the token is correctly pushed onto the stack
    //ASSERT_EQ(get_stack_pointer(), 1); // Check if stack pointer is incremented
    ASSERT_EQ(get_stack()[0]->type, NUMBER); // Check if the token type is correct
    ASSERT_STREQ(get_stack()[0]->text, "36"); // Check if the token text is correct

    //Pop Result
    pop_token();
}

TEST(TokenStackTest, Subtract) {
    // Create a token
    token_t* token1 = create_token(NUMBER, "4");
    token_t* token2 = create_token(NUMBER, "12");
    token_t* token3 = create_token(OPERATOR, "-");

    // Push the token onto the stack
    push_token(token1);
    push_token(token2);
    push_token(token3);

    //Get and execute stack
    int stack_pointer = get_stack_pointer();
    token_t** stack = get_stack();
    for (int i = 0; i < stack_pointer; i++) {
            executeToken(stack[i]);
        }

    // Check if the token is correctly pushed onto the stack
    //ASSERT_EQ(get_stack_pointer(), 1); // Check if stack pointer is incremented
    ASSERT_EQ(get_stack()[0]->type, NUMBER); // Check if the token type is correct
    ASSERT_STREQ(get_stack()[0]->text, "8"); // Check if the token text is correct

    //Pop Result
    pop_token();
}

TEST(TokenStackTest, Multiply) {
    // Create a token
    token_t* token1 = create_token(NUMBER, "32");
    token_t* token2 = create_token(NUMBER, "67");
    token_t* token3 = create_token(OPERATOR, "*");

    // Push the token onto the stack
    push_token(token1);
    push_token(token2);
    push_token(token3);

   //Get and execute stack
    int stack_pointer = get_stack_pointer();
    token_t** stack = get_stack();
    for (int i = 0; i < stack_pointer; i++) {
            executeToken(stack[i]);
        }

    // Check if the token is correctly pushed onto the stack
    //ASSERT_EQ(get_stack_pointer(), 1); // Check if stack pointer is incremented
    ASSERT_EQ(get_stack()[0]->type, NUMBER); // Check if the token type is correct
    ASSERT_STREQ(get_stack()[0]->text, "2144"); // Check if the token text is correct

     //Pop Result
    pop_token();
}

TEST(TokenStackTest, Divide) {
    // Create a token
    token_t* token1 = create_token(NUMBER, "3");
    token_t* token2 = create_token(NUMBER, "6");
    token_t* token3 = create_token(OPERATOR, "/");

    // Push the token onto the stack
    push_token(token1);
    push_token(token2);
    push_token(token3);

    //Get and execute stack
    int stack_pointer = get_stack_pointer();
    token_t** stack = get_stack();
    for (int i = 0; i < stack_pointer; i++) {
            executeToken(stack[i]);
        }

    // Check if the token is correctly pushed onto the stack
    //ASSERT_EQ(get_stack_pointer(), 1); // Check if stack pointer is incremented
    ASSERT_EQ(get_stack()[0]->type, NUMBER); // Check if the token type is correct
    ASSERT_STREQ(get_stack()[0]->text, "2"); // Check if the token text is correct

     //Pop Result
    pop_token();
}

//Comparison Tests, add cases for <,>,<=,>=, !=, ==, &&, ||
TEST(TokenStackTest, LessThan) {
    // Prepare the stack with operands and operator
    push_token(create_token(NUMBER, "5"));
    push_token(create_token(NUMBER, "10"));
    push_token(create_token(COMPARISON, "<"));

   //Get and execute stack
    int stack_pointer = get_stack_pointer();
    token_t** stack = get_stack();
    for (int i = 0; i < stack_pointer; i++) {
            executeToken(stack[i]);
        }

    // Check the result
   //ASSERT_EQ(get_stack_pointer(), 1); // Check if stack pointer is decremented after comparison
    ASSERT_EQ(get_stack()[0]->type, NUMBER); // Check if the result type is correct
    ASSERT_STREQ(get_stack()[0]->text, "1"); // Check if the result is correct

     //Pop Result
    pop_token();
}

//Forth Keyword Tests
TEST(TokenStackTest, Forth_Swap) {
    // Prepare the stack with elements
    push_token(create_token(NUMBER, "5"));
    push_token(create_token(NUMBER, "10"));
    
    // Add a SWAP operator
    push_token(create_token(FORTH, "SWAP"));

    //Get and execute stack
    int stack_pointer = get_stack_pointer();
    token_t** stack = get_stack();
    for (int i = 0; i < stack_pointer; i++) {
            executeToken(stack[i]);
        }

    // Check the result
    //ASSERT_EQ(get_stack_pointer(), 2); // Check if stack pointer remains unchanged
    ASSERT_STREQ(get_stack()[0]->text, "10"); // Check if the elements are swapped correctly
    ASSERT_STREQ(get_stack()[1]->text, "5");

     //Pop Tokens
    pop_token();
    pop_token();
}

TEST(TokenStackTest, Forth_Drop) {
    // Prepare the stack with elements
    push_token(create_token(NUMBER, "5"));
    push_token(create_token(NUMBER, "10"));
    
    // Add a SWAP operator
    push_token(create_token(FORTH, "DROP"));

    //Get and execute stack
    int stack_pointer = get_stack_pointer();
    token_t** stack = get_stack();
    for (int i = 0; i < stack_pointer; i++) {
            executeToken(stack[i]);
        }

    // Check the result
    //ASSERT_EQ(get_stack_pointer(), 2); // Check if stack pointer remains unchanged
    ASSERT_STREQ(get_stack()[0]->text, "5"); // Check if the elements are swapped correctly

    // Clean-up the stack
    pop_token(); // Remove the top element
}

//Add Test Cases for DUP, OVER, ROT, 2DROP, 2SWAP, 2DUP, 2ROT, 2OVER

//Token.c Tests
TEST(TokenTest, CreateToken) {
    // Create a token using the create_token function
    token_t* token = create_token(NUMBER, "123");

    // Check if the token is not null
    //ASSERT_NE(token, nullptr);

    // Check if the token type and text match the expected values
    ASSERT_EQ(token->type, NUMBER);
    ASSERT_STREQ(token->text, "123");

    // Free the memory allocated for the token
    free_token(token);
}

/*TEST(TokenTest, FreeToken) {
    // Create a token
    token_t* token = create_token(NUMBER, "123");

    // Free the token using the free_token function
    free_token(token);

    // Expect death when trying to access the token after freeing it
    EXPECT_DEATH({
        // Try to access the token inside this lambda function
        [&]() {
            token->type = NUMBER;
        }();
    }, ""); // Accessing freed memory should cause the program to terminate
}*/



// Add more test cases as needed

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
