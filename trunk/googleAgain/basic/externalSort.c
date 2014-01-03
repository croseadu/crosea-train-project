#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define K 5

typedef struct _LoserTree
{
  unsigned int idx[K];
}LoserTree, *LPLoserTree;

typedef struct _External
{
  int key[K+1];
}External, *LPExternal;

#define MAX_KEY 0x7FFFFFFF
#define MIN_KEY -1


#define INIT_SIZE 10
#define INCRE_SIZE 5


void reserve(int **pArray, int *pCapacity, int i)
{
  int *p = *pArray;

  if (i < *pCapacity)
    return;

  p = realloc(p, sizeof(int)*(*pCapacity + INCRE_SIZE));
  if (NULL == p) {
    printf("Out Of Memory in %s", __func__);
    exit(-1);
  }
  *pCapacity = *pCapacity + INCRE_SIZE;
  *pArray = p;
}


void mergeK(int* []);
void internalSort(int *a, int n)
{
  int i = 0, j;
  int temp;

  for (i = 1; i < n; ++i) {
    if (a[i] < a[i-1]) {
      j = i-1;
      temp = a[i];
      while (j >= 0 && a[j] > temp) {
	a[j+1] = a[j];
	--j;
      }
      a[j+1] = temp;
    }
  }

}
int main()
{

  LoserTree loserTree;
  External external;
  int *a;
  int data, length, capacity;
  FILE *fp;
  int *disk[K] = {NULL};
  int m, k;
  int i, j;

  if ((fp = fopen("sort.txt", "r")) == NULL) {
    printf("Can't Open Input file\n");
    exit(-1);
  }

  length = 0;
  a = (int * )malloc(sizeof(int) * INIT_SIZE);
  if (NULL == a) {
    printf("Out Of Memory in %d", __LINE__);
    fclose(fp);
    exit(-1);
  }
  capacity = INIT_SIZE;
  while (fscanf(fp, "%d", &data) > 0) {
    reserve(&a, &capacity, length);
    a[length++] = data;
  }
  

  k = K;
  m = length/5;
  disk[0] = (int *)malloc(sizeof(int)*(length+5+length%5));
  if (NULL == disk[0]) {
    goto cleanup;
  }

  // init external storage

  disk[1] = disk[0] + m+1;
  disk[2] = disk[1] + m+1;
  disk[3] = disk[2] + m+1;
  disk[4] = disk[3] + m+1;
  memcpy(disk[0], a, sizeof(int)*m);
  disk[0][m] = MAX_KEY;
  memcpy(disk[1], a+m, sizeof(int)*m);
  disk[1][m] = MAX_KEY;
  memcpy(disk[2], a+2*m, sizeof(int)*m);
  disk[2][m] = MAX_KEY;
  memcpy(disk[3], a+3*m, sizeof(int)*m);
  disk[3][m] = MAX_KEY;
  memcpy(disk[4], a+4*m, sizeof(int)*(length-4*m));
  disk[4][length-4*m] = MAX_KEY;

  printf("Dump K Input Sequence:");
  for (i = 0; i < K; ++i) {
    printf("\nInput disk[%d] :", i);
    for (j = 0; disk[i][j] != MAX_KEY; ++j)
      printf("%5d", disk[i][j]);
  }
  putchar('\n');  
  printf("Sort Each segment:\n");
  for (i = 0; i < K; ++i)
    internalSort(disk[i], i < K-1?m+1:(length-4*m+1));
  for (i = 0; i < K; ++i) {
    printf("\nInput disk[%d] :", i);
    for (j = 0; disk[i][j] != MAX_KEY; ++j)
      printf("%5d", disk[i][j]);
  }
  putchar('\n');
  mergeK(disk);

 cleanup:
  if (a)
    free (a);
  if (disk[0])
    free (disk[0]);

  return 0;
}

void adjust(LPLoserTree pTree, int idx, LPExternal pExt)
{
  int f;
  int s = idx;
  int temp;

  f = (s+K)/2;
  while (f > 0) {

    if (pExt->key[s] > pExt->key[pTree->idx[f]]) {
      temp = s;
      s = pTree->idx[f];
      pTree->idx[f] = temp;
    } 
    f = f/2;
  }
  pTree->idx[0] = s;
}

void createLoserTree(LPLoserTree pTree, LPExternal pExt)
{
  int i;
  
  for (i = 0; i < K; ++i)
    pTree->idx[i] = K;
  pExt->key[K] = MIN_KEY;
  
  for (i = K-1; i >=0 ; --i)
    adjust(pTree, i, pExt);

  printf ("\nLoser Tree: ");
  for (i = 0; i < K; ++i) {
    printf("\nloser[%d] = %d, b[%d] = %d", i, pTree->idx[i], pTree->idx[i],pExt->key[pTree->idx[i]]);
  }
  putchar('\n');  
}

void mergeK(int *disk[])
{
  LoserTree loserTree;
  External external;
  int i;
  int cur[K] = {0};
  int value;
  int curMinIdx;
  int dumpCounter = 0;

  for (i = 0; i < K; ++i) {
    external.key[i] = disk[i][cur[i]++];
  }
  
  createLoserTree(&loserTree, &external);

  printf("\nStart External Sort:\n");
  while (external.key[loserTree.idx[0]] != MAX_KEY) {
    curMinIdx = loserTree.idx[0];
    value = external.key[curMinIdx];
    printf("%5d", value);
    dumpCounter++;
    if (dumpCounter%10 == 0)
      putchar('\n');
    external.key[curMinIdx] = disk[curMinIdx][cur[curMinIdx]];
    
    adjust(&loserTree, curMinIdx, &external);
    cur[curMinIdx]++;
  }
  putchar('\n');
}
