FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
    forth
    forth.c
    token.c
    token_stack.c
    error_handling.c
)

add_executable(
    token_stack_tests
    token_stack_tests.cc
    token.c 
    token_stack.c
)

target_link_libraries(
  token_stack_tests
  gtest_main
  -lpthread
  -lm
)

include(GoogleTest)
