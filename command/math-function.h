#pragma once

 

//����˷���ƣ�
//M=A*B^T ������û��棬��Сmiss
//���Ծ���B���д洢
int sgemm_tranB_f(float *aData, int aRows, int aCols, float *bData, int bRows, int bCols, float* mData, int mRows, int mCols);


//��bVec�ӵ�aVec��
int addVec(float *aVec,int aCols,float*bVec,int bCols);