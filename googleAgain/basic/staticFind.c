// 1. linear search on unsorted array.
// 2. fold-half search on sorted array.
// 3. fibonacci search on sorted array.

#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>


// return 0 means fail to find.
// a[0] is a guard
int search(int *a, int value, int end)
{
  int i = end -1;

  a[0] = value;
  for (; a[i] != value; --i);
  return i;
}

int foldHalfSearch(int *a, int value, int end)
{
  int low, high, median;

  low = 1;
  high = end-1;
  while (low <= high) {
    median = (low+high)/2;
    if (a[median] == value)
      return median;
    else if (a[median] > value) 
      high = median-1;
    else
      low = median+1;
  }
  return 0;
}

const int maxF = 15;
int findK(long long f[], int n)
{
  int i = maxF;
  while (i > 0) {
    if (f[i] >= n && f[i-1] < n)
      break;
    --i;
  }
  return i;
}

int fibonacciSearch(int *a, int value, int end)
{
  long long f[maxF+1];
  int i;
  int off = 0;
  int k;

  f[0] = 0;
  f[1] = 1;
  i = 2;
  while (i <= maxF) {
    f[i] = f[i-1] + f[i-2];
    ++i;
  } 

  /*
  printf("\n Dump fibonacci number:\n");
  for (i = 0; i <= maxF; ++i) {
    printf(" %d ", f[i]);
  }
  putchar('\n');
  */

  k = findK(f, end-1);
  
  while (k > 0) {
    if (off+f[k-1] >= end || 
	a[off+f[k-1]] > value) 
      --k;
    else if (a[off+f[k-1]] == value)
      break;
    else {
      off += f[k-1];
      k -= 2;
    }
  }
  
  if (k > 0)
    return f[k-1]+off;
  return 0;
}

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


void sort(int *a, int end)
{
  int i, j;
  int temp;

  for (i = 2; i < end; ++i) {
    if (a[i] < a[i-1]) {
      temp = a[i];
      j = i-1;
      while (j > 0 && a[j] > temp) {
	a[j+1] = a[j];
	--j;
      }
      a[j+1] = temp;
    }
  }
}
int main()
{
  FILE *fp;
  int *a;
  int length;
  int capacity;
  int idx, idx2;
  int data;
  int i;

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
    reserve(&a, &capacity, length+1);
    a[++length] = data;
  }

  printf("Input Array is :\n");
  for (i = 1; i <= length; ++i) {
    printf("%5d", a[i]);
    if ((i+1)%10 == 0)
      putchar('\n');
  }
  if ((i+1)%10)
    putchar('\n'); 
  
  sort(a, length+1);
  printf("After Sort:\n");
  for (i = 1; i <= length; ++i) {
    printf("%5d", a[i]);
    if ((i+1)%10 == 0)
      putchar('\n');
  }
  if ((i+1)%10)
    putchar('\n'); 

  idx = fibonacciSearch(a, a[1], length+1);
  idx2 = foldHalfSearch(a, a[1], length+1);
  printf("\nFind a[1] in a, idx is :%d and %d", idx, idx2);

  idx = fibonacciSearch(a, a[3], length+1);
  idx2 = foldHalfSearch(a, a[3], length+1);

  printf("\nFind a[3] in a, idx is :%d and %d", idx, idx2);

  idx = fibonacciSearch(a, a[5], length+1);
  idx2 = foldHalfSearch(a, a[5], length+1);

  printf("\nFind a[5] in a, idx is :%d and %d", idx, idx2);

  idx = fibonacciSearch(a, a[7], length+1);
  idx2 = foldHalfSearch(a, a[7], length+1);

  printf("\nFind a[7] in a, idx is :%d and %d", idx, idx2);

  idx = fibonacciSearch(a, a[length], length+1);
  idx2 = foldHalfSearch(a, a[length], length+1);

  printf("\nFind a[length %d] in a, idx is :%d and %d", length, idx, idx2);

  idx = fibonacciSearch(a, a[1]-1, length+1);
  idx2 = foldHalfSearch(a, a[1]-1, length+1);

  printf("\nFind non-exisit a[1]-1 in a, idx is :%d and %d", idx, idx2);

  idx = fibonacciSearch(a, a[length]+1, length+1);
  idx2 = foldHalfSearch(a, a[length]+1, length+1);
  printf("\nFind non-exisit a[length]+1 in a, idx is :%d and %d", idx, idx2);

  putchar('\n');
  fclose(fp);
  free(a);
  
}
