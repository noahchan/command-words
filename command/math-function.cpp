#include "stdafx.h"
#include "math-function.h"

//#define VERSION_ORI 1
#define VERSION_LOOP  1
//#define SSE_OPT 1
//#define NEON_OPT 1

//高效的矩阵设计，
//M=A*B^T 充分利用缓存
//所以矩阵B按列存储
int sgemm_tranB_f(float *aData, int aRows, int aCols, float *bData, int bRows, int bCols, float* mData, int mRows, int mCols) {

	//判断传入的行列是否满足要求
	if (aCols != bRows || aRows != mRows || bCols != mCols)
		return -1;

	//原始版本
#if  VERSION_ORI
	for (int i = 0; i < mRows; i++) {
		for (int j = 0; j < mCols; j++) {
			float temp = 0.0;
			for (int k = 0; k < aCols; k++) {
				temp += aData[i*aRows + k] * bData[j*bCols + k];
			}
			mData[i*mRows + j] = temp;
		}
	}
#elif  VERSION_LOOP
	for (int i = 0; i < mRows; i++) {
		for (int j = 0; j < mCols; j++) {
			float temp = 0.0;
			int k = 0;
			for (; k < aCols-3; k+=4) {
				temp += aData[i*aRows + k] * bData[j*bCols + k];
				temp += aData[i*aRows + k] * bData[j*bCols + k+1];
				temp += aData[i*aRows + k] * bData[j*bCols + k+2];
				temp += aData[i*aRows + k] * bData[j*bCols + k+3];
			}
			for (; k < aCols; k ++) {
				temp += aData[i*aRows + k] * bData[j*bCols + k];
			}
			mData[i*mRows + j] = temp;
		}
	}

#endif //  VERSION_ORI

	return 0;
}

int addVec(float *aVec, int aCols, float*bVec, int bCols) {
	//判断传入的维数是否相同
	if (aCols != bCols)
		return -1;
#ifdef VERSION_ORI
	//原始版本
	for (int i = 0; i < aCols; i++) {
		aVec[i] += bVec[i];
	}
#elif  VERSION_LOOP
	int i = 0;
	for (; i < aCols-3; i+=4) {
		aVec[i] += bVec[i];
	}
	for (; i < aCols ; i ++) {
		aVec[i] += bVec[i];
	}
#endif // VERSION_ORI


	//TODO 展开和指令优化
	return 0;
}