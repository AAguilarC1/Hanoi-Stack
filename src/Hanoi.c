#include "Hanoi.h"
#include "stack.h"

Hanoi_t hanoi_init(unsigned int num_disks, PrintMoves_t print_moves){
  Hanoi_t hanoi = {0};

  if (num_disks <= 0 || num_disks > MAX_DISKS) {
    return (Hanoi_t){
      .source = {0},
      .target = {0},
      .auxiliary = {0},
      .num_disks = 0,
      .print_moves = NO_PRINT_MOVES
    }; // Invalid number of num_disks
  } 

  hanoi.num_disks = num_disks;
  hanoi.print_moves = print_moves;
  hanoi.source    = stack_create(num_disks);
  hanoi.target    = stack_create(num_disks);
  hanoi.auxiliary = stack_create(num_disks);

  if (hanoi.source.data == NULL || hanoi.target.data == NULL || hanoi.auxiliary.data == NULL) {
    return (Hanoi_t){
      .source = {0},
      .target = {0},
      .auxiliary = {0},
      .num_disks = 0,
      .print_moves = NO_PRINT_MOVES
    }; // Memory allocation failed
  }

  for (size_t i = num_disks; i > 0; i--) {
    stack_push(&hanoi.source, (uint8_t)i);
  }

  return hanoi;
}

Status_t hanoi_destroy(Hanoi_t *hanoi){
  if (hanoi == NULL) {
    return HANOI_NULL_POINTER;
  }

  if (hanoi->source.data == NULL || hanoi->target.data == NULL || hanoi->auxiliary.data == NULL) {
    return HANOI_MEMORY_ERROR; // One of the stacks' data pointer is NULL
  }

  StackStatus_t source_status    = stack_destroy(&hanoi->source);
  StackStatus_t target_status    = stack_destroy(&hanoi->target);
  StackStatus_t auxiliary_status = stack_destroy(&hanoi->auxiliary);

  if (source_status != STACK_OK || target_status != STACK_OK || auxiliary_status != STACK_OK) {
    return HANOI_MEMORY_ERROR; // Error destroying one of the stacks
  }

  *hanoi = (Hanoi_t){
    .source = {0},
    .target = {0},
    .auxiliary = {0},
    .num_disks = 0
  }; // Reset hanoi to default state

  return HANOI_OK;
  
}

Status_t hanoi_move_disk(Stack_t *from, Stack_t *to, PrintMoves_t print_moves, ...){
  va_list args;
  va_start(args, print_moves);
  const char* from_name = va_arg(args, const char*);
  const char* to_name = va_arg(args, const char*);
  va_end(args);

  if (from == NULL || to == NULL) {
    return HANOI_NULL_POINTER; // One of the pointers is NULL
  }

  if (from->data == NULL || to->data == NULL) {
    return HANOI_MEMORY_ERROR; // One of the stacks' data pointer is NULL
  }

  if (from == to) {
    return HANOI_ILLEGAL_MOVE; // Cannot move disk to the same stack
  }

  if(stack_is_empty(from) && stack_is_empty(to)) {
    return HANOI_NO_DISKS_TO_MOVE; // No disks to move from in both stacks
  }

  uint8_t disk = 0;
  uint8_t top_to_disk = 0;
  uint8_t top_from_disk = 0;

  stack_peek(to, &top_to_disk);
  stack_peek(from, &top_from_disk);

  if(stack_is_empty(to) || (!stack_is_empty(from) && top_from_disk < top_to_disk)){
    
    StackStatus_t push_status = stack_push(to, top_from_disk);
    if (push_status != STACK_OK) {
      // Error pushing disk to 'to' stack, put the disk back to the 'from' stack
      stack_push(from, disk);
      return HANOI_UNABLE_TO_MOVE_DISK; // Unable to move disk from 'from'-stack to 'to'-stack
    }

    StackStatus_t pop_status = stack_pop(from, &disk);

    if (pop_status != STACK_OK) {
      return HANOI_MEMORY_ERROR; // Error popping disk from 'from' stack
    }


  } else {
      return hanoi_move_disk(to, from, print_moves, to_name, from_name);
  }

  if (print_moves == PRINT_MOVES) {
    printf("Move disk %u from %s to %s\n", disk, from_name, to_name);
  }

  return HANOI_OK;
}

Status_t hanoi_solve(Hanoi_t *hanoi){
  if (hanoi == NULL) {
    return HANOI_NULL_POINTER; // Pointer is NULL
  }

  if (hanoi->source.data == NULL || hanoi->target.data == NULL || hanoi->auxiliary.data == NULL) {
    return HANOI_MEMORY_ERROR; // One of the stacks' data pointer is NULL
  }

  if (hanoi->num_disks <= 0 || hanoi->num_disks > MAX_DISKS) {
    return HANOI_INVALID_NUM_DISKS; // Invalid number of disks
  }

  size_t total_num_moves = (1 << hanoi->num_disks) - 1; 

  Stack_t *src = &hanoi->source;
  Stack_t *aux = &hanoi->auxiliary;
  Stack_t *tgt = &hanoi->target;
  
  char* src_name = (hanoi->print_moves == PRINT_MOVES) ? "Source" : "";
  char* aux_name = (hanoi->print_moves == PRINT_MOVES) ? "Auxiliary" : "";
  char* tgt_name = (hanoi->print_moves == PRINT_MOVES) ? "Target" : "";

  if (hanoi->num_disks % 2 == 0) {
    tgt = &hanoi->auxiliary;
    aux = &hanoi->target;

    char* temp = tgt_name;
    tgt_name = aux_name;
    aux_name = temp;

  }

  if (hanoi->print_moves == PRINT_MOVES) {
    printf("Total number of moves: %zu\n\n", total_num_moves);
    printf("Disk moves:\n");
    printf("--------------------------\n");
  }

  for (size_t i = 1; i <= total_num_moves; i++) {
    Status_t status = HANOI_OK;

    if (hanoi->print_moves == PRINT_MOVES){
      printf("Step %zu: ", i);
    }

    if (i % 3 == 0) {
      status = hanoi_move_disk(aux, tgt, hanoi->print_moves, aux_name, tgt_name);
    } else if (i % 3 == 1) {
      status = hanoi_move_disk(src, tgt, hanoi->print_moves, src_name, tgt_name);
    } else {
      status = hanoi_move_disk(src, aux, hanoi->print_moves, src_name, aux_name);
    }

    if (status != HANOI_OK) {
      return status; // Error moving disk
    }
  }
  if (hanoi->print_moves == PRINT_MOVES){
    printf("--------------------------\n");
  }

  return HANOI_OK;
}

Status_t hanoi_print(const Hanoi_t *hanoi){
  if (hanoi == NULL) {
    return HANOI_NULL_POINTER; // Pointer is NULL
  }

  if (hanoi->source.data == NULL || hanoi->target.data == NULL || hanoi->auxiliary.data == NULL) {
    return HANOI_MEMORY_ERROR; // One of the stacks' data pointer is NULL
  }

  printf("Number of disks: %u\n", hanoi->num_disks);

  printf("Source Stack:\n");
  if (stack_print((Stack_t*)&hanoi->source) != STACK_OK) {
    return HANOI_MEMORY_ERROR; // Error printing source stack
  }

  printf("Target Stack:\n");
  if (stack_print((Stack_t*)&hanoi->target) != STACK_OK) {
    return HANOI_MEMORY_ERROR; // Error printing target stack
  }

  printf("Auxiliary Stack:\n");
  if (stack_print((Stack_t*)&hanoi->auxiliary) != STACK_OK) {
    return HANOI_MEMORY_ERROR; // Error printing auxiliary stack
  }

  return HANOI_OK;
}

