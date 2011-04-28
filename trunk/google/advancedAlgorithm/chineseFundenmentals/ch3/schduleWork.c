#include "../../../include/common.h"




int p[] = {-1,35,30,25,20,15,10,5};
int d[] = {-1,4, 2, 4, 3, 4, 8, 3};

void fastSchedule(int p[], int d[], int j[], int size, int *pNumber);
int main()
{
  int j[8];
  int r, n, q;
  int i;

  j[0] = 0;
  n = 0;
  for (i = 1; i <=7; i++)
    {
      r = n;
      while (d[i] < d[j[r]] && d[j[r]] > r)
	r--;
      if (d[i] >= r+1)
	{
	  q = n;
	  while (q > r)
	    {
	      j[q+1] = j[q];
	      q--;
	    }
	  j[q+1] = i;
	  n++;
	}
    }
  
  printf("\nWork Can be Done:");
  for (i = 1; i <= n; i++)
    printf("\nTime%d Task%d [p=%d,d=%d]",i, j[i], p[j[i]], d[j[i]]);
  putchar('\n');

  
  memset(j, 0, sizeof(j));

  n = 0;
  fastSchedule(p,d,j,7, &n);
  printf("\nUse Fast Schedule:");
  for (i = 1; i <= n; i++)
    printf("\nTime%d Task%d [p=%d,d=%d]",i, j[i], p[j[i]], d[j[i]]);
  putchar('\n');

  return 0;
    


}

int find(int *f, int i)
{
  while(f[i] >= 0)
    i = f[i];
  return i;
}

int unify(int *f, int i1, int i2)
{

  if (i1 == 0)
    {
      f[i1] = f[i1] + f[i2];
      f[i2] = i1; 
    }
  else if (f[i1] <= f[i2])
    {
      f[i1] = f[i1] + f[i2];
      f[i2] = i1;
    }
  else
    {
      f[i2] = f[i1] + f[i2];
      f[i1] = i2;
    }
  return 0;
}

void fastSchedule(int p[], int d[], int j[], int size, int *pNumber)
{
  
  int *father;
  int n;
  int maxd = -1;
  int i;
  int min;
  int f, pf;

  for (i = 1; i <= size; i++)
    if (d[i] > maxd)
      maxd = d[i];
  min = (maxd < size)?maxd:size;
  

  father = (int *)malloc(sizeof(int)*(min+1));
  if (NULL == father)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  memset(father, 0xFF, sizeof(int)*(min+1));

  j[0] = 0;
  n = 1;
  for (i = 1; i <= size; i++)
    {
      min = (d[i] < size)?d[i]:size;

      f = find(father, min);
      if (f != 0)
	{
	  j[n++] = i;
	  pf = find(father, f-1);
	  unify(father, pf, f);
	}

    }



  *pNumber = n-1;

  free(father);
}
