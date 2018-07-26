#pragma once

 

//矩阵乘法设计，
//M=A*B^T 充分利用缓存，减小miss
//所以矩阵B按列存储
int sgemm_tranB_f(float *aData, int aRows, int aCols, float *bData, int bRows, int bCols, float* mData, int mRows, int mCols);


//将bVec加到aVec中
int addVec(float *aVec,int aCols,float*bVec,int bCols);