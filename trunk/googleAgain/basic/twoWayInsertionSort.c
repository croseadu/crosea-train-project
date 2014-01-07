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


int main()
{

  FILE *fp;
  int *a;
  int length;
  int capacity;
  int i, data;
  int *b;
  int first, last;
  int j, temp;

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

  b = (int * )malloc(sizeof(int) * length);
  if (NULL == b) {
    printf("Out Of Memory in %d", __LINE__);
    free(a);
    fclose(fp);
    exit(-1);
  }
  b[0] = a[0];
  first = last = 0;
  for (i = 1; i < length; ++i) {
    if (a[i] >= b[0]) {
      if (b[last] > a[i]) {
	temp = a[i];
	j = last;
	while (j >= 0 && b[j] > temp) {
	  b[j+1] = b[j];
	  --j;
	}
	b[j+1] = temp;
	++last;
      }
      else {
	b[++last] = a[i];
      }
    }
    else {
      if (first == 0) {
	first = length-1;
	b[first] = a[i];
      }
      else {
	if (a[i] > b[first]) {
	  j = first;
	  while (j < length && b[j] < a[i]) {
	    b[j-1] = b[j];
	    ++j;
	  }
	  b[j-1] = a[i];
	  --first;
	}
	else {
	  b[--first] = a[i];
	}
      }
    }
  }

  i = 0;
  while (first < length) {
    a[i++] = b[first++];
  }
  j = 0;
  while (i < length)
    a[i++] = b[j++];

  printf("\nAfter Sort is :\n");
  for (i = 0; i < length; ++i) {
    printf("%5d", a[i]);
    if ((i+1)%10 == 0)
      putchar('\n');
  }
  if ((i+1)%10)
    putchar('\n');

  fclose(fp);
  free(b);
  free(a);
  return 0;
}
