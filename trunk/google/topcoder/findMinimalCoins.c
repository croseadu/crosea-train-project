#include "../../../include/common.h"










int main()
{
  int v[4]= {1,3,4,11};

  int pay = 10;
  int i,j;

  int min[11];
  

  min[0] = 0;
  for (i = 1; i < 11; i++)
    min[i] = 0xFF;

  for (i = 1; i <= 10; i++)
    for (j = 0; j < 4; j++)
      if (v[j] <= i 
	  && 1 + min[i-v[j]] < min[i])
	min[i] = 1 + min[i-v[j]];



  printf("\nMin Coins which sum is 10 are %d coins\n", min[10]);



  return 0;
}
