#include "../../../include/common.h"










int main()
{

  int a[6] = {5,3,4,8,6,7};
  int l[6];
  int i, j, max;

  


  for (i = 0; i < 6; i++)
    {
      max = 0;
      j = i;
      while (--j >= 0)
	{
	  if (a[i] > a[j] 
	      && max < l[j])
	    max = l[j];
	}
      l[i] = max+1;
    }

  printf("\nMaxSequence:\n");
  for (i = 0; i < 6; i++)
    printf(" a%d-%d ", i, l[i]);




  putchar('\n');
  return 0;
  
}
