#include "stdafx.h"
#include "math-function.h"


//高效的矩阵设计，
//M=A*B^T 充分利用缓存
//所以矩阵B按列存储
int sgemm_tranB_f(float *aData, int aRows, int aCols, float *bData, int bRows, int bCols, float* mData, int mRows, int mCols) {

	//判断传入的行列是否满足要求
	if (aCols != bRows || aRows != mRows || bCols != mCols)
		return -1;

	//原始版本
	for (int i = 0; i < mRows; i++) {
		for (int j = 0; j < mCols; j++) {
			float temp = 0.0;
			for (int k = 0; k < aCols; k++) {
				temp += aData[i*aRows + k] * bData[j*bCols + k];
			}
			mData[i*mRows + j] = temp;
		}
	}
	//TODO 展开和指令优化
	return 0;
}

int addVec(float *aVec, int aCols, float*bVec, int bCols) {
	//判断传入的维数是否相同
	if (aCols != bCols)
		return -1;

	//原始版本
	for (int i = 0; i < aCols; i++) {
		aVec[i] += bVec[i];
	}
	//TODO 展开和指令优化
	return 0;
}