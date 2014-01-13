
#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>


#define N 5

typedef struct _Tree
{
  char data;
  struct _Tree *pLeftChild;
  struct _Tree *pRightChild;
}Tree, *LPTree;

void preOrder(LPTree pRoot) {
  putchar(pRoot->data);
  printf("(%c,%c)", pRoot->pLeftChild?pRoot->pLeftChild->data:' ',
	 pRoot->pRightChild?pRoot->pRightChild->data:' ');
  if (pRoot->pLeftChild)
    preOrder(pRoot->pLeftChild);
  if (pRoot->pRightChild)
    preOrder(pRoot->pRightChild);
}

void inOrder(LPTree pRoot) {
  if (pRoot->pLeftChild)
    inOrder(pRoot->pLeftChild);
  putchar(pRoot->data);
  if (pRoot->pRightChild)
    inOrder(pRoot->pRightChild); 
}

void calcOptimalSearchTreeV2(float p[N+1], int r[N+1][N+1])
{
  float sw[N+1];
  int i, k, l;
  float alt;
  float minCost;
  int minIdx;
  float c[N+1][N+1];
  
  sw[0] = 0.0f;
  for (i = 1; i <= N; ++i)
    sw[i] = sw[i-1] + p[i];

  for (i = 0; i <= N; ++i)
    c[i][i] = 0.0f;

  for (l = 1; l <= N; ++l)
    for (i = 0; i <= N - l; ++i) {
      minIdx = i+1;
      minCost = c[i][minIdx-1] + c[minIdx][i+l];
      for (k = minIdx+1; k <= i+l; ++k) {
	alt = c[i][k-1] + c[k][i+l];
	if (alt < minCost) {
	  minIdx = k;
	  minCost = alt;
	}
      }
      
      c[i][i+l] = minCost + sw[i+l] - sw[i];
      r[i][i+l] = minIdx;
    }


}

void calcOptimalSearchTree(float p[N+1], int r[N+1][N+1])
{
  float sw[N+1];
  int i;
  float c[N+1][N+1];
  int j, k, minIdx;
  float minCost;
  float alt;

  sw[0] = 0.0f;
  
  for (i = 1; i <= N; ++i)
    sw[i] = sw[i-1]+p[i];
  
  for (i = 1; i <= N; ++i) {
    c[i][i] = p[i];
    r[i][i] = i;
  }

  for (i = 2; i <= N; ++i)
    for (j = 1; j <= N - i + 1; ++j) {
      minIdx = j;
      minCost = c[j+1][j+i-1];
      for (k = j+1; k < j+i-1; ++k) {
	alt = c[j][k-1] + c[k+1][j+i-1];
	if (alt < minCost) {
	  minCost = alt;
	  minIdx = k;
	}
      }
      if (minCost > c[j][j+i-2]) {
	minIdx = j+i-1;
	minCost = c[j][j+i-2];
      }
      c[j][j+i-1] = sw[j+i-1] - sw[j-1]+minCost;
      r[j][j+i-1] = minIdx;
    }
}

LPTree buildOptimalSearchTreeV2(char a[N+1], int r[N+1][N+1], int start, int end)
{
  LPTree pRoot;
  int rootIdx;

  if (start >= end)
    return NULL;
  pRoot = (LPTree)malloc(sizeof(Tree));
  if (NULL == pRoot) {
    printf ("Out OF Memory in %s", __func__);
    return NULL;
  }

  rootIdx = r[start][end];
  pRoot->data = a[rootIdx];
  pRoot->pLeftChild = buildOptimalSearchTreeV2(a, r, start, rootIdx-1);
  pRoot->pRightChild = buildOptimalSearchTreeV2(a, r, rootIdx, end);
  return pRoot;
}

LPTree buildOptimalSearchTree(char a[N+1], int r[N+1][N+1], int start, int end)
{
  LPTree pRoot;
  int rootIdx;

  if (start > end)
    return NULL;
  pRoot = (LPTree)malloc(sizeof(Tree));
  if (NULL == pRoot) {
    printf ("Out OF Memory in %s", __func__);
    return NULL;
  }

  rootIdx = r[start][end];
  pRoot->data = a[rootIdx];
  pRoot->pLeftChild = buildOptimalSearchTree(a, r, start, rootIdx-1);
  pRoot->pRightChild = buildOptimalSearchTree(a, r, rootIdx+1, end);
  return pRoot;
}

void destroyTree(LPTree *ppRoot) {
  LPTree pRoot = *ppRoot;
  if (pRoot->pLeftChild)
    destroyTree(&pRoot->pLeftChild);
  if (pRoot->pRightChild)
    destroyTree(&pRoot->pRightChild);
  free(pRoot);
  *ppRoot = NULL;
}


int main()
{
  //char a[N+1] = {};
  //float p[N+1] = {};

  float p[] = {0.0f, 0.01f, 0.3f, 0.02f, 0.29f, 0.03f};
  char a[] = {' ', 'A', 'B', 'C', 'D', 'E'};
  int r[N+1][N+1];
  LPTree pRoot = NULL;

  //calcOptimalSearchTree(p, r);
  calcOptimalSearchTreeV2(p, r);

  //pRoot = buildOptimalSearchTree(a, r, 1, N);
  pRoot = buildOptimalSearchTreeV2(a, r, 0, N);

  printf ("PreOrder:\n");
  preOrder(pRoot);
  printf("\nInOrder:\n");
  inOrder(pRoot);

  destroyTree(&pRoot);

  return 0;
}




