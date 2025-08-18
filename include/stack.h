#ifndef STACK_H
#define STACK_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define stack_is_empty(__stack__) ((__stack__)->size == 0)
#define stack_is_full(__stack__) ((__stack__)->size >= (__stack__)->capacity)

struct Stack {
  size_t size;
  size_t capacity;
  uint8_t *data;
};
typedef struct Stack Stack_t;

enum StackStatus {
  STACK_OK = 0,
  STACK_FULL = -1,
  STACK_EMPTY = -2,
  STACK_INVALID = -3,
  STACK_MEMORY_ERROR = -4,
  STACK_NULL_POINTER = -5,
  STACK_UNDERFLOW = -6,
  STACK_OVERFLOW = -7
};
typedef enum StackStatus StackStatus_t;

Stack_t *stack_create(size_t capacity);
StackStatus_t stack_destroy(Stack_t *stack);
StackStatus_t stack_clear(Stack_t *stack);

StackStatus_t stack_valid_index(size_t index, size_t capacity);
StackStatus_t stack_set_at_index(Stack_t *stack, size_t index, uint8_t value);
int stack_get_at_index(Stack_t *stack, size_t index);

StackStatus_t stack_push(Stack_t *stack, uint8_t value);
StackStatus_t stack_pop(Stack_t *stack, uint8_t *value);
int stack_peek(Stack_t *stack, uint8_t *value);


StackStatus_t stack_get_size(Stack_t *stack, size_t *size);
StackStatus_t stack_get_capacity(Stack_t *stack, size_t *capacity);

StackStatus_t stack_print(Stack_t *stack);

#endif // STACK_H

