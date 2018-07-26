#include "stdafx.h"
#include "math-function.h"

//#define VERSION_ORI 1
#define VERSION_LOOP  1
//#define SSE_OPT 1
//#define NEON_OPT 1

//��Ч�ľ�����ƣ�
//M=A*B^T ������û���
//���Ծ���B���д洢
int sgemm_tranB_f(float *aData, int aRows, int aCols, float *bData, int bRows, int bCols, float* mData, int mRows, int mCols) {

	//�жϴ���������Ƿ�����Ҫ��
	if (aCols != bRows || aRows != mRows || bCols != mCols)
		return -1;

	//ԭʼ�汾
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
	//�жϴ����ά���Ƿ���ͬ
	if (aCols != bCols)
		return -1;
#ifdef VERSION_ORI
	//ԭʼ�汾
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


	//TODO չ����ָ���Ż�
	return 0;
}