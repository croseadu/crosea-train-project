#include "../../../include/common.h"




int findKthSmallestOptimal(int a[], int k, int size);

int main()
{
  int a[35], b[35];
  int i;
  char c;
  int data, value;

  srand((int)time(0));
  

  for (i = 0; i < 35; i++)
    {
      int temp;
      temp = rand();
      
      a[i] = (temp%100 + (temp/100)%100)%100;
      b[i] = a[i];
    }
  
  printf("\bRand Array is :\n");
  for (i = 0; i < 35; i++)
    printf("%4d%s", a[i], ((i+1)%7)?"":"\n");
  putchar('\n');

  
  while(1)
    {
      printf("\nWant To Find Kth (Y|N):");
      c = getchar();
      while (c == '\n')
	c = getchar();
      if (c != 'Y' && c != 'y')
	break;
      printf("\nInput Kth You Want to Find:");
      scanf("%d", &data);
      putchar('\n');
      if (data > 34)
	{
	  printf("Array Size is smaller than you want to find\n");
	  exit(-1);
	}
      value = findKthSmallestOptimal(a, data-1, 34);

      printf("\nThe %dth Smallest Number is %d", data, value);
    }

  return 0;
}

int partion(int a[], int from, int end)
{
  int temp = a[from];
  int low = from, high = end;
  while(low < high)
    {
      while (low < high && a[high] >= temp)
	high--;
      a[low] = a[high];
      while(low < high && a[low] <= temp)
	low++;
      a[high] = a[low];
    }
  a[low] = temp;
  return low;
}

#define R 7
int findKthSmallest(int a[], int k, int n)
{
  int from = 0, end = n;
  int pivot;

  while(1)
    {
      pivot = partion(a, from, end);
      if (pivot == k)
	return a[pivot];
      else if (pivot < k)
	from = pivot+1;
      else
	end = pivot-1;
       
    }
}
int findKthSmallestOptimal(int a[], int k, int size)
{
  int *m;
  int i, j;
  int middle, temp, pivot;


  if (size <= R)
    return findKthSmallest(a, k, size);
  
  m = (int *)malloc((size+1)/R);
  if (m == NULL)
    {
      printf("Out Of Memory In Line %d, Function %s", __LINE__,__FUNCTION__);
      exit(OVERFLOW);
    }
  putchar('\n');
  printf("M:");
  for (i = 0; i < (size+1)/R; i++)
    {
      m[i] = findKthSmallest(a+i*R, R/2, R-1);
      printf("%4d", m[i]);
    }
  putchar('\n');

  printf("\bAfter Found M Array is :\n");
  for (i = 0; i <= size; i++)
    printf("%4d%s", a[i], ((i+1)%7)?"":"\n");
  putchar('\n');

  middle = findKthSmallest(m, ((size+1)/R)/2, (size+1)/R);
  free(m);
  for (i = 0; i < size; i++)
    if (middle == a[i])
      break;

  assert(i < size);
  printf("\nFound the Middle is a[%d] = %d", i , a[i]);
  temp = a[0];
  a[0] = a[i];
  a[i] = temp;
  

  pivot = partion(a, 0, size);
  if (pivot == k)
    return a[pivot];
  else if (pivot < k)
    return findKthSmallestOptimal(a+pivot+1, k-pivot, size-pivot-1);
  else
    return findKthSmallestOptimal(a, k, pivot-1);

}

