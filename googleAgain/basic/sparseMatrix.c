#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define N 10
#define M 8
ElementType matrix1[8][10] = 
{
  {0,4,0,0,0,0,-5,0,0,0},
  {0,0,0,6,0,0,0,-7,0,0},
  {-1,0,0,1,0,0,0,0,0,0},
  {0,9,0,0,0,0,0,0,0,-2},
  {0,0,0,0,0,0,0,0,3,0},
  {0,0,0,0,5,0,0,0,0,0},
  {0,0,4,0,0,0,0,0,0,11},
  {0,-5,0,0,0,0,0,0,0,0},
};

ElementType matrix2[10][9] = 
{
  {2,0,0,0,9,0,0,0,0},
  {0,6,0,7,0,10,0,0,0},
  {0,0,8,0,0,0,220,0,0},
  {0,0,0,0,0,0,0,330,0},
  {0,0,5,0,0,4,0,0,0},
  {0,-7,0,0,0,0,0,8,0},
  {-6,0,0,0,0,0,0,0,9},
  {0,6,0,0,0,0,0,0,0},
  {0,0,5,0,0,0,0,0,10},
  {0,0,0,4,0,0,0,0,-1},
};

ElementType matrix3[10][8];

typedef struct _Item
{
  unsigned int i;
  unsigned int j;
  ElementType data;
}Item, *LPItem;

typedef struct _SMatrix
{
  LPItem items;
  unsigned int row;
  unsigned int col;
  unsigned int numOfNonZeroItem;
}SMatrix, *LPSMatrix;

void printMatrix(ElementType (*pMatrix)[N], unsigned int m, unsigned int n)
{
  int i,j;
  printf("Matrix:\n");
  for(i = 0; i < m ; ++i) {
    for(j = 0; j < n; ++j){
      printf("%5d", (*(pMatrix+i))[j]);
    }
    putchar('\n');
  }
}

void printSMatrix(LPSMatrix pMatrix)
{
  int i,j;
  int k = 0;
  printf("SMatrix:\n");
  for (i = 0; i < pMatrix->row; ++i) {
    for (j = 0; j < pMatrix->col; ++j) {
      if (k < pMatrix->numOfNonZeroItem
	  && pMatrix->items[k].i == i 
	  && pMatrix->items[k].j == j) {
	printf("%5d", pMatrix->items[k].data);
	++k;
      }
      else {
	printf("%5d", 0);
      }
    }
    putchar('\n');
  }
}

bool createSMatrixFromMatrix(LPSMatrix *ppSMatrix, ElementType (*pMatrix)[N], 
			     unsigned int m, unsigned int n)
{
  LPSMatrix pSMatrix;
  int i, j, k;
  
  pSMatrix = (LPSMatrix)malloc(sizeof(SMatrix));
  if (NULL == pSMatrix) {
    printf("Out Of Memory in %s", __func__);
    return false;
  }
  
  k = 0;
  for (i = 0; i < m; ++i)
    for (j = 0; j < n; ++j)
      if ((*(pMatrix+i))[j] != 0)
	++k;
  pSMatrix->numOfNonZeroItem = k;
  pSMatrix->row = m;
  pSMatrix->col = n;

  pSMatrix->items = (LPItem)malloc(sizeof(Item) * k);
  if (NULL == pSMatrix->items) {
    free(pSMatrix);
    printf("Out Of Memory in %s", __func__);
    return false;
  }
  
  k = 0;
  for (i = 0; i < m; ++i)
    for (j = 0; j < n; ++j)
      if ((*(pMatrix + i))[j] != 0) {
	pSMatrix->items[k].i = i;
	pSMatrix->items[k].j = j;
	pSMatrix->items[k].data = (*(pMatrix + i))[j];
	++k;
      }
  *ppSMatrix = pSMatrix;
  return true;
}

void transposeMatrix(ElementType (*src)[N], ElementType (*dst)[M])
{
  int i,j;
  for (i = 0; i < M; ++i)
    for (j = 0; j < N; ++j)
      (*(dst+j))[i] = (*(src+i))[j];
}

void transposeSMatrix(LPSMatrix pSrc, LPSMatrix *ppDst)
{
  LPSMatrix pDst = NULL;
  int k;
  int i, j;

  pDst = (LPSMatrix)malloc(sizeof(SMatrix));
  if (NULL == pDst) {
    printf ("Out Of memory in %s", __func__);
    return;
  }
  pDst->items = (LPItem)malloc(sizeof(Item) * pSrc->numOfNonZeroItem);
  if (NULL == pDst->items) {
    free(pDst);
    printf ("Out Of Memory in %s", __func__);
    return;
  }

  pDst->row = pSrc->col;
  pDst->col = pSrc->row;
  pDst->numOfNonZeroItem = pSrc->numOfNonZeroItem;
  
  k = 0;
  for (i = 0; i < pDst->row; i++)
    for (j = 0; j < pDst->numOfNonZeroItem; ++j) {
      if (pSrc->items[j].j == i) {
	pDst->items[k].i = i;
	pDst->items[k].j = pSrc->items[j].i;
	pDst->items[k].data = pSrc->items[j].data;
	++k;
      }
    }
  *ppDst = pDst;
}

void transposeSMatrix2(LPSMatrix pSrc, LPSMatrix *ppDst)
{
  LPSMatrix pDst = NULL;
  int pos[N+1];
  int i,j,k;

  for (i = 0; i < N; ++i)
    pos[i] = 0;
  for (k = 0; k < pSrc->numOfNonZeroItem; ++k)
    ++pos[pSrc->items[k].j+1];

  for (i = 1; i < N; ++i)
    pos[i] += pos[i-1];


  pDst = (LPSMatrix)malloc(sizeof(SMatrix));
  if (NULL == pDst) {
    printf ("Out Of memory in %s", __func__);
    return;
  }
  pDst->items = (LPItem)malloc(sizeof(Item) * pSrc->numOfNonZeroItem);
  if (NULL == pDst->items) {
    free(pDst);
    printf ("Out Of Memory in %s", __func__);
    return;
  }

  pDst->row = pSrc->col;
  pDst->col = pSrc->row;
  pDst->numOfNonZeroItem = pSrc->numOfNonZeroItem;

  for (k = 0; k < pSrc->numOfNonZeroItem; ++k) {
    i = pos[pSrc->items[k].j];
    ++pos[pSrc->items[k].j];
    pDst->items[i].i = pSrc->items[k].j;
    pDst->items[i].j = pSrc->items[k].i;
    pDst->items[i].data = pSrc->items[k].data;
  }
    
  *ppDst = pDst;
}

int main()
{
  LPSMatrix pSMatrix = NULL;
  LPSMatrix pDstSMatrix = NULL;
  int i,j;

  printMatrix(matrix1, 8,10);
  createSMatrixFromMatrix(&pSMatrix, matrix1, 8, 10);
  printSMatrix(pSMatrix);
  
  transposeMatrix(matrix1, matrix3);
  printf("Matrix:\n");
  for(i = 0; i < N ; ++i) {
    for(j = 0; j < M; ++j){
      printf("%5d", matrix3[i][j]);
    }
    putchar('\n');
  }

  transposeSMatrix2(pSMatrix, &pDstSMatrix);
  printSMatrix(pDstSMatrix);

  free(pSMatrix->items);
  free(pSMatrix);
  return 0;
}
