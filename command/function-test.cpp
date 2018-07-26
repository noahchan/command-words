#include "stdafx.h"
#include "function-test.h"


int function_test() {


	if(test_sgemm_tranB_f())
		printf(" test_sgemm_tranB_f error\n");

	if(test_addVec())
		printf(" test_addVec error\n");

	return 0;
}
int test_sgemm_tranB_f() {

	float a[2] = { 1,2 };
	float b[4] = { 2,1,2,3 };
	//a*b^T

	float c[2];
	float res[2] = { 4,8 };

	int ret = 0;
	ret = sgemm_tranB_f(a, 1, 2, b, 2, 2, c, 1, 2);

	for (int i = 0; i < 2; i++) {
		if (c[i] != res[i]){
			printf("sgemm_f error.\n");
			return -1;
		}
	}
	return 0;
}

int test_addVec() {
	float a[4] = { 1,2,3,4 };
	float b[4] = { 2,1,2,3 };

	float res[4] = { 3,3,5,7 };

	int ret = 0;
	ret = addVec(a, 4, b, 4);

	for (int i = 0; i < 4; i++) {
		if (a[i] != res[i]) {
			printf("addvec error.\n");
			return -1;
		}
	}
	return 0;
}
