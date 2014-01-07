#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char KeyType;

typedef struct _Cell
{
  KeyType data[4];
  int next;
}Cell, *LPCell;


#define INIT_SIZE 10
#define INCRE_SIZE 5

int getValue(LPCell pValue)
{
  unsigned int value;
  value = pValue->data[0];
  value |= (pValue->data[1]<<8);
  value |= (pValue->data[2]<<16);
  value |= (pValue->data[3]<<24);

  return value;
}
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
void distribute(LPCell sortList, int length, int idx, int *f, int *e);
void collect(LPCell sortList, int *f, int *e);


int main()
{
  FILE *fp;
  int *a = NULL;
  int data, length, capacity;
  int i, j;
  int *f, *e;
  unsigned int v;
  LPCell sortList;
  int p ,q;
  Cell temp;

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

  printf("Input Array is :\n");
  for (i = 0; i < length; ++i) {
    printf("%5d", a[i]);
    if ((i+1)%10 == 0)
      putchar('\n');
  }
  if ((i+1)%10)
    putchar('\n');

  sortList = (LPCell)malloc(sizeof(Cell)*(length+1));
  if (NULL == sortList) {
    printf ("Out Of Memory in %s", __func__);
    goto cleanup;
  }

  for (i = 0; i < length; ++i) {
    v = a[i];
    for (j = 0; j < 4; ++j) {
      sortList[i+1].data[j] = (v>>(j*8))&0xff;
    }
    sortList[i+1].next = i+2;
  }
  sortList[length].next = 0;
  sortList[0].next = 1;

  f = (int *)malloc(sizeof(int)*255);
  e = (int *)malloc(sizeof(int)*255);
  if (NULL == f || NULL == e)
    goto cleanup;

  printf ("\ninit list is :\n");
  for (i = 1; i <= length; ++i) {
    printf("%5d", getValue(sortList+i));
    if ((i+1)%10 == 0)
      putchar('\n');
  }
  putchar('\n');

  for (i = 0; i < 4; ++i) {
    distribute(sortList, length, i, f, e);
    collect(sortList, f, e);
  }

  printf("\nAfter list sort:\n");
  i = 0;
  j = sortList[0].next;
  while (j != 0) {
    printf("%5d", getValue(sortList+j));
    j = sortList[j].next;
    ++i;
    if ((i+1)%10 == 0)
      putchar('\n');
  }
  putchar('\n');


  p = sortList[0].next;
  for (i = 1; i <= length; ++i) {
    while (p < i)
      p = sortList[p].next;
    q = sortList[p].next;
    if (p != i) {
      temp = sortList[p];
      sortList[p] = sortList[i];
      sortList[i] = temp;
      sortList[i].next = p;
    }
    p = q;
  }

  printf("\nAfter rearrange:\n");
  for (i = 1; i <= length; ++i) {
    printf("%5d", getValue(sortList+i));
    if (i%10 == 0)
      putchar('\n');
  }
  putchar('\n'); 
  

 cleanup:
  if (f)
    free (f);
  if (e)
    free (e);
  if (sortList)
    free (sortList);
  if (a) 
    free (a);
  fclose(fp);
}



void distribute(LPCell sortList, int length, int idx, int *f, int *e)
{
  int i = 0;
  int j;

  for (i = 0; i < 256; ++i)
    f[i] = 0;

  for (i = sortList[0].next; i != 0; i = sortList[i].next) {
    j = sortList[i].data[idx];
    if (!f[j]) 
      f[j] = i;
    else
      sortList[e[j]].next = i;
    e[j] = i;
  }
}

int succ(int *f, int i)
{
  if (i == 255)
    return 256;
  while(!f[++i]);
  return i;
}

void collect(LPCell sortList, int *f, int *e)
{
  int i;
  int prev;
  i = 0;
  if (!f[i])
    i = succ(f, i);
  prev = 0;
  for (; i < 256; i = succ(f,i)) {
    sortList[prev].next = f[i];
    prev = e[i];
  }
    
  sortList[prev].next = 0;
}


