#include "../../../include/common.h"


void mergeSort(int array[], int link[], int from, int end, int *pFirst);
void merge(int array[], int link[],int firstLink, int secondLink, int *pResult);
void arrange(int array[], int link[], int size);
int main()
{

  int a[21] = {0,87, 1, 45, 23,102,567,230, 21,77,56,
	       90, 12,64, 35,48, 25, 76,  34,88,63};
  int l[21];
  int *link;
  int first;
  int i;

  memset(l, 0, sizeof(l));
  link = l;

  mergeSort(a, link, 1, 20, &first);

  printf("\nSort Link is :\n");
  printf("\nLeader:%d", l[0]);
  for (i = 1; i <=20; i++)
    {
      printf("%4d[N:%d]", a[i], link[i]);
    }
  putchar('\n');
  printf("Output by Link:\n");
  i = first;
  while (i)
    {
      printf("%4d", a[i]);
      i = link[i];
    }

  arrange(a, l,20);
  printf("\nAfter Arrange by link:\n");
  for (i = 1; i <=20; i++)
    printf("%4d", a[i]);

  return 0;
}


void mergeSort(int array[], int link[], int from, int end, int *pFirst)
{
  int q,r,p;

  if (end - from <= 1)
    {
      if (end == from)
	{
	  *pFirst = end;
	  link[end] = 0;
	}
      else
	{
	  if (array[end] > array[from])
	    {
	      *pFirst = from;
	      link[from] = end;
	      link[end] = 0;
	    }
	  else
	    {
	      *pFirst = end;
	      link[end] = from;
	      link[from] = 0;
	    }
	}
    }
  else
    {
      int mid = (from+end)/2;
      mergeSort(array, link, from, mid, &q);
      mergeSort(array, link, mid+1, end, &r);
      merge(array, link, q,r,&p);
      *pFirst = p;
      
    }

}

void merge(int array[], int link[],int firstLink, int secondLink, int *pResult)
{
  int i, j, prev = 0;
  i = firstLink;
  j = secondLink;

  while (i !=0 && j != 0)
    {
      if (array[i] < array[j])
	{
	  link[prev] = i;
	  prev = i;
	  i = link[i];
	}
      else
	{
	  link[prev] = j;
	  prev = j;
	  j = link[j];
	}
    }

  if (i != 0)
    link[prev] = i;
  else
    link[prev] = j;
  *pResult = link[0];
}


void arrange(int array[], int link[], int size)
{
  int i, p, q;
  int temp;

  for (i = 1, p = link[0]; i < size; i++)
    {
      while (p < i)
	{
	  p = link[p];
	}
      if (p == i)
	{
	  p = link[p];
	}
      else
	{
	  temp = array[i];
	  array[i] = array[p];
	  array[p] = temp;

	  q = link[p];
	  link[p] = link[i];
	  link[i] = p;
	  p = q;
	}

    }


}
