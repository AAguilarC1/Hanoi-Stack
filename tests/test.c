#include<CUnit/Basic.h>
#include "test_stack.h"
#include "test_hanoi.h"

int initialize_suite() { return 0; }

int clean_suite() { return 0; }

//void test() { CU_ASSERT(1 == 1); }

int main() { 
  if (CUE_SUCCESS != CU_initialize_registry()){
    return CU_get_error();
  }
  
  CU_pSuite suite_stack = CU_add_suite("Stack Suite", initialize_suite, clean_suite);
  
  if(CUE_SUCCESS != add_stack_tests(suite_stack)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
 
  CU_pSuite suite_hanoi = CU_add_suite("Hanoi Suite", initialize_suite, clean_suite);

  if(CUE_SUCCESS != add_hanoi_tests(suite_hanoi)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // suite = CU_add_suite("Suite", initialize_suite, clean_suite);
  //CU_add_test(suite, "Test", test);

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();

  CU_cleanup_registry();

  return CU_get_error(); 
}
