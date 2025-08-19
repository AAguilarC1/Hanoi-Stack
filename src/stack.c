#include "stack.h"

Stack_t *stack_create(size_t capacity) {
  if (capacity == 0 || capacity > SIZE_MAX) {
    return NULL; // Invalid capacity
  }

  Stack_t *stack = (Stack_t *)malloc(sizeof(Stack_t));

  if (stack == NULL) {
    return NULL; // Memory allocation failed  
  }

  stack->data = (uint8_t *)calloc(capacity, sizeof(uint8_t));
  if (stack->data == NULL) {
    free(stack);
    return NULL; // Memory allocation failed
  }

  stack->size = 0;
  stack->capacity = capacity;

  return stack;
}

StackStatus_t stack_destroy(Stack_t *stack){
  if (stack == NULL) {
    return STACK_NULL_POINTER;
  }

  if (stack->data == NULL) {
    return STACK_MEMORY_ERROR; // Stack data pointer is NULL
  }

  stack_clear(stack);
  stack->capacity = 0; // Set capacity to 0 to avoid dangling pointer
  stack->size = 0; // Set size to 0 to avoid dangling pointer

  free(stack->data);
  stack->data = NULL; // Set data pointer to NULL to avoid dangling pointer

  free(stack);
  stack = NULL; // Set pointer to NULL to avoid dangling pointer

  return STACK_OK;
}

inline StackStatus_t stack_valid_index(size_t index, size_t capacity) {
  if (index >= capacity || index < 0) {
    return STACK_OUT_OF_BOUNDS; // Index out of bounds 
  }
  return STACK_OK; // Index is valid
}

inline StackStatus_t stack_set_at_index(Stack_t *stack, size_t index, uint8_t value){
  if (stack == NULL) {
    return STACK_NULL_POINTER; // Stack pointer is NULL
  }
  
  if (stack->data == NULL) {
    return STACK_MEMORY_ERROR; // Stack data pointer is NULL
  }

  StackStatus_t status = stack_valid_index(index, stack_get_capacity(stack));
  if (status != STACK_OK) {
    return status; // Invalid index
  }

  stack->data[index] = value; // Set the value at index
  return STACK_OK;
}

inline int stack_get_at_index(Stack_t *stack, size_t index){
  if (stack == NULL) {
    return STACK_NULL_POINTER; // Stack pointer is NULL
  }
  
  if (stack->data == NULL) {
    return STACK_MEMORY_ERROR; // Stack data pointer is NULL
  }

  StackStatus_t status = stack_valid_index(index, stack_get_capacity(stack));

  if (status != STACK_OK) {
    return status; // Invalid index
  }

  return stack->data[index]; // Get the value at index
}


StackStatus_t stack_clear(Stack_t *stack){
  if (stack == NULL) {
    return STACK_NULL_POINTER; // Stack pointer is NULL
  }
  
  if (stack->data == NULL) {
    return STACK_MEMORY_ERROR; // Stack data pointer is NULL
  }

  // if (stack_get_capacity(stack) <= 0) {
  //   return STACK_INVALID_CAPACITY; // Stack capacity is less than or equal to 0
  // }

  for(size_t i = 0; i < stack_get_capacity(stack); i++) {
    stack_set_at_index(stack, i, 0);

  }

  stack->size = 0; // Reset size to 0
  return STACK_OK;
}

StackStatus_t stack_push(Stack_t *stack, uint8_t value){
  if (stack == NULL) {
    return STACK_NULL_POINTER; // Stack pointer is NULL
  }
  
  if (stack->data == NULL) {
    return STACK_MEMORY_ERROR; // Stack data pointer is NULL
  }

  // if (stack_get_capacity(stack) <= 0) {
  //   return STACK_INVALID_CAPACITY; // Stack capacity is less than or equal to 0
  // }
  //
  // if (stack->size < 0) {
  //   return STACK_UNDERFLOW; // Stack size is negative
  // } 

  if (stack_get_size(stack) > stack_get_capacity(stack)) {
    return STACK_OVERFLOW; // Stack size exceeds capacity
  }
  
  if(stack_is_full(stack)){
    return STACK_FULL; // Stack is full
  }
  
  StackStatus_t status = stack_set_at_index(stack, stack_get_size(stack), value);

  stack->size++; // Increment size
  return status;
}

StackStatus_t stack_pop(Stack_t *stack, uint8_t *value){
  if (stack == NULL || value == NULL) {
    return STACK_NULL_POINTER; // Stack pointer is NULL
  }

  if (stack->data == NULL) {
    return STACK_MEMORY_ERROR; // Stack data pointer is NULL
  }
  //
  // if(stack_get_capacity(stack) <= 0) {
  //   return STACK_INVALID_CAPACITY; // Stack capacity is less than or equal to 0
  // }
  //
  // if (get_stack_size(stack) < 0) {
  //   return STACK_UNDERFLOW; // Stack size is negative
  // }

  if (stack_get_size(stack) > stack_get_capacity(stack)) {
    return STACK_OVERFLOW; // Stack size exceeds capacity
  }

  if (stack_is_empty(stack)) {
    return STACK_EMPTY; // Stack is empty
  }

  int tmp = stack_get_at_index(stack, stack_get_size(stack)-1);
  if (tmp < 0) {
    return tmp; // Error getting value at index
  }

  if(tmp > UINT8_MAX) {
    return STACK_OVERFLOW; // Value exceeds uint8_t range
  }

  *value = (uint8_t)tmp; // Get the value at the top of the stack
  tmp = stack_set_at_index(stack, stack_get_size(stack)-1, 0);

  if (tmp < 0) {
    return tmp; // Error setting value at Index
  }

  stack->size--; // Decrement size
  return STACK_OK;

}

int stack_peek(Stack_t *stack, uint8_t *value){
  if (stack == NULL || value == NULL) {
    return STACK_NULL_POINTER; // Stack pointer is NULL
  }

  if (stack->data == NULL) {
    return STACK_MEMORY_ERROR; // Stack data pointer is NULL
  }

  // if (stack_get_capacity(stack) <= 0) {
  //   return STACK_INVALID_CAPACITY; // Stack capacity is less than or equal to 0
  // }  
  //
  // if (get_stack_size(stack) < 0) {
  //   return STACK_UNDERFLOW; // Stack size is negative
  // }

  if (stack_get_size(stack) > stack_get_capacity(stack)) {
    return STACK_OVERFLOW; // Stack size exceeds capacity
  }

  if (stack_is_empty(stack)) {
    return STACK_EMPTY; // Stack is empty
  }

  int tmp = stack_get_at_index(stack, stack_get_size(stack)-1);
  if (tmp < 0) {
    return tmp; // Error getting value at index
  }

  if(tmp > UINT8_MAX) {
    return STACK_OVERFLOW; // Value exceeds uint8_t range
  }

  *value = (uint8_t)tmp; // Get the value at the top of the stack
  return STACK_OK;
}

StackStatus_t stack_get_size(Stack_t *stack, size_t *size){
  if (stack == NULL) {
    return STACK_NULL_POINTER; // Stack pointer is NULL
  }
  
  if (stack->data == NULL) {
    return STACK_MEMORY_ERROR; // Stack data pointer is NULL
  }

  if (size == NULL) {
    return STACK_NULL_POINTER; // Size pointer is NULL
  }

  *size = stack->size; // Get the size of the stack
  return STACK_OK;
}

StackStatus_t stack_get_capacity(Stack_t *stack, size_t *capacity){
  if (stack == NULL) {
    return STACK_NULL_POINTER; // Stack pointer is NULL
  }
  
  if (stack->data == NULL) {
    return STACK_MEMORY_ERROR; // Stack data pointer is NULL
  }

  if (capacity == NULL) {
    return STACK_NULL_POINTER; // Capacity pointer is NULL
  }

  *capacity = stack->capacity; // Get the capacity of the stack
  return STACK_OK;
}

StackStatus_t stack_print(Stack_t *stack){
  if (stack == NULL) {
    return STACK_NULL_POINTER; // Stack pointer is NULL
  }
  
  if (stack->data == NULL) {
    return STACK_MEMORY_ERROR; // Stack data pointer is NULL
  }

  printf("Stack size: %zu\n", stack->size);
  printf("Stack capacity: %zu\n", stack->capacity);
  printf("Stack contents: ");
  
  for (size_t i = 0; i < stack->size; i++) {
    printf("%d ", stack_get_at_index(stack, i));
  }
  
  printf("\n");
  return STACK_OK;
}

