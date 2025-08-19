#ifndef TEST_STACK_H
#define TEST_STACK_H
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include "stack.h"

void test_stack_create(void){
  Stack_t stack = stack_create(0);
  CU_ASSERT_PTR_NULL_FATAL(stack.data);
  CU_ASSERT_EQUAL(stack.size, 0);
  CU_ASSERT_EQUAL(stack.capacity, 0);

  stack = stack_create(SIZE_MAX);
  CU_ASSERT_PTR_NULL_FATAL(stack.data);
  CU_ASSERT_EQUAL(stack.size, 0);
  CU_ASSERT_EQUAL(stack.capacity, 0);

  stack = stack_create(10);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack.data);
  CU_ASSERT_EQUAL(stack.size, 0);
  CU_ASSERT_EQUAL(stack.capacity, 10);
  stack_destroy(&stack);

  stack = stack_create(100);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack.data);
  CU_ASSERT_EQUAL(stack.size, 0);
  CU_ASSERT_EQUAL(stack.capacity, 100);
  stack_destroy(&stack);

  stack = stack_create(1000);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack.data);
  CU_ASSERT_EQUAL(stack.size, 0);
  CU_ASSERT_EQUAL(stack.capacity, 1000);
  stack_destroy(&stack);

  stack = stack_create(10000);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack.data);
  CU_ASSERT_EQUAL(stack.size, 0);
  CU_ASSERT_EQUAL(stack.capacity, 10000);
  stack_destroy(&stack);

}

void test_stack_destroy(void){
  for(size_t i = 1; i < 100; i++){
    Stack_t stack = stack_create(i);
    CU_ASSERT_PTR_NOT_NULL_FATAL(stack.data);
    CU_ASSERT_EQUAL(stack.size, 0);
    CU_ASSERT_EQUAL(stack.capacity, i);

    StackStatus_t status = stack_destroy(&stack);
    CU_ASSERT_EQUAL_FATAL(status, STACK_OK);
    CU_ASSERT_EQUAL(stack.size, 0);
    CU_ASSERT_EQUAL(stack.capacity, 0);
    CU_ASSERT_PTR_NULL_FATAL(stack.data);
  }

  Stack_t stack = stack_create(0);
  StackStatus_t status = stack_destroy(&stack);
  CU_ASSERT_EQUAL_FATAL(status, STACK_MEMORY_ERROR);

  stack = stack_create(10);
  free(stack.data);
  stack.data = NULL; // Simulate a memory error
  status = stack_destroy(&stack);
  CU_ASSERT_EQUAL_FATAL(status, STACK_MEMORY_ERROR);
  CU_ASSERT_EQUAL(stack.size, 0);
  CU_ASSERT_EQUAL(stack.capacity, 10);
  CU_ASSERT_PTR_NULL_FATAL(stack.data);

  stack = stack_create(SIZE_MAX);
  status = stack_destroy(&stack);
  CU_ASSERT_EQUAL_FATAL(status, STACK_MEMORY_ERROR);
  CU_ASSERT_EQUAL(stack.size, 0);
  CU_ASSERT_EQUAL(stack.capacity, 0);
  CU_ASSERT_PTR_NULL_FATAL(stack.data);
  
  status = stack_destroy(NULL);
  CU_ASSERT_EQUAL_FATAL(status, STACK_NULL_POINTER); // Test destroying a NULL stack

}

void test_stack_push(void){
  Stack_t stack = stack_create(10);

  for(size_t i = 0; i < 10; i++) {
    uint8_t value = (uint8_t)i;
    StackStatus_t status = stack_push(&stack, value);
    CU_ASSERT_EQUAL_FATAL(status, STACK_OK);
    CU_ASSERT_EQUAL(stack.size, i + 1);
    CU_ASSERT_EQUAL(stack.capacity, 10);
    CU_ASSERT_EQUAL(stack_get_at_index(&stack, i), (int) value);
  }
  
  StackStatus_t status = stack_push(&stack, 10);
  CU_ASSERT_EQUAL_FATAL(status, STACK_FULL); // Stack is full, should return STACK_FULL
  CU_ASSERT_EQUAL(stack.size, 10);
  CU_ASSERT_EQUAL(stack.capacity, 10);

  stack_destroy(&stack);

  status = stack_push(NULL, 10);
  CU_ASSERT_EQUAL_FATAL(status, STACK_NULL_POINTER); // Test pushing to a NULL stack

  Stack_t null_data_stack = (Stack_t) {0, 10, NULL};
  status = stack_push(&null_data_stack, 10);
  CU_ASSERT_EQUAL_FATAL(status, STACK_MEMORY_ERROR); // Test pushing to a stack with NULL data pointer data

}

void test_stack_pop(void){
  uint8_t value[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  Stack_t stack = stack_create(10);

  for(size_t i = 0; i < 10; i++) {
    StackStatus_t status = stack_push(&stack, value[i]);
    CU_ASSERT_EQUAL_FATAL(status, STACK_OK);
  }
  CU_ASSERT_EQUAL(stack.size, 10);
  CU_ASSERT_EQUAL(stack.capacity, 10);

  for(size_t i = 10; i > 0; i--) {
    uint8_t popped_value = 0;
    StackStatus_t status = stack_pop(&stack, &popped_value);
    CU_ASSERT_EQUAL_FATAL(status, STACK_OK);
    CU_ASSERT_EQUAL(popped_value, value[i - 1]);
    CU_ASSERT_EQUAL(stack.size, i - 1);
    CU_ASSERT_EQUAL(stack.capacity, 10);
  }

  uint8_t popped_value = 0;
  StackStatus_t status = stack_pop(&stack, &popped_value);
  CU_ASSERT_EQUAL_FATAL(status, STACK_EMPTY); // Stack is empty, should return STACK_EMPTY
  CU_ASSERT_EQUAL(stack.size, 0);
  CU_ASSERT_EQUAL(stack.capacity, 10);
  CU_ASSERT_EQUAL(popped_value, 0); // Popped value should keep its initial value

  status = stack_pop(NULL, &popped_value);
  CU_ASSERT_EQUAL_FATAL(status, STACK_NULL_POINTER); // Test popping from a NULL stack
  
  status = stack_pop(&stack, NULL);
  CU_ASSERT_EQUAL_FATAL(status, STACK_NULL_POINTER); // Test popping with a NULL value pointer

  status = stack_pop(NULL, NULL);
  CU_ASSERT_EQUAL_FATAL(status, STACK_NULL_POINTER); // Test popping from NULL stack and NULL value

  stack_destroy(&stack);

  Stack_t null_data_stack = (Stack_t) {0, 10, NULL};
  status = stack_pop(&null_data_stack, &popped_value);
  CU_ASSERT_EQUAL_FATAL(status, STACK_MEMORY_ERROR); // Test popping from a stack with NULL data pointer

}

void test_stack_peek(void){
  Stack_t stack = stack_create(10);
  uint8_t value[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for(size_t i = 0; i < 10; i++) {
    StackStatus_t status = stack_push(&stack, value[i]);
    CU_ASSERT_EQUAL_FATAL(status, STACK_OK);
    CU_ASSERT_EQUAL(stack.size, i + 1);
    CU_ASSERT_EQUAL(stack.capacity, 10);
  }

  uint8_t peeked_value = 0;
  uint8_t popped_value = 0;

  StackStatus_t status = stack_peek(&stack, &peeked_value);
  CU_ASSERT_EQUAL_FATAL(status, STACK_OK);
  CU_ASSERT_EQUAL(peeked_value, value[9]); // Peek should return the last pushed value
  CU_ASSERT_EQUAL(stack.size, 10);
  
  for(size_t i = 10; i > 1; i--) {
    status = stack_pop(&stack, &popped_value); // Pop to reduce size
    CU_ASSERT_EQUAL_FATAL(status, STACK_OK);
    CU_ASSERT_EQUAL(stack.size, i - 1);
    
    status = stack_peek(&stack, &peeked_value);
    CU_ASSERT_EQUAL_FATAL(status, STACK_OK);
    // Peek should return the current top value which is value at index i-2
    CU_ASSERT_EQUAL(peeked_value, value[i - 2]); 
    peeked_value = 0; // Reset peeked value for next iteration
    popped_value = 0; // Reset popped value for next iteration
  }

  status = stack_pop(&stack, &popped_value); // Pop the last element
  CU_ASSERT_EQUAL_FATAL(status, STACK_OK);

  peeked_value = 0; // Reset peeked value (This is for verbosity, not strictly necessary)
  status = stack_peek(&stack, &peeked_value);
  CU_ASSERT_EQUAL_FATAL(status, STACK_EMPTY); // Stack is empty now
  CU_ASSERT_EQUAL(peeked_value, 0); // Peek should not change the initial value of peeked_value

  status = stack_peek(NULL, &peeked_value);
  CU_ASSERT_EQUAL_FATAL(status, STACK_NULL_POINTER); // Test peeking from a NULL stack
  
  status = stack_peek(&stack, NULL);
  CU_ASSERT_EQUAL_FATAL(status, STACK_NULL_POINTER); // Test peeking with a NULL value pointer

  status = stack_peek(NULL, NULL);
  CU_ASSERT_EQUAL_FATAL(status, STACK_NULL_POINTER); // Test peeking from NULL stack and NULL value

  stack.size -= 1; // Simulate an invalid stack state
  status = stack_peek(&stack, &peeked_value);
  CU_ASSERT_EQUAL_FATAL(status, STACK_OVERFLOW); // Test peeking with an invalid stack size 
  
  stack_destroy(&stack);

  Stack_t null_data_stack = (Stack_t) {0, 10, NULL};
  status = stack_peek(&null_data_stack, &peeked_value);
  CU_ASSERT_EQUAL_FATAL(status, STACK_MEMORY_ERROR); // Test peeking from a stack with NULL data pointer
  CU_ASSERT_EQUAL(peeked_value, 0); // Peek should not change the initial value of peeked_value

}

void test_stack_get_size(void){
  Stack_t stack = stack_create(10);

  size_t size = stack_get_size(&stack);
  CU_ASSERT_EQUAL(size, 0); // Initially, the stack size should be 0

  for(size_t i = 0; i < 5; i++) {
    stack_push(&stack, (uint8_t)i);
    size = stack_get_size(&stack);
    CU_ASSERT_EQUAL(size, i + 1); // Size should match the number of elements pushed
    size = 0; // Reset size for next iteration
  }

  size = stack_get_size(NULL);
  CU_ASSERT_EQUAL_FATAL(size, 0); // Test getting size from a NULL stack

  stack_destroy(&stack);
  size = stack_get_size(&stack);
  CU_ASSERT_EQUAL_FATAL(size, 0); // Test getting size from a destroyed stack

  size = 10; // Reset size for next test
  Stack_t null_data_stack = (Stack_t) {3, 10, NULL};
  size = stack_get_size(&null_data_stack);
  CU_ASSERT_EQUAL(size, 0); // Size should be 0 for a stack with NULL data pointer
  
}

void test_stack_get_capacity(void){
  Stack_t stack = stack_create(10);
  size_t capacity = stack_get_capacity(&stack);
  CU_ASSERT_EQUAL(capacity, 10); // Initially, the stack capacity should be 10

  for(size_t i = 0; i < 5; i++) {
    stack_push(&stack, (uint8_t)i);
    capacity = stack_get_capacity(&stack);
    CU_ASSERT_EQUAL(capacity, 10); // Capacity should remain unchanged
    capacity = 0; // Reset capacity for next iteration
  }

  capacity = stack_get_capacity(NULL);
  CU_ASSERT_EQUAL_FATAL(capacity, 0); // Test getting capacity from a NULL stack

  stack_destroy(&stack);
  capacity = stack_get_capacity(&stack);
  CU_ASSERT_EQUAL(stack.capacity, 0);

  capacity = 10; // Reset capacity for next test
  Stack_t null_data_stack = (Stack_t) {10, 10, NULL};
  capacity = stack_get_capacity(&null_data_stack);
  CU_ASSERT_EQUAL_FATAL(capacity, 0); // Test getting capacity from a stack with NULL data pointer
}

void test_stack_clear(void){
  Stack_t stack = stack_create(10);
  
  while(!stack_is_full(&stack)){
    uint8_t top = 0;
    stack_push(&stack, 10);
    stack_peek(&stack, &top);
    CU_ASSERT_TRUE(top != 0);

  }

  CU_ASSERT_EQUAL(stack.capacity, 10);
  CU_ASSERT_EQUAL(stack.size, 10);

  StackStatus_t status = stack_clear(&stack);
  CU_ASSERT_EQUAL_FATAL(status, STACK_OK);

  for(size_t i = 0; i < stack.capacity; i++){
    // Could be done with EQUAL_FATAL but decided to use TRUE_FATAL to keep the same 
    // logic as the one described in the while loop above
    CU_ASSERT_TRUE_FATAL(stack.data[i] == 0);  
  }

  CU_ASSERT_EQUAL(stack.size, 0) 

  status = stack_clear(NULL);
  CU_ASSERT_EQUAL_FATAL(status, STACK_NULL_POINTER);
  
  stack_destroy(&stack);

  status = stack_clear(&stack);
  CU_ASSERT_EQUAL_FATAL(status, STACK_MEMORY_ERROR);

}

int add_stack_tests(CU_pSuite suite){
  if (NULL == suite) {
    return CUE_NOSUITE;
  }
  
  if(CU_add_test(suite, "test_stack_create", test_stack_create) == NULL ||
     CU_add_test(suite, "test_stack_destroy", test_stack_destroy) == NULL ||
     CU_add_test(suite, "test_stack_push", test_stack_push) == NULL ||
     CU_add_test(suite, "test_stack_pop", test_stack_pop) == NULL ||
     CU_add_test(suite, "test_stack_peek", test_stack_peek) == NULL ||
     CU_add_test(suite, "test_stack_get_size", test_stack_get_size) == NULL ||
     CU_add_test(suite, "test_stack_get_capacity", test_stack_get_capacity) == NULL ||
     CU_add_test(suite, "test_stack_clear", test_stack_clear) == NULL) {
    return CU_get_error();
  }

  return CUE_SUCCESS;
}

#endif // TEST_STACK_H

