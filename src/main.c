#include <stdio.h> 
#include "Hanoi.h"

int main(int argv, char** argc) {
  uint8_t num_disks = 3; // Default number of disks
  
  if (argv > 1) {
    int tmp = atoi(argc[1]);
    if (tmp > 0 && tmp <= UINT8_MAX) {
      num_disks = (uint8_t)tmp;
    } else {
      printf("Invalid number of disks, using default of 3\n\n");
    }
  }

  Hanoi_t hanoi = hanoi_init(num_disks, PRINT_MOVES);

  Status_t status = hanoi_solve(&hanoi);

  // printf("\n-------------------------\n");
  // hanoi_print(&hanoi);
  if (status != HANOI_OK) {
    printf("Error solving Tower of Hanoi: %d\n", status);
  }

  hanoi_destroy(&hanoi);

  return 0;
}
