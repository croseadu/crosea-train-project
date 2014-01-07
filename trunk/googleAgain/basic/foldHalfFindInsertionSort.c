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
  int i,j, median, temp,data;
  int low, high;
  
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


  for (i = 1; i < length; ++i) {
    if (a[i] < a[i-1]) {
      temp = a[i];
      low = 0;
      high = i-1;
      while (low <= high) {
	median = (low + high)/2;
	if (a[median] > temp)
	  high = median - 1;
	else
	  low = median + 1;

      }
      printf("%d insert to %d\n", i, high+1);
      j = i-1;
      while (j > high) {
	a[j+1] = a[j];
	--j;
      }
      a[j+1] = temp;
    }
  
  }

  printf("\nAfter Sort is :\n");
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
