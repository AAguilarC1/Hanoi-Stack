#ifndef TEST_STACK_H
#define TEST_STACK_H
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include "stack.h"

void test_stack_create(void){
  Stack_t *stack = stack_create(0);
  CU_ASSERT_PTR_NULL_FATAL(stack);
  stack = stack_create(SIZE_MAX);
  CU_ASSERT_PTR_NULL_FATAL(stack);

  stack = stack_create(10);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack->data);
  CU_ASSERT_EQUAL(stack->size, 0);
  CU_ASSERT_EQUAL(stack->capacity, 10);
  stack_destroy(stack);

  stack = stack_create(100);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack->data);
  CU_ASSERT_EQUAL(stack->size, 0);
  CU_ASSERT_EQUAL(stack->capacity, 100);
  stack_destroy(stack);

  stack = stack_create(1000);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack->data);
  CU_ASSERT_EQUAL(stack->size, 0);
  CU_ASSERT_EQUAL(stack->capacity, 1000);
  stack_destroy(stack);

  stack = stack_create(10000);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack);
  CU_ASSERT_PTR_NOT_NULL_FATAL(stack->data);
  CU_ASSERT_EQUAL(stack->size, 0);
  CU_ASSERT_EQUAL(stack->capacity, 10000);
  stack_destroy(stack);

}

void test_stack_destroy(void){
  for(size_t i = 1; i < 100; i++){
    Stack_t *stack = stack_create(i);
    CU_ASSERT_PTR_NOT_NULL_FATAL(stack);
    CU_ASSERT_PTR_NOT_NULL_FATAL(stack->data);
    CU_ASSERT_EQUAL(stack->size, 0);
    CU_ASSERT_EQUAL(stack->capacity, i);

    StackStatus_t status = stack_destroy(stack);
    CU_ASSERT_EQUAL_FATAL(status, STACK_OK);
  }

  Stack_t *stack = stack_create(0);
  CU_ASSERT_EQUAL_FATAL(stack_destroy(stack), STACK_NULL_POINTER);

  stack = stack_create(10);
  free(stack->data);
  stack->data = NULL;
  CU_ASSERT_EQUAL_FATAL(stack_destroy(stack), STACK_MEMORY_ERROR);
  stack->capacity = 0;
  stack->size = 0;
  free(stack);

}

void test_stack_push(void){
  __asm volatile ("nop"); // Placeholder for assembly instruction }
}

void test_stack_pop(void){
  __asm volatile ("nop"); // Placeholder for assembly instruction }
}
void test_stack_peek(void){
  __asm volatile ("nop"); // Placeholder for assembly instruction }
}

void test_stack_get_size(void){
  __asm volatile ("nop"); // Placeholder for assembly instruction }
}
void test_stack_get_capacity(void){
  __asm volatile ("nop"); // Placeholder for assembly instruction }
}

void test_stack_clear(void){
  __asm volatile ("nop"); // Placeholder for assembly instruction }
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

