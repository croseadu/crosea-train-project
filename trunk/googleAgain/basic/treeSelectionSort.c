
#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>


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


#define MAX_KEY 0x7FFFFFFF

int getValue(int *a, int idx, int size)
{
  if (idx < size)
    return a[a[idx]];
  else
    return a[idx];
}
int main()
{

  FILE *fp;
  int *a;
  int length;
  int capacity;
  int i,j, median, temp,data;
  int low, high;
  int f, idx;
  int *tree;

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

  tree = (int * )malloc(sizeof(int) * 2 * length);
  if (NULL == tree) {
    printf("Out Of Memory in %d", __LINE__);
    fclose(fp);
    exit(-1);
  }
  
  // Leaf Node contain Value
  for (i = length; i < 2*length; ++i)
    tree[i] = a[i-length];

  for (i = length-1; i > 0; --i) {
    if (getValue(tree, 2*i, length) < getValue(tree, 2*i+1, length))
      idx = 2*i;
    else
      idx = 2*i+1;
    tree[i] = idx > length-1?idx:tree[idx];
  }

  printf("Tree is :\n");
  for (i = 0; i < length; ++i) {
    printf("%5d", tree[i]);
    if ((i+1)%10 == 0)
      putchar('\n');
  }
  if ((i+1)%10)
    putchar('\n');

  for (i = 0; i < length; ++i) {
    a[i] = tree[tree[1]];
    idx = tree[1];
    tree[idx] = MAX_KEY;
    while (idx > 0) {
      f = idx/2;
      if (getValue(tree, 2*f, length) < getValue(tree, 2*f+1, length))
	tree[f] = 2*f > length-1?2*f:tree[2*f];
      else
	tree[f] = 2*f+1 > length-1?2*f+1:tree[2*f+1];
      idx = f;
    }
  }

  printf("Sort is :\n");
  for (i = 0; i < length; ++i) {
    printf("%5d", a[i]);
    if ((i+1)%10 == 0)
      putchar('\n');
  }
  if ((i+1)%10)
    putchar('\n');
  
  fclose(fp);
  free(a);
  return 0;
}
