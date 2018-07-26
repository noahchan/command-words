#include "stdafx.h"
#include "math-function.h"


//��Ч�ľ�����ƣ�
//M=A*B^T ������û���
//���Ծ���B���д洢
int sgemm_tranB_f(float *aData, int aRows, int aCols, float *bData, int bRows, int bCols, float* mData, int mRows, int mCols) {

	//�жϴ���������Ƿ�����Ҫ��
	if (aCols != bRows || aRows != mRows || bCols != mCols)
		return -1;

	//ԭʼ�汾
	for (int i = 0; i < mRows; i++) {
		for (int j = 0; j < mCols; j++) {
			float temp = 0.0;
			for (int k = 0; k < aCols; k++) {
				temp += aData[i*aRows + k] * bData[j*bCols + k];
			}
			mData[i*mRows + j] = temp;
		}
	}
	//TODO չ����ָ���Ż�
	return 0;
}

int addVec(float *aVec, int aCols, float*bVec, int bCols) {
	//�жϴ����ά���Ƿ���ͬ
	if (aCols != bCols)
		return -1;

	//ԭʼ�汾
	for (int i = 0; i < aCols; i++) {
		aVec[i] += bVec[i];
	}
	//TODO չ����ָ���Ż�
	return 0;
}