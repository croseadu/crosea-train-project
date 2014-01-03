#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct _Cell
{
  ElementType data;
  int next;
}Cell, *LPCell;


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


int main()
{
  FILE *fp;
  int *a = NULL;
  int data, length, capacity;
  int i;
  LPCell sortList = NULL;
  int j;
  int p, q;
  int prev, last;
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
    sortList[i+1].data = a[i];
    sortList[i+1].next = i+2;
  }
  sortList[length].next = 0;
  
  j = 2;
  sortList[0].next = 1;
  sortList[1].next = 0;
  last = 1;
  while (j <= length) {
    if (sortList[j].data < sortList[last].data) {
      prev = 0;
      while (sortList[prev].next && sortList[sortList[prev].next].data <= sortList[j].data)
	prev = sortList[prev].next;
      sortList[j].next = sortList[prev].next;
      sortList[prev].next = j;
    }
    else {
      sortList[last].next = j;
      sortList[j].next = 0;
      last = j;
    }
    ++j;
  }

  j = sortList[0].next;
  i = 0;
  printf("\nAfter list sort:\n");
  while (j != 0) {
    printf("%5d", sortList[j].data);
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
      //swap p  i
      temp = sortList[p];
      sortList[p] = sortList[i];
      sortList[i] = temp;
      sortList[i].next = p;
    }
    p = q;
  }


  printf("\nAfter Adjust: \n");
  for (i = 1; i <= length; ++i) {
    printf("%5d", sortList[i].data);
    if (i%10 == 0)
      putchar('\n');
  }
  putchar('\n');

  free (sortList);
 cleanup:
  free (a);
  fclose(fp);
}







