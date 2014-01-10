#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct _Tree
{
  ElementType data;
  struct _Tree *pLeftChild;
  struct _Tree *pRightChild;
}Tree, *LPTree;

int findMinDelta(int low, int high, float sw[])
{
  float dw = sw[high] + sw[low-1];
  int minIdx = low;
  float minDelta = sw[high]-sw[low];
  int i;
  for (i = low+1; i <= high; ++i) {
    float alt = dw - sw[i] - sw[i-1];
    if (alt < 0.0f)
      alt = -alt;
    if (minDelta > alt) {
      minIdx = i;
      minDelta = alt;
    }
  }

  return minIdx;
}

LPTree createSecondOptimalTree(ElementType a[], int low, int high, float sw[], float p[], bool adjRoot)
{
  int rootIdx;
  LPTree pRoot;
  int maxAdj;

  if (low > high)
    return NULL;

  rootIdx  = findMinDelta(low ,high, sw);
  pRoot = (LPTree)malloc(sizeof(Tree));
  if (NULL == pRoot) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }

  maxAdj = rootIdx;
  if (rootIdx > low && p[rootIdx-1] > p[maxAdj])
    maxAdj = rootIdx-1;
  if (rootIdx < high && p[rootIdx+1] > p[maxAdj])
    maxAdj = rootIdx+1;
  
  rootIdx = maxAdj;
  pRoot->data = a[rootIdx];
  
  if (rootIdx > low)
    pRoot->pLeftChild = createSecondOptimalTree(a, low, rootIdx - 1, sw, p, adjRoot);
  else
    pRoot->pLeftChild = NULL;
  if (rootIdx < high)
    pRoot->pRightChild = createSecondOptimalTree(a, rootIdx + 1, high, sw, p, adjRoot);
  else
    pRoot->pRightChild = NULL;
  return pRoot;
}


void preOrder(LPTree pRoot) {
  printf(" %c ",pRoot->data);
  if (pRoot->pLeftChild)
    preOrder(pRoot->pLeftChild);
  if (pRoot->pRightChild)
    preOrder(pRoot->pRightChild);
}

void inOrder(LPTree pRoot)
{
  if (pRoot->pLeftChild)
    inOrder(pRoot->pLeftChild);
  printf(" %c ",pRoot->data);
  if (pRoot->pRightChild)
    inOrder(pRoot->pRightChild);
}

void destroyTree(LPTree *ppTree)
{
  if ((*ppTree)->pLeftChild)
    destroyTree(&(*ppTree)->pLeftChild);
  if ((*ppTree)->pRightChild)
    destroyTree(&(*ppTree)->pRightChild);
  free(*ppTree);
  *ppTree = NULL;
}

int main()
{
  LPTree pTree;
  float p[] = {0.0f, 0.01f, 0.3f, 0.02f, 0.29f, 0.03f};
  char a[] = {' ', 'A', 'B', 'C', 'D', 'E'};
  float *sw;
  int i, n;

  n = sizeof(p)/sizeof(float)-1;

  sw = (float *)malloc(sizeof(p));
  if (NULL == sw) {
    printf ("Out Of Memory in %s", __func__);
    return 0;
  }
  
  sw[0] = 0.0f;
  for (i = 0; i <=n; ++i)
    sw[i] = sw[i-1] + p[i];

  pTree = createSecondOptimalTree(a, 1, n, sw, p, false);
  printf ("\npreOrder :\n");
  preOrder(pTree);
  printf ("\ninOrder: \n");
  inOrder(pTree);

  destroyTree(&pTree);

  pTree = createSecondOptimalTree(a, 1, n, sw, p, true);
  printf ("\npreOrder Adj :\n");
  preOrder(pTree);
  printf ("\ninOrder Adj: \n");
  inOrder(pTree);

  destroyTree(&pTree);

  free (sw);
  return 0;
}
