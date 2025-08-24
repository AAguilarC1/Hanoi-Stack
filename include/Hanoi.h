#ifndef HANOI_H
#define HANOI_H
#include "stack.h"

enum Status {
  HANOI_OK = 0,
  HANOI_NULL_POINTER = -1,
  HANOI_MEMORY_ERROR = -2,
  HANOI_INVALID_NUM_DISKS = -3,
  HANOI_NO_DISKS_TO_MOVE = -4,
  HANOI_ILLEGAL_MOVE = -5,
  HANOI_UNABLE_TO_MOVE_DISK = -6
};
typedef enum Status Status_t;

struct Hanoi {
  Stack_t source;
  Stack_t target;
  Stack_t auxiliary;
  unsigned int num_disks;
};
typedef struct Hanoi Hanoi_t;

Hanoi_t hanoi_init(unsigned int num_disks);
Status_t hanoi_destroy(Hanoi_t *hanoi);

Status_t hanoi_move_disk(Stack_t *from, Stack_t *to, const char* from_name, const char* to_name);
Status_t hanoi_solve(Hanoi_t *hanoi);

Status_t hanoi_print(const Hanoi_t *hanoi);

#endif // HANOI_H
