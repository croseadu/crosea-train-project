#include "../../../include/common.h"

// v {15,40,30,50}
// w {5,4,6,3}
// max W = 10

void findMaxW(int v[], int w[], int size, int maxW);
void findMaxW2(int v[], int w[], int size, int maxW);
int main()
{
  int v[] = {15,40,30,50};
  int w[] = {5,4,6,3};
  int i;
  
  printf("\nv:");
  for (i = 0; i < 4; i++)
    printf("%3d", v[i]);
  printf("\nw:");
  for (i = 0; i < 4; i++)
    printf("%3d", w[i]);
  
  printf("\nMaxW %d\n", 10);

  findMaxW(v, w, sizeof(v)/sizeof(v[0]), 10);
  findMaxW2(v, w, sizeof(v)/sizeof(v[0]), 10);

  return 0;
}


void findMaxW(int v[], int w[], int size, int maxW)
{
  int i, j;
  int c[size+1][maxW+1];
  int k[size+1][maxW+1];

  for (i = 0; i <= maxW; i++)
    c[0][i] = 0;

  for (i = 1; i <= size; i++)
    for (j = 0; j <= maxW; j++)
      {
	if (j >= w[i-1] 
	    && c[i-1][j] < c[i-1][j-w[i-1]]+v[i-1])
	  {
	    c[i][j] = c[i-1][j-w[i-1]]+v[i-1];
	    k[i][j] = 1;
	  }
	else
	  {
	    c[i][j] = c[i-1][j];
	    k[i][j] = 0;
	  }
      }
  
  printf("\nFind Max W Version1: %d, subSet:\n", c[size][maxW]);
  j = maxW;
  
  for (i = size; i > 0; i--)
    {
      if (k[i][j])
	{
	  printf(" v[%d] ", i-1);
	  j -= w[i-1];
	}
    }
  putchar('\n');
  
}
typedef struct 
{
  int p;
  int w;
}PAIR, *LP_PAIR;

void findMaxW2(int v[], int w[], int size, int maxW)
{
  PAIR s[(size+1)*size];
  int e[size+1];
  int i = 0;
  int j, k, m, r;
  PAIR t[maxW];

  s[0].p = 0;
  s[0].w = 0;

  printf("\nFind MaxW Version 2:\n");
  printf("Init S: s[%d]%d %d\n", 0, 0, 0);

  e[0] = 1;
  for (i = 1; i <= size; i++)
    {
      for (r = e[i-1]-1; r>= 0; r--)
	{
	  if (s[r].w+w[i-1] <= maxW)
	    break;
	}

      if (r < 0)
	{
	  e[i] = e[i-1];
	  continue;
	}
      
      printf("New Item: ");
      for (j = 0; j <= r; j++)
	{
	  t[j].p = s[j].p+v[i-1];
	  t[j].w = s[j].w+w[i-1];
	  printf("t[%d]%d %d ", j, t[j].p, t[j].w);
	}
      
      printf("\nMerge and Delete\n");
      
      for (j = 0; j <=r; j++)
	{
	  for (k = e[i-1]-1; k >=0; k--)
	    {
	      if (s[k].w >= t[j].w 
		  && s[k].p <= t[j].p)
		{
		  for (m = k; m < e[i-1]-1; m++)
		    s[m] = s[m+1];
		  e[i-1]--;
		}
	    }
	}
      e[i] = e[i-1];
      for (j = 0; j <=r; j++)
	s[e[i]++] = t[j];

      for (m = 0; m < e[i]; m++)
	printf("s[%d]%d %d ", m, s[m].p, s[m].w);
      putchar('\n');
      
    }

}

