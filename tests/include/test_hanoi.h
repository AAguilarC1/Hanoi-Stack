#ifndef TEST_HANOI_H //TEST_HANOI_H
#define TEST_HANOI_H
#include "stack.h"
#define HANOI_PRINT NO_PRINT_MOVES
#include "Hanoi.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void test_hanoi_init(void){
  Hanoi_t hanoi = hanoi_init(0, PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, 0);
  CU_ASSERT_EQUAL(hanoi.print_moves, NO_PRINT_MOVES);
  CU_ASSERT_TRUE_FATAL(hanoi.source.capacity == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.source.data == NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.target.capacity == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.target.data == NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.capacity == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.data == NULL);
  hanoi_destroy(&hanoi);
  
  hanoi = hanoi_init(UINT32_MAX + 1, PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, 0);
  CU_ASSERT_EQUAL(hanoi.print_moves, NO_PRINT_MOVES);
  CU_ASSERT_TRUE_FATAL(hanoi.source.capacity == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.source.data == NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.target.capacity == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.target.data == NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.capacity == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.data == NULL);

  hanoi_destroy(&hanoi);  

  hanoi = hanoi_init(5, PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, 5);
  CU_ASSERT_EQUAL(hanoi.print_moves, PRINT_MOVES);
  CU_ASSERT_TRUE_FATAL(hanoi.source.capacity == 5);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 5);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.source.data != NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.target.capacity == 5);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.target.data != NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.capacity == 5);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.auxiliary.data != NULL);

  hanoi_destroy(&hanoi);

  hanoi = hanoi_init(1, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, 1);
  CU_ASSERT_EQUAL(hanoi.print_moves, NO_PRINT_MOVES);
  CU_ASSERT_TRUE_FATAL(hanoi.source.capacity == 1);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 1);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.source.data != NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.target.capacity == 1);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.target.data != NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.capacity == 1);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.auxiliary.data != NULL);

  hanoi_destroy(&hanoi);

  hanoi = hanoi_init(21, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, 21);
  CU_ASSERT_EQUAL(hanoi.print_moves, NO_PRINT_MOVES);
  CU_ASSERT_TRUE_FATAL(hanoi.source.capacity == 21);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 21);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.source.data != NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.target.capacity == 21);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.target.data != NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.capacity == 21);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.auxiliary.data != NULL);
}

void test_hanoi_move_disk(void){
  Hanoi_t hanoi = hanoi_init(3, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, 3);
  CU_ASSERT_EQUAL(hanoi.print_moves, NO_PRINT_MOVES);
  CU_ASSERT_TRUE_FATAL(hanoi.source.capacity == 3);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 3);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.source.data != NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.target.capacity == 3);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.target.data != NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.capacity == 3);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.auxiliary.data != NULL);

  Status_t status = hanoi_move_disk(&hanoi.source, &hanoi.target, NO_PRINT_MOVES);

  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 2);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 1);
  CU_ASSERT_EQUAL_FATAL(hanoi.target.data[hanoi.target.size - 1], 1);

  status = hanoi_move_disk(&hanoi.source, &hanoi.auxiliary, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 1);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 1);
  CU_ASSERT_EQUAL_FATAL(hanoi.auxiliary.data[hanoi.auxiliary.size - 1], 2);

  status = hanoi_move_disk(&hanoi.source, &hanoi.auxiliary, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 2);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  CU_ASSERT_EQUAL_FATAL(hanoi.auxiliary.data[hanoi.auxiliary.size - 1], 0);
  CU_ASSERT_EQUAL_FATAL(hanoi.source.data[hanoi.source.size - 1], 2);

  Stack_t empty_stack1 = stack_create(3);
  Stack_t empty_stack2 = stack_create(3);
  Stack_t empty_stack3 = stack_create(3);

  status = hanoi_move_disk(&hanoi.source, &empty_stack1, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 1);

  status = hanoi_move_disk(&empty_stack2, &hanoi.source, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 0);

  status = hanoi_move_disk(&hanoi.target, &empty_stack3, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 0);

  status = hanoi_move_disk(&hanoi.source, &hanoi.target, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_NO_DISKS_TO_MOVE);

  status = hanoi_move_disk(&hanoi.target, &hanoi.target, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_ILLEGAL_MOVE);
  
  status = hanoi_move_disk(NULL, &hanoi.target, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_NULL_POINTER);

  status = hanoi_move_disk(&hanoi.source, NULL, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_NULL_POINTER);

  status = hanoi_move_disk(NULL, NULL, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_NULL_POINTER);

  free(empty_stack1.data);
  empty_stack1.data = NULL;
  status = hanoi_move_disk(&empty_stack1, &hanoi.target, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_MEMORY_ERROR);

  free(empty_stack2.data);
  empty_stack2.data = NULL;
  status = hanoi_move_disk(&hanoi.source, &empty_stack2, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_MEMORY_ERROR);
  
  stack_destroy(&empty_stack1);
  stack_destroy(&empty_stack2);
  stack_destroy(&empty_stack3);

  hanoi_destroy(&hanoi);

}

void test_hanoi_solve(void){
  Hanoi_t hanoi = hanoi_init(3, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, 3);
  CU_ASSERT_EQUAL(hanoi.print_moves, NO_PRINT_MOVES);
  CU_ASSERT_TRUE_FATAL(hanoi.source.capacity == 3);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 3);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.source.data != NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.target.capacity == 3);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.target.data != NULL);

  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.capacity == 3);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(hanoi.auxiliary.data != NULL);

  Status_t status = hanoi_solve(&hanoi);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 3);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);

  for (uint8_t i = 3; i > 0; i--) {
    CU_ASSERT_EQUAL_FATAL(hanoi.target.data[hanoi.target.size - i], i);
  }

  hanoi_destroy(&hanoi);
  
  hanoi = hanoi_init(5, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, 5);
 
  status = hanoi_solve(&hanoi);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 5);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);

  for (uint8_t i = 5; i > 0; i--) {
    CU_ASSERT_EQUAL_FATAL(hanoi.target.data[hanoi.target.size - i], i);
  }

  hanoi_destroy(&hanoi);

  hanoi = hanoi_init(10, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, 10);
  
  status = hanoi_solve(&hanoi);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 10);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  for (uint8_t i = 10; i > 0; i--) {
    CU_ASSERT_EQUAL_FATAL(hanoi.target.data[hanoi.target.size - i], i);
  }
  hanoi_destroy(&hanoi);

  hanoi = hanoi_init(20, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, 20);

  status = hanoi_solve(&hanoi);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == 20);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  for (uint8_t i = 20; i > 0; i--) {
    CU_ASSERT_EQUAL_FATAL(hanoi.target.data[hanoi.target.size - i], i);
  }
  hanoi_destroy(&hanoi);

  hanoi = hanoi_init(MAX_DISKS, NO_PRINT_MOVES);
  CU_ASSERT_EQUAL(hanoi.num_disks, MAX_DISKS);

  status = hanoi_solve(&hanoi);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_OK);
  CU_ASSERT_TRUE_FATAL(hanoi.source.size == 0);
  CU_ASSERT_TRUE_FATAL(hanoi.target.size == MAX_DISKS);
  CU_ASSERT_TRUE_FATAL(hanoi.auxiliary.size == 0);
  for (uint8_t i = MAX_DISKS; i > 0; i--){
    CU_ASSERT_EQUAL_FATAL(hanoi.target.data[hanoi.target.size - i], i);
  }

  status = hanoi_solve(NULL);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_NULL_POINTER);

  hanoi = hanoi_init(3, NO_PRINT_MOVES);
  free(hanoi.source.data);
  hanoi.source.data = NULL;
  status = hanoi_solve(&hanoi);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_MEMORY_ERROR);
  hanoi_destroy(&hanoi);

  hanoi = hanoi_init(3, NO_PRINT_MOVES);
  free(hanoi.target.data);
  hanoi.target.data = NULL;
  status = hanoi_solve(&hanoi);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_MEMORY_ERROR);
  hanoi_destroy(&hanoi);

  hanoi = hanoi_init(3, NO_PRINT_MOVES);
  free(hanoi.auxiliary.data);
  hanoi.auxiliary.data = NULL;
  status = hanoi_solve(&hanoi);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_MEMORY_ERROR);
  hanoi_destroy(&hanoi);

  hanoi = hanoi_init(3, NO_PRINT_MOVES);
  hanoi.num_disks = 0;
  status = hanoi_solve(&hanoi);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_INVALID_NUM_DISKS);

  hanoi.num_disks = MAX_DISKS + 1;
  status = hanoi_solve(&hanoi);
  CU_ASSERT_EQUAL_FATAL(status, HANOI_INVALID_NUM_DISKS);
  hanoi_destroy(&hanoi);

}

int add_hanoi_tests(CU_pSuite suite){
  if (NULL == suite) {
    return CUE_NOSUITE;
  }
  
  if(CU_add_test(suite, "test_hanoi_init", test_hanoi_init) == NULL ||
     CU_add_test(suite, "test_hanoi_move_disk", test_hanoi_move_disk) == NULL ||
     CU_add_test(suite, "test_hanoi_solve", test_hanoi_solve) == NULL) {
    return CU_get_error();
  }

  return CUE_SUCCESS;
}

#endif //TEST_HANOI_H
