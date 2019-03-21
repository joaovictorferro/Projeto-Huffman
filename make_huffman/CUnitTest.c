#include "compress.h"
#include "decompress.h"
#include "hash.h"
#include "p_queue.h"
#include "tree.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int init_suite(void) {
	return 0;
}

int clear_suite(void) {
	return 0;
}

void hash_tests() {
	hash *newHash = NULL;
	CU_ASSERT(newHash == NULL);
	newHash = createHash(10);
	CU_ASSERT(newHash != NULL);
}

void huff_tree_tests(){

}

void p_queue_tests(){

}

int run_tests(){
	p_queue_tests();
	huff_tree_tests();
	hash_tests();
}

int main(){

	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("Basic_Test_Suite", init_suite, clear_suite);
	if(pSuite == NULL){
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "p_queue_tests", p_queue_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "huff_tree_tests", huff_tree_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "hash_tests", hash_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();

	return CU_get_error();
}

