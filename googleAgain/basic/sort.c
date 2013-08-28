#include <stdio.h>
#include <stdlib.h>


#define INIT_SIZE 10
#define INCRE_SIZE 5

typedef int BOOL;

int selectMin(int a[], int start, int end);
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

void bubbleSort(int a[], int N);
void insertSort(int a[], int N);
void selectSort(int a[], int N);
void shellSort(int a[], int N);
void mergeSort(int a[], int N);
void quickSort(int a[], int N);
void heapSort(int a[], int N);
int main()
{
  FILE *fp;
  int *a = NULL;
  int data, length, capacity;
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

  //bubbleSort(a, length);
  //insertSort(a, length);
  //selectSort(a, length);
  //quickSort(a, length);
  //heapSort(a, length);
  //shellSort(a, length);
  mergeSort(a, length);

  printf("After sort Array is :\n");
  for (i = 0; i < length; ++i) {
    printf("%5d", a[i]);
    if ((i+1)%10 == 0)
      putchar('\n');
  }
  if ((i+1)%10)
    putchar('\n');

  return 0;

}


void bubbleSort(int a[], int N)
{
  int i,j;
  BOOL isChanged = 0;
  int temp;

  for (i = N; i > 1; --i) {
    isChanged = 0;
    for (j = 0; j < i-1; ++j) {
      if (a[j] > a[j+1]) {
	isChanged = 1;
	temp = a[j];
	a[j] = a[j+1];
	a[j+1] = temp;
      }
    }
    if (isChanged == 0)
      break;
  }
}

void insertSort(int a[], int N)
{
  int i,j, data;
  for (i = 1; i < N; ++i) {
    if (a[i] >= a[i-1])
      continue;
    data = a[i];
    for (j = i-1; j >= 0; --j) {
      if (a[j] > data) {
	a[j+1] = a[j];
      }
      else
	break;
    }
    a[j+1] = data;
  }
}

int selectMin(int a[], int start, int end)
{
  int min = start;
  int i = start+1;
  while(i < end) {
    if (a[i] < a[min])
      min = i;
    ++i;
  }
  return min;
}

void selectSort(int a[], int N)
{
  int i;
  int minIndex;
  int temp;
  for (i = 0; i < N-1; ++i) {
    minIndex = selectMin(a, i, N);
    if (minIndex != i) {
      temp = a[i];
      a[i] = a[minIndex];
      a[minIndex] = temp;
    }
  } 
}

int partition(int a[], int start, int end)
{
  int key = a[start];
  int low = start, high = end-1;
  while (low < high) {
    while (high > low && a[high] >= key)
      --high;
    a[low] = a[high];
    while (low < high && a[low] <= key)
      ++low;
    a[high] = a[low];
  }
  a[low] = key;
  return low;
}

void qSort(int a[], int start, int end)
{
  if (start +1 >= end)
    return;
  int pivot = partition(a, start, end);
  qSort(a, start, pivot);
  qSort(a, pivot+1, end);

}

void quickSort(int a[], int N)
{
  qSort(a, 0, N);
}

void heapAdjust(int a[], int start, int end)
{
  int i = start;
  int t = a[i];
  int j;
  for (; 2*i <= end;) {
    j = 2*i;
    if (j+1<= end && a[j+1] > a[j])
      ++j;
    if (a[j] <= t)
      break;
    a[i] = a[j];
    i = j;
  }
  a[i] = t;
 
}

void heapSort(int a[], int N)
{
  int i = N/2;
  int temp;

  for (;i >= 0; --i)
    heapAdjust(a, i, N-1);

  for (i = N-1; i >0; --i) {
    temp = a[i];
    a[i] = a[0];
    a[0] = temp;
    heapAdjust(a, 0, i-1);
  }
}

void shellSort(int a[], int N)
{
  int d[] = {5, 3, 1};
  int i, j, k;
  int key;

  for (k = 0; k < sizeof(d)/sizeof(int); ++k) {
    for (i = 1; i < N; ++i) {
      if (i-d[k]< 0 || a[i-d[k]] <= a[i])
	continue;
      key = a[i];
      for (j = i - d[k]; j >=0 && a[j] > key; j-=d[k]) {
	a[j+d[k]] = a[j];
      }
      a[j+d[k]] = key;
    }
  }
}

void merge(int src[], int dst[], int start, int end)
{
  int middle = (start+end)/2;
  int i,j,k;
  k=start, i = start, j = middle+1;
  while(i <= middle && j <= end) {
    if (src[i] <= src[j]) {
      dst[k++] = src[i++];
    }
    else
      dst[k++] = src[j++];
  }
  while (i <= middle)
    dst[k++] = src[i++];
  while (j <= end)
    dst[k++] = src[j++];
}

void mSort(int src[], int dst[], int start, int end)
{
  int middle;
  int *tmp;
  if (start > end)
    return;
  else if (start == end) {
    dst[start] = src[start];
    return;
  }

  tmp = (int *)malloc(sizeof(int)*(end+1));
  middle = (start + end)/2;
  mSort(src, tmp, start, middle);
  mSort(src, tmp, middle+1, end);
  merge(tmp, dst, start, end);
  free(tmp);
}

void mergeSort(int a[], int N)
{
  mSort(a, a,0, N-1);
  
}
