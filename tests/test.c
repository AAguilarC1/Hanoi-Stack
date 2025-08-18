#include<stdio.h>
#include<CUnit/Basic.h>
#include<CUnit/CUError.h>
 

 int initialize_suite() { return 0; }

 int clean_suite() { return 0; }

 //void test() { CU_ASSERT(1 == 1); }

 int main() { 
	CU_pSuite suite = NULL;

 	if (CUE_SUCCESS != CU_initialize_registry()){
 		 return CU_get_error();
	}

 	//suite = CU_add_suite("Suite", initialize_suite, clean_suite);

 	//CU_add_test(suite, "Test", test);

 	CU_basic_set_mode(CU_BRM_VERBOSE);

 	CU_basic_run_tests();

 	CU_cleanup_registry();

 	return CU_get_error(); 
}