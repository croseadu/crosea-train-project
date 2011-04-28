#include "../../../include/common.h"



int findKthSmallest(int a[], int k, int n);
int partion(int a[], int from, int end);

int main()
{
  int a[] = {0,7,9,1,4,5,6,3,2,8};
  int pos;
  char c;
  int data;
  int value;


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

      if (data > 9)
	{
	  printf("Array Size is smaller than you want to find\n");
	  exit(-1);
	}
      value = findKthSmallest(a, data, 9);

      printf("\nThe %dth Smallest Number is %d", data, value);
    }



  return 0;
}


int findKthSmallest(int a[], int k, int n)
{
  int from = 1, end = n;
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
