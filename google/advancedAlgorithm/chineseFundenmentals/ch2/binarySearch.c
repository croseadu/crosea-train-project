#include <stdio.h>

int a[10] = {19, 23, 35, 41,56,62,78,89,91,99};


int binarySearch(int low, int high, int key);
int binarySearch2(int low, int high, int key);

int main()
{
  int i;
  char c;
  int data;
  int pos;

  printf("\bArray: ");
  for (i = 0; i < 10; i++)
    printf("%4d", a[i]);
  putchar('\n');

  while(1)
    {
      printf("\nWant To Search(Y|N):");
      c = getchar();
      while (c == '\n')
	c = getchar();
      if (c != 'Y' && c != 'y')
	break;
      printf("\nInput Number You Want to Search:");
      scanf("%d", &data);
      putchar('\n');
      pos = binarySearch2(0, 9,data);
      if (pos >= 0)
	{
	  printf("Succes, In %d", pos);
	}
      else
	{
	  printf("Failed.");
	}
    }

  return 0;
}

int binarySearch(int low, int high, int key)
{
  int mid;
  while (low <= high)
    {
      mid = (low+high)/2;
      if (a[mid] == key)
	return mid;
      else if (a[mid] < key)
	{
	  low = mid+1;
	}
      else
	{
	  high = mid-1;
	}
    }
  return -1;
}
int binarySearch2(int low, int high, int key)
{
  int mid = (low+high)/2;
  while (low <= high)
    {
      mid = (low+high)/2;
      if (a[mid] > key)
	{
	  high = mid-1;
	}
      else
	{
	  low = mid+1;
	}
    }
  return a[high]==key?high:-1;
}
