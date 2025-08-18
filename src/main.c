#include <stdio.h> 
#include "stack.h"

int main(int argv, char** argc) {
  Stack_t *stack = stack_create(10);

  stack_push(stack, 4);
  stack_push(stack, 8);
  stack_push(stack, 15);
  stack_push(stack, 16);
  stack_push(stack, 23);

  uint8_t popped_value;
  if (stack_pop(stack, &popped_value) == STACK_OK) {
    printf("Popped value: %d\n", popped_value);
  } else {
    printf("Error popping the stack\n");
  }
  
  printf("Peek the top value: ");
  uint8_t top_value;
  if (stack_peek(stack, &top_value) == STACK_OK) {
    printf("%d\n", top_value);
  } else {
    printf("Error peeking the stack\n");
  }

  stack_print(stack);
  stack_destroy(stack);

  return 0;
}
